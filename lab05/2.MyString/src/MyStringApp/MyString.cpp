#include "stdafx.h"
#include "MyString.h"


using namespace std;

char CMyString::m_zeroChar = '\0';


namespace
{
	int MyStrCompare(CMyString const &str1, CMyString const &str2)
	{
		int compareResult = memcmp(str1.GetStringData(), str2.GetStringData(), min(str1.GetLength(), str2.GetLength()));
		if (compareResult == 0)
		{
			if (str1.GetLength() < str2.GetLength())
			{
				return -1;
			}
			if (str1.GetLength() > str2.GetLength())
			{
				return 1;
			}
			return 0;
		}
		else
		{
			return compareResult;
		}
	}
}


CMyString::CMyString() :
m_pData(make_unique<char[]>(m_capacity))
{
	*m_pData.get() = '\0';
}


CMyString::CMyString(const char *pString) :
m_pData(make_unique<char[]>(m_capacity))
{
	m_length = strlen(pString);
	SetCapacity(m_length + 1);
	memcpy(m_pData.get(), pString, m_length + 1);
}


CMyString::CMyString(const char *pString, size_t length) :
m_pData(make_unique<char[]>(m_capacity))
{
	if (length == 0)
	{
		*m_pData.get() = '\0';
	}
	else
	{
		m_length = length;
		SetCapacity(m_length + 1);
		memcpy(m_pData.get(), pString, m_length);
		m_pData.get()[m_length] = '\0';
	}
}


CMyString::CMyString(CMyString const &other) :
m_pData(make_unique<char[]>(m_capacity))
{
	m_length = other.m_length;
	SetCapacity(m_length + 1);
	if (other.m_pData)
	{
		memcpy(m_pData.get(), other.m_pData.get(), m_length + 1);
	}
	else
	{
		*m_pData.get() = '\0';
	}	
}


CMyString::CMyString(CMyString &&other) :
m_pData(make_unique<char[]>(m_capacity))
{
	*this = move(other);
}


CMyString::CMyString(std::string const &stlString) :
m_pData(make_unique<char[]>(m_capacity))
{
	*this = CMyString(stlString.c_str(), stlString.length());
}


size_t CMyString::GetLength() const
{
	return m_length;
}


char const *CMyString::GetStringData() const
{
	return (m_pData) ? m_pData.get() : &m_zeroChar;
}


CMyString const CMyString::SubString(size_t start, size_t length) const
{
	if ((!m_pData)
		|| (start >= m_length))
	{
		return CMyString();
	}
	return CMyString((m_pData.get() + start), min(length, m_length - start));
}


void CMyString::Clear()
{
	m_length = 0;
	if (m_pData)
	{
		*m_pData.get() = '\0';
	}
	else
	{
		SetCapacity(1);
	}
}


CMyString &CMyString::operator =(CMyString const &str2)
{
	SetCapacity(str2.m_length + 1);
	m_length = str2.m_length;
	if (str2.m_pData)
	{
		if (m_pData != str2.m_pData)
		{
			memcpy(m_pData.get(), str2.m_pData.get(), m_length + 1);
		}
	}
	else
	{
		*m_pData.get() = '\0';
	}

	return *this;
}


CMyString &CMyString::operator =(CMyString &&other)
{
	if (m_pData != other.m_pData)
	{
		m_length = other.m_length;
		m_capacity = other.m_capacity;
		m_pData = move(other.m_pData);

		other.m_length = 0;
		other.m_capacity = 0;
	}

	return *this;
}


CMyString operator +(CMyString const &str1, CMyString const &str2)
{
	CMyString result;
	result.SetCapacity(str1.GetLength() + str2.GetLength() + 1);
	(result += str1) += str2;
	return result;
}


CMyString &CMyString::operator +=(CMyString const &other)
{
	SetCapacity(m_length + other.m_length + 1);
	memcpy(m_pData.get() + m_length, other.GetStringData(), other.GetLength() + 1);
	m_length += other.m_length;

	return *this;
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
	if (MyStrCompare(str1, str2) < 0)
	{
		return true;
	}
	return false;
}


bool operator >(CMyString const &str1, CMyString const &str2)
{
	return str2 < str1;
}


bool operator <=(CMyString const &str1, CMyString const &str2)
{
	if (MyStrCompare(str1, str2) <= 0)
	{
		return true;
	}
	return false;
}


