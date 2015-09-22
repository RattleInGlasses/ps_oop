#include "stdafx.h"
#include "StrLst.h"

using namespace std;


// iterator functions

CStrLst::iterator::iterator(ElementPointer const &pEl) :
m_pData(pEl)
{
};


bool CStrLst::iterator::operator ==(CStrLst::iterator const &it) const
{
	return m_pData == it.m_pData;
}


bool CStrLst::iterator::operator !=(iterator const & it) const
{
	return !(*this == it);
}


CStrLst::iterator& CStrLst::iterator::operator ++()
{
	assert(m_pData->next);
	if (m_pData)
	{
		m_pData = m_pData->next;
	}
	return *this;
}


CStrLst::iterator const CStrLst::iterator::operator ++(int)
{
	iterator copy = *this;
	++(*this);
	return copy;
}


CStrLst::iterator& CStrLst::iterator::operator --()
{
	assert(m_pData->prev);
	if (m_pData)
	{
		m_pData = m_pData->prev;
	}
	return *this;
}


CStrLst::iterator const CStrLst::iterator::operator --(int)
{
	iterator copy = *this;
	--(*this);
	return copy;
}


string& CStrLst::iterator::operator *()
{
	return m_pData->data;
}


// const_iterator functions

CStrLst::const_iterator::const_iterator(ConstElementPointer const &pEl) :
m_pData(pEl)
{
};


bool CStrLst::const_iterator::operator ==(CStrLst::const_iterator const &it) const
{
	return m_pData == it.m_pData;
}


bool CStrLst::const_iterator::operator !=(const_iterator const & it) const
{
	return !(*this == it);
}


CStrLst::const_iterator& CStrLst::const_iterator::operator ++()
{
	assert(m_pData->next);
	if (m_pData)
	{
		m_pData = m_pData->next;
	}
	return *this;
}


CStrLst::const_iterator const CStrLst::const_iterator::operator ++(int)
{
	const_iterator copy = *this;
	++(*this);
	return copy;
}


CStrLst::const_iterator& CStrLst::const_iterator::operator --()
{
	assert(m_pData->prev);
	if (m_pData)
	{
		m_pData = m_pData->prev;
	}
	return *this;
}


CStrLst::const_iterator const CStrLst::const_iterator::operator --(int)
{
	const_iterator copy = *this;
	--(*this);
	return copy;
}


string const& CStrLst::const_iterator::operator *()
{
	return m_pData->data;
}



// CStrLst functions

CStrLst::CStrLst() :
	m_pEnd(MakeNewElement()),
	m_pBegin(m_pEnd)
{
}


CStrLst::~CStrLst()
{
	for (auto it = begin(); it != end();)
	{
		auto *pEl = (it++).m_pData.get();
		pEl->next.reset();
		pEl->prev.reset();
	}
}


CStrLst::iterator CStrLst::begin()
{
	return iterator(m_pBegin);
}


CStrLst::const_iterator CStrLst::begin() const
{
	return const_iterator(m_pBegin);
}


CStrLst::reverse_iterator CStrLst::rbegin()
{
	return reverse_iterator(end());
}


CStrLst::const_reverse_iterator CStrLst::rbegin() const
{
	return const_reverse_iterator(end());
}


CStrLst::iterator CStrLst::end()
{
	return iterator(m_pEnd);
}


CStrLst::const_iterator CStrLst::end() const
{
	return const_iterator(m_pEnd);
}


CStrLst::reverse_iterator CStrLst::rend()
{
	return reverse_iterator(begin());
}


CStrLst::const_reverse_iterator CStrLst::rend() const
{
	return const_reverse_iterator(begin());
}



void CStrLst::Insert(std::string const &data, iterator const &pos)
{
	ElementPointer pNewEl = MakeNewElement(data, pos.m_pData, pos.m_pData->prev);
	pos.m_pData->prev = pNewEl;

	if (pos == begin())
	{
		m_pBegin = pNewEl;
	}
	else
	{
		pNewEl->prev->next = move(pNewEl);
	}
}


void CStrLst::Delete(CStrLst::iterator const &pos)
{
	if (pos != m_pEnd)
	{
		pos.m_pData->next->prev = pos.m_pData->prev;
		if (pos == m_pBegin)
		{
			m_pBegin = pos.m_pData->next;
		}
		else
		{
			pos.m_pData->prev->next = pos.m_pData->next;
		}

		//pos = pos.m_pData->next;
	}
}


CStrLst::ElementPointer CStrLst::MakeNewElement()
{
	return make_shared<StrLstElem>();
}


CStrLst::ElementPointer CStrLst::MakeNewElement(string const &initData, CStrLst::ElementPointer const &initNext, CStrLst::ElementPointer const &initPrev)
{
	return make_shared<StrLstElem>(initData, initNext, initPrev);
}


// StrLstElem functions

CStrLst::StrLstElem::StrLstElem(string const &initData, ElementPointer const &initNext, ElementPointer const &initPrev) :
data(initData),
next(initNext),
prev(initPrev)
{
}

