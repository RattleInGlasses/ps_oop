#pragma once
#include "stdafx.h"
#include <string>
#include <memory>
class CBody
{
public:
	virtual ~CBody() {};
	virtual double GetDensity()const = 0;
	virtual double GetMass()const = 0;
	virtual double GetVolume()const = 0;
	virtual std::string ToString()const = 0;

	bool HasParent()const { return m_pParent != nullptr; }
	CBody *GetParent()const { return m_pParent; }
	bool SetParent(CBody *pParent)
	{
		if (!HasParent())
		{
			m_pParent = pParent;
			return true;
		}
		return false;
	}
private:
	 CBody *m_pParent = nullptr;
};
