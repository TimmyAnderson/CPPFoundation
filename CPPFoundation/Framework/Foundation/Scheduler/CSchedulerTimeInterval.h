//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Types/CNullable.h>
#include "CSchedulerTime.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSchedulerTimeInterval final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CNullable<CSchedulerTime>							MBeginTime;
			CNullable<CSchedulerTime>							MEndTime;

		public:
			virtual CString ToString(void) const override;
			const CNullable<CSchedulerTime>& GetBeginTime(void) const noexcept;
			const CNullable<CSchedulerTime>& GetEndTime(void) const noexcept;

		public:
			CSchedulerTimeInterval(const CNullable<CSchedulerTime>& BeginTime, const CNullable<CSchedulerTime>& EndTime);
			virtual ~CSchedulerTimeInterval(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------