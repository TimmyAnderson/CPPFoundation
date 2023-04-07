//----------------------------------------------------------------------------------------------------------------------
#include "CSchedulerTimePeriodByWeekDay.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerTimePeriodByWeekDay::CSchedulerTimePeriodByWeekDay(EDayOfWeek DayOfWeek, int32 Hour, int32 Minute, int32 Second)
		: MDayOfWeek(DayOfWeek), MHour(Hour), MMinute(Minute), MSecond(Second)
	{
		CDateTime::CheckDayOfWeek(DayOfWeek);
		CDateTime::CheckHour(Hour);
		CDateTime::CheckMinute(Minute);
		CDateTime::CheckSecond(Second);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerTimePeriodByWeekDay::~CSchedulerTimePeriodByWeekDay(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSchedulerTimePeriodByWeekDay::ToString(void) const
	{
		return(CString::Format("TIME PERIOD BY WEEK DAY - DAY OF WEEK [",MDayOfWeek,"] HOUR [",MHour,"] MINUTE [",MMinute,"] SECOND [",MSecond,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerTime CSchedulerTimePeriodByWeekDay::CalculateNextSchedulerTime(const CSchedulerTime& TimeToCheck) const
	{
		CSchedulerTime											NextSchedulerTime(CDateTime(TimeToCheck.GetDateTime().GetYear(),TimeToCheck.GetDateTime().GetMonth(),TimeToCheck.GetDateTime().GetDay(),MHour,MMinute,MSecond,0));
		int32													DayOfWeek=static_cast<int32>(MDayOfWeek);
		int32													NextSchedulerTimeDayOfWeek=static_cast<int32>(NextSchedulerTime.GetDateTime().GetDayOfWeek());
		int32													NumberOfDaysPerWeek=static_cast<int32>(CDateTime::GetNumberOfDaysPerWeek());
		int32													DayDifference=DayOfWeek-NextSchedulerTimeDayOfWeek;

		if (DayDifference<0)
		{
			DayDifference+=NumberOfDaysPerWeek;
		}

		NextSchedulerTime.AddDays(DayDifference);

		if (NextSchedulerTime<TimeToCheck)
		{
			NextSchedulerTime.AddDays(NumberOfDaysPerWeek);

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
	EDayOfWeek CSchedulerTimePeriodByWeekDay::GetDayOfWeek(void) const noexcept
	{
		return(MDayOfWeek);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSchedulerTimePeriodByWeekDay::GetHour(void) const noexcept
	{
		return(MHour);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSchedulerTimePeriodByWeekDay::GetMinute(void) const noexcept
	{
		return(MMinute);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSchedulerTimePeriodByWeekDay::GetSecond(void) const noexcept
	{
		return(MSecond);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------