//----------------------------------------------------------------------------------------------------------------------
#include "CStopWatch.h"
#include <chrono>
#include <Framework/Platform/Global/CFunctions.h>
#include <Framework/Platform/Global/Macros.h>
#include "CSteadyClock.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace std;
	using namespace std::chrono;
	using namespace CPPFoundation::Platform;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CStopWatch::CStopWatch(void)
		: MTicks(0)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStopWatch::~CStopWatch(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	float64 CStopWatch::GetTickToSecondRatio(void)
	{
		float64													Ratio=CSteadyClock::GetTickToSecondRatio();

		return(Ratio);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CStopWatch::Start(void)
	{
		MTicks=static_cast<int64>(steady_clock::now().time_since_epoch().count());
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStopWatch::Reset(void)
	{
		MTicks=0;
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStopWatch::IsRunning(void) const
	{
		if (MTicks!=0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int64 CStopWatch::ElapsedTicks(void) const
	{
		if (IsRunning()==true)
		{
			int64												Ticks=CSteadyClock::GetCurrentTimeInTicks();
			int64												Difference=(Ticks-MTicks);

			return(Difference);
		}
		else
		{
			return(0);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CStopWatch::ElapsedMilliseconds(void) const
	{
		if (IsRunning()==true)
		{
			int64												Ticks=CSteadyClock::GetCurrentTimeInTicks();
			int64												Difference=(Ticks-MTicks);
			float64												FloatDifferenceInMS=static_cast<float64>(Difference)*(GetTickToSecondRatio()*1000.0);
			int64												DifferenceInMS=static_cast<int64>(CFunctions::Floor(FloatDifferenceInMS));

			return(DifferenceInMS);
		}
		else
		{
			return(0);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------