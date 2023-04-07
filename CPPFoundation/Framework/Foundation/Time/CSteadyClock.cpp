//----------------------------------------------------------------------------------------------------------------------
#include "CSteadyClock.h"
#include <chrono>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Platform/Global/CFunctions.h>
#include <Framework/Platform/Global/Macros.h>
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
	CSteadyClock::Ticks CSteadyClock::GetCurrentTimeInTicks(void)
	{
		Ticks													NumberOfTicks=static_cast<Ticks>(std::chrono::steady_clock::now().time_since_epoch().count());

		return(NumberOfTicks);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSteadyClock::Milliseconds CSteadyClock::GetCurrentTimeInMilliseconds(void)
	{
		int64													NumberOfTicks=static_cast<int64>(std::chrono::steady_clock::now().time_since_epoch().count());
		float64													FloatTicksInMS=static_cast<float64>(NumberOfTicks)*(GetTickToSecondRatio()*1000.0);
		Milliseconds											TicksInMS=static_cast<Milliseconds>(CPPFoundation::Platform::CFunctions::Floor(FloatTicksInMS));

		return(TicksInMS);
	}
//----------------------------------------------------------------------------------------------------------------------
	float64 CSteadyClock::GetTickToSecondRatio(void)
	{
		float64													Ratio=static_cast<float64>(std::chrono::steady_clock::period::num)/static_cast<float64>(std::chrono::steady_clock::period::den);

		return(Ratio);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------