//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CGeometryObject.h"
#include "CPoint2D.h"
#include "CLine2D.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CCircle2D final : public CGeometryObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			// Uses FORMULA [(X-SX)*(X-SX)+(Y-SY)*(Y-SY)=R*R].
			CPoint2D											MCenter;
			float64												MRadius;

		public:
			bool operator==(const CCircle2D& Value) const;
			bool operator!=(const CCircle2D& Value) const;

		private:
			static void CheckCircle(double Radius);

		public:
			const CPoint2D& GetCenter(void) const noexcept;
			void SetCenter(const CPoint2D& Value);
			float64 GetRadius(void) const noexcept;
			void SetRadius(float64 Value);

		public:
			bool ContainsPoint(const CPoint2D& Point) const;
			bool HasLineSegmentIntersection(const CLine2D& Line) const;
			bool OverlapsCircle(const CCircle2D& Circle) const;

		public:
			CCircle2D(void);
			CCircle2D(const CPoint2D& Center, float64 Radius);
			virtual ~CCircle2D(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CCircle2DCollection=CVector<CCircle2D>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------