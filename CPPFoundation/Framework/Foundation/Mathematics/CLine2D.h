//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CGeometryObject.h"
#include "CPoint2D.h"
#include "ELine2DPointPosition.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CLine2D final : public CGeometryObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CPoint2D											MPoint1;
			CPoint2D											MPoint2;
			// Uses FORMULA [AX+BY+C=0].
			float64												MA;
			float64												MB;
			float64												MC;

		public:
			bool operator==(const CLine2D& Value) const;
			bool operator!=(const CLine2D& Value) const;

		private:
			static void CheckLine(const CPoint2D& Point1, const CPoint2D& Point2);
			static float64 CalculateMin(float64 Value1, float64 Value2);
			static float64 CalculateMax(float64 Value1, float64 Value2);

		private:
			void CalculateABC(void);

		public:
			const CPoint2D& GetPoint1(void) const noexcept;
			void SetPoint1(const CPoint2D& Value);
			const CPoint2D& GetPoint2(void) const noexcept;
			void SetPoint2(const CPoint2D& Value);
			float64 GetA(void) const noexcept;
			float64 GetB(void) const noexcept;
			float64 GetC(void) const noexcept;

		public:
			float64 Width(void) const;
			float64 Height(void) const;
			float64 Length(void) const;
			float64 Distance(const CPoint2D& Point) const;
			bool IsPointOnLineSegment(const CPoint2D& Point) const;
			bool HasLineSegmentIntersection(const CLine2D& Line) const;
			ELine2DPointPosition GetPointPosition(const CPoint2D& Point) const;

		public:
			CLine2D(void);
			CLine2D(const CPoint2D& Point1, const CPoint2D& Point2);
			virtual ~CLine2D(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CLine2DCollection=CVector<CLine2D>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------