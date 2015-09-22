#pragma once
#include <stdint.h>
#include <crtdefs.h>
#include <iterator>
class CMyString
{
public:
	class iterator : public std::iterator<std::random_access_iterator_tag, char>
	{
	public:
		iterator(CMyString *pString, char *pChar);
	public:
		iterator &operator ++();
		iterator operator ++(int);
		iterator &operator --();
		iterator operator --(int);
		iterator operator +(ptrdiff_t offset)const;
		iterator operator -(ptrdiff_t offset)const;
		ptrdiff_t operator -(iterator const &it2)const;
		iterator &operator +=(ptrdiff_t offset);
		iterator &operator -=(ptrdiff_t offset);
		iterator &operator =(iterator const &it2);
		char &operator *()const;
		char &operator [](ptrdiff_t index)const;
		bool operator ==(iterator const &it2)const;
		bool operator !=(iterator const &it2)const;
	private:
		CMyString *const m_pString;
		char *m_pChar;
	};
	class const_iterator : public std::iterator<std::random_access_iterator_tag, char const>
	{
	public:
		const_iterator(CMyString const *pString, char const *pChar);
	public:
		const_iterator &operator ++();
		const_iterator operator ++(int);
		const_iterator &operator --();
		const_iterator operator --(int);
		const_iterator operator +(ptrdiff_t offset)const;
		const_iterator operator -(ptrdiff_t offset)const;
		ptrdiff_t operator -(const_iterator const &it2)const;
		const_iterator &operator +=(ptrdiff_t offset);
		const_iterator &operator -=(ptrdiff_t offset);
		const_iterator &operator =(const_iterator const &it2);
		char const &operator *()const;
		char const &operator [](ptrdiff_t index)const;
		bool operator ==(const_iterator const &it2)const;
		bool operator !=(const_iterator const &it2)const;
	private:
		CMyString const *const m_pString;
		char const *m_pChar;
	};
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
public:
	iterator begin();
	const_iterator begin()const;
	reverse_iterator rbegin();
	const_reverse_iterator rbegin()const;
	iterator end();
	const_iterator end()const;
	reverse_iterator rend();
	const_reverse_iterator rend()const;
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

CMyString::iterator operator +(ptrdiff_t offset, CMyString::iterator const &it);
CMyString::const_iterator operator +(ptrdiff_t offset, CMyString::const_iterator const &it);

CMyString operator +(CMyString const &str1, CMyString const &str2);
bool operator ==(CMyString const &str1, CMyString const &str2);
bool operator !=(CMyString const &str1, CMyString const &str2);
bool operator < (CMyString const &str1, CMyString const &str2);
bool operator <=(CMyString const &str1, CMyString const &str2);
bool operator > (CMyString const &str1, CMyString const &str2);
bool operator >=(CMyString const &str1, CMyString const &str2);
std::ostream &operator <<(std::ostream &output, CMyString const &str);
std::istream &operator >>(std::istream &input, CMyString &str);
