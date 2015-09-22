#include "stdafx.h"
#include "Body.h"


bool CBody::HasParent() const
{
	return m_pParent != nullptr;
}


CBody *CBody::GetParent() const
{
	return m_pParent;
}


bool CBody::SetParent(CBody *pParent)
{
	if (!HasParent())
	{
		m_pParent = pParent;
		return true;
	}
	return false;
}
