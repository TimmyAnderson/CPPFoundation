//----------------------------------------------------------------------------------------------------------------------
#include "CMathematicsTest.h"
#include <Framework/Foundation/Console/CConsoleHelper.h>
#include <Framework/Foundation/Mathematics/CMathematics.h>
#include <Framework/Foundation/Types/CMethod.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace std;
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CMathematicsTest::CMathematicsTest(CLogWriter& LogWriter, const CLogCategory& LogCategoryTest)
		: CTest(LogWriter,LogCategoryTest,"MATHEMATICS TEST")
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CMathematicsTest::~CMathematicsTest(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CMathematicsTest::TestLine1(void)
	{
		CLine2D													Line(CPoint2D(1.0,1.0),CPoint2D(4.0,4.0));
		CVector<SLineIntersectionTestData>						LineIntersectionTestDataCollection;

		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(3.0,0.0),CPoint2D(0.0,3.0)),true));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(8.0,0.0),CPoint2D(0.0,8.0)),true));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(9.0,0.0),CPoint2D(0.0,9.0)),false));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(9.0,0.0),CPoint2D(9.0,9.0)),false));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(2.0,0.0),CPoint2D(2.0,10.0)),true));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(0.0,9.0),CPoint2D(9.0,9.0)),false));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(0.0,2.0),CPoint2D(10.0,2.0)),true));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(2.0,1.0),CPoint2D(5.0,4.0)),false));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(5.0,5.0),CPoint2D(7.0,7.0)),false));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(3.0,3.0),CPoint2D(7.0,7.0)),true));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(0.0,0.0),CPoint2D(2.0,2.0)),true));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(0.0,0.0),CPoint2D(7.0,7.0)),true));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(2.0,2.0),CPoint2D(3.0,3.0)),true));

		Size													TestNumber=0;

		for(const SLineIntersectionTestData& LineTestData : LineIntersectionTestDataCollection)
		{
			TestNumber++;

			if (LineTestData.GetHasIntersection()==true)
			{
				if (Line.HasLineSegmentIntersection(LineTestData.GetLineToCheck())==false)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to FIND INTERSECTION !\n"));
					return(false);
				}
			}
			else
			{
				if (Line.HasLineSegmentIntersection(LineTestData.GetLineToCheck())==true)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FOUND INVALID INTERSECTION !\n"));
					return(false);
				}
			}
		}

		if (CMathematics::EpsilonComparisonEqual(Line.Distance(CPoint2D(-1,4)),3.535533905,0.000001)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to CALCULATE DISTANCE !\n"));
			return(false);
		}

		if (CMathematics::EpsilonComparisonEqual(Line.Distance(CPoint2D(5,5)),0.0,0.000001)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to CALCULATE DISTANCE !\n"));
			return(false);
		}

		if (Line.GetPointPosition(CPoint2D(-5,3))!=ELine2DPointPosition::E_LEFT_TO_LINE)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETERMINE CORRECT POINT POSITION !\n"));
			return(false);
		}

		if (Line.GetPointPosition(CPoint2D(15,3))!=ELine2DPointPosition::E_RIGHT_TO_LINE)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETERMINE CORRECT POINT POSITION !\n"));
			return(false);
		}

		if (Line.GetPointPosition(CPoint2D(3,3))!=ELine2DPointPosition::E_ON_LINE)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETERMINE CORRECT POINT POSITION !\n"));
			return(false);
		}

		if (Line.GetPointPosition(CPoint2D(-5,10))!=ELine2DPointPosition::E_LEFT_TO_LINE)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETERMINE CORRECT POINT POSITION !\n"));
			return(false);
		}

		if (Line.GetPointPosition(CPoint2D(15,10))!=ELine2DPointPosition::E_RIGHT_TO_LINE)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETERMINE CORRECT POINT POSITION !\n"));
			return(false);
		}

		if (Line.GetPointPosition(CPoint2D(10,10))!=ELine2DPointPosition::E_ON_LINE)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETERMINE CORRECT POINT POSITION !\n"));
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CMathematicsTest::TestLine2(void)
	{
		CLine2D													Line(CPoint2D(1.0,1.0),CPoint2D(4.0,7.0));
		CVector<SLineIntersectionTestData>						LineIntersectionTestDataCollection;

		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(3.0,0.0),CPoint2D(0.0,3.0)),true));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(8.0,0.0),CPoint2D(0.0,8.0)),true));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(15.0,0.0),CPoint2D(0.0,15.0)),false));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(9.0,0.0),CPoint2D(9.0,9.0)),false));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(2.0,0.0),CPoint2D(2.0,10.0)),true));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(0.0,9.0),CPoint2D(9.0,9.0)),false));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(0.0,2.0),CPoint2D(10.0,2.0)),true));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(2.0,1.0),CPoint2D(5.0,7.0)),false));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(5.0,9.0),CPoint2D(6.0,11.0)),false));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(3.0,5.0),CPoint2D(5.0,9.0)),true));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(-2.0,-5.0),CPoint2D(2.0,3.0)),true));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(-2.0,-5.0),CPoint2D(5.0,9.0)),true));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(2.0,3.0),CPoint2D(3.0,5.0)),true));

		Size													TestNumber=0;

		for(const SLineIntersectionTestData& LineIntersectionTestData : LineIntersectionTestDataCollection)
		{
			TestNumber++;

			if (LineIntersectionTestData.GetHasIntersection()==true)
			{
				if (Line.HasLineSegmentIntersection(LineIntersectionTestData.GetLineToCheck())==false)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to FIND INTERSECTION !\n"));
					return(false);
				}
			}
			else
			{
				if (Line.HasLineSegmentIntersection(LineIntersectionTestData.GetLineToCheck())==true)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FOUND INVALID INTERSECTION !\n"));
					return(false);
				}
			}
		}

		if (CMathematics::EpsilonComparisonEqual(Line.Distance(CPoint2D(-1,4)),3.1304951684997,0.000001)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to CALCULATE DISTANCE !\n"));
			return(false);
		}

		if (CMathematics::EpsilonComparisonEqual(Line.Distance(CPoint2D(10,19)),0.0,0.000001)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to CALCULATE DISTANCE !\n"));
			return(false);
		}

		if (Line.GetPointPosition(CPoint2D(-5,3))!=ELine2DPointPosition::E_LEFT_TO_LINE)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETERMINE CORRECT POINT POSITION !\n"));
			return(false);
		}

		if (Line.GetPointPosition(CPoint2D(15,3))!=ELine2DPointPosition::E_RIGHT_TO_LINE)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETERMINE CORRECT POINT POSITION !\n"));
			return(false);
		}

		if (Line.GetPointPosition(CPoint2D(3,5))!=ELine2DPointPosition::E_ON_LINE)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETERMINE CORRECT POINT POSITION !\n"));
			return(false);
		}

		if (Line.GetPointPosition(CPoint2D(-5,10))!=ELine2DPointPosition::E_LEFT_TO_LINE)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETERMINE CORRECT POINT POSITION !\n"));
			return(false);
		}

		if (Line.GetPointPosition(CPoint2D(15,10))!=ELine2DPointPosition::E_RIGHT_TO_LINE)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETERMINE CORRECT POINT POSITION !\n"));
			return(false);
		}

		if (Line.GetPointPosition(CPoint2D(10,19))!=ELine2DPointPosition::E_ON_LINE)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETERMINE CORRECT POINT POSITION !\n"));
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CMathematicsTest::TestCircle(void)
	{
		CCircle2D												Circle(CPoint2D(10,5),3);
		CVector<SLineIntersectionTestData>						LineIntersectionTestDataCollection;

		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(11,-4),CPoint2D(18,3)),false));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(16,5),CPoint2D(10,9)),false));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(10,1),CPoint2D(15,5)),false));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(5,2),CPoint2D(13,2)),true));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(7,1),CPoint2D(7,10)),true));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(5,3),CPoint2D(10,6)),true));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(8,6),CPoint2D(11,4)),false));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(6,6),CPoint2D(12,1)),true));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(11,5),CPoint2D(12,5)),false));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(12,5),CPoint2D(12,6)),false));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(2,6),CPoint2D(16,6)),true));
		LineIntersectionTestDataCollection.Add(SLineIntersectionTestData(CLine2D(CPoint2D(9,1),CPoint2D(9,9)),true));

		Size													TestNumber=0;

		for(const SLineIntersectionTestData& LineIntersectionTestData : LineIntersectionTestDataCollection)
		{
			TestNumber++;

			if (LineIntersectionTestData.GetHasIntersection()==true)
			{
				if (Circle.HasLineSegmentIntersection(LineIntersectionTestData.GetLineToCheck())==false)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to FIND INTERSECTION !\n"));
					return(false);
				}
			}
			else
			{
				if (Circle.HasLineSegmentIntersection(LineIntersectionTestData.GetLineToCheck())==true)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FOUND INVALID INTERSECTION !\n"));
					return(false);
				}
			}
		}

		if (Circle.ContainsPoint(CPoint2D(9,3))==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that CIRCLE contains POINT !\n"));
			return(false);
		}

		if (Circle.ContainsPoint(CPoint2D(10,2))==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that CIRCLE contains POINT !\n"));
			return(false);
		}

		if (Circle.ContainsPoint(CPoint2D(7,5))==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that CIRCLE contains POINT !\n"));
			return(false);
		}

		if (Circle.ContainsPoint(CPoint2D(13,3))==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that CIRCLE doesn't contain POINT !\n"));
			return(false);
		}

		if (Circle.ContainsPoint(CPoint2D(14,4))==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that CIRCLE doesn't contain POINT !\n"));
			return(false);
		}

		if (Circle.OverlapsCircle(CCircle2D(CPoint2D(-5,5),3))==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two CIRCLES OVERLAP !\n"));
			return(false);
		}

		if (Circle.OverlapsCircle(CCircle2D(CPoint2D(10,1),3))==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two CIRCLES don't OVERLAP !\n"));
			return(false);
		}

		if (Circle.OverlapsCircle(CCircle2D(CPoint2D(10,1),10))==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two CIRCLES don't OVERLAP !\n"));
			return(false);
		}

		if (Circle.OverlapsCircle(CCircle2D(CPoint2D(8,3),10))==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two CIRCLES don't OVERLAP !\n"));
			return(false);
		}

		if (Circle.OverlapsCircle(CCircle2D(CPoint2D(8,3),1))==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two CIRCLES don't OVERLAP !\n"));
			return(false);
		}

		if (Circle.OverlapsCircle(CCircle2D(CPoint2D(7,2),8))==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two CIRCLES don't OVERLAP !\n"));
			return(false);
		}

		if (Circle.OverlapsCircle(CCircle2D(CPoint2D(3,5),4))==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two CIRCLES don't OVERLAP !\n"));
			return(false);
		}

		if (Circle.OverlapsCircle(CCircle2D(CPoint2D(3,5),3.99999999))==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two CIRCLES OVERLAP !\n"));
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CMathematicsTest::TestPolygon1(void)
	{
		CLine2DCollection										LineCollection;
		CPoint2D												StartPoint(1,1);

		LineCollection.Add(CLine2D(StartPoint+CPoint2D(0,0),StartPoint+CPoint2D(0,9)));
		LineCollection.Add(CLine2D(StartPoint+CPoint2D(0,9),StartPoint+CPoint2D(10,9)));
		LineCollection.Add(CLine2D(StartPoint+CPoint2D(10,9),StartPoint+CPoint2D(10,2)));
		LineCollection.Add(CLine2D(StartPoint+CPoint2D(10,2),StartPoint+CPoint2D(7,7)));
		LineCollection.Add(CLine2D(StartPoint+CPoint2D(7,7),StartPoint+CPoint2D(4,7)));
		LineCollection.Add(CLine2D(StartPoint+CPoint2D(4,7),StartPoint+CPoint2D(4,4)));
		LineCollection.Add(CLine2D(StartPoint+CPoint2D(4,4),StartPoint+CPoint2D(12,4)));
		LineCollection.Add(CLine2D(StartPoint+CPoint2D(12,4),StartPoint+CPoint2D(12,0)));
		LineCollection.Add(CLine2D(StartPoint+CPoint2D(12,0),StartPoint+CPoint2D(0,0)));

		CPolygon2D												Polygon(LineCollection);
		CVector<SPolygonContainsPointTestData>					PolygonContainsPointTestDataCollection;

		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(-1,-5),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(-100,5),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(100,5),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(5,-100),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(5,100),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(2,9),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(2,11),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(0,0),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(7,0),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(12,4),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(10,6),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(6,6),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(6,7),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(7,6),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(7,7),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(8,6),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(8,7),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(9,6),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(9,7),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(10.5,4.5),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(15,3),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(12,6),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(1,1),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(1,10),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(11,10),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(11,3),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(8,8),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(5,8),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(5,5),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(13,5),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(13,1),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(12,10),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(10,10),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(11,4),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(5,6),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(12,5),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(13,3),true));

		Size													TestNumber=0;

		for(const SPolygonContainsPointTestData& PolygonContainsPointTestData : PolygonContainsPointTestDataCollection)
		{
			TestNumber++;

			if (PolygonContainsPointTestData.GetHasIntersection()==true)
			{
				if (Polygon.ContainsPoint(PolygonContainsPointTestData.GetPointToCheck())==false)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to DETECT that POINT (",PolygonContainsPointTestData.GetPointToCheck().GetX(),",",PolygonContainsPointTestData.GetPointToCheck().GetY(),") lies INSIDE of POLYGON !\n"));
					return(false);
				}
			}
			else
			{
				if (Polygon.ContainsPoint(PolygonContainsPointTestData.GetPointToCheck())==true)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to DETECT that POINT (",PolygonContainsPointTestData.GetPointToCheck().GetX(),",",PolygonContainsPointTestData.GetPointToCheck().GetY(),") lies OUT of POLYGON !\n"));
					return(false);
				}
			}
		}

		CLine2DCollection										LineCollection1;

		LineCollection1.Add(CLine2D(CPoint2D(-1,9),CPoint2D(-1,11)));
		LineCollection1.Add(CLine2D(CPoint2D(-1,11),CPoint2D(2,11)));
		LineCollection1.Add(CLine2D(CPoint2D(2,11),CPoint2D(2,9)));
		LineCollection1.Add(CLine2D(CPoint2D(2,9),CPoint2D(-1,9)));

		CPolygon2D												Polygon1(LineCollection1);

		if (Polygon.OverlapsPolygon(Polygon1)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two POLYGONS OVERLAP !\n"));
			return(false);
		}

		CLine2DCollection										LineCollection2;

		LineCollection2.Add(CLine2D(CPoint2D(-2,8),CPoint2D(9,-1)));
		LineCollection2.Add(CLine2D(CPoint2D(9,-1),CPoint2D(8,-2)));
		LineCollection2.Add(CLine2D(CPoint2D(8,-2),CPoint2D(-2,6)));
		LineCollection2.Add(CLine2D(CPoint2D(-2,6),CPoint2D(-2,8)));

		CPolygon2D												Polygon2(LineCollection2);

		if (Polygon.OverlapsPolygon(Polygon2)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two POLYGONS OVERLAP !\n"));
			return(false);
		}

		CLine2DCollection										LineCollection3;

		LineCollection3.Add(CLine2D(CPoint2D(9,2),CPoint2D(12,2)));
		LineCollection3.Add(CLine2D(CPoint2D(12,2),CPoint2D(12,4)));
		LineCollection3.Add(CLine2D(CPoint2D(12,4),CPoint2D(9,4)));
		LineCollection3.Add(CLine2D(CPoint2D(9,4),CPoint2D(9,2)));

		CPolygon2D												Polygon3(LineCollection3);

		if (Polygon.OverlapsPolygon(Polygon3)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two POLYGONS OVERLAP !\n"));
			return(false);
		}

		CLine2DCollection										LineCollection4;

		LineCollection4.Add(CLine2D(CPoint2D(9,8),CPoint2D(9,9)));
		LineCollection4.Add(CLine2D(CPoint2D(9,9),CPoint2D(10,9)));
		LineCollection4.Add(CLine2D(CPoint2D(10,9),CPoint2D(10,8)));
		LineCollection4.Add(CLine2D(CPoint2D(10,8),CPoint2D(9,8)));

		CPolygon2D												Polygon4(LineCollection4);

		if (Polygon.OverlapsPolygon(Polygon4)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two POLYGONS OVERLAP !\n"));
			return(false);
		}

		CLine2DCollection										LineCollection5;

		LineCollection5.Add(CLine2D(CPoint2D(12,6),CPoint2D(14,6)));
		LineCollection5.Add(CLine2D(CPoint2D(14,6),CPoint2D(14,10)));
		LineCollection5.Add(CLine2D(CPoint2D(14,10),CPoint2D(12,10)));
		LineCollection5.Add(CLine2D(CPoint2D(12,10),CPoint2D(12,6)));

		CPolygon2D												Polygon5(LineCollection5);

		if (Polygon.OverlapsPolygon(Polygon5)==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two POLYGONS don't OVERLAP !\n"));
			return(false);
		}

		CLine2DCollection										LineCollection6;

		LineCollection6.Add(CLine2D(CPoint2D(10.5,4.5),CPoint2D(10.6,4.5)));
		LineCollection6.Add(CLine2D(CPoint2D(10.6,4.5),CPoint2D(10.6,4.6)));
		LineCollection6.Add(CLine2D(CPoint2D(10.6,4.6),CPoint2D(10.5,4.6)));
		LineCollection6.Add(CLine2D(CPoint2D(10.5,4.6),CPoint2D(10.5,4.5)));

		CPolygon2D												Polygon6(LineCollection6);

		if (Polygon.OverlapsPolygon(Polygon6)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two POLYGONS OVERLAP !\n"));
			return(false);
		}

		CLine2DCollection										LineCollection7;

		LineCollection7.Add(CLine2D(CPoint2D(6,6),CPoint2D(6,7)));
		LineCollection7.Add(CLine2D(CPoint2D(6,7),CPoint2D(8,7)));
		LineCollection7.Add(CLine2D(CPoint2D(8,7),CPoint2D(8,6)));
		LineCollection7.Add(CLine2D(CPoint2D(8,6),CPoint2D(6,6)));

		CPolygon2D												Polygon7(LineCollection7);

		if (Polygon.OverlapsPolygon(Polygon7)==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two POLYGONS don't OVERLAP !\n"));
			return(false);
		}

		CLine2DCollection										LineCollection8;

		LineCollection8.Add(CLine2D(CPoint2D(16,12),CPoint2D(-3,12)));
		LineCollection8.Add(CLine2D(CPoint2D(-3,12),CPoint2D(-3,-3)));
		LineCollection8.Add(CLine2D(CPoint2D(-3,-3),CPoint2D(16,-3)));
		LineCollection8.Add(CLine2D(CPoint2D(16,-3),CPoint2D(16,12)));

		CPolygon2D												Polygon8(LineCollection8);

		if (Polygon.OverlapsPolygon(Polygon8)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two POLYGONS OVERLAP !\n"));
			return(false);
		}

		CCircle2D												Circle1(CPoint2D(15,10),3);

		if (Polygon.OverlapsCircle(Circle1)==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that POLYGON and CIRCLE don't OVERLAP !\n"));
			return(false);
		}

		CCircle2D												Circle2(CPoint2D(15,10),4);

		if (Polygon.OverlapsCircle(Circle2)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that POLYGON and CIRCLE OVERLAP !\n"));
			return(false);
		}

		CCircle2D												Circle3(CPoint2D(7,6.5),1);

		if (Polygon.OverlapsCircle(Circle3)==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that POLYGON and CIRCLE don't OVERLAP !\n"));
			return(false);
		}

		CCircle2D												Circle4(CPoint2D(7,6.5),1.5);

		if (Polygon.OverlapsCircle(Circle4)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that POLYGON and CIRCLE OVERLAP !\n"));
			return(false);
		}

		CCircle2D												Circle5(CPoint2D(7,6.5),2);

		if (Polygon.OverlapsCircle(Circle5)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that POLYGON and CIRCLE OVERLAP !\n"));
			return(false);
		}

		CCircle2D												Circle6(CPoint2D(7,3),1);

		if (Polygon.OverlapsCircle(Circle6)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that POLYGON and CIRCLE OVERLAP !\n"));
			return(false);
		}

		CCircle2D												Circle7(CPoint2D(7,3),30);

		if (Polygon.OverlapsCircle(Circle7)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that POLYGON and CIRCLE OVERLAP !\n"));
			return(false);
		}

		CCircle2D												Circle8(CPoint2D(15,10),30);

		if (Polygon.OverlapsCircle(Circle8)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that POLYGON and CIRCLE OVERLAP !\n"));
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CMathematicsTest::TestPolygon2(void)
	{
		CLine2DCollection										LineCollection;

		LineCollection.Add(CLine2D(CPoint2D(11,4),CPoint2D(5,12)));
		LineCollection.Add(CLine2D(CPoint2D(5,12),CPoint2D(11,12)));
		LineCollection.Add(CLine2D(CPoint2D(11,12),CPoint2D(5,4)));
		LineCollection.Add(CLine2D(CPoint2D(5,4),CPoint2D(11,4)));
		LineCollection.Add(CLine2D(CPoint2D(11,4),CPoint2D(11,8)));
		LineCollection.Add(CLine2D(CPoint2D(11,8),CPoint2D(15,4)));
		LineCollection.Add(CLine2D(CPoint2D(15,4),CPoint2D(15,8)));
		LineCollection.Add(CLine2D(CPoint2D(15,8),CPoint2D(11,4)));

		CPolygon2D												Polygon(LineCollection);
		CVector<SPolygonContainsPointTestData>					PolygonContainsPointTestDataCollection;

		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(-100,4),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(100,4),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(15,-100),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(15,100),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(6,6),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(10,6),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(3,4),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(13,4),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(13,5),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(13,7),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(16,6),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(10,10),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(10,8),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(7,13),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(12,12),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(15,12),false));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(6,5),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(10,5),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(12,5),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(14,5),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(15,5),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(14,6),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(12,6),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(8,6),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(8,10),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(10,11),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(11,4),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(5,12),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(11,12),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(5,4),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(11,4),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(11,8),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(15,4),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(15,8),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(8,8),true));
		PolygonContainsPointTestDataCollection.Add(SPolygonContainsPointTestData(CPoint2D(13,6),true));

		Size													TestNumber=0;

		for(const SPolygonContainsPointTestData& PolygonContainsPointTestData : PolygonContainsPointTestDataCollection)
		{
			TestNumber++;

			if (PolygonContainsPointTestData.GetHasIntersection()==true)
			{
				if (Polygon.ContainsPoint(PolygonContainsPointTestData.GetPointToCheck())==false)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to DETECT that POINT (",PolygonContainsPointTestData.GetPointToCheck().GetX(),",",PolygonContainsPointTestData.GetPointToCheck().GetY(),") lies INSIDE of POLYGON !\n"));
					return(false);
				}
			}
			else
			{
				if (Polygon.ContainsPoint(PolygonContainsPointTestData.GetPointToCheck())==true)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to DETECT that POINT (",PolygonContainsPointTestData.GetPointToCheck().GetX(),",",PolygonContainsPointTestData.GetPointToCheck().GetY(),") lies OUT of POLYGON !\n"));
					return(false);
				}
			}
		}

		CLine2DCollection										LineCollection1;

		LineCollection1.Add(CLine2D(CPoint2D(4,10),CPoint2D(4,13)));
		LineCollection1.Add(CLine2D(CPoint2D(4,13),CPoint2D(6,13)));
		LineCollection1.Add(CLine2D(CPoint2D(6,13),CPoint2D(6,10)));
		LineCollection1.Add(CLine2D(CPoint2D(6,10),CPoint2D(4,10)));

		CPolygon2D												Polygon1(LineCollection1);

		if (Polygon.OverlapsPolygon(Polygon1)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two POLYGONS OVERLAP !\n"));
			return(false);
		}

		CLine2DCollection										LineCollection2;

		LineCollection2.Add(CLine2D(CPoint2D(7,10),CPoint2D(8,10)));
		LineCollection2.Add(CLine2D(CPoint2D(8,10),CPoint2D(8,11)));
		LineCollection2.Add(CLine2D(CPoint2D(8,11),CPoint2D(7,11)));
		LineCollection2.Add(CLine2D(CPoint2D(7,11),CPoint2D(7,10)));

		CPolygon2D												Polygon2(LineCollection2);

		if (Polygon.OverlapsPolygon(Polygon2)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two POLYGONS OVERLAP !\n"));
			return(false);
		}

		CLine2DCollection										LineCollection3;

		LineCollection3.Add(CLine2D(CPoint2D(7,4),CPoint2D(7,6)));
		LineCollection3.Add(CLine2D(CPoint2D(7,6),CPoint2D(9,6)));
		LineCollection3.Add(CLine2D(CPoint2D(9,6),CPoint2D(9,4)));
		LineCollection3.Add(CLine2D(CPoint2D(9,4),CPoint2D(7,4)));

		CPolygon2D												Polygon3(LineCollection3);

		if (Polygon.OverlapsPolygon(Polygon3)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two POLYGONS OVERLAP !\n"));
			return(false);
		}

		CLine2DCollection										LineCollection4;

		LineCollection4.Add(CLine2D(CPoint2D(13,7),CPoint2D(13,13)));
		LineCollection4.Add(CLine2D(CPoint2D(13,13),CPoint2D(10,13)));
		LineCollection4.Add(CLine2D(CPoint2D(10,13),CPoint2D(10,7)));
		LineCollection4.Add(CLine2D(CPoint2D(10,7),CPoint2D(13,7)));

		CPolygon2D												Polygon4(LineCollection4);

		if (Polygon.OverlapsPolygon(Polygon4)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two POLYGONS OVERLAP !\n"));
			return(false);
		}

		CLine2DCollection										LineCollection5;

		LineCollection5.Add(CLine2D(CPoint2D(13,3),CPoint2D(13,5)));
		LineCollection5.Add(CLine2D(CPoint2D(13,5),CPoint2D(14,5)));
		LineCollection5.Add(CLine2D(CPoint2D(14,5),CPoint2D(14,3)));
		LineCollection5.Add(CLine2D(CPoint2D(14,3),CPoint2D(13,3)));

		CPolygon2D												Polygon5(LineCollection5);

		if (Polygon.OverlapsPolygon(Polygon5)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two POLYGONS OVERLAP !\n"));
			return(false);
		}

		CLine2DCollection										LineCollection6;

		LineCollection6.Add(CLine2D(CPoint2D(5,2),CPoint2D(5,14)));
		LineCollection6.Add(CLine2D(CPoint2D(5,14),CPoint2D(19,2)));
		LineCollection6.Add(CLine2D(CPoint2D(19,2),CPoint2D(5,2)));

		CPolygon2D												Polygon6(LineCollection6);

		if (Polygon.OverlapsPolygon(Polygon6)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two POLYGONS OVERLAP !\n"));
			return(false);
		}

		CLine2DCollection										LineCollection7;

		LineCollection7.Add(CLine2D(CPoint2D(1,1),CPoint2D(1,4)));
		LineCollection7.Add(CLine2D(CPoint2D(1,4),CPoint2D(4,3)));
		LineCollection7.Add(CLine2D(CPoint2D(4,3),CPoint2D(1,3)));
		LineCollection7.Add(CLine2D(CPoint2D(1,3),CPoint2D(1,1)));

		CPolygon2D												Polygon7(LineCollection7);

		if (Polygon.OverlapsPolygon(Polygon7)==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two POLYGONS don't OVERLAP !\n"));
			return(false);
		}

		CLine2DCollection										LineCollection8;

		LineCollection8.Add(CLine2D(CPoint2D(2,7),CPoint2D(7,7)));
		LineCollection8.Add(CLine2D(CPoint2D(7,7),CPoint2D(7,8)));
		LineCollection8.Add(CLine2D(CPoint2D(7,8),CPoint2D(2,8)));
		LineCollection8.Add(CLine2D(CPoint2D(2,8),CPoint2D(2,7)));

		CPolygon2D												Polygon8(LineCollection8);

		if (Polygon.OverlapsPolygon(Polygon8)==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two POLYGONS don't OVERLAP !\n"));
			return(false);
		}

		CLine2DCollection										LineCollection9;

		LineCollection9.Add(CLine2D(CPoint2D(-2,-2),CPoint2D(18,-2)));
		LineCollection9.Add(CLine2D(CPoint2D(18,-2),CPoint2D(18,14)));
		LineCollection9.Add(CLine2D(CPoint2D(18,14),CPoint2D(-2,14)));
		LineCollection9.Add(CLine2D(CPoint2D(-2,14),CPoint2D(-2,-2)));

		CPolygon2D												Polygon9(LineCollection9);

		if (Polygon.OverlapsPolygon(Polygon9)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that two POLYGONS OVERLAP !\n"));
			return(false);
		}

		CCircle2D												Circle1(CPoint2D(4,7),2);

		if (Polygon.OverlapsCircle(Circle1)==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that POLYGON and CIRCLE don't OVERLAP !\n"));
			return(false);
		}

		CCircle2D												Circle2(CPoint2D(14,6),1);

		if (Polygon.OverlapsCircle(Circle2)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that POLYGON and CIRCLE OVERLAP !\n"));
			return(false);
		}

		CCircle2D												Circle3(CPoint2D(15,2),2);

		if (Polygon.OverlapsCircle(Circle3)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that POLYGON and CIRCLE OVERLAP !\n"));
			return(false);
		}

		CCircle2D												Circle4(CPoint2D(3,4),2);

		if (Polygon.OverlapsCircle(Circle4)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that POLYGON and CIRCLE OVERLAP !\n"));
			return(false);
		}

		CCircle2D												Circle5(CPoint2D(10,8),1);

		if (Polygon.OverlapsCircle(Circle5)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that POLYGON and CIRCLE OVERLAP !\n"));
			return(false);
		}

		CCircle2D												Circle6(CPoint2D(10,8),0.999);

		if (Polygon.OverlapsCircle(Circle6)==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that POLYGON and CIRCLE don't OVERLAP !\n"));
			return(false);
		}

		CCircle2D												Circle7(CPoint2D(8,5),0.8);

		if (Polygon.OverlapsCircle(Circle7)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that POLYGON and CIRCLE OVERLAP !\n"));
			return(false);
		}

		CCircle2D												Circle8(CPoint2D(8,5),10);

		if (Polygon.OverlapsCircle(Circle8)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that POLYGON and CIRCLE OVERLAP !\n"));
			return(false);
		}

		CCircle2D												Circle9(CPoint2D(10,7),10);

		if (Polygon.OverlapsCircle(Circle9)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to DETECT that POLYGON and CIRCLE OVERLAP !\n"));
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CMathematicsTest::ExecuteTest(void)
	{
		CVector<CTestMethod<CMathematicsTest>>					Tests;

		Tests.Add(CTestMethod<CMathematicsTest>(this,&CMathematicsTest::TestLine1));
		Tests.Add(CTestMethod<CMathematicsTest>(this,&CMathematicsTest::TestLine2));
		Tests.Add(CTestMethod<CMathematicsTest>(this,&CMathematicsTest::TestCircle));
		Tests.Add(CTestMethod<CMathematicsTest>(this,&CMathematicsTest::TestPolygon1));
		Tests.Add(CTestMethod<CMathematicsTest>(this,&CMathematicsTest::TestPolygon2));

		bool													AllTestPassed=true;
		Size													TestNumber=0;

		for(CTestMethod<CMathematicsTest>& Method : Tests)
		{
			if (Method()==true)
			{
				CString											Output;

				Output+=GetSeparator(true);
				Output+="\tSUBTEST [";
				Output+=CString(++TestNumber);
				Output+="] PASSED SUCCESSFULLY !\n";
				Output+=GetSeparator(true);

				CConsoleHelper::WriteLine(Output,EConsoleColor::E_LIGHT_GREEN,EConsoleColor::E_DEFAULT,false);
			}
			else
			{
				CString											Output;

				Output+=GetSeparator(true);
				Output+="\tSUBTEST [";
				Output+=CString(++TestNumber);
				Output+="] FAILED !\n";
				Output+=GetSeparator(true);

				AllTestPassed=false;

				CConsoleHelper::WriteLine(Output,EConsoleColor::E_LIGHT_RED,EConsoleColor::E_DEFAULT,false);
			}
		}

		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));

		if (AllTestPassed==true)
		{
			CConsoleHelper::WriteLine("ALL TESTS PASSED SUCCESSFULLY !",EConsoleColor::E_LIGHT_GREEN,EConsoleColor::E_DEFAULT,false);
		}
		else
		{
			CConsoleHelper::WriteLine("SOME TESTS FAILED !",EConsoleColor::E_LIGHT_RED,EConsoleColor::E_DEFAULT,false);
		}

		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));

		return(AllTestPassed);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------