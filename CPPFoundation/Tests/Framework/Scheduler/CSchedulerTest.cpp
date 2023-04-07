//----------------------------------------------------------------------------------------------------------------------
#include "CSchedulerTest.h"
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Console/CConsoleHelper.h>
#include <Framework/Foundation/Types/CMethod.h>
#include <Framework/Foundation/Scheduler/CSchedulerTimePeriodByDay.h>
#include <Framework/Foundation/Scheduler/CSchedulerTimePeriodByHour.h>
#include <Framework/Foundation/Scheduler/CSchedulerTimePeriodByMinute.h>
#include <Framework/Foundation/Scheduler/CSchedulerTimePeriodByMonth.h>
#include <Framework/Foundation/Scheduler/CSchedulerTimePeriodByWeekDay.h>
#include <Framework/Foundation/Scheduler/CSchedulerTimePeriodByYear.h>
#include <Framework/Foundation/Scheduler/CSchedulerItem.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace std;
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerTest::CSchedulerTest(CLogWriter& LogWriter, const CLogCategory& LogCategoryTest)
		: CTest(LogWriter,LogCategoryTest,"SCHEDULER TEST")
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerTest::~CSchedulerTest(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CSchedulerTest::TestSchedulerTimePeriod(void)
	{
		CVector<SSchedulerTimePeriodData>						SchedulerTimePeriodDataCollection;

		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMinute(30)),CSchedulerTime(CDateTime(2016,10,13,7,25,25,0)),CSchedulerTime(CDateTime(2016,10,13,7,25,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMinute(30)),CSchedulerTime(CDateTime(2016,10,13,7,25,35,0)),CSchedulerTime(CDateTime(2016,10,13,7,26,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMinute(30)),CSchedulerTime(CDateTime(2016,10,13,7,25,30,0)),CSchedulerTime(CDateTime(2016,10,13,7,25,30,0))));

		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByHour(15,30)),CSchedulerTime(CDateTime(2016,10,13,7,5,10,0)),CSchedulerTime(CDateTime(2016,10,13,7,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByHour(15,30)),CSchedulerTime(CDateTime(2016,10,13,7,25,10,0)),CSchedulerTime(CDateTime(2016,10,13,8,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByHour(15,30)),CSchedulerTime(CDateTime(2016,10,13,7,15,30,0)),CSchedulerTime(CDateTime(2016,10,13,7,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByHour(15,30)),CSchedulerTime(CDateTime(2016,10,13,7,15,29,0)),CSchedulerTime(CDateTime(2016,10,13,7,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByHour(15,30)),CSchedulerTime(CDateTime(2016,10,13,7,15,31,0)),CSchedulerTime(CDateTime(2016,10,13,8,15,30,0))));

		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByDay(14,15,30)),CSchedulerTime(CDateTime(2016,10,13,14,15,30,0)),CSchedulerTime(CDateTime(2016,10,13,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByDay(14,15,30)),CSchedulerTime(CDateTime(2016,10,13,14,15,29,0)),CSchedulerTime(CDateTime(2016,10,13,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByDay(14,15,30)),CSchedulerTime(CDateTime(2016,10,13,14,14,30,0)),CSchedulerTime(CDateTime(2016,10,13,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByDay(14,15,30)),CSchedulerTime(CDateTime(2016,10,13,13,15,30,0)),CSchedulerTime(CDateTime(2016,10,13,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByDay(14,15,30)),CSchedulerTime(CDateTime(2016,10,13,14,15,31,0)),CSchedulerTime(CDateTime(2016,10,14,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByDay(14,15,30)),CSchedulerTime(CDateTime(2016,10,13,14,16,30,0)),CSchedulerTime(CDateTime(2016,10,14,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByDay(14,15,30)),CSchedulerTime(CDateTime(2016,10,13,15,15,30,0)),CSchedulerTime(CDateTime(2016,10,14,14,15,30,0))));

		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByWeekDay(EDayOfWeek::E_FRIDAY,14,15,30)),CSchedulerTime(CDateTime(2016,11,4,14,15,30,0)),CSchedulerTime(CDateTime(2016,11,4,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByWeekDay(EDayOfWeek::E_FRIDAY,14,15,30)),CSchedulerTime(CDateTime(2016,11,4,14,15,29,0)),CSchedulerTime(CDateTime(2016,11,4,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByWeekDay(EDayOfWeek::E_FRIDAY,14,15,30)),CSchedulerTime(CDateTime(2016,11,4,14,14,30,0)),CSchedulerTime(CDateTime(2016,11,4,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByWeekDay(EDayOfWeek::E_FRIDAY,14,15,30)),CSchedulerTime(CDateTime(2016,11,4,13,15,30,0)),CSchedulerTime(CDateTime(2016,11,4,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByWeekDay(EDayOfWeek::E_FRIDAY,14,15,30)),CSchedulerTime(CDateTime(2016,11,4,10,15,30,0)),CSchedulerTime(CDateTime(2016,11,4,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByWeekDay(EDayOfWeek::E_FRIDAY,14,15,30)),CSchedulerTime(CDateTime(2016,10,29,10,15,30,0)),CSchedulerTime(CDateTime(2016,11,4,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByWeekDay(EDayOfWeek::E_FRIDAY,14,15,30)),CSchedulerTime(CDateTime(2016,10,28,14,15,31,0)),CSchedulerTime(CDateTime(2016,11,4,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByWeekDay(EDayOfWeek::E_FRIDAY,14,15,30)),CSchedulerTime(CDateTime(2016,10,28,14,16,30,0)),CSchedulerTime(CDateTime(2016,11,4,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByWeekDay(EDayOfWeek::E_FRIDAY,14,15,30)),CSchedulerTime(CDateTime(2016,10,28,15,15,30,0)),CSchedulerTime(CDateTime(2016,11,4,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByWeekDay(EDayOfWeek::E_FRIDAY,14,15,30)),CSchedulerTime(CDateTime(2016,11,4,14,15,31,0)),CSchedulerTime(CDateTime(2016,11,11,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByWeekDay(EDayOfWeek::E_FRIDAY,14,15,30)),CSchedulerTime(CDateTime(2016,11,4,14,16,30,0)),CSchedulerTime(CDateTime(2016,11,11,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByWeekDay(EDayOfWeek::E_FRIDAY,14,15,30)),CSchedulerTime(CDateTime(2016,11,4,15,15,30,0)),CSchedulerTime(CDateTime(2016,11,11,14,15,30,0))));

		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMonth(5,14,15,30)),CSchedulerTime(CDateTime(2016,11,5,14,15,30,0)),CSchedulerTime(CDateTime(2016,11,5,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMonth(5,14,15,30)),CSchedulerTime(CDateTime(2016,11,5,14,15,29,0)),CSchedulerTime(CDateTime(2016,11,5,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMonth(5,14,15,30)),CSchedulerTime(CDateTime(2016,11,5,14,15,29,0)),CSchedulerTime(CDateTime(2016,11,5,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMonth(5,14,15,30)),CSchedulerTime(CDateTime(2016,11,5,14,14,30,0)),CSchedulerTime(CDateTime(2016,11,5,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMonth(5,14,15,30)),CSchedulerTime(CDateTime(2016,11,5,13,15,30,0)),CSchedulerTime(CDateTime(2016,11,5,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMonth(5,14,15,30)),CSchedulerTime(CDateTime(2016,11,4,13,15,30,0)),CSchedulerTime(CDateTime(2016,11,5,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMonth(5,14,15,30)),CSchedulerTime(CDateTime(2016,10,25,13,15,30,0)),CSchedulerTime(CDateTime(2016,11,5,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMonth(5,14,15,30)),CSchedulerTime(CDateTime(2016,10,5,14,15,31,0)),CSchedulerTime(CDateTime(2016,11,5,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMonth(5,14,15,30)),CSchedulerTime(CDateTime(2016,10,5,14,16,30,0)),CSchedulerTime(CDateTime(2016,11,5,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMonth(5,14,15,30)),CSchedulerTime(CDateTime(2016,10,5,15,15,30,0)),CSchedulerTime(CDateTime(2016,11,5,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMonth(5,14,15,30)),CSchedulerTime(CDateTime(2016,11,5,14,15,31,0)),CSchedulerTime(CDateTime(2016,12,5,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMonth(5,14,15,30)),CSchedulerTime(CDateTime(2016,12,5,14,15,31,0)),CSchedulerTime(CDateTime(2017,1,5,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMonth(31,14,15,30)),CSchedulerTime(CDateTime(2016,12,31,14,15,30,0)),CSchedulerTime(CDateTime(2016,12,31,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMonth(31,14,15,30)),CSchedulerTime(CDateTime(2016,12,31,14,15,31,0)),CSchedulerTime(CDateTime(2017,1,31,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMonth(31,14,15,30)),CSchedulerTime(CDateTime(2017,1,31,14,15,31,0)),CSchedulerTime(CDateTime(2017,3,31,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMonth(31,14,15,30)),CSchedulerTime(CDateTime(2017,2,25,14,15,30,0)),CSchedulerTime(CDateTime(2017,3,31,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMonth(29,14,15,30)),CSchedulerTime(CDateTime(2016,2,20,14,15,30,0)),CSchedulerTime(CDateTime(2016,2,29,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMonth(29,14,15,30)),CSchedulerTime(CDateTime(2016,2,20,14,15,30,0)),CSchedulerTime(CDateTime(2016,2,29,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMonth(29,14,15,30)),CSchedulerTime(CDateTime(2015,2,20,14,15,30,0)),CSchedulerTime(CDateTime(2015,3,29,14,15,30,0))));

		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByYear(7,5,14,15,30)),CSchedulerTime(CDateTime(2016,7,5,14,15,30,0)),CSchedulerTime(CDateTime(2016,7,5,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByYear(7,5,14,15,30)),CSchedulerTime(CDateTime(2016,7,5,14,15,19,0)),CSchedulerTime(CDateTime(2016,7,5,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByYear(7,5,14,15,30)),CSchedulerTime(CDateTime(2016,7,5,14,14,30,0)),CSchedulerTime(CDateTime(2016,7,5,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByYear(7,5,14,15,30)),CSchedulerTime(CDateTime(2016,7,5,13,15,30,0)),CSchedulerTime(CDateTime(2016,7,5,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByYear(7,5,14,15,30)),CSchedulerTime(CDateTime(2016,7,5,14,15,31,0)),CSchedulerTime(CDateTime(2017,7,5,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByYear(12,31,14,15,30)),CSchedulerTime(CDateTime(2016,12,31,14,15,31,0)),CSchedulerTime(CDateTime(2017,12,31,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByYear(2,29,14,15,30)),CSchedulerTime(CDateTime(2015,12,31,14,15,31,0)),CSchedulerTime(CDateTime(2016,2,29,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByYear(2,29,14,15,30)),CSchedulerTime(CDateTime(2016,2,29,14,15,31,0)),CSchedulerTime(CDateTime(2020,2,29,14,15,30,0))));
		SchedulerTimePeriodDataCollection.Add(SSchedulerTimePeriodData(CSPSchedulerTimePeriod(new CSchedulerTimePeriodByYear(2,29,14,15,30)),CSchedulerTime(CDateTime(2016,2,28,14,15,31,0)),CSchedulerTime(CDateTime(2016,2,29,14,15,30,0))));

		Size													TestNumber=0;

		for(const SSchedulerTimePeriodData& SchedulerTimePeriodData : SchedulerTimePeriodDataCollection)
		{
			TestNumber++;

			CSchedulerTime										NextSchedulerTime=SchedulerTimePeriodData.GetTimePeriod()->CalculateNextSchedulerTime(SchedulerTimePeriodData.GetTimeToCheck());

			if (SchedulerTimePeriodData.GetExpectedTime()!=NextSchedulerTime)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to CALCULATE CORRECT SCHEDULER TIME ! EXPECTED TIME [",SchedulerTimePeriodData.GetExpectedTime().GetDateTime().ToString(),"] CALCULATED TIME [",NextSchedulerTime.GetDateTime().ToString(),"] !\n"));
				return(false);
			}
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSchedulerTest::TestSchedulerValidityPeriod(void)
	{
		Size													TestNumber=0;
		CSchedulerItem											Item1(CSchedulerItemID("ITEM 1"),CSchedulerTimeInterval(CNullable<CSchedulerTime>(CDateTime(2016,11,9,10,0,0,0)),CNullable<CSchedulerTime>(CDateTime(2016,11,9,11,0,0,0))),CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMinute(10)));
		CTimeout												InfiniteTimeout;
		bool													ExecuteSchedulerItem=false;

		++TestNumber;

		if (Item1.HasNextSchedulerTimeExpired(CSchedulerTime(CDateTime(2016,11,9,10,15,0,0)),InfiniteTimeout,ExecuteSchedulerItem)==false || ExecuteSchedulerItem==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to DETECT that EXECUTION TIME is VALID !\n"));
			return(false);
		}

		++TestNumber;

		Item1.RecalculateNextSchedulerTime(CSchedulerTime(CDateTime(2016,11,9,10,15,0,0)));

		if (Item1.GetNextSchedulerItemExecutionTime()!=CSchedulerTime(CDateTime(2016,11,9,10,15,10,0)))
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to CALCULATE CORRECT EXECUTION TIME !\n"));
			return(false);
		}

		++TestNumber;

		if (Item1.HasNextSchedulerTimeExpired(CSchedulerTime(CDateTime(2016,11,9,10,18,15,0)),InfiniteTimeout,ExecuteSchedulerItem)==false || ExecuteSchedulerItem==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to DETECT that EXECUTION TIME is VALID !\n"));
			return(false);
		}

		++TestNumber;

		Item1.RecalculateNextSchedulerTime(CSchedulerTime(CDateTime(2016,11,9,10,18,15,0)));

		if (Item1.GetNextSchedulerItemExecutionTime()!=CSchedulerTime(CDateTime(2016,11,9,10,19,10,0)))
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to CALCULATE CORRECT EXECUTION TIME !\n"));
			return(false);
		}

		CSchedulerItem											Item2(CSchedulerItemID("ITEM 2"),CSchedulerTimeInterval(CNullable<CSchedulerTime>(CDateTime(2016,11,9,10,0,0,0)),CNullable<CSchedulerTime>(CDateTime(2016,11,9,11,0,0,0))),CSPSchedulerTimePeriod(new CSchedulerTimePeriodByHour(10,30)));

		++TestNumber;

		if (Item2.HasNextSchedulerTimeExpired(CSchedulerTime(CDateTime(2016,11,9,10,15,0,0)),InfiniteTimeout,ExecuteSchedulerItem)==false || ExecuteSchedulerItem==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to DETECT that EXECUTION TIME is VALID !\n"));
			return(false);
		}
		
		CSchedulerItem											Item3(CSchedulerItemID("ITEM 3"),CSchedulerTimeInterval(CNullable<CSchedulerTime>(CDateTime(2016,11,9,10,0,0,0)),CNullable<CSchedulerTime>(CDateTime(2016,11,9,11,0,0,0))),CSPSchedulerTimePeriod(new CSchedulerTimePeriodByHour(10,30)));

		++TestNumber;

		if (Item3.HasNextSchedulerTimeExpired(CSchedulerTime(CDateTime(2016,11,9,10,5,55,0)),InfiniteTimeout,ExecuteSchedulerItem)==false || ExecuteSchedulerItem==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to DETECT that EXECUTION TIME INTERVAL is VALID !\n"));
			return(false);
		}

		++TestNumber;

		Item3.RecalculateNextSchedulerTime(CSchedulerTime(CDateTime(2016,11,9,10,5,55,0)));

		if (Item3.GetNextSchedulerItemExecutionTime()!=CSchedulerTime(CDateTime(2016,11,9,10,10,30,0)))
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to CALCULATE CORRECT EXECUTION TIME !\n"));
			return(false);
		}

		CSchedulerItem											Item4(CSchedulerItemID("ITEM 4"),CSchedulerTimeInterval(CNullable<CSchedulerTime>(),CNullable<CSchedulerTime>(CDateTime(2016,11,9,11,0,0,0))),CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMinute(30)));

		++TestNumber;

		if (Item4.HasNextSchedulerTimeExpired(CSchedulerTime(CDateTime(2010,1,1,10,15,0,0)),InfiniteTimeout,ExecuteSchedulerItem)==false || ExecuteSchedulerItem==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to DETECT that EXECUTION TIME is VALID !\n"));
			return(false);
		}

		++TestNumber;

		Item4.RecalculateNextSchedulerTime(CSchedulerTime(CDateTime(2010,1,1,10,15,0,0)));

		if (Item4.GetNextSchedulerItemExecutionTime()!=CSchedulerTime(CDateTime(2010,1,1,10,15,30,0)))
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to CALCULATE CORRECT EXECUTION TIME !\n"));
			return(false);
		}

		++TestNumber;

		if (Item4.HasNextSchedulerTimeExpired(CSchedulerTime(CDateTime(2016,11,9,11,0,0,0)),InfiniteTimeout,ExecuteSchedulerItem)==false || ExecuteSchedulerItem==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to DETECT that EXECUTION TIME is VALID !\n"));
			return(false);
		}

		++TestNumber;

		Item4.RecalculateNextSchedulerTime(CSchedulerTime(CDateTime(2016,11,9,11,0,0,0)));

		if (Item4.HasNextSchedulerTimeExpired(CSchedulerTime(CDateTime(2016,11,9,11,0,0,0)),InfiniteTimeout,ExecuteSchedulerItem)==true || ExecuteSchedulerItem==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," INCORRECTLY DETECTED that EXECUTION TIME is VALID !\n"));
			return(false);
		}

		CSchedulerItem											Item5(CSchedulerItemID("ITEM 5"),CSchedulerTimeInterval(CNullable<CSchedulerTime>(CDateTime(2016,11,9,10,0,0,0)),CNullable<CSchedulerTime>()),CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMinute(10)));

		++TestNumber;

		if (Item5.HasNextSchedulerTimeExpired(CSchedulerTime(CDateTime(2016,11,10,10,0,0,0)),InfiniteTimeout,ExecuteSchedulerItem)==false || ExecuteSchedulerItem==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to DETECT that EXECUTION TIME is VALID !\n"));
			return(false);
		}

		++TestNumber;

		Item5.RecalculateNextSchedulerTime(CSchedulerTime(CDateTime(2016,11,10,10,0,0,0)));

		if (Item5.GetNextSchedulerItemExecutionTime()!=CSchedulerTime(CDateTime(2016,11,10,10,0,10,0)))
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to CALCULATE CORRECT EXECUTION TIME !\n"));
			return(false);
		}

		++TestNumber;

		if (Item5.HasNextSchedulerTimeExpired(CSchedulerTime(CDateTime(2016,11,8,10,0,0,0)),InfiniteTimeout,ExecuteSchedulerItem)==true || ExecuteSchedulerItem==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," INCORRECTLY DETECTED that EXECUTION TIME is VALID !\n"));
			return(false);
		}

		CSchedulerItem											Item6(CSchedulerItemID("ITEM 6"),CSchedulerTimeInterval(CNullable<CSchedulerTime>(),CNullable<CSchedulerTime>()),CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMinute(10)));

		++TestNumber;

		if (Item6.HasNextSchedulerTimeExpired(CSchedulerTime(CDateTime(2016,11,10,10,0,0,0)),InfiniteTimeout,ExecuteSchedulerItem)==false || ExecuteSchedulerItem==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to DETECT that EXECUTION TIME is VALID !\n"));
			return(false);
		}

		++TestNumber;

		Item6.RecalculateNextSchedulerTime(CSchedulerTime(CDateTime(2016,11,10,10,0,0,0)));

		if (Item6.GetNextSchedulerItemExecutionTime()!=CSchedulerTime(CDateTime(2016,11,10,10,0,10,0)))
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to CALCULATE CORRECT EXECUTION TIME !\n"));
			return(false);
		}

		++TestNumber;

		if (Item6.GetTimeout(CSchedulerTime(CDateTime(2016,11,10,10,0,0,0)),CTimeout(100*1000)).GetTimeoutInMS()!=10000)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to CALCULATE CORRECT TIMEOUT !\n"));
			return(false);
		}

		++TestNumber;

		if (Item6.GetTimeout(CSchedulerTime(CDateTime(2016,11,10,9,59,0,0)),CTimeout(100*1000)).GetTimeoutInMS()!=70000)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to CALCULATE CORRECT TIMEOUT !\n"));
			return(false);
		}

		++TestNumber;

		if (Item6.GetTimeout(CSchedulerTime(CDateTime(2016,11,10,9,58,0,0)),CTimeout(100*1000)).GetTimeoutInMS()!=100000)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to CALCULATE CORRECT TIMEOUT !\n"));
			return(false);
		}

		++TestNumber;

		CSchedulerItem											Item7(CSchedulerItemID("ITEM 1"),CSchedulerTimeInterval(CNullable<CSchedulerTime>(CDateTime(2016,11,9,10,0,0,0)),CNullable<CSchedulerTime>(CDateTime(2016,11,9,11,0,0,0))),CSPSchedulerTimePeriod(new CSchedulerTimePeriodByMinute(10)));

		if (Item7.HasNextSchedulerTimeExpired(CSchedulerTime(CDateTime(2016,11,9,10,15,0,0)),InfiniteTimeout,ExecuteSchedulerItem)==false || ExecuteSchedulerItem==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to DETECT that EXECUTION TIME is VALID !\n"));
			return(false);
		}

		++TestNumber;

		Item7.RecalculateNextSchedulerTime(CSchedulerTime(CDateTime(2016,11,9,10,15,0,0)));

		if (Item7.GetNextSchedulerItemExecutionTime()!=CSchedulerTime(CDateTime(2016,11,9,10,15,10,0)))
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to CALCULATE CORRECT EXECUTION TIME !\n"));
			return(false);
		}

		CTimeout												Timeout1(200*1000);

		++TestNumber;

		if (Item7.HasNextSchedulerTimeExpired(CSchedulerTime(CDateTime(2016,11,9,10,18,15,0)),Timeout1,ExecuteSchedulerItem)==false || ExecuteSchedulerItem==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," FAILED to CALCULATE CORRECT EXECUTION TIME !\n"));
			return(false);
		}

		CTimeout												Timeout2(100*1000);

		++TestNumber;

		if (Item7.HasNextSchedulerTimeExpired(CSchedulerTime(CDateTime(2016,11,9,10,18,15,0)),Timeout2,ExecuteSchedulerItem)==false || ExecuteSchedulerItem==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ",TestNumber," INCORRECTLY DETECTED that EXECUTION TIME is VALID !\n"));
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CSchedulerTest::ExecuteTest(void)
	{
		CVector<CTestMethod<CSchedulerTest>>					Tests;

		Tests.Add(CTestMethod<CSchedulerTest>(this,&CSchedulerTest::TestSchedulerTimePeriod));
		Tests.Add(CTestMethod<CSchedulerTest>(this,&CSchedulerTest::TestSchedulerValidityPeriod));

		bool													AllTestPassed=true;
		Size													TestNumber=0;

		for(CTestMethod<CSchedulerTest>& Method : Tests)
		{
			if (Method()==true)
			{
				CString											Output;

				Output+=GetSeparator(true);
				Output+="\tSUBTEST [";
				Output+=CString(++TestNumber);
				Output+="] PASSED SUCCESSFULLY !\n";
				Output+=GetSeparator(true);

				CConsoleHelper::WriteLine(Output,EConsoleColor::E_LIGHT_GREEN,EConsoleColor::E_DEFAULT,false);
			}
			else
			{
				CString											Output;

				Output+=GetSeparator(true);
				Output+="\tSUBTEST [";
				Output+=CString(++TestNumber);
				Output+="] FAILED !\n";
				Output+=GetSeparator(true);

				AllTestPassed=false;

				CConsoleHelper::WriteLine(Output,EConsoleColor::E_LIGHT_RED,EConsoleColor::E_DEFAULT,false);
			}
		}

		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));

		if (AllTestPassed==true)
		{
			CConsoleHelper::WriteLine("ALL TESTS PASSED SUCCESSFULLY !",EConsoleColor::E_LIGHT_GREEN,EConsoleColor::E_DEFAULT,false);
		}
		else
		{
			CConsoleHelper::WriteLine("SOME TESTS FAILED !",EConsoleColor::E_LIGHT_RED,EConsoleColor::E_DEFAULT,false);
		}

		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));

		return(AllTestPassed);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------