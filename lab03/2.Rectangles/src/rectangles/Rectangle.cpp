#include "stdafx.h"
#include <climits>
#include <algorithm>
#include "Rectangle.h"


// public methods


CRectangle::CRectangle(int x, int y, int width, int height)
{
	m_x = x;
	m_y = y;
	m_width = (width < 0) ? 0 : width;
	m_height = (height < 0) ? 0 : height;
}


CRectangle::~CRectangle()
{
}


void CRectangle::SetWidth(unsigned int width)
{
	m_width = (width > static_cast<unsigned int>(INT_MAX - m_x)) ? (INT_MAX - m_x) : width;
}


void CRectangle::SetWidth(int width)
{
	width = (width < 0) ? 0 : width;
	SetWidth(static_cast<unsigned int>(width));
}


unsigned int CRectangle::GetWidth() const
{
	return m_width;
}


void CRectangle::SetHeight(unsigned int height)
{
	m_height = (height >  static_cast<unsigned int>(INT_MAX - m_y)) ? (INT_MAX - m_y) : height;
}


void CRectangle::SetHeight(int height)
{
	height = (height < 0) ? 0 : height;
	SetHeight(static_cast<unsigned int>(height));
}


unsigned int CRectangle::GetHeight() const
{
	return m_height;
}


void CRectangle::SetLeft(int left)
{
	left = (left > GetRight()) ? GetRight() : left;
	m_width -= left - m_x;
	m_x = left;
}


int CRectangle::GetLeft() const
{
	return m_x;
}


void CRectangle::SetRight(int right)
{
	right = (right < m_x) ? m_x : right;
	m_width = right - m_x;
}


int CRectangle::GetRight() const
{
	return m_x + m_width;
}


void CRectangle::SetTop(int top)
{
	top = (top > GetBottom()) ? GetBottom() : top;
	m_height -= top - m_y;
	m_y = top;
}


int CRectangle::GetTop() const
{
	return m_y;
}


void CRectangle::SetBottom(int bottom)
{
	bottom = (bottom < m_y) ? m_y : bottom;
	m_height = bottom - m_y;
}


int CRectangle::GetBottom() const
{
	return m_y + m_height;
}


boost::optional<unsigned int> CRectangle::GetArea() const
{
	
	if ((m_width != 0) && (m_height != 0) && ((m_width * m_height / m_width) != m_height))
	{
		return boost::none;
	}
	
	return m_width * m_height;
}


boost::optional<unsigned int> CRectangle::GetPerimeter() const
{
	if (((m_width + m_height) < m_width)          // add overflow
		|| (m_width + m_height) > (UINT_MAX / 2)) // multiplication overflow
	{
		return boost::none;
	}
	
	return 2 * (m_width + m_height);
}


void CRectangle::Move(int dx, int dy)
{
	if (dx > 0)
	{
		if ((GetRight() + dx) < GetRight())
		{
			dx = INT_MAX - GetRight();
		}
	}
	else if (dx < 0)
	{
		if ((m_x + dx) > m_x)
		{
			dx = INT_MIN - m_x;
		}
	}

	if (dy > 0)
	{
		if ((GetBottom() + dy) < GetBottom())
		{
			dy = INT_MAX - GetBottom();
		}
	}
	else if (dy < 0)
	{
		if ((m_y + dy) > m_y)
		{
			dy = INT_MIN - m_y;
		}
	}

	m_x += dx;
	m_y += dy;
}

void CRectangle::Scale(int sx, int sy)
{
	if ((sx >= 0) && (sy >= 0))
	{
		if ((sx > 0) && ((m_width * sx / sx) != m_width)
		|| ((m_width * sx) > (static_cast<unsigned int>(INT_MAX) - m_x)))
		{
			SetWidth(UINT_MAX);
		}
		else if ((sy > 0) && ((m_height * sy / sy) != m_height)
		|| ((m_height * sy) > (static_cast<unsigned int>(INT_MAX) - m_y)))
		{
			SetHeight(UINT_MAX);
		}
		else
		{
			m_width *= sx;
			m_height *= sy;
		}
	}
}

bool CRectangle::Intersect(CRectangle const &other)
{
	boost::optional<LineSegment> OXIntersection, OYIntersection;
	if ((OXIntersection = DimensionSegmentIntersection({ GetLeft(), GetRight() }, { other.GetLeft(), other.GetRight() }))
	&& (OYIntersection = DimensionSegmentIntersection({ GetTop(), GetBottom() }, { other.GetTop(), other.GetBottom() })))
	{
		m_x = OXIntersection->begining;
		m_y = OYIntersection->begining;
		SetRight(OXIntersection->end);
		SetBottom(OYIntersection->end);
		return true;
	}
	else
	{
		SetWidth(0);
		SetHeight(0);
		return false;
	}
}


// private methods


// returns intersection between two segments
boost::optional<CRectangle::LineSegment> CRectangle::DimensionSegmentIntersection(LineSegment segment1, LineSegment segment2)
{
	if (segment1.begining > segment2.begining)
	{
		std::swap(segment1, segment2);
	}

	if (segment2.begining < segment1.end)
	{
		LineSegment intersection = { segment2.begining, std::min(segment1.end, segment2.end) };
		return intersection;
	}
	return boost::none;
}