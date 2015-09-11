#pragma once
#include <limits>
class CMyString
{
public:
	class iterator
	{
	public:
		iterator(CMyString const *pString, char *pChar);
	public:
		iterator &operator ++();
		iterator operator ++(int);
		iterator &operator --();
		iterator operator --(int);
		iterator operator +(int offset) const;
		iterator operator -(int offset) const;
		int operator -(iterator const &it2) const;
		char const &operator *() const;
		char &operator *();
		char const& operator [](int index) const;
		char &operator [](int index);
		bool operator ==(iterator const &it2) const;
		bool operator !=(iterator const &it2) const;
	private:
		CMyString const *m_pString;
		char *m_pChar;
	};
	iterator begin();
	iterator const begin() const;
	iterator end();
	iterator const end() const;
public:
	CMyString();
	CMyString(const char *pString);
	CMyString(const char *pString, size_t length);
	CMyString(CMyString const &other);
	CMyString(CMyString &&other);
	CMyString(std::string const &stlString);

	size_t GetLength()const;
	const char* GetStringData()const;
	CMyString const SubString(size_t start, size_t length = SIZE_MAX)const;
	void Clear();

	CMyString &operator =(CMyString const &other);
	CMyString &operator =(CMyString &&other);
	CMyString &operator +=(CMyString const &other);
	char& operator [](size_t index);
	char const &operator [](size_t index)const;

	void SetCapacity(size_t requiredSize);
private:
	size_t GetNewSize(size_t requiredSize)const;
private:
	size_t m_length = 0;
	size_t m_capacity = 15;
	std::unique_ptr<char[]> m_pData;
	static char m_zeroChar;
};

CMyString::iterator operator +(int offset, CMyString::iterator const &it);

CMyString operator +(CMyString const &str1, CMyString const &str2);
bool operator ==(CMyString const &str1, CMyString const &str2);
bool operator !=(CMyString const &str1, CMyString const &str2);
bool operator < (CMyString const &str1, CMyString const &str2);
bool operator <=(CMyString const &str1, CMyString const &str2);
bool operator > (CMyString const &str1, CMyString const &str2);
bool operator >=(CMyString const &str1, CMyString const &str2);
std::ostream &operator <<(std::ostream &output, CMyString const &str);
std::istream &operator >>(std::istream &input, CMyString &str);
