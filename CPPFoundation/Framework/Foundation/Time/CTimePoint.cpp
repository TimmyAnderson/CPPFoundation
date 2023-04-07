//----------------------------------------------------------------------------------------------------------------------
#include "CTimePoint.h"
#include "CDateTime.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CTimePoint::CTimePoint(void)
		: MYear(0), MMonth(0), MDay(0), MHour(0), MMinute(0), MSecond(0), MMillisecond(0)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimePoint::CTimePoint(int32 Year, int32 Month, int32 Day, int32 Hour, int32 Minute, int32 Second, int32 Millisecond)
		: MYear(0), MMonth(0), MDay(0), MHour(0), MMinute(0), MSecond(0), MMillisecond(0)
	{
		CDateTime::CheckYear(Year);
		CDateTime::CheckMonth(Month);
		CDateTime::CheckDay(Day,Month,Year);
		CDateTime::CheckHour(Hour);
		CDateTime::CheckMinute(Minute);
		CDateTime::CheckSecond(Second);
		CDateTime::CheckMillisecond(Millisecond);

		MYear=Year;
		MMonth=Month;
		MDay=Day;
		MHour=Hour;
		MMinute=Minute;
		MSecond=Second;
		MMillisecond=Millisecond;
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------