#include "stdafx.h"
#include <algorithm>
#include "Canvas.h"


// public functions


CCanvas::CCanvas(unsigned width, unsigned height)
{
	if ((width > 0) && (height > 0))
	{
		m_data.assign(height, std::vector<char>(width));
		Clear();
	}
}


CCanvas::~CCanvas()
{
}


unsigned CCanvas::GetWidth()const
{
	return (m_data.size() > 0) ? m_data[0].size() : 0;
}


unsigned CCanvas::GetHeight()const
{
	return m_data.size();
}


void CCanvas::Clear(char code)
{
	if (CharCodeIsExceptable(code))
	{
		std::transform(m_data.begin(), m_data.end(), m_data.begin(), [code](std::vector<char> row)
		{
			std::fill(row.begin(), row.end(), code);
			return row;
		});
	}
}


void CCanvas::SetPixel(int x, int y, char code)
{
	if ((!PositionIsOutOfCanvas(x, y)) && CharCodeIsExceptable(code))
	{
		m_data.at(y).at(x) = code;
	}
}


char CCanvas::GetPixel(int x, int y)const
{
	if (!PositionIsOutOfCanvas(x, y))
	{
		return m_data.at(y).at(x);
	}
	return ' ';
}


void CCanvas::Write(std::ostream &ostream)const
{
	if (m_data.size() > 0)
	{
		std::for_each(m_data.begin(), m_data.end(), [&ostream](std::vector<char> row)
		{
			std::for_each(row.begin(), row.end(), [&ostream](char ch){ ostream << ch; });
			ostream << std::endl;
		});
	}
}


// private functions 


bool CCanvas::PositionIsOutOfCanvas(int x, int y)const
{
	return ((m_data.size() == 0) || (x < 0) || (y < 0) || (static_cast<unsigned>(y) >= m_data.size()) || (static_cast<unsigned>(x) >= m_data[0].size()));
}


bool CCanvas::CharCodeIsExceptable(char code)const
{
	return (code >= ' ');
}
