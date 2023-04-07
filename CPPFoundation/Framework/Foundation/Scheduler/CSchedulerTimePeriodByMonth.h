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
	class CSchedulerTimePeriodByMonth final : public CSchedulerTimePeriod
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			int32												MDay;
			int32												MHour;
			int32												MMinute;
			int32												MSecond;

		public:
			virtual CString ToString(void) const override;
			virtual CSchedulerTime CalculateNextSchedulerTime(const CSchedulerTime& TimeToCheck) const override;

		public:
			int32 GetDay(void) const noexcept;
			int32 GetHour(void) const noexcept;
			int32 GetMinute(void) const noexcept;
			int32 GetSecond(void) const noexcept;

		public:
			CSchedulerTimePeriodByMonth(int32 Day, int32 Hour, int32 Minute, int32 Second);
			virtual ~CSchedulerTimePeriodByMonth(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSchedulerTimePeriodByMonth=CSharedPointer<CSchedulerTimePeriodByMonth>;
	using														CCSPSchedulerTimePeriodByMonth=CSharedPointer<const CSchedulerTimePeriodByMonth>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------