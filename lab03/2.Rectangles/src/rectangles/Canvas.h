#pragma once

#include <vector>

class CCanvas
{
public:
	CCanvas(unsigned width, unsigned height);
	~CCanvas();
	unsigned GetWidth()const;
	unsigned GetHeight()const;
	void Clear(char code = ' ');
	void SetPixel(int x, int y, char code);
	char GetPixel(int x, int y)const;
	void Write(std::ostream & ostream)const;
private:
	bool PositionIsOutOfCanvas(int x, int y)const;
	bool CharCodeIsExceptable(char code)const;

	std::vector<std::vector<char>> m_data;
};