bool operator >=(CMyString const &str1, CMyString const &str2)
{
	return str2 <= str1;
}


char& CMyString::operator [](size_t index)
{
	if (index >= m_length)
	{
		throw range_error("CMyString out of range");
	}
	return *(m_pData.get() + index);
}


char const &CMyString::operator [](size_t index) const
{
	if (index >= m_length)
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


void CMyString::SetCapacity(size_t requiredSize)
{
	if (requiredSize == 0)
	{
		throw invalid_argument("attempt at setting capacity to 0");
	}
	
	if (!m_pData)
	{
		m_pData = make_unique<char[]>(15);
		m_capacity = 15;
		*m_pData.get() = '\0';
	}	
	size_t newSize = GetNewSize(requiredSize);
	if (m_capacity < newSize)
	{
		auto pNewData = make_unique<char[]>(newSize);
		memcpy(pNewData.get(), m_pData.get(), m_length + 1);
		m_pData = move(pNewData);
		m_capacity = newSize;
	}
}


size_t CMyString::GetNewSize(size_t requiredSize) const
{
	return (requiredSize > m_capacity) ? (max(requiredSize, m_capacity * 2)) : m_capacity;
}


// iterator

CMyString::iterator CMyString::begin()
{
	return (m_pData) ? iterator(this, m_pData.get()) : iterator(this, &m_zeroChar);
}

CMyString::iterator CMyString::end()
{
	return (m_pData) ? iterator(this, &m_pData.get()[m_length]) : iterator(this, &m_zeroChar);
}


CMyString::iterator::iterator(CMyString *pString, char *pChar) :
m_pString(pString),
m_pChar(pChar)
{
}

CMyString::iterator &CMyString::iterator::operator ++()
{
	assert(*this != m_pString->end());
	++m_pChar;
	return *this;
}

CMyString::iterator CMyString::iterator::operator ++(int)
{
	iterator copy(*this);
	++(*this);
	return copy;
}

CMyString::iterator &CMyString::iterator::operator --()
{
	assert(*this != m_pString->begin());
	--m_pChar;
	return *this;
}

CMyString::iterator CMyString::iterator::operator --(int)
{
	iterator copy(*this);
	--(*this);
	return copy;
}

CMyString::iterator CMyString::iterator::operator +(ptrdiff_t offset) const
{
	iterator result(m_pString, m_pChar + offset);
	
	if (offset > 0)
	{
		assert(m_pString->end() - result >= 0);
	}
	else
	{
		assert(result - m_pString->begin() >= 0);
	}
	
	return result;
}

CMyString::iterator operator +(ptrdiff_t offset, CMyString::iterator const &it)
{
	return it + offset;
}

CMyString::iterator CMyString::iterator::operator -(ptrdiff_t offset) const
{
	return *this + (-offset);
}

ptrdiff_t CMyString::iterator::operator -(iterator const &it2) const
{
	assert(m_pString == it2.m_pString);
	return m_pChar - it2.m_pChar;
}

char &CMyString::iterator::operator *() const
{
	assert(*this != this->m_pString->end());
	return *m_pChar;
}

char &CMyString::iterator::operator [](ptrdiff_t index) const
{
	return *(*this + index).m_pChar;
}

bool CMyString::iterator::operator ==(iterator const &it2) const
{
	return ((m_pString == it2.m_pString) && (m_pChar == it2.m_pChar));
}

bool CMyString::iterator::operator !=(iterator const &it2) const
{
	return !(*this == it2);
}


// const_iterator

CMyString::const_iterator CMyString::begin() const
{
	return (m_pData) ? const_iterator(this, m_pData.get()) : const_iterator(this, &m_zeroChar);
}

CMyString::const_iterator CMyString::end() const
{
	return (m_pData) ? const_iterator(this, &m_pData.get()[m_length]) : const_iterator(this, &m_zeroChar);
}


CMyString::const_iterator::const_iterator(CMyString const *pString, char const *pChar) :
m_pString(pString),
m_pChar(pChar)
{
}

CMyString::const_iterator &CMyString::const_iterator::operator ++()
{
	assert(*this != m_pString->end());
	++m_pChar;
	return *this;
}

CMyString::const_iterator CMyString::const_iterator::operator ++(int)
{
	const_iterator copy(*this);
	++(*this);
	return copy;
}

CMyString::const_iterator &CMyString::const_iterator::operator --()
{
	assert(*this != m_pString->begin());
	--m_pChar;
	return *this;
}

CMyString::const_iterator CMyString::const_iterator::operator --(int)
{
	const_iterator copy(*this);
	--(*this);
	return copy;
}

CMyString::const_iterator CMyString::const_iterator::operator +(ptrdiff_t offset) const
{
	const_iterator result(m_pString, m_pChar + offset);

	if (offset > 0)
	{
		assert((m_pString->end() - result) >= 0);
	}
	else
	{
		assert((result - m_pString->begin()) >= 0);
	}

	return result;
}

CMyString::const_iterator operator +(ptrdiff_t offset, CMyString::const_iterator const &it)
{
	return it + offset;
}

CMyString::const_iterator CMyString::const_iterator::operator -(ptrdiff_t offset) const
{
	return *this + (-offset);
}

ptrdiff_t CMyString::const_iterator::operator -(const_iterator const &it2) const
{
	assert(m_pString == it2.m_pString);
	return m_pChar - it2.m_pChar;
}

char const &CMyString::const_iterator::operator *() const
{
	assert(*this != this->m_pString->end());
	return *m_pChar;
}

char const &CMyString::const_iterator::operator [](ptrdiff_t index) const
{
	return *(*this + index).m_pChar;
}

bool CMyString::const_iterator::operator ==(const_iterator const &it2) const
{
	return ((m_pString == it2.m_pString) && (m_pChar == it2.m_pChar));
}

bool CMyString::const_iterator::operator !=(const_iterator const &it2) const
{
	return !(*this == it2);
}


// reverse_iterator

CMyString::reverse_iterator CMyString::rbegin()
{
	return (m_length > 0) ? reverse_iterator(this, &m_pData.get()[m_length - 1]) : rend();
}

CMyString::reverse_iterator CMyString::rend()
{
	return reverse_iterator(this, nullptr);
}


CMyString::reverse_iterator::reverse_iterator(CMyString *pString, char *pChar) :
m_pString(pString),
m_pChar(pChar)
{
}

CMyString::reverse_iterator &CMyString::reverse_iterator::operator ++()
{
	assert(*this != m_pString->rend());
	if (m_pChar == &*m_pString->begin())
	{
		*this = m_pString->rend();
	}
	else
	{
		--m_pChar;
	}
	return *this;
}

CMyString::reverse_iterator CMyString::reverse_iterator::operator ++(int)
{
	reverse_iterator copy(*this);
	++(*this);
	return copy;
}

CMyString::reverse_iterator &CMyString::reverse_iterator::operator --()
{
	assert(*this != m_pString->rbegin());
	if (*this == m_pString->rend())
	{
		m_pChar = &*m_pString->begin();
	}
	else
	{
		++m_pChar;
	}
	return *this;
}

CMyString::reverse_iterator CMyString::reverse_iterator::operator --(int)
{
	reverse_iterator copy(*this);
	--(*this);
	return copy;
}

CMyString::reverse_iterator CMyString::reverse_iterator::operator +(ptrdiff_t offset) const
{
	if (m_pString->GetLength() == 0)
	{
		assert(*this == m_pString->rend());
		assert(offset == 0);
		return *this;
	}

	char *itPos = (*this == m_pString->rend()) ? (&*m_pString->begin() - 1) : m_pChar;
	itPos -= offset;
	assert(itPos >= m_pString->GetStringData() - 1);
	assert(itPos <= m_pString->GetStringData() + m_pString->GetLength() - 1);

	return (itPos != (m_pString->GetStringData() - 1)) ? reverse_iterator(m_pString, itPos) : m_pString->rend();
}

CMyString::reverse_iterator operator +(ptrdiff_t offset, CMyString::reverse_iterator const &it)
{
	return it + offset;
}

CMyString::reverse_iterator CMyString::reverse_iterator::operator -(ptrdiff_t offset) const
{
	return *this + (-offset);
}

ptrdiff_t CMyString::reverse_iterator::operator -(reverse_iterator const &it2) const
{
	assert(m_pString == it2.m_pString);

	if (*this == it2)
	{
		return 0;
	}

	size_t pos1, pos2;
	if (*this == m_pString->rend())
	{
		pos1 = size_t(&*m_pString->begin()) - 1;
	}
	else
	{
		pos1 = size_t(m_pChar);
	}
	if (it2 == it2.m_pString->rend())
	{
		pos2 = size_t(&*m_pString->begin()) - 1;
	}
	else
	{
		pos2 = size_t(it2.m_pChar);
	}

	return pos2 - pos1;
}

char &CMyString::reverse_iterator::operator *() const
{
	assert(*this != this->m_pString->rend());
	return *m_pChar;
}

char &CMyString::reverse_iterator::operator [](ptrdiff_t index) const
{
	return *(*this + index).m_pChar;
}

bool CMyString::reverse_iterator::operator ==(reverse_iterator const &it2) const
{
	return ((m_pString == it2.m_pString) && (m_pChar == it2.m_pChar));
}

bool CMyString::reverse_iterator::operator !=(reverse_iterator const &it2) const
{
	return !(*this == it2);
}


// const_reverse_iterator

CMyString::const_reverse_iterator CMyString::rbegin() const
{
	return (m_length > 0) ? const_reverse_iterator(this, &m_pData.get()[m_length - 1]) : rend();
}

CMyString::const_reverse_iterator CMyString::rend() const
{
	return const_reverse_iterator(this, nullptr);
}


CMyString::const_reverse_iterator::const_reverse_iterator(CMyString const *pString, char const *pChar) :
m_pString(pString),
m_pChar(pChar)
{
}

CMyString::const_reverse_iterator &CMyString::const_reverse_iterator::operator ++()
{
	assert(*this != m_pString->rend());
	if (m_pChar == &*m_pString->begin())
	{
		*this = m_pString->rend();
	}
	else
	{
		--m_pChar;
	}
	return *this;
}

CMyString::const_reverse_iterator CMyString::const_reverse_iterator::operator ++(int)
{
	const_reverse_iterator copy(*this);
	++(*this);
	return copy;
}

CMyString::const_reverse_iterator &CMyString::const_reverse_iterator::operator --()
{
	assert(*this != m_pString->rbegin());
	if (*this == m_pString->rend())
	{
		m_pChar = &*m_pString->begin();
	}
	else
	{
		++m_pChar;
	}
	return *this;
}

CMyString::const_reverse_iterator CMyString::const_reverse_iterator::operator --(int)
{
	const_reverse_iterator copy(*this);
	--(*this);
	return copy;
}

CMyString::const_reverse_iterator CMyString::const_reverse_iterator::operator +(ptrdiff_t offset) const
{
	if (m_pString->GetLength() == 0)
	{
		assert(*this == m_pString->rend());
		assert(offset == 0);
		return *this;
	}

	char const *itPos = (*this == m_pString->rend()) ? (&*m_pString->begin() - 1) : m_pChar;
	itPos -= offset;
	assert(itPos >= m_pString->GetStringData() - 1);
	assert(itPos <= m_pString->GetStringData() + m_pString->GetLength() - 1);

	return (itPos != (m_pString->GetStringData() - 1)) ? const_reverse_iterator(m_pString, itPos) : m_pString->rend();
}

CMyString::const_reverse_iterator operator +(ptrdiff_t offset, CMyString::const_reverse_iterator const &it)
{
	return it + offset;
}

CMyString::const_reverse_iterator CMyString::const_reverse_iterator::operator -(ptrdiff_t offset) const
{
	return *this + (-offset);
}

ptrdiff_t CMyString::const_reverse_iterator::operator -(const_reverse_iterator const &it2) const
{
	assert(m_pString == it2.m_pString);

	if (*this == it2)
	{
		return 0;
	}

	char const *pos1, *pos2;
	if (*this == m_pString->rend())
	{
		pos1 = &*m_pString->begin() - 1;
	}
	else
	{
		pos1 = m_pChar;
	}
	if (it2 == it2.m_pString->rend())
	{
		pos2 = &*m_pString->begin() - 1;
	}
	else
	{
		pos2 = it2.m_pChar;
	}

	return pos2 - pos1;
}

char const &CMyString::const_reverse_iterator::operator *() const
{
	assert(*this != this->m_pString->rend());
	return *m_pChar;
}

char const &CMyString::const_reverse_iterator::operator [](ptrdiff_t index) const
{
	return *(*this + index).m_pChar;
}

bool CMyString::const_reverse_iterator::operator ==(const_reverse_iterator const &it2) const
{
	return ((m_pString == it2.m_pString) && (m_pChar == it2.m_pChar));
}

bool CMyString::const_reverse_iterator::operator !=(const_reverse_iterator const &it2) const
{
	return !(*this == it2);
}
