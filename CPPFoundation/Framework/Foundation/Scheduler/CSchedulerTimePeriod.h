//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CSchedulerTime.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSchedulerTimePeriod : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			virtual CString ToString(void) const override=0;
			virtual CSchedulerTime CalculateNextSchedulerTime(const CSchedulerTime& TimeToCheck) const=0;

		public:
			CSchedulerTimePeriod(void);
			virtual ~CSchedulerTimePeriod(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSchedulerTimePeriod=CSharedPointer<CSchedulerTimePeriod>;
	using														CCSPSchedulerTimePeriod=CSharedPointer<const CSchedulerTimePeriod>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------