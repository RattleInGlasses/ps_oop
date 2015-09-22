#pragma once
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

	bool HasParent()const;
	CBody *GetParent()const;
	bool SetParent(CBody *pParent);
private:
	 CBody *m_pParent = nullptr;
};
