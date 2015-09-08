#include "stdafx.h"
#include "MyString.h"


using namespace std;


CMyString::CMyString() :
m_pData(make_unique<char[]>(m_allocatedSize))
{
	*m_pData.get() = '\0';
}


CMyString::CMyString(const char *pString) :
m_pData(make_unique<char[]>(m_allocatedSize))
{
	m_dataSize = strlen(pString);
	SetSize(m_dataSize + 1);
	memcpy(m_pData.get(), pString, m_dataSize + 1);
}


CMyString::CMyString(const char *pString, size_t length) :
m_pData(make_unique<char[]>(m_allocatedSize))
{
	if (length == 0)
	{
		*m_pData.get() = '\0';
	}
	else
	{
		m_dataSize = length;
		SetSize(m_dataSize + 1);
		memcpy(m_pData.get(), pString, m_dataSize);
		m_pData.get()[m_dataSize] = '\0';
	}
}


CMyString::CMyString(CMyString const &other) :
m_pData(make_unique<char[]>(m_allocatedSize))
{
	m_dataSize = other.m_dataSize;
	SetSize(m_dataSize + 1);
	memcpy(m_pData.get(), other.m_pData.get(), m_dataSize + 1);
}


CMyString::CMyString(CMyString &&other) :
m_pData(make_unique<char[]>(m_allocatedSize))
{
	*this = move(other);
}


CMyString::CMyString(std::string const &stlString) :
m_pData(make_unique<char[]>(m_allocatedSize))
{
	*this = stlString.c_str();
}


size_t CMyString::GetLength() const
{
	return m_dataSize;
}


char const *CMyString::GetStringData() const
{
	return m_pData.get();
}


CMyString const CMyString::SubString(unsigned start, unsigned length) const
{
	if (start > m_dataSize)
	{
		return CMyString();
	}
	return CMyString((m_pData.get() + start), min(length, m_dataSize - start));
}


void CMyString::Clear()
{
	m_dataSize = 0;
	*m_pData.get() = '\0';
}


void CMyString::operator =(CMyString const &str2)
{
	m_dataSize = str2.m_dataSize;
	SetSize(m_dataSize + 1);
	memcpy(m_pData.get(), str2.m_pData.get(), m_dataSize + 1);
}


void CMyString::operator =(CMyString &&other)
{
	m_dataSize = other.m_dataSize;
	m_allocatedSize = other.m_allocatedSize;
	m_pData = move(other.m_pData);
}


CMyString operator +(CMyString str1, CMyString const &str2)
{
	str1 += str2;
	return str1;
}


void CMyString::operator +=(CMyString const &other)
{
	SetSize(m_dataSize + other.m_dataSize);
	memcpy(m_pData.get() + m_dataSize, other.GetStringData(), other.GetLength() + 1);
	m_dataSize += other.m_dataSize;
}


bool operator ==(CMyString const &str1, CMyString const &str2)
{
	if (str1.GetLength() != str2.GetLength())
	{
		return false;
	}

	for (size_t i = 0; i < str1.GetLength(); ++i)
	{
		if (str1[i] != str2[i])
		{
			return false;
		}
	}

	return true;
}


bool operator !=(CMyString const &str1, CMyString const &str2)
{
	return !(str1 == str2);
}


bool operator <(CMyString const &str1, CMyString const &str2)
{
	int compareResults = memcmp(str1.GetStringData(), str2.GetStringData(), min(str1.GetLength(), str2.GetLength()));
	if (compareResults == 0)
	{
		return str1.GetLength() < str2.GetLength();
	}
	if (compareResults < 0)
	{
		return true;
	}
	if (compareResults > 0)
	{
		return false;
	}
}


bool operator >(CMyString const &str1, CMyString const &str2)
{
	return str2 < str1;
}


bool operator <=(CMyString const &str1, CMyString const &str2)
{
	return ((str1 < str2) || (str1 == str2));
}


bool operator >=(CMyString const &str1, CMyString const &str2)
{
	return ((str1 > str2) || (str1 == str2));
}


char& CMyString::operator [](size_t index)
{
	if (index > m_dataSize)
	{
		throw range_error("CMyString out of range");
	}
	return *(m_pData.get() + index);
}


char CMyString::operator [](size_t index) const
{
	if (index > m_dataSize)
	{
		throw range_error("CMyString out of range");
	}
	return *(m_pData.get() + index);
}


ostream &operator <<(ostream &output, CMyString const &str)
{
	for (size_t i = 0; i < str.GetLength(); ++i)
	{
		output << str[i];
	}
	return output;
}


std::istream &operator >>(std::istream &input, CMyString &str)
{
	string s;
	input >> s;
	str = s;

	return input;
}


void CMyString::SetSize(size_t requiredSize)
{
	size_t newSize = GetNewSize(requiredSize);
	if (m_allocatedSize < newSize)
	{
		m_allocatedSize = GetNewSize(requiredSize);
		auto pNewData = make_unique<char[]>(m_allocatedSize);
		memcpy(pNewData.get(), m_pData.get(), m_dataSize + 1);
		m_pData = move(pNewData);
	}
}


size_t CMyString::GetNewSize(size_t requiredSize)
{
	size_t newSize = m_allocatedSize;
	while (requiredSize > newSize)
	{
		newSize *= 2;
	}
	return newSize;
}
