//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CSchedulerTimePeriod.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSchedulerTimePeriodByYear final : public CSchedulerTimePeriod
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			int32												MMonth;
			int32												MDay;
			int32												MHour;
			int32												MMinute;
			int32												MSecond;

		public:
			virtual CString ToString(void) const override;
			virtual CSchedulerTime CalculateNextSchedulerTime(const CSchedulerTime& TimeToCheck) const override;

		public:
			int32 GetMonth(void) const noexcept;
			int32 GetDay(void) const noexcept;
			int32 GetHour(void) const noexcept;
			int32 GetMinute(void) const noexcept;
			int32 GetSecond(void) const noexcept;

		public:
			CSchedulerTimePeriodByYear(int32 Month, int32 Day, int32 Hour, int32 Minute, int32 Second);
			virtual ~CSchedulerTimePeriodByYear(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSchedulerTimePeriodByYear=CSharedPointer<CSchedulerTimePeriodByYear>;
	using														CCSPSchedulerTimePeriodByYear=CSharedPointer<const CSchedulerTimePeriodByYear>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------