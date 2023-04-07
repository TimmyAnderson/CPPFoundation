//----------------------------------------------------------------------------------------------------------------------
#include "CSchedulerTimeInterval.h"
#include <Framework/Foundation/Exceptions/CArgumentException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerTimeInterval::CSchedulerTimeInterval(const CNullable<CSchedulerTime>& BeginTime, const CNullable<CSchedulerTime>& EndTime)
		: MBeginTime(BeginTime), MEndTime(EndTime)
	{
		if (BeginTime.GetHasValue()==true && EndTime.GetHasValue()==true)
		{
			if (BeginTime.GetValue()>EndTime.GetValue())
			{
				throw(CArgumentException("BEGIN TIME must NOT point to a later TIME POINT than END TIME !"));
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerTimeInterval::~CSchedulerTimeInterval(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSchedulerTimeInterval::ToString(void) const
	{
		return(CString::Format("TIME INTERVAL - BEGIN TIME [",MBeginTime,"] END TIME [",MEndTime,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	const CNullable<CSchedulerTime>& CSchedulerTimeInterval::GetBeginTime(void) const noexcept
	{
		return(MBeginTime);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CNullable<CSchedulerTime>& CSchedulerTimeInterval::GetEndTime(void) const noexcept
	{
		return(MEndTime);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------