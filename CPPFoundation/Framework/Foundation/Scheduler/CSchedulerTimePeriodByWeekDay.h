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
	class CSchedulerTimePeriodByWeekDay final : public CSchedulerTimePeriod
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			EDayOfWeek											MDayOfWeek;
			int32												MHour;
			int32												MMinute;
			int32												MSecond;

		public:
			virtual CString ToString(void) const override;
			virtual CSchedulerTime CalculateNextSchedulerTime(const CSchedulerTime& TimeToCheck) const override;

		public:
			EDayOfWeek GetDayOfWeek(void) const noexcept;
			int32 GetHour(void) const noexcept;
			int32 GetMinute(void) const noexcept;
			int32 GetSecond(void) const noexcept;

		public:
			CSchedulerTimePeriodByWeekDay(EDayOfWeek DayOfWeek, int32 Hour, int32 Minute, int32 Second);
			virtual ~CSchedulerTimePeriodByWeekDay(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSchedulerTimePeriodByWeekDay=CSharedPointer<CSchedulerTimePeriodByWeekDay>;
	using														CCSPSchedulerTimePeriodByWeekDay=CSharedPointer<const CSchedulerTimePeriodByWeekDay>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------