#pragma once
class CRectangle
{
public:
	CRectangle(int x, int y, int width, int height);
	~CRectangle();

	void SetWidth(unsigned int width);
	void SetWidth(int width);
	void SetHeight(unsigned int height);
	void SetHeight(int height);
	void SetLeft(int left);
	void SetRight(int right);
	void SetTop(int top);
	void SetBottom(int bottom);

	unsigned int GetWidth() const;
	unsigned int GetHeight() const;	
	int GetLeft() const;
	int GetRight() const;
	int GetTop() const;
	int GetBottom() const;

	boost::optional<unsigned int> GetArea() const;
	boost::optional<unsigned int> GetPerimeter() const;

	void Move(int dx, int dy);
	void Scale(int sx, int sy);
	bool Intersect(CRectangle const &other);

private:
	struct LineSegment
	{
		int begining;
		int end;
	};
	
	unsigned int m_width;
	unsigned int m_height;
	int m_x;
	int m_y;

	boost::optional<LineSegment> CRectangle::DimensionSegmentIntersection(LineSegment segment1, LineSegment segment2);
};

