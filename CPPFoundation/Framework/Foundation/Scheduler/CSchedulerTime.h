//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Time/CDateTime.h>
#include <Framework/Foundation/Time/CTimeout.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSchedulerTime final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CDateTime											MDateTime;

		public:
			bool operator==(const CSchedulerTime& Other) const;
			bool operator!=(const CSchedulerTime& Other) const;
			bool operator<(const CSchedulerTime& Other) const;
			bool operator<=(const CSchedulerTime& Other) const;
			bool operator>(const CSchedulerTime& Other) const;
			bool operator>=(const CSchedulerTime& Other) const;

		public:
			virtual CString ToString(void) const override;
			const CDateTime& GetDateTime(void) const noexcept;
			void AddYears(int32 Years);
			void AddMonths(int32 Months);
			void AddDays(int32 Days);
			void AddHours(int64 Hours);
			void AddMinutes(int64 Minutes);
			void AddSeconds(int64 Seconds);
			void AddMilliseconds(int64 Milliseconds);

		public:
			CSchedulerTime(void);
			CSchedulerTime(const CDateTime& DateTime);
			virtual ~CSchedulerTime(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// RETURNS DIFFERENCE in TICKS.
	CTimeout operator-(const CSchedulerTime& Left, const CSchedulerTime& Right);
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------