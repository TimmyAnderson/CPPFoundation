//----------------------------------------------------------------------------------------------------------------------
#include "CLine2D.h"
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/Types/CPrimitiveType.h>
#include "CMathematics.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CLine2D::CLine2D(void)
		: MPoint1(), MPoint2(), MA(), MB(), MC()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLine2D::CLine2D(const CPoint2D& Point1, const CPoint2D& Point2)
		: MPoint1(Point1), MPoint2(Point2), MA(), MB(), MC()
	{
		CheckLine(Point1,Point2);

		CalculateABC();
	}
//----------------------------------------------------------------------------------------------------------------------
	CLine2D::~CLine2D(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CLine2D::operator==(const CLine2D& Value) const
	{
		if (MPoint1==Value.MPoint1 && MPoint2==Value.MPoint2)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CLine2D::operator!=(const CLine2D& Value) const
	{
		return(!(*this==Value));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CLine2D::CheckLine(const CPoint2D& Point1, const CPoint2D& Point2)
	{
		if (Point1==Point2)
		{
			throw(CInvalidOperationException("POINTS can't be SAME !"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	float64 CLine2D::CalculateMin(float64 Value1, float64 Value2)
	{
		if (Value1<Value2)
		{
			return(Value1);
		}
		else
		{
			return(Value2);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	float64 CLine2D::CalculateMax(float64 Value1, float64 Value2)
	{
		if (Value1>Value2)
		{
			return(Value1);
		}
		else
		{
			return(Value2);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CLine2D::CalculateABC(void)
	{
		// FORMULA [A=Y1-Y2].
		MA=MPoint1.GetY()-MPoint2.GetY();
		// FORMULA [B=X2-X1].
		MB=MPoint2.GetX()-MPoint1.GetX();
		// FORMULA [C=X1Y2-X2Y1].
		MC=(MPoint1.GetX()*MPoint2.GetY())-(MPoint2.GetX()*MPoint1.GetY());
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CPoint2D& CLine2D::GetPoint1(void) const noexcept
	{
		return(MPoint1);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CLine2D::SetPoint1(const CPoint2D& Value)
	{
		CheckLine(Value,MPoint2);

		MPoint1=Value;

		CalculateABC();
	}
//----------------------------------------------------------------------------------------------------------------------
	const CPoint2D& CLine2D::GetPoint2(void) const noexcept
	{
		return(MPoint2);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CLine2D::SetPoint2(const CPoint2D& Value)
	{
		CheckLine(MPoint1,Value);

		MPoint2=Value;

		CalculateABC();
	}
//----------------------------------------------------------------------------------------------------------------------
	float64 CLine2D::GetA(void) const noexcept
	{
		return(MA);
	}
//----------------------------------------------------------------------------------------------------------------------
	float64 CLine2D::GetB(void) const noexcept
	{
		return(MB);
	}
//----------------------------------------------------------------------------------------------------------------------
	float64 CLine2D::GetC(void) const noexcept
	{
		return(MC);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	float64 CLine2D::Width(void) const
	{
		return(CMathematics::AbsoluteValueFloatingPoint(MPoint2.GetX()-MPoint1.GetX()));
	}
//----------------------------------------------------------------------------------------------------------------------
	float64 CLine2D::Height(void) const
	{
		return(CMathematics::AbsoluteValueFloatingPoint(MPoint2.GetY()-MPoint1.GetY()));
	}
//----------------------------------------------------------------------------------------------------------------------
	float64 CLine2D::Length(void) const
	{
		// Uses FORMULA [Length=SQRT((Width*Width)+(Height*Height))].
		float64													Length=CMathematics::SquareRoot((Width()*Width())+(Height()*Height()));

		return(Length);
	}
//----------------------------------------------------------------------------------------------------------------------
	float64 CLine2D::Distance(const CPoint2D& Point) const
	{
		// Uses FORMULA [Distance=ABS(AX+BY+C)/SQRT(A*A+B*B)].
		float64													Numerator=CMathematics::AbsoluteValueFloatingPoint((MA*Point.GetX())+(MB*Point.GetY())+MC);
		float64													Divisor=CMathematics::SquareRoot((MA*MA)+(MB*MB));
		float64													Distance=Numerator/Divisor;

		return(Distance);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CLine2D::IsPointOnLineSegment(const CPoint2D& Point) const
	{
		float64													AX=MA*Point.GetX();
		float64													BY=MB*Point.GetY();
		float64													PointOnLine=AX+BY+MC;

		// Checks FORMULA [Ax+By+C=0].
		if (CMathematics::EpsilonComparisonEqual(PointOnLine,0.0,VALUE_EPSILON)==true)
		{
			float64												MinX=CalculateMin(MPoint1.GetX(),MPoint2.GetX());
			float64												MaxX=CalculateMax(MPoint1.GetX(),MPoint2.GetX());
			float64												MinY=CalculateMin(MPoint1.GetY(),MPoint2.GetY());
			float64												MaxY=CalculateMax(MPoint1.GetY(),MPoint2.GetY());

			if (CMathematics::EpsilonComparisonGreaterToOrEqual(Point.GetX(),MinX,VALUE_EPSILON)==false)
			{
				return(false);
			}

			if (CMathematics::EpsilonComparisonLowerThanOrEqual(Point.GetX(),MaxX,VALUE_EPSILON)==false)
			{
				return(false);
			}

			if (CMathematics::EpsilonComparisonGreaterToOrEqual(Point.GetY(),MinY,VALUE_EPSILON)==false)
			{
				return(false);
			}

			if (CMathematics::EpsilonComparisonLowerThanOrEqual(Point.GetY(),MaxY,VALUE_EPSILON)==false)
			{
				return(false);
			}

			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CLine2D::HasLineSegmentIntersection(const CLine2D& Line) const
	{
		float64													A1=GetA();
		float64													B1=GetB();
		float64													C1=GetC();
		float64													A2=Line.GetA();
		float64													B2=Line.GetB();
		float64													C2=Line.GetC();
		// Uses FORMULA [DETERMINANT=A1B2-A2B1].
		float64													Determinant=(A1*B2-A2*B1);

		if (CMathematics::EpsilonComparisonEqual(Determinant,0.0,VALUE_EPSILON)==false)
		{
			// Uses FORMULA [X=(B1C2-B2C1)/(A1B2-A2B1)=(B1C2-B2C1)/Determinant].
			float64												X=((B1*C2)-(B2*C1))/Determinant;
			// Uses FORMULA [X=(A2C1-A1C2)/(A1B2-A2B1)=(A2C1-A1C2)/Determinant].
			float64												Y=((A2*C1)-(A1*C2))/Determinant;
			CPoint2D											Point(X,Y);

			if (IsPointOnLineSegment(Point)==false)
			{
				return(false);
			}

			if (Line.IsPointOnLineSegment(Point)==false)
			{
				return(false);
			}

			return(true);
		}
		else
		{
			if (IsPointOnLineSegment(Line.GetPoint1())==true)
			{
				return(true);
			}

			if (IsPointOnLineSegment(Line.GetPoint2())==true)
			{
				return(true);
			}

			if (Line.IsPointOnLineSegment(MPoint1)==true)
			{
				return(true);
			}

			if (Line.IsPointOnLineSegment(MPoint2)==true)
			{
				return(true);
			}

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	ELine2DPointPosition CLine2D::GetPointPosition(const CPoint2D& Point) const
	{
		// Uses FORMULA [Position=float64(((X2-X1)*(Y-Y1))-((X-X1)*(Y2-Y1)))].
		float64													RawPosition=((MPoint2.GetX()-MPoint1.GetX())*(Point.GetY()-MPoint1.GetY())-(Point.GetX()-MPoint1.GetX())*(MPoint2.GetY()-MPoint1.GetY()));

		if (RawPosition>0.0)
		{
			return(ELine2DPointPosition::E_LEFT_TO_LINE);
		}
		else if (RawPosition<0.0)
		{
			return(ELine2DPointPosition::E_RIGHT_TO_LINE);
		}
		else
		{
			return(ELine2DPointPosition::E_ON_LINE);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------