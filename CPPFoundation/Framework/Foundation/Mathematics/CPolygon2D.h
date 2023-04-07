//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CGeometryObject.h"
#include "CPoint2D.h"
#include "CCircle2D.h"
#include "CLine2D.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CPolygon2D final : public CGeometryObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CLine2DCollection									MLines;

		public:
			CPolygon2D& operator=(const CPolygon2D& Other);
			CPolygon2D& operator=(CPolygon2D&& Other) noexcept;

		public:
			const CLine2D& operator[](Size Index) const;
			bool operator==(const CPolygon2D& Value) const;
			bool operator!=(const CPolygon2D& Value) const;

		private:
			static void CheckPolygon(const CLine2DCollection& Lines);

		private:
			bool HasIntersection(const CPolygon2D& Polygon) const;

		public:
			const CLine2DCollection& GetLines(void) const noexcept;

		public:
			bool ContainsPoint(const CPoint2D& Point) const;
			bool OverlapsCircle(const CCircle2D& Circle) const;
			bool OverlapsPolygon(const CPolygon2D& Polygon) const;

		public:
			CPolygon2D(void);
			CPolygon2D(const CLine2DCollection& Lines);
			CPolygon2D(CLine2DCollection&& Lines);
			CPolygon2D(const CPolygon2D& Other);
			CPolygon2D(CPolygon2D&& Other) noexcept;
			virtual ~CPolygon2D(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------