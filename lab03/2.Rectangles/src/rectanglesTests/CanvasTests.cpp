#include "stdafx.h"
#include "..\rectangles\Canvas.h"
#include <chrono>
#include <iostream>

BOOST_AUTO_TEST_SUITE(CanvasTests)

	void CheckEqualEveryCanvasPoint(CCanvas const &canvas, char ch)
	{
		for (unsigned y = 0; y < canvas.GetHeight(); ++y)
		{
			for (unsigned x = 0; x < canvas.GetWidth(); ++x)
			{
				BOOST_CHECK_EQUAL(canvas.GetPixel(x, y), ch);
			}
		}
	}

	BOOST_AUTO_TEST_CASE(InitialStateSizeMatchesGivenArguments)
	{
		CCanvas canvas(10, 100);
		BOOST_CHECK_EQUAL(canvas.GetHeight(), 100);
		BOOST_CHECK_EQUAL(canvas.GetWidth(), 10);
	}

	BOOST_AUTO_TEST_CASE(InitialStateIsClearedBySpaces)
	{
		CCanvas canvas(10, 100);
		CheckEqualEveryCanvasPoint(canvas, ' ');
	}

	BOOST_AUTO_TEST_CASE(ZeroSizeCanvasIsNormallyWorking)
	{
		CCanvas canvas(0, 0);
		
		BOOST_CHECK_EQUAL(canvas.GetHeight(), 0);
		BOOST_CHECK_EQUAL(canvas.GetWidth(), 0);

		canvas.Clear();
		canvas.SetPixel(0, 0, 'a');
		BOOST_CHECK_EQUAL(canvas.GetPixel(0, 0), ' ');
	}

	BOOST_AUTO_TEST_CASE(GetWidthAlwaysReturnsRealSize)
	{
		CCanvas canvas(1, 1);
		BOOST_CHECK_EQUAL(canvas.GetWidth(), 1);

		CCanvas canvas2(100, 1);
		BOOST_CHECK_EQUAL(canvas2.GetWidth(), 100);

		CCanvas canvas3(0, 1);
		BOOST_CHECK_EQUAL(canvas3.GetWidth(), 0);

		CCanvas canvas4(150, 0);
		BOOST_CHECK_EQUAL(canvas4.GetWidth(), 0);
	}

	BOOST_AUTO_TEST_CASE(GetHeightAlwaysReturnsRealSize)
	{
		CCanvas canvas(1, 1);
		BOOST_CHECK_EQUAL(canvas.GetHeight(), 1);

		CCanvas canvas2(1, 100);
		BOOST_CHECK_EQUAL(canvas2.GetHeight(), 100);

		CCanvas canvas3(0, 1);
		BOOST_CHECK_EQUAL(canvas3.GetHeight(), 0);

		CCanvas canvas4(150, 0);
		BOOST_CHECK_EQUAL(canvas4.GetHeight(), 0);
	}

	BOOST_AUTO_TEST_CASE(ClearChangesEveryChar)
	{
		CCanvas canvas(10, 10);
		canvas.Clear('c');
		CheckEqualEveryCanvasPoint(canvas, 'c');
	}

	BOOST_AUTO_TEST_CASE(ClearDoesntWorkWithCodesLessSpace)
	{
		CCanvas canvas(10, 10);
		canvas.Clear(' ' - 1);
		CheckEqualEveryCanvasPoint(canvas, ' ');

		canvas.Clear('c');
		canvas.Clear(' ');
		CheckEqualEveryCanvasPoint(canvas, ' ');
	}

	BOOST_AUTO_TEST_CASE(SetPixelSetsThePixel)
	{
		CCanvas canvas(10, 10);
		canvas.SetPixel(3, 3, 'n');
		BOOST_CHECK_EQUAL(canvas.GetPixel(3, 3), 'n');
	}

	void CheckNotSetPixel(CCanvas &canvas, int x, int y)
	{
		canvas.SetPixel(x, y, 'd');
		BOOST_CHECK_EQUAL(canvas.GetPixel(x, y), ' ');
	}

	BOOST_AUTO_TEST_CASE(SetPixelDoesntChangeAThingOutOfBounds)
	{
		CCanvas canvas(10, 10);
		CheckNotSetPixel(canvas, -1, 0);
		CheckNotSetPixel(canvas, 0, -1);
		CheckNotSetPixel(canvas, -1, -1);
		CheckNotSetPixel(canvas, 10, 0);
		CheckNotSetPixel(canvas, 0, 10);
		CheckNotSetPixel(canvas, 10, 10);
		CheckEqualEveryCanvasPoint(canvas, ' ');

		CCanvas canvas2(0, 0);
		canvas2.SetPixel(0, 0, 'n');
		BOOST_CHECK_EQUAL(canvas2.GetPixel(0, 0), ' ');
	}

	BOOST_AUTO_TEST_CASE(SetPixelDoesntWorkWithCodesLess32)
	{
		CCanvas canvas(10, 10);
		canvas.SetPixel(3, 3, ' ' - 1);
		BOOST_CHECK_EQUAL(canvas.GetPixel(3, 3), ' ');

		canvas.SetPixel(3, 3, 'n');
		canvas.SetPixel(3, 3, ' ');
		BOOST_CHECK_EQUAL(canvas.GetPixel(3, 3), ' ');
	}

	BOOST_AUTO_TEST_CASE(GetPixelGetsThePixel)
	{
		CCanvas canvas(10, 10);
		canvas.SetPixel(5, 5, 'd');
		BOOST_CHECK_EQUAL(canvas.GetPixel(5, 5), 'd');

		canvas.SetPixel(9, 0, 'd');
		BOOST_CHECK_EQUAL(canvas.GetPixel(9, 0), 'd');
	}

	BOOST_AUTO_TEST_CASE(GetPixelReturnsSpaceForOutOfBounds)
	{
		CCanvas canvas(10, 10);
		canvas.Clear('c');
		BOOST_REQUIRE_EQUAL(canvas.GetPixel(0, 0), 'c');
		BOOST_CHECK_EQUAL(canvas.GetPixel(10, 0), ' ');
		BOOST_CHECK_EQUAL(canvas.GetPixel(0, 10), ' ');
		BOOST_CHECK_EQUAL(canvas.GetPixel(10, 10), ' ');
		BOOST_CHECK_EQUAL(canvas.GetPixel(-1, 0), ' ');
		BOOST_CHECK_EQUAL(canvas.GetPixel(0, -1), ' ');
		BOOST_CHECK_EQUAL(canvas.GetPixel(-1, -1), ' ');
		
		CCanvas canvas2(0, 0);
		BOOST_CHECK_EQUAL(canvas2.GetPixel(0, 0), ' ');
	}

BOOST_AUTO_TEST_SUITE_END()
