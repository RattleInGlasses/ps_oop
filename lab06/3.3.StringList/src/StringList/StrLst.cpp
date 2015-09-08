#include "stdafx.h"
#include "StrLst.h"

using namespace std;

#define MakeElementPointer std::make_shared<StrLstElem>


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


// CStrLst functions

CStrLst::CStrLst() :
	m_pEnd(MakeElementPointer()),
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


CStrLst::iterator CStrLst::begin() const
{
	return iterator(m_pBegin);
}


CStrLst::iterator CStrLst::end() const
{
	return iterator(m_pEnd);
}


void CStrLst::Insert(std::string const &data, iterator &pos)
{
	ElementPointer pNewEl = MakeElementPointer();
	pNewEl->data = data;

	pNewEl->prev = pos.m_pData->prev;
	pNewEl->next = pos.m_pData;
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


void CStrLst::Delete(CStrLst::iterator &pos)
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

		pos = pos.m_pData->next;
	}
}

#undef MakeElementPointer
