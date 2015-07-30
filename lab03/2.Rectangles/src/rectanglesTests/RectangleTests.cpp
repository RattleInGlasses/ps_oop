#include "stdafx.h";
#include "..\rectangles\Rectangle.h"

BOOST_AUTO_TEST_SUITE(RectangleTests)
	
	// init state

	BOOST_AUTO_TEST_CASE(InitialState)
	{
		CRectangle rect(0, 0, 0, 0);
		BOOST_CHECK_EQUAL(rect.GetLeft(),       0);
		BOOST_CHECK_EQUAL(rect.GetRight(),      0);
		BOOST_CHECK_EQUAL(rect.GetTop(),        0);
		BOOST_CHECK_EQUAL(rect.GetBottom(),     0);
		BOOST_CHECK_EQUAL(rect.GetHeight(),     0);
		BOOST_CHECK_EQUAL(rect.GetWidth(),      0);
		BOOST_CHECK_EQUAL(*rect.GetArea(),      0);
		BOOST_CHECK_EQUAL(*rect.GetPerimeter(), 0);

		CRectangle rect2(10, 25, 100, 200);
		BOOST_CHECK_EQUAL(rect2.GetLeft(),        10);
		BOOST_CHECK_EQUAL(rect2.GetRight(),      110);
		BOOST_CHECK_EQUAL(rect2.GetTop(),         25);
		BOOST_CHECK_EQUAL(rect2.GetBottom(),     225);
		BOOST_CHECK_EQUAL(rect2.GetHeight(),     200);
		BOOST_CHECK_EQUAL(rect2.GetWidth(),      100);
		BOOST_CHECK_EQUAL(*rect2.GetArea(),    20000);
		BOOST_CHECK_EQUAL(*rect2.GetPerimeter(), 600);

		CRectangle rect3(10, 25, -100, -200);
		BOOST_CHECK_EQUAL(rect3.GetLeft(),      10);
		BOOST_CHECK_EQUAL(rect3.GetRight(),     10);
		BOOST_CHECK_EQUAL(rect3.GetTop(),       25);
		BOOST_CHECK_EQUAL(rect3.GetBottom(),    25);
		BOOST_CHECK_EQUAL(rect3.GetHeight(),     0);
		BOOST_CHECK_EQUAL(rect3.GetWidth(),      0);
		BOOST_CHECK_EQUAL(*rect3.GetArea(),      0);
		BOOST_CHECK_EQUAL(*rect3.GetPerimeter(), 0);
	}

	// properties
	//// properties setting

	BOOST_AUTO_TEST_CASE(WidthCanBeSet)
	{
		CRectangle rect(0, 0, 0, 0);
		rect.SetWidth(20);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 20);
		rect.SetWidth(100);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 100);
		rect.SetWidth(0);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 0);
	}

	BOOST_AUTO_TEST_CASE(HeightCanBeSet)
	{
		CRectangle rect(0, 0, 0, 0);
		rect.SetHeight(20);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 20);
		rect.SetHeight(100);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 100);
		rect.SetHeight(0);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 0);
	}

	BOOST_AUTO_TEST_CASE(LeftCanBeSet)
	{
		CRectangle rect(0, 0, 100, 0);
		rect.SetLeft(20);
		BOOST_CHECK_EQUAL(rect.GetLeft(), 20);
		rect.SetLeft(-100);
		BOOST_CHECK_EQUAL(rect.GetLeft(), -100);
		rect.SetLeft(0);
		BOOST_CHECK_EQUAL(rect.GetLeft(), 0);
	}

	BOOST_AUTO_TEST_CASE(TopCanBeSet)
	{
		CRectangle rect(0, 0, 0, 100);
		rect.SetTop(20);
		BOOST_CHECK_EQUAL(rect.GetTop(), 20);
		rect.SetTop(-100);
		BOOST_CHECK_EQUAL(rect.GetTop(), -100);
		rect.SetTop(0);
		BOOST_CHECK_EQUAL(rect.GetTop(), 0);
	}

	BOOST_AUTO_TEST_CASE(RightCanBeSet)
	{
		CRectangle rect(-200, 0, 0, 0);
		rect.SetRight(20);
		BOOST_CHECK_EQUAL(rect.GetRight(), 20);
		rect.SetRight(-100);
		BOOST_CHECK_EQUAL(rect.GetRight(), -100);
		rect.SetRight(0);
		BOOST_CHECK_EQUAL(rect.GetRight(), 0);
	}

	BOOST_AUTO_TEST_CASE(BottomCanBeSet)
	{
		CRectangle rect(0, -200, 0, 0);
		rect.SetBottom(20);
		BOOST_CHECK_EQUAL(rect.GetBottom(), 20);
		rect.SetBottom(-100);
		BOOST_CHECK_EQUAL(rect.GetBottom(), -100);
		rect.SetBottom(0);
		BOOST_CHECK_EQUAL(rect.GetBottom(), 0);
	}

	//// properties relations

	BOOST_AUTO_TEST_CASE(SetWidthChangeRight)
	{
		CRectangle rect(0, 0, 0, 0);
		rect.SetWidth(10);
		BOOST_CHECK_EQUAL(rect.GetRight(), 10);
		rect.SetWidth(222);
		BOOST_CHECK_EQUAL(rect.GetRight(), 222);
		rect.SetWidth(0);
		BOOST_CHECK_EQUAL(rect.GetRight(), 0);
	}

	BOOST_AUTO_TEST_CASE(SetRightChangeWidth)
	{
		CRectangle rect(0, 0, 0, 0);
		rect.SetRight(10);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 10);
		rect.SetRight(222);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 222);
		rect.SetRight(0);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 0);
	}

	BOOST_AUTO_TEST_CASE(SetLeftChangeWidth)
	{
		CRectangle rect(0, 0, 0, 0);
		rect.SetLeft(-10);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 10);
		rect.SetLeft(-222);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 222);
		rect.SetLeft(0);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 0);
	}

	BOOST_AUTO_TEST_CASE(SetHeightChangeBottom)
	{
		CRectangle rect(0, 0, 0, 0);
		rect.SetHeight(10);
		BOOST_CHECK_EQUAL(rect.GetBottom(), 10);
		rect.SetHeight(222);
		BOOST_CHECK_EQUAL(rect.GetBottom(), 222);
		rect.SetHeight(0);
		BOOST_CHECK_EQUAL(rect.GetBottom(), 0);
	}

	BOOST_AUTO_TEST_CASE(SetBottomChangeHeight)
	{
		CRectangle rect(0, 0, 0, 0);
		rect.SetBottom(10);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 10);
		rect.SetBottom(222);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 222);
		rect.SetBottom(0);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 0);
	}

	BOOST_AUTO_TEST_CASE(SetTopChangeHeight)
	{
		CRectangle rect(0, 0, 0, 0);
		rect.SetTop(-10);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 10);
		rect.SetTop(-222);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 222);
		rect.SetTop(0);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 0);
	}

	BOOST_AUTO_TEST_CASE(ChangeAreaBySettingWidthHeight)
	{
		CRectangle rect(0, 0, 0, 0);
		BOOST_CHECK_EQUAL(*rect.GetArea(), 0);
		
		// zero area
		rect.SetWidth(10);
		rect.SetHeight(0);
		BOOST_CHECK_EQUAL(*rect.GetArea(), 0);
		rect.SetWidth(0);
		rect.SetHeight(10);
		BOOST_CHECK_EQUAL(*rect.GetArea(), 0);

		// non-zero area
		rect.SetWidth(10);
		rect.SetHeight(5);
		BOOST_CHECK_EQUAL(*rect.GetArea(), 50);
		rect.SetWidth(125);
		rect.SetHeight(20);
		BOOST_CHECK_EQUAL(*rect.GetArea(), 2500);
	}

	BOOST_AUTO_TEST_CASE(ChangePerimeterBySettingWidthHeight)
	{
		CRectangle rect(0, 0, 0, 0);
		BOOST_CHECK_EQUAL(*rect.GetPerimeter(), 0);

		// 1 param check
		rect.SetWidth(250);
		rect.SetHeight(0);
		BOOST_CHECK_EQUAL(*rect.GetPerimeter(), 500);
		rect.SetWidth(0);
		rect.SetHeight(500);
		BOOST_CHECK_EQUAL(*rect.GetPerimeter(), 1000);

		// 2 params check
		rect.SetWidth(250);
		rect.SetHeight(500);
		BOOST_CHECK_EQUAL(*rect.GetPerimeter(), 1500);
	}

	//// properties restrictions

	BOOST_AUTO_TEST_CASE(MinMaxLeft)
	{
		CRectangle rect(0, 0, 0, 0);
		
		// min value
		rect.SetLeft(INT_MIN);
		BOOST_CHECK_EQUAL(rect.GetLeft(), INT_MIN);

		// max value
		rect.SetLeft(0);
		BOOST_CHECK_EQUAL(rect.GetLeft(), 0);
		rect.SetLeft(1);
		BOOST_CHECK_EQUAL(rect.GetLeft(), 0);

		rect.SetRight(100);
		rect.SetLeft(100);
		BOOST_CHECK_EQUAL(rect.GetLeft(), 100);
		rect.SetLeft(101);
		BOOST_CHECK_EQUAL(rect.GetLeft(), 100);
	}

	BOOST_AUTO_TEST_CASE(MinMaxRight)
	{
		CRectangle rect(0, 0, 0, 0);

		// min value
		rect.SetRight(0);
		BOOST_CHECK_EQUAL(rect.GetRight(), 0);
		rect.SetRight(-1);
		BOOST_CHECK_EQUAL(rect.GetRight(), 0);

		rect.SetLeft(-100);
		rect.SetRight(-100);
		BOOST_CHECK_EQUAL(rect.GetRight(), -100);
		rect.SetRight(-101);
		BOOST_CHECK_EQUAL(rect.GetRight(), -100);
		
		// max value
		rect.SetRight(INT_MAX);
		BOOST_CHECK_EQUAL(rect.GetRight(), INT_MAX);
	}

	BOOST_AUTO_TEST_CASE(MinMaxTop)
	{
		CRectangle rect(0, 0, 0, 0);

		// min value
		rect.SetTop(INT_MIN);
		BOOST_CHECK_EQUAL(rect.GetTop(), INT_MIN);
		
		// max value
		rect.SetTop(0);
		BOOST_CHECK_EQUAL(rect.GetTop(), 0);
		rect.SetTop(1);
		BOOST_CHECK_EQUAL(rect.GetTop(), 0);

		rect.SetBottom(100);
		rect.SetTop(100);
		BOOST_CHECK_EQUAL(rect.GetTop(), 100);
		rect.SetTop(101);
		BOOST_CHECK_EQUAL(rect.GetTop(), 100);
	}

	BOOST_AUTO_TEST_CASE(MinMaxBottom)
	{
		CRectangle rect(0, 0, 0, 0);

		// min value
		rect.SetBottom(0);
		BOOST_CHECK_EQUAL(rect.GetBottom(), 0);
		rect.SetBottom(-1);
		BOOST_CHECK_EQUAL(rect.GetBottom(), 0);

		rect.SetTop(-100);
		rect.SetBottom(-100);
		BOOST_CHECK_EQUAL(rect.GetBottom(), -100);
		rect.SetBottom(-101);
		BOOST_CHECK_EQUAL(rect.GetBottom(), -100);

		// max value
		rect.SetBottom(INT_MAX);
		BOOST_CHECK_EQUAL(rect.GetBottom(), INT_MAX);
	}

	BOOST_AUTO_TEST_CASE(MinMaxWidth)
	{
		CRectangle rect(0, 0, 0, 0);

		// min value
		rect.SetWidth(0);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 0);
		rect.SetWidth(-1);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 0);

		// max value
		rect.SetLeft(INT_MIN);
		rect.SetRight(INT_MAX);
		BOOST_CHECK_EQUAL(rect.GetWidth(), UINT_MAX);

		rect.SetLeft(INT_MIN);
		rect.SetRight(0);
		rect.SetWidth(UINT_MAX);
		BOOST_CHECK_EQUAL(rect.GetWidth(), UINT_MAX);

		
	}

	BOOST_AUTO_TEST_CASE(MinMaxHeight)
	{
		CRectangle rect(0, 0, 0, 0);

		// min value
		rect.SetHeight(0);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 0);
		rect.SetHeight(-1);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 0);

		// max value
		rect.SetTop(INT_MIN);
		rect.SetBottom(INT_MAX);
		BOOST_CHECK_EQUAL(rect.GetHeight(), UINT_MAX);

		rect.SetBottom(0);
		rect.SetHeight(UINT_MAX);
		BOOST_CHECK_EQUAL(rect.GetHeight(), UINT_MAX);
	}

	//// properties overflow

	BOOST_AUTO_TEST_CASE(RightOverflow)
	{
		CRectangle rect(0, 0, 0, 0);

		rect.SetLeft(-23451);
		rect.SetWidth(static_cast<unsigned>(23451) + INT_MAX);
		BOOST_CHECK_EQUAL(rect.GetRight(), INT_MAX);
		rect.SetWidth(static_cast<unsigned>(23451) + INT_MAX + 1);
		BOOST_CHECK_EQUAL(rect.GetRight(), INT_MAX);
	}

	BOOST_AUTO_TEST_CASE(BottomOverflow)
	{
		CRectangle rect(0, 0, 0, 0);

		rect.SetTop(-23451);
		rect.SetHeight(static_cast<unsigned>(23451) + INT_MAX);
		BOOST_CHECK_EQUAL(rect.GetBottom(), INT_MAX);
		rect.SetHeight(static_cast<unsigned>(23451) + INT_MAX + 1);
		BOOST_CHECK_EQUAL(rect.GetBottom(), INT_MAX);
	}


	BOOST_AUTO_TEST_CASE(PerimeterOverflow)
	{
		CRectangle rect(0, 0, 0, 0);

		// max value
		rect.SetLeft(INT_MIN);
		rect.SetWidth(INT_MAX - 1000);
		rect.SetHeight(1000);
		BOOST_CHECK_EQUAL(*rect.GetPerimeter(), UINT_MAX - 1);

		// overflow
		rect.SetLeft(INT_MIN);
		rect.SetWidth(INT_MAX - 999);
		rect.SetHeight(1000);
		BOOST_CHECK(rect.GetPerimeter() == boost::none);

		rect.SetWidth(UINT_MAX);
		rect.SetHeight(1000);
		BOOST_CHECK(rect.GetPerimeter() == boost::none);
	}

	BOOST_AUTO_TEST_CASE(AreaOverflow)
	{
		CRectangle rect(0, 0, 0, 0);

		// max value
		rect.SetLeft(INT_MIN);
		rect.SetWidth(UINT_MAX);
		rect.SetHeight(1);
		BOOST_CHECK_EQUAL(*rect.GetArea(), UINT_MAX);

		// oveflow
		rect.SetLeft(INT_MIN);
		rect.SetWidth(static_cast<unsigned>(INT_MAX) + 1);
		rect.SetHeight(2);
		BOOST_CHECK(rect.GetArea() == boost::none);
	}

	// methods
	//// move

	BOOST_AUTO_TEST_CASE(MoveChangeLeftRight)
	{
		CRectangle rect(0, 0, 100, 100);

		rect.Move(10, 0);
		BOOST_CHECK_EQUAL(rect.GetLeft(), 10);
		BOOST_CHECK_EQUAL(rect.GetRight(), 110);

		rect.Move(-10, 0);
		BOOST_CHECK_EQUAL(rect.GetLeft(), 0);
		BOOST_CHECK_EQUAL(rect.GetRight(), 100);
	}

	BOOST_AUTO_TEST_CASE(MoveRightOverflow)
	{
		CRectangle rect(0, 0, 0, 0);
		
		rect.Move(100, 0);
		BOOST_CHECK_EQUAL(rect.GetLeft(), 100);
		BOOST_CHECK_EQUAL(rect.GetRight(), 100);

		// max value after move
		rect.Move(INT_MAX, 0);
		BOOST_CHECK_EQUAL(rect.GetLeft(), INT_MAX);
		BOOST_CHECK_EQUAL(rect.GetRight(), INT_MAX);

		// max value before move
		rect.Move(1, 0);
		BOOST_CHECK_EQUAL(rect.GetLeft(), INT_MAX);
		BOOST_CHECK_EQUAL(rect.GetRight(), INT_MAX);
	}

	BOOST_AUTO_TEST_CASE(MoveLeftOverflow)
	{
		CRectangle rect(0, 0, 0, 0);

		rect.Move(-100, 0);
		BOOST_CHECK_EQUAL(rect.GetLeft(), -100);
		BOOST_CHECK_EQUAL(rect.GetRight(), -100);

		// min value after move
		rect.Move(INT_MIN, 0);
		BOOST_CHECK_EQUAL(rect.GetLeft(), INT_MIN);
		BOOST_CHECK_EQUAL(rect.GetRight(), INT_MIN);

		// min value before move
		rect.Move(-1, 0);
		BOOST_CHECK_EQUAL(rect.GetLeft(), INT_MIN);
		BOOST_CHECK_EQUAL(rect.GetRight(), INT_MIN);
	}

	BOOST_AUTO_TEST_CASE(MoveChangeTopBottom)
	{
		CRectangle rect(0, 0, 100, 100);

		rect.Move(0, 10);
		BOOST_CHECK_EQUAL(rect.GetTop(), 10);
		BOOST_CHECK_EQUAL(rect.GetBottom(), 110);

		rect.Move(0, -10);
		BOOST_CHECK_EQUAL(rect.GetTop(), 0);
		BOOST_CHECK_EQUAL(rect.GetBottom(), 100);
	}

	BOOST_AUTO_TEST_CASE(MoveBottomOverflow)
	{
		CRectangle rect(0, 0, 0, 0);

		rect.Move(0, 100);
		BOOST_CHECK_EQUAL(rect.GetTop(), 100);
		BOOST_CHECK_EQUAL(rect.GetBottom(), 100);

		// max value after move
		rect.Move(0, INT_MAX);
		BOOST_CHECK_EQUAL(rect.GetTop(), INT_MAX);
		BOOST_CHECK_EQUAL(rect.GetBottom(), INT_MAX);

		// max value before move
		rect.Move(0, 1);
		BOOST_CHECK_EQUAL(rect.GetTop(), INT_MAX);
		BOOST_CHECK_EQUAL(rect.GetBottom(), INT_MAX);
	}

	BOOST_AUTO_TEST_CASE(MoveTopOverflow)
	{
		CRectangle rect(0, 0, 0, 0);

		rect.Move(0, -100);
		BOOST_CHECK_EQUAL(rect.GetTop(), -100);
		BOOST_CHECK_EQUAL(rect.GetBottom(), -100);

		// min value after move
		rect.Move(0, INT_MIN);
		BOOST_CHECK_EQUAL(rect.GetTop(), INT_MIN);
		BOOST_CHECK_EQUAL(rect.GetBottom(), INT_MIN);

		// min value before move
		rect.Move(0, -1);
		BOOST_CHECK_EQUAL(rect.GetTop(), INT_MIN);
		BOOST_CHECK_EQUAL(rect.GetBottom(), INT_MIN);
	}

	BOOST_AUTO_TEST_CASE(MoveChangeLeftRightTopBottom)
	{
		CRectangle rect(0, 0, 1000, 2000);

		rect.Move(100, -100);
		BOOST_CHECK_EQUAL(rect.GetLeft(),    100);
		BOOST_CHECK_EQUAL(rect.GetRight(),  1100);
		BOOST_CHECK_EQUAL(rect.GetTop(),    -100);
		BOOST_CHECK_EQUAL(rect.GetBottom(), 1900);
	}

	//// scale

	BOOST_AUTO_TEST_CASE(ScaleChangeWidth)
	{
		CRectangle rect(0, 0, 100, 100);

		rect.Scale(2, 1);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 200);

		rect.Scale(100, 1);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 20000);

		rect.Scale(0, 1);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 0);
	}

	BOOST_AUTO_TEST_CASE(ScaleWidthOverflow)
	{
		CRectangle rect(-2000, 0, 1, 100);

		// out of Right bound
		rect.Scale(INT_MAX, 1);
		rect.Scale(2, 1);
		BOOST_CHECK_EQUAL(rect.GetRight(), INT_MAX);

		// out of Width bound
		rect.Scale(2, 1);
		BOOST_CHECK_EQUAL(rect.GetRight(), INT_MAX);
	}

	BOOST_AUTO_TEST_CASE(ScaleChangeHeight)
	{
		CRectangle rect(0, 0, 100, 100);

		rect.Scale(1, 2);
		BOOST_CHECK_EQUAL(rect.GetWidth(),  100);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 200);

		rect.Scale(1, 100);
		BOOST_CHECK_EQUAL(rect.GetWidth(),    100);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 20000);
	}

	BOOST_AUTO_TEST_CASE(ScaleHeightOverflow)
	{
		CRectangle rect(0, -2000, 100, 1);

		// out of Bottom bound
		rect.Scale(1, INT_MAX);
		rect.Scale(1, 2);
		BOOST_CHECK_EQUAL(rect.GetBottom(), INT_MAX);

		// out of Height bound
		rect.Scale(1, 2);
		BOOST_CHECK_EQUAL(rect.GetBottom(), INT_MAX);
	}

	BOOST_AUTO_TEST_CASE(ScaleChangeWidhtHeight)
	{
		CRectangle rect(0, 0, 100, 200);

		rect.Scale(2, 3);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 200);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 600);
	}

	BOOST_AUTO_TEST_CASE(ScaleNotChangeLeftTop)
	{
		CRectangle rect(0, 0, 100, 100);

		rect.Scale(10, 2);
		BOOST_CHECK_EQUAL(rect.GetLeft(), 0);
		BOOST_CHECK_EQUAL(rect.GetTop(),  0);

		rect.Scale(0, 0);
		BOOST_CHECK_EQUAL(rect.GetLeft(), 0);
		BOOST_CHECK_EQUAL(rect.GetTop(),  0);
	}

	BOOST_AUTO_TEST_CASE(ScaleNotAlwaysChangeWidthHeight)
	{
		CRectangle rect(0, 0, 100, 100);

		// scale by 1, 1
		rect.Scale(1, 1);
		BOOST_CHECK_EQUAL(rect.GetWidth(),  100);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 100);

		// scale by negative number
		rect.Scale(5, -10);
		BOOST_CHECK_EQUAL(rect.GetWidth(),  100);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 100);

		rect.Scale(-5, 10);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 100);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 100);

		// scale zero dimensions rect
		rect.SetWidth(0);
		rect.SetHeight(0);
		rect.Scale(2, 10);
		BOOST_CHECK_EQUAL(rect.GetWidth(),  0);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 0);
	}

	//// intersect
	////// main properties

	BOOST_AUTO_TEST_CASE(IntersectionReturnTrue)
	{
		CRectangle rect(10, 20, 100, 100);

		BOOST_CHECK_EQUAL(rect.Intersect(rect), true);
	}

	BOOST_AUTO_TEST_CASE(NoIntersectionReturnFalse)
	{
		CRectangle rect1(10, 20, 100, 100);
		CRectangle rect2(1000, 2000, 100, 100);

		BOOST_CHECK_EQUAL(rect1.Intersect(rect2), false);
	}

	BOOST_AUTO_TEST_CASE(NoIntersectionNoMove)
	{
		CRectangle rect1(10, 20, 100, 100);
		CRectangle rect2(1000, 2000, 100, 100);

		BOOST_REQUIRE_EQUAL(rect1.Intersect(rect2), false);
		BOOST_CHECK_EQUAL(rect1.GetLeft(), 10);
		BOOST_CHECK_EQUAL(rect1.GetTop(),  20);
	}

	BOOST_AUTO_TEST_CASE(NoIntersectionSet0WidthHeight)
	{
		CRectangle rect1(10, 20, 100, 100);
		CRectangle rect2(1000, 2000, 100, 100);

		BOOST_REQUIRE_EQUAL(rect1.Intersect(rect2), false);
		BOOST_CHECK_EQUAL(rect1.GetWidth(), 0);
		BOOST_CHECK_EQUAL(rect1.GetHeight(), 0);
	}
	
	////// rects collocations
	//////// no intersection

	void CheckNoIntersectionWithStandardRect(CRectangle const &rect2)
	{
		CRectangle rect1(0, 0, 100, 100);
		BOOST_CHECK_EQUAL(rect1.Intersect(rect2), false);
	}

	BOOST_AUTO_TEST_CASE(NoIntersectWithDistanceRect2Upper)
	{
		CheckNoIntersectionWithStandardRect({ 0, -300, 100, 100 });
	}

	BOOST_AUTO_TEST_CASE(NoIntersectWithDistanceRect2Lower)
	{
		CheckNoIntersectionWithStandardRect({ 0, 300, 100, 100 });
	}

	BOOST_AUTO_TEST_CASE(NoIntersectWithDistanceRect2Right)
	{
		CheckNoIntersectionWithStandardRect({ 300, 0, 100, 100 });
	}

	BOOST_AUTO_TEST_CASE(NoIntersectWithDistanceRect2Left)
	{
		CheckNoIntersectionWithStandardRect({ -300, 0, 100, 100 });
	}

	BOOST_AUTO_TEST_CASE(NoIntersectCloseRect2Upper)
	{
		CheckNoIntersectionWithStandardRect({ 0, -100, 100, 100 });
	}

	BOOST_AUTO_TEST_CASE(NoIntersectCloseRect2Lower)
	{
		CheckNoIntersectionWithStandardRect({ 0, 100, 100, 100 });
	}

	BOOST_AUTO_TEST_CASE(NoIntersectCloseRect2Right)
	{
		CheckNoIntersectionWithStandardRect({ 100, 0, 100, 100 });
	}

	BOOST_AUTO_TEST_CASE(NoIntersectCloseRect2Left)
	{
		CheckNoIntersectionWithStandardRect({ -100, 0, 100, 100 });
	}

	//////// intersect OX projection

	BOOST_AUTO_TEST_CASE(XIntersectRect2Inside)
	{
		CheckNoIntersectionWithStandardRect({ 0, 300, 50, 100 });
	}

	BOOST_AUTO_TEST_CASE(XIntersectRect2OutSide)
	{
		CheckNoIntersectionWithStandardRect({ -50, 300, 200, 100 });
	}

	BOOST_AUTO_TEST_CASE(XIntersectRect2Left)
	{
		CheckNoIntersectionWithStandardRect({ -50, 300, 100, 100 });
	}

	BOOST_AUTO_TEST_CASE(XIntersectRect2Right)
	{
		CheckNoIntersectionWithStandardRect({ 50, 300, 200, 100 });
	}

	//////// intersect OY projection

	BOOST_AUTO_TEST_CASE(YIntersectRect2Inside)
	{
		CheckNoIntersectionWithStandardRect({ 300, 20, 100, 50 });
	}

	BOOST_AUTO_TEST_CASE(YIntersectRect2OutSide)
	{
		CheckNoIntersectionWithStandardRect({ 300, -50, 100, 200 });
	}

	BOOST_AUTO_TEST_CASE(YIntersectRect2Upper)
	{
		CheckNoIntersectionWithStandardRect({ 300, -50, 100, 100 });
	}

	BOOST_AUTO_TEST_CASE(YIntersectRect2Lower)
	{
		CheckNoIntersectionWithStandardRect({ 300, 50, 100, 100 });
	}

	//////// real intersection
	////////// rect 2 upper

	void CheckIntersectionWithStandardRect(CRectangle const &rect2, CRectangle const &expectedResult)
	{
		CRectangle rect1(0, 0, 100, 100);
		BOOST_CHECK_EQUAL(rect1.Intersect(rect2), true);
		BOOST_CHECK_EQUAL(rect1.GetLeft(),   expectedResult.GetLeft());
		BOOST_CHECK_EQUAL(rect1.GetTop(),    expectedResult.GetTop());
		BOOST_CHECK_EQUAL(rect1.GetWidth(),  expectedResult.GetWidth());
		BOOST_CHECK_EQUAL(rect1.GetHeight(), expectedResult.GetHeight());
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2UpperLeft)
	{
		CheckIntersectionWithStandardRect({ -50, -50, 100, 100 }, { 0, 0, 50, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2UpperRight)
	{
		CheckIntersectionWithStandardRect({ 50, -50, 100, 100 }, { 50, 0, 50, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2UpperInside)
	{
		CheckIntersectionWithStandardRect({ 20, -50, 50, 100 }, { 20, 0, 50, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2UpperOutside)
	{
		CheckIntersectionWithStandardRect({ -50, -50, 200, 100 }, { 0, 0, 100, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2UpperCloseLeft)
	{
		CheckIntersectionWithStandardRect({ 0, -50, 200, 100 }, { 0, 0, 100, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2UpperCloseRight)
	{
		CheckIntersectionWithStandardRect({ 50, -50, 50, 100 }, { 50, 0, 50, 50 });
	}

	////////// rect 2 lower

	BOOST_AUTO_TEST_CASE(RealIntersectRect2LowerLeft)
	{
		CheckIntersectionWithStandardRect({ -50, 50, 100, 100 }, { 0, 50, 50, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2LowerRight)
	{
		CheckIntersectionWithStandardRect({ 50, 50, 100, 100 }, { 50, 50, 50, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2LowerInside)
	{
		CheckIntersectionWithStandardRect({ 20, 50, 50, 100 }, { 20, 50, 50, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2LowerOutside)
	{
		CheckIntersectionWithStandardRect({ -50, 50, 200, 100 }, { 0, 50, 100, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2LowerCloseLeft)
	{
		CheckIntersectionWithStandardRect({ 0, 50, 200, 100 }, { 0, 50, 100, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2LowerCloseRight)
	{
		CheckIntersectionWithStandardRect({ 50, 50, 50, 100 }, { 50, 50, 50, 50 });
	}

	////////// rect 2 inside

	BOOST_AUTO_TEST_CASE(RealIntersectRect2InsideLeft)
	{
		CheckIntersectionWithStandardRect({ -50, 20, 100, 50 }, { 0, 20, 50, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2InsideRight)
	{
		CheckIntersectionWithStandardRect({ 50, 20, 100, 50 }, { 50, 20, 50, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2InsideInside)
	{
		CheckIntersectionWithStandardRect({ 20, 20, 50, 50 }, { 20, 20, 50, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2InsideOutside)
	{
		CheckIntersectionWithStandardRect({ -50, 20, 200, 50 }, { 0, 20, 100, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2InsideCloseLeft)
	{
		CheckIntersectionWithStandardRect({ 0, 20, 200, 50 }, { 0, 20, 100, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2InsideCloseRight)
	{
		CheckIntersectionWithStandardRect({ 50, 20, 50, 50 }, { 50, 20, 50, 50 });
	}

	////////// rect 2 outside

	BOOST_AUTO_TEST_CASE(RealIntersectRect2OutsideLeft)
	{
		CheckIntersectionWithStandardRect({ -50, -50, 100, 200 }, { 0, 0, 50, 100 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2OutsideRight)
	{
		CheckIntersectionWithStandardRect({ 50, -50, 100, 200 }, { 50, 0, 50, 100 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2OutsideInside)
	{
		CheckIntersectionWithStandardRect({ 20, -50, 50, 200 }, { 20, 0, 50, 100 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2OutsideOutside)
	{
		CheckIntersectionWithStandardRect({ -50, -50, 200, 200 }, { 0, 0, 100, 100 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2OutsideCloseLeft)
	{
		CheckIntersectionWithStandardRect({ 0, -50, 200, 200 }, { 0, 0, 100, 100 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2OutsideCloseRight)
	{
		CheckIntersectionWithStandardRect({ 50, -50, 50, 200 }, { 50, 0, 50, 100 });
	}

	////////// rect 2 close top

	BOOST_AUTO_TEST_CASE(RealIntersectRect2CloseTopLeft)
	{
		CheckIntersectionWithStandardRect({ -50, 0, 100, 50 }, { 0, 0, 50, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2CloseTopRight)
	{
		CheckIntersectionWithStandardRect({ 50, 0, 100, 50 }, { 50, 0, 50, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2CloseTopInside)
	{
		CheckIntersectionWithStandardRect({ 20, 0, 50, 50 }, { 20, 0, 50, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2CloseTopOutside)
	{
		CheckIntersectionWithStandardRect({ -50, 0, 200, 50 }, { 0, 0, 100, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2CloseTopCloseLeft)
	{
		CheckIntersectionWithStandardRect({ 0, 0, 200, 50 }, { 0, 0, 100, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2CloseTopCloseRight)
	{
		CheckIntersectionWithStandardRect({ 50, 0, 50, 50 }, { 50, 0, 50, 50 });
	}

	////////// rect 2 close bottom

	BOOST_AUTO_TEST_CASE(RealIntersectRect2CloseBottomLeft)
	{
		CheckIntersectionWithStandardRect({ -50, 50, 100, 50 }, { 0, 50, 50, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2CloseBottomRight)
	{
		CheckIntersectionWithStandardRect({ 50, 50, 100, 50 }, { 50, 50, 50, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2CloseBottomInside)
	{
		CheckIntersectionWithStandardRect({ 20, 50, 50, 50 }, { 20, 50, 50, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2CloseBottomOutside)
	{
		CheckIntersectionWithStandardRect({ -50, 50, 200, 50 }, { 0, 50, 100, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2CloseBottomCloseLeft)
	{
		CheckIntersectionWithStandardRect({ 0, 50, 200, 50 }, { 0, 50, 100, 50 });
	}

	BOOST_AUTO_TEST_CASE(RealIntersectRect2CloseBottomCloseRight)
	{
		CheckIntersectionWithStandardRect({ 50, 50, 50, 50 }, { 50, 50, 50, 50 });
	}

BOOST_AUTO_TEST_SUITE_END()
