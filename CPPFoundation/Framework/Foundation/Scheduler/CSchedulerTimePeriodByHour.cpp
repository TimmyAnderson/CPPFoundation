//----------------------------------------------------------------------------------------------------------------------
#include "CSchedulerTimePeriodByHour.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerTimePeriodByHour::CSchedulerTimePeriodByHour(int32 Minute, int32 Second)
		: MMinute(Minute), MSecond(Second)
	{
		CDateTime::CheckMinute(Minute);
		CDateTime::CheckSecond(Second);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerTimePeriodByHour::~CSchedulerTimePeriodByHour(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSchedulerTimePeriodByHour::ToString(void) const
	{
		return(CString::Format("TIME PERIOD BY HOUR - MINUTE [",MMinute,"] SECOND [",MSecond,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerTime CSchedulerTimePeriodByHour::CalculateNextSchedulerTime(const CSchedulerTime& TimeToCheck) const
	{
		CSchedulerTime											NextSchedulerTime(CDateTime(TimeToCheck.GetDateTime().GetYear(),TimeToCheck.GetDateTime().GetMonth(),TimeToCheck.GetDateTime().GetDay(),TimeToCheck.GetDateTime().GetHour(),MMinute,MSecond,0));

		if (NextSchedulerTime<TimeToCheck)
		{
			NextSchedulerTime.AddHours(1);

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
	int32 CSchedulerTimePeriodByHour::GetMinute(void) const noexcept
	{
		return(MMinute);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSchedulerTimePeriodByHour::GetSecond(void) const noexcept
	{
		return(MSecond);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------