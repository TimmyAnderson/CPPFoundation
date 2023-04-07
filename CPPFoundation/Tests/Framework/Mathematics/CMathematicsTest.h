//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Testing/CTest.h>
#include <Framework/Foundation/Mathematics/CCircle2D.h>
#include <Framework/Foundation/Mathematics/CLine2D.h>
#include <Framework/Foundation/Mathematics/CPoint2D.h>
#include <Framework/Foundation/Mathematics/CPolygon2D.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CMathematicsTest final : public CTest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			struct SLineIntersectionTestData
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					CPPFoundation::Foundation::CLine2D				MLineToCheck;
					bool										MHasIntersection;

				public:
					const CPPFoundation::Foundation::CLine2D& GetLineToCheck(void) const noexcept
					{
						return(MLineToCheck);
					}

					bool GetHasIntersection(void) const noexcept
					{
						return(MHasIntersection);
					}

				public:
					SLineIntersectionTestData(const CPPFoundation::Foundation::CLine2D& LineToCheck, bool HasIntersection)
						: MLineToCheck(LineToCheck), MHasIntersection(HasIntersection)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private:
			struct SPolygonContainsPointTestData
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					CPPFoundation::Foundation::CPoint2D			MPointToCheck;
					bool										MHasIntersection;

				public:
					const CPPFoundation::Foundation::CPoint2D& GetPointToCheck(void) const noexcept
					{
						return(MPointToCheck);
					}

					bool GetHasIntersection(void) const noexcept
					{
						return(MHasIntersection);
					}

				public:
					SPolygonContainsPointTestData(const CPPFoundation::Foundation::CPoint2D& PointToCheck, bool HasIntersection)
						: MPointToCheck(PointToCheck), MHasIntersection(HasIntersection)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private:
			bool TestLine1(void);
			bool TestLine2(void);
			bool TestCircle(void);
			bool TestPolygon1(void);
			bool TestPolygon2(void);

		public:
			virtual bool ExecuteTest(void) override;

		public:
			CMathematicsTest(CPPFoundation::Foundation::CLogWriter& LogWriter, const CPPFoundation::Foundation::CLogCategory& LogCategoryTest);
			virtual ~CMathematicsTest(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------