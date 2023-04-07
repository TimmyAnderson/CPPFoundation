//----------------------------------------------------------------------------------------------------------------------
#include "CSchedulerTimePeriodByDay.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerTimePeriodByDay::CSchedulerTimePeriodByDay(int32 Hour, int32 Minute, int32 Second)
		: MHour(Hour), MMinute(Minute), MSecond(Second)
	{
		CDateTime::CheckHour(Hour);
		CDateTime::CheckMinute(Minute);
		CDateTime::CheckSecond(Second);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerTimePeriodByDay::~CSchedulerTimePeriodByDay(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSchedulerTimePeriodByDay::ToString(void) const
	{
		return(CString::Format("TIME PERIOD BY DAY - HOUR [",MHour,"] MINUTE [",MMinute,"] SECOND [",MSecond,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerTime CSchedulerTimePeriodByDay::CalculateNextSchedulerTime(const CSchedulerTime& TimeToCheck) const
	{
		CSchedulerTime											NextSchedulerTime(CDateTime(TimeToCheck.GetDateTime().GetYear(),TimeToCheck.GetDateTime().GetMonth(),TimeToCheck.GetDateTime().GetDay(),MHour,MMinute,MSecond,0));

		if (NextSchedulerTime<TimeToCheck)
		{
			NextSchedulerTime.AddDays(1);

			return(NextSchedulerTime);
		}
		else
		{
			return(NextSchedulerTime);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int32 CSchedulerTimePeriodByDay::GetHour(void) const noexcept
	{
		return(MHour);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSchedulerTimePeriodByDay::GetMinute(void) const noexcept
	{
		return(MMinute);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSchedulerTimePeriodByDay::GetSecond(void) const noexcept
	{
		return(MSecond);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------