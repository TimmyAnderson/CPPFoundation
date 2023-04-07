//----------------------------------------------------------------------------------------------------------------------
#include "CCircle2D.h"
#include "CMathematics.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CCircle2D::CCircle2D(void)
		: MCenter(), MRadius()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CCircle2D::CCircle2D(const CPoint2D& Center, float64 Radius)
		: MCenter(Center), MRadius(Radius)
	{
		CheckCircle(Radius);
	}
//----------------------------------------------------------------------------------------------------------------------
	CCircle2D::~CCircle2D(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCircle2D::operator==(const CCircle2D& Value) const
	{
		if (MCenter==Value.MCenter && MRadius==Value.MRadius)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CCircle2D::operator!=(const CCircle2D& Value) const
	{
		return(!(*this==Value));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CCircle2D::CheckCircle(double Radius)
	{
		if (Radius<=0)
		{
			throw(CInvalidOperationException("RADIUS must have POSITIVE VALUE !"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CPoint2D& CCircle2D::GetCenter(void) const noexcept
	{
		return(MCenter);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CCircle2D::SetCenter(const CPoint2D& Value)
	{
		MCenter=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	float64 CCircle2D::GetRadius(void) const noexcept
	{
		return(MRadius);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CCircle2D::SetRadius(float64 Value)
	{
		MRadius=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCircle2D::ContainsPoint(const CPoint2D& Point) const
	{
		float64													X=Point.GetX();
		float64													Y=Point.GetY();
		float64													SX=MCenter.GetX();
		float64													SY=MCenter.GetY();
		float64													R=MRadius;
		// Uses FORMULA [LeftSide=(X-SX)*(X-SX)+(Y-SY)*(Y-SY)].
		float64													LeftSide=(X-SX)*(X-SX)+(Y-SY)*(Y-SY);
		// Uses FORMULA [RightSide=R*R].
		float64													RightSide=R*R;

		if (LeftSide<=RightSide)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CCircle2D::HasLineSegmentIntersection(const CLine2D& Line) const
	{
		float64													A=Line.GetA();
		float64													B=Line.GetB();
		float64													C=Line.GetC();
		float64													SX=MCenter.GetX();
		float64													SY=MCenter.GetY();
		float64													R=MRadius;

		if (CMathematics::EpsilonComparisonNotEqual(B,0.0,VALUE_EPSILON)==true)
		{
			// Uses FORMULA [QuadraticA=(A*A)+(B*B)].
			float64												QuadraticA=(A*A)+(B*B);
			// Uses FORMULA [QuadraticB=(2*A*B*SY)+(2*A*C)-(2*B*B*SX)].
			float64												QuadraticB=(2*A*B*SY)+(2*A*C)-(2*B*B*SX);
			// Uses FORMULA [QuadraticC=(B*B*SX*SX)+(2*B*C*SY)+(B*B*SY*SY)-(B*B*R*R)+(C*C)].
			float64												QuadraticC=(B*B*SX*SX)+(2*B*C*SY)+(B*B*SY*SY)-(B*B*R*R)+(C*C);
			// Uses FORMULA [Discriminant=(QuadraticB*QuadraticB)-(4*QuadraticA*QuadraticC)].
			float64												Discriminant=(QuadraticB*QuadraticB)-(4*QuadraticA*QuadraticC);

			if (Discriminant>=0.0)
			{
				float64											DiscriminantSQRT=CMathematics::SquareRoot(Discriminant);
				// Uses FORMULA [X1=(-QuadraticB+SQRT(Discriminant))/(2*QuadraticA)].
				float64											X1=(-QuadraticB+DiscriminantSQRT)/(2*QuadraticA);
				// Uses FORMULA [Y1=-(((A*X1)+C)/B)].
				float64											Y1=-(((A*X1)+C)/B);
				// Uses FORMULA [X2=(-QuadraticB+SQRT(Discriminant))/(2*QuadraticA)].
				float64											X2=(-QuadraticB-DiscriminantSQRT)/(2*QuadraticA);
				// Uses FORMULA [Y2=-(((A*X2)+C)/B)].
				float64											Y2=-(((A*X2)+C)/B);

				if (Line.IsPointOnLineSegment(CPoint2D(X1,Y1))==true)
				{
					return(true);
				}

				if (Line.IsPointOnLineSegment(CPoint2D(X2,Y2))==true)
				{
					return(true);
				}

				return(false);
			}
			else
			{
				return(false);
			}
		}
		else
		{
			// Uses FORMULA [QuadraticA=(A*A)+(B*B)].
			float64												QuadraticA=(A*A)+(B*B);
			// Uses FORMULA [QuadraticB=(2*A*B*SX)+(2*B*C)-(2*A*A*SY)].
			float64												QuadraticB=(2*A*B*SX)+(2*B*C)-(2*A*A*SY);
			// Uses FORMULA [QuadraticC=(A*A*SY*SY)+(2*A*C*SX)+(A*A*SX*SX)-(A*A*R*R)+(C*C)].
			float64												QuadraticC=(A*A*SY*SY)+(2*A*C*SX)+(A*A*SX*SX)-(A*A*R*R)+(C*C);
			// Uses FORMULA [Discriminant=(QuadraticB*QuadraticB)-(4*QuadraticA*QuadraticC)].
			float64												Discriminant=(QuadraticB*QuadraticB)-(4*QuadraticA*QuadraticC);

			if (Discriminant>=0.0)
			{
				float64											DiscriminantSQRT=CMathematics::SquareRoot(Discriminant);
				// Uses FORMULA [Y1=(-QuadraticB+SQRT(Discriminant))/(2*QuadraticA)].
				float64											Y1=(-QuadraticB+DiscriminantSQRT)/(2*QuadraticA);
				// Uses FORMULA [X1=-(((B*Y1)+C)/A)].
				float64											X1=-(((B*Y1)+C)/A);
				// Uses FORMULA [Y2=(-QuadraticB+SQRT(Discriminant))/(2*QuadraticA)].
				float64											Y2=(-QuadraticB-DiscriminantSQRT)/(2*QuadraticA);
				// Uses FORMULA [X2=-(((B*Y2)+C)/A)].
				float64											X2=-(((B*Y2)+C)/A);

				if (Line.IsPointOnLineSegment(CPoint2D(X1,Y1))==true)
				{
					return(true);
				}

				if (Line.IsPointOnLineSegment(CPoint2D(X2,Y2))==true)
				{
					return(true);
				}

				return(false);
			}
			else
			{
				return(false);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CCircle2D::OverlapsCircle(const CCircle2D& Circle) const
	{
		float64													DistanceOfCenters=MCenter.Distance(Circle.MCenter);
		float64													RadiusesLength=MRadius+Circle.MRadius;

		if (DistanceOfCenters<=RadiusesLength)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------