#pragma once
class CCliMenu
{
protected:
	CCliMenu() {};
	virtual ~CCliMenu() {};
protected:
	void MarkChangesOccurrence();
	bool HaveChangesBeenHappened();
private:
	bool m_dataChanged = false;
};

