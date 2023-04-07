//----------------------------------------------------------------------------------------------------------------------
#include "CSchedulerTimePeriodByMonth.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerTimePeriodByMonth::CSchedulerTimePeriodByMonth(int32 Day, int32 Hour, int32 Minute, int32 Second)
		: MDay(Day), MHour(Hour), MMinute(Minute), MSecond(Second)
	{
		CDateTime::CheckDay(Day);
		CDateTime::CheckHour(Hour);
		CDateTime::CheckMinute(Minute);
		CDateTime::CheckSecond(Second);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerTimePeriodByMonth::~CSchedulerTimePeriodByMonth(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSchedulerTimePeriodByMonth::ToString(void) const
	{
		return(CString::Format("TIME PERIOD BY MONTH - DAY [",MDay,"] HOUR [",MHour,"] MINUTE [",MMinute,"] SECOND [",MSecond,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerTime CSchedulerTimePeriodByMonth::CalculateNextSchedulerTime(const CSchedulerTime& TimeToCheck) const
	{
		CSchedulerTime											NextSchedulerTime;

		if (CDateTime::IsValidDay(MDay,TimeToCheck.GetDateTime().GetMonth(),TimeToCheck.GetDateTime().GetYear())==true)
		{
			NextSchedulerTime=CSchedulerTime(CDateTime(TimeToCheck.GetDateTime().GetYear(),TimeToCheck.GetDateTime().GetMonth(),MDay,MHour,MMinute,MSecond,0));
		}
		else
		{
			NextSchedulerTime=CSchedulerTime(CDateTime(TimeToCheck.GetDateTime().GetYear(),TimeToCheck.GetDateTime().GetMonth(),TimeToCheck.GetDateTime().GetDay(),MHour,MMinute,MSecond,0));
		}

		while(true)
		{
			if (CDateTime::IsValidDay(MDay,NextSchedulerTime.GetDateTime().GetMonth(),NextSchedulerTime.GetDateTime().GetYear())==true)
			{
				if (NextSchedulerTime>=TimeToCheck)
				{
					NextSchedulerTime=CSchedulerTime(CDateTime(NextSchedulerTime.GetDateTime().GetYear(),NextSchedulerTime.GetDateTime().GetMonth(),MDay,MHour,MMinute,MSecond,0));

					return(NextSchedulerTime);
				}
			}

			NextSchedulerTime.AddMonths(1);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int32 CSchedulerTimePeriodByMonth::GetDay(void) const noexcept
	{
		return(MDay);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSchedulerTimePeriodByMonth::GetHour(void) const noexcept
	{
		return(MHour);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSchedulerTimePeriodByMonth::GetMinute(void) const noexcept
	{
		return(MMinute);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSchedulerTimePeriodByMonth::GetSecond(void) const noexcept
	{
		return(MSecond);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------