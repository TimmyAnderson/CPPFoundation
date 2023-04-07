//----------------------------------------------------------------------------------------------------------------------
#include "CPolygon2D.h"
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CPolygon2D::CPolygon2D(void)
		: MLines()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CPolygon2D::CPolygon2D(const CLine2DCollection& Lines)
		: MLines(Lines)
	{
		CheckPolygon(Lines);
	}
//----------------------------------------------------------------------------------------------------------------------
	CPolygon2D::CPolygon2D(CLine2DCollection&& Lines)
		: MLines(FUNCTION_MOVE(Lines))
	{
		CheckPolygon(Lines);
	}
//----------------------------------------------------------------------------------------------------------------------
	CPolygon2D::CPolygon2D(const CPolygon2D& Other)
		: MLines(Other.MLines)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CPolygon2D::CPolygon2D(CPolygon2D&& Other) noexcept
		: MLines(FUNCTION_MOVE(Other.MLines))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CPolygon2D::~CPolygon2D(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CPolygon2D& CPolygon2D::operator=(const CPolygon2D& Other)
	{
		MLines=Other.MLines;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CPolygon2D& CPolygon2D::operator=(CPolygon2D&& Other) noexcept
	{
		MLines=FUNCTION_MOVE(Other.MLines);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CLine2D& CPolygon2D::operator[](Size Index) const
	{
		return(MLines[Index]);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CPolygon2D::operator==(const CPolygon2D& Value) const
	{
		if (MLines.GetLength()!=Value.GetLines().GetLength())
		{
			return(false);
		}

		for(const CLine2D& Line1 : MLines)
		{
			for(const CLine2D& Line2 : Value.GetLines())
			{
				if (Line1!=Line2)
				{
					return(false);
				}
			}
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CPolygon2D::operator!=(const CPolygon2D& Value) const
	{
		return(!(*this==Value));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CPolygon2D::CheckPolygon(const CLine2DCollection& Lines)
	{
		if (Lines.GetLength()<3)
		{
			throw(CInvalidOperationException("POLYGON must have at least 3 LINES !"));
		}

		if (Lines[0].GetPoint1()!=Lines[Lines.GetLength()-1].GetPoint2())
		{
			throw(CInvalidOperationException("POLYGON must be CLOSED ! FIRST POINT of FIRST LINE and SECOND POINT LAST LINE must MATCH !"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CPolygon2D::HasIntersection(const CPolygon2D& Polygon) const
	{
		for(const CLine2D& Line1 : MLines)
		{
			for(const CLine2D& Line2 : Polygon.MLines)
			{
				if (Line1.HasLineSegmentIntersection(Line2)==true)
				{
					return(true);
				}
			}
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CLine2DCollection& CPolygon2D::GetLines(void) const noexcept
	{
		return(MLines);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CPolygon2D::ContainsPoint(const CPoint2D& Point) const
	{
		bool													ContainsPoint=false;
		int32													WindingNumber=0;

		// ALGORITHM MUST NOT USE EPSILON COMPARISIONS.

		for(const CLine2D& Line : MLines)
		{
			// Y>=Y1.
			if (Point.GetY()>=Line.GetPoint1().GetY())
			{
				// Y<Y2.
				if (Point.GetY()<Line.GetPoint2().GetY())
				{
					// Y lies INSIDE of <Y1,Y2>.

					ELine2DPointPosition						PointPosition=Line.GetPointPosition(Point);

					// POINT must be LEFT to LINE SEGMENT.
					if (PointPosition==ELine2DPointPosition::E_LEFT_TO_LINE)
					{
						 WindingNumber++;
					}
				}
			}
			// Y<Y1.
			else
			{
				// Y>=Y2.
				if (Point.GetY()>=Line.GetPoint2().GetY())
				{
					// Y lies INSIDE of <Y2,Y1>.

					ELine2DPointPosition						PointPosition=Line.GetPointPosition(Point);

					// POINT must be RIGHT to LINE SEGMENT.
					if (PointPosition==ELine2DPointPosition::E_RIGHT_TO_LINE)
					{
						 WindingNumber--;
					}
				}
			}
		}

		if (WindingNumber!=0)
		{
			ContainsPoint=true;
		}

		if (ContainsPoint==false)
		{
			for(const CLine2D& Line : MLines)
			{
				if (Line.IsPointOnLineSegment(Point)==true)
				{
					return(true);
				}
			}

			return(false);
		}
		else
		{
			return(true);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CPolygon2D::OverlapsCircle(const CCircle2D& Circle) const
	{
		// Check if any LINE SEGMENT of the POLYGON has an INTERSECTION with the CIRCLE.
		for(const CLine2D& Line : MLines)
		{
			if (Circle.HasLineSegmentIntersection(Line)==true)
			{
				return(true);
			}
		}

		// If CIRCLE is completely inside of the POLYGON, check if CIRCLE CENTER is inside of the POLYGON.
		if (ContainsPoint(Circle.GetCenter())==true)
		{
			return(true);
		}

		// If POLYGON is completely inside of the CIRCLE, check if any POINT of the POLYGON is inside of the CIRCLE.
		if (Circle.ContainsPoint(MLines[0].GetPoint1())==true)
		{
			return(true);
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CPolygon2D::OverlapsPolygon(const CPolygon2D& Polygon) const
	{
		// Check if POLYGON 1 has INTERSECTION with POLYGON 2.
		if (HasIntersection(Polygon)==true)
		{
			return(true);
		}

		// Check if POLYGON 2 has INTERSECTION with POLYGON 1.
		if (Polygon.HasIntersection(*this)==true)
		{
			return(true);
		}

		// INTERSECTION not FOUND. Check if POLYGON 1 doesn't completely lies withing POLYGON 2.
		if (ContainsPoint(Polygon[0].GetPoint1())==true)
		{
			return(true);
		}

		// INTERSECTION not FOUND. Check if POLYGON 1 doesn't completely lies withing POLYGON 2.
		if (Polygon.ContainsPoint(MLines[0].GetPoint1())==true)
		{
			return(true);
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------