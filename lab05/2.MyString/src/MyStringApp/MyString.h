#pragma once
class CMyString
{
public:
	CMyString();
	CMyString(const char *pString);
	CMyString(const char *pString, size_t length);
	CMyString(CMyString const &other);
	CMyString(CMyString &&other);
	CMyString(std::string const &stlString);
	//~CMyString();

	size_t GetLength()const;
	const char* GetStringData()const;
	CMyString const SubString(unsigned start, unsigned length = UINT_MAX)const;
	void Clear();

	void operator =(CMyString const &other);
	void operator =(CMyString &&other);
	void operator +=(CMyString const &other);
	char& operator [](size_t index);
	char operator [](size_t index) const;
private:
	void SetSize(size_t requiredSize);
	size_t GetNewSize(size_t requiredSize);
private:
	size_t m_dataSize = 0;
	size_t m_allocatedSize = 15;
	std::unique_ptr<char[]> m_pData;
};

CMyString operator +(CMyString str1, CMyString const &str2);
bool operator ==(CMyString const &str1, CMyString const &str2);
bool operator !=(CMyString const &str1, CMyString const &str2);
bool operator < (CMyString const &str1, CMyString const &str2);
bool operator <=(CMyString const &str1, CMyString const &str2);
bool operator > (CMyString const &str1, CMyString const &str2);
bool operator >=(CMyString const &str1, CMyString const &str2);
std::ostream &operator <<(std::ostream &output, CMyString const &str);
std::istream &operator >>(std::istream &input, CMyString &str);
