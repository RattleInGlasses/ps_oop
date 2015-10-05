#include "stdafx.h"
#include "CliMenu.h"


void CCliMenu::MarkChangesOccurrence()
{
	if (!m_dataChanged)
	{
		m_dataChanged = true;
	}
}

bool CCliMenu::HaveChangesBeenHappened()
{
	return m_dataChanged;
}
