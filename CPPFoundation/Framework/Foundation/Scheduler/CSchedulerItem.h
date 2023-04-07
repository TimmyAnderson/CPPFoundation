//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Time/CSteadyClock.h>
#include <Framework/Foundation/Time/CTimeout.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CSchedulerItemID.h"
#include "CSchedulerTimeInterval.h"
#include "CSchedulerTimePeriod.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSchedulerItem final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSchedulerItemID									MID;
			CSchedulerTimeInterval								MValidityInterval;
			CSPSchedulerTimePeriod								MTimePeriod;
			CSchedulerTime										MNextSchedulerItemExecutionTime;

		private:
			bool IsItemWithinValidInterval(const CSchedulerTime& Time) const;
			bool HasItemExpired(const CSchedulerTime& Time) const;

		public:
			virtual CString ToString(void) const override;
			const CSchedulerItemID& GetID(void) const noexcept;
			const CSchedulerTimeInterval& GetValidityInterval(void) const noexcept;
			CSPSchedulerTimePeriod GetTimePeriod(void) const noexcept;
			const CSchedulerTime& GetNextSchedulerItemExecutionTime(void) const noexcept;

		public:
			bool HasNextSchedulerTimeExpired(const CSchedulerTime& Time, const CTimeout& MaximumTimeDifference, bool& ExecuteSchedulerItem);
			void ResetExecutionTimeout(const CSchedulerTime& Time);
			void RecalculateNextSchedulerTime(const CSchedulerTime& Time);
			CTimeout GetTimeout(const CSchedulerTime& Time, const CTimeout& MaximumTimeout) const;

		public:
			CSchedulerItem(const CSchedulerItemID& ID, const CSchedulerTimeInterval& ValidityInterval, CSPSchedulerTimePeriod TimePeriod);
			virtual ~CSchedulerItem(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSchedulerItem=CSharedPointer<CSchedulerItem>;
	using														CCSPSchedulerItem=CSharedPointer<const CSchedulerItem>;
	using														CSchedulerItemCollection=CVector<CSPSchedulerItem>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------