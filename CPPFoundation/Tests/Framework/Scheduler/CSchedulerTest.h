//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Scheduler/CSchedulerTime.h>
#include <Framework/Foundation/Scheduler/CSchedulerTimePeriod.h>
#include <Framework/Testing/CTest.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CSchedulerTest final : public CTest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			struct SSchedulerTimePeriodData
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					CPPFoundation::Foundation::CSPSchedulerTimePeriod	MTimePeriod;
					CPPFoundation::Foundation::CSchedulerTime		MTimeToCheck;
					CPPFoundation::Foundation::CSchedulerTime		MExpectedTime;

				public:
					CPPFoundation::Foundation::CSPSchedulerTimePeriod GetTimePeriod(void) const noexcept
					{
						return(MTimePeriod);
					}

					const CPPFoundation::Foundation::CSchedulerTime& GetTimeToCheck(void) const noexcept
					{
						return(MTimeToCheck);
					}

					const CPPFoundation::Foundation::CSchedulerTime& GetExpectedTime(void) const noexcept
					{
						return(MExpectedTime);
					}

				public:
					SSchedulerTimePeriodData(CPPFoundation::Foundation::CSPSchedulerTimePeriod TimePeriod, const CPPFoundation::Foundation::CSchedulerTime& TimeToCheck, const CPPFoundation::Foundation::CSchedulerTime& ExpectedTime)
						: MTimePeriod(TimePeriod), MTimeToCheck(TimeToCheck), MExpectedTime(ExpectedTime)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private:
			bool TestSchedulerTimePeriod(void);
			bool TestSchedulerValidityPeriod(void);

		public:
			virtual bool ExecuteTest(void) override;

		public:
			CSchedulerTest(CPPFoundation::Foundation::CLogWriter& LogWriter, const CPPFoundation::Foundation::CLogCategory& LogCategoryTest);
			virtual ~CSchedulerTest(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------