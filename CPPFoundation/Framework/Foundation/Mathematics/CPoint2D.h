//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Objects/CObject.h>
#include "CGeometryObject.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CPoint2D final : public CGeometryObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			float64												MX;
			float64												MY;

		public:
			bool operator==(const CPoint2D& Value) const;
			bool operator!=(const CPoint2D& Value) const;
			CPoint2D operator+(const CPoint2D& Value) const;
			CPoint2D operator-(const CPoint2D& Value) const;
			CPoint2D operator*(const CPoint2D& Value) const;
			CPoint2D operator/(const CPoint2D& Value) const;
			CPoint2D operator*(float64 Value) const;
			CPoint2D operator/(float64 Value) const;
			CPoint2D& operator+=(const CPoint2D& Value);
			CPoint2D& operator-=(const CPoint2D& Value);
			CPoint2D& operator*=(const CPoint2D& Value);
			CPoint2D& operator/=(const CPoint2D& Value);
			CPoint2D& operator*=(float64 Value);
			CPoint2D& operator/=(float64 Value);

		public:
			float64 GetX(void) const noexcept;
			void SetX(float64 Value) noexcept;
			float64 GetY(void) const noexcept;
			void SetY(float64 Value) noexcept;
			float64 Distance(const CPoint2D& Value) const;

		public:
			CPoint2D(void);
			CPoint2D(float64 X, float64 Y);
			virtual ~CPoint2D(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CPoint2DCollection=CVector<CPoint2D>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------