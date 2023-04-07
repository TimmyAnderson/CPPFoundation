//----------------------------------------------------------------------------------------------------------------------
#include "CSchedulerTimePeriodByYear.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerTimePeriodByYear::CSchedulerTimePeriodByYear(int32 Month, int32 Day, int32 Hour, int32 Minute, int32 Second)
		: MMonth(Month), MDay(Day), MHour(Hour), MMinute(Minute), MSecond(Second)
	{
		CDateTime::CheckMonth(Month);
		CDateTime::CheckDay(Day);
		CDateTime::CheckHour(Hour);
		CDateTime::CheckMinute(Minute);
		CDateTime::CheckSecond(Second);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerTimePeriodByYear::~CSchedulerTimePeriodByYear(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSchedulerTimePeriodByYear::ToString(void) const
	{
		return(CString::Format("TIME PERIOD BY YEAR - MONTH [",MMonth,"] DAY [",MDay,"] HOUR [",MHour,"] MINUTE [",MMinute,"] SECOND [",MSecond,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerTime CSchedulerTimePeriodByYear::CalculateNextSchedulerTime(const CSchedulerTime& TimeToCheck) const
	{
		CSchedulerTime											NextSchedulerTime;

		if (CDateTime::IsValidDay(MDay,MMonth,TimeToCheck.GetDateTime().GetYear())==true)
		{
			NextSchedulerTime=CSchedulerTime(CDateTime(TimeToCheck.GetDateTime().GetYear(),MMonth,MDay,MHour,MMinute,MSecond,0));
		}
		else
		{
			NextSchedulerTime=CSchedulerTime(CDateTime(TimeToCheck.GetDateTime().GetYear(),TimeToCheck.GetDateTime().GetMonth(),TimeToCheck.GetDateTime().GetDay(),MHour,MMinute,MSecond,0));
		}

		while(true)
		{
			if (CDateTime::IsValidDay(MDay,MMonth,NextSchedulerTime.GetDateTime().GetYear())==true)
			{
				if (NextSchedulerTime>=TimeToCheck)
				{
					NextSchedulerTime=CSchedulerTime(CDateTime(NextSchedulerTime.GetDateTime().GetYear(),MMonth,MDay,MHour,MMinute,MSecond,0));

					return(NextSchedulerTime);
				}
			}

			NextSchedulerTime.AddYears(1);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int32 CSchedulerTimePeriodByYear::GetMonth(void) const noexcept
	{
		return(MMonth);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSchedulerTimePeriodByYear::GetDay(void) const noexcept
	{
		return(MDay);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSchedulerTimePeriodByYear::GetHour(void) const noexcept
	{
		return(MHour);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSchedulerTimePeriodByYear::GetMinute(void) const noexcept
	{
		return(MMinute);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSchedulerTimePeriodByYear::GetSecond(void) const noexcept
	{
		return(MSecond);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------