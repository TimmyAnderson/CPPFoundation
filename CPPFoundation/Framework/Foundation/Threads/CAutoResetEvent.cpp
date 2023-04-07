//----------------------------------------------------------------------------------------------------------------------
#include "CAutoResetEvent.h"
#include <ratio>
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CAutoResetEvent::CAutoResetEvent(void)
		: MMutex(), MConditionalVariable(), MIsSignalized(false)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CAutoResetEvent::CAutoResetEvent(bool IsSignalized)
		: MMutex(), MConditionalVariable(), MIsSignalized(IsSignalized)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CAutoResetEvent::~CAutoResetEvent(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CAutoResetEvent::IsSignalized(void) const
	{
		unique_lock<mutex>										Lock(MMutex);
		{
			return(MIsSignalized);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CAutoResetEvent::Set(void)
	{
		unique_lock<mutex>										Lock(MMutex);
		{
			MIsSignalized=true;

			MConditionalVariable.notify_one();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CAutoResetEvent::Reset(void)
	{
		unique_lock<mutex>										Lock(MMutex);
		{
			MIsSignalized=false;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CAutoResetEvent::Wait(void)
	{
		unique_lock<mutex>										Lock(MMutex);
		{
			MConditionalVariable.wait(Lock,[this]{return(MIsSignalized);});

			MIsSignalized=false;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CAutoResetEvent::Wait(uint64 Milliseconds)
	{
		unique_lock<mutex>										Lock(MMutex);
		{
			duration<uint64,milli>								Timeout(Milliseconds);
			bool												IsSignalized=MConditionalVariable.wait_for(Lock,Timeout,[this]{return(MIsSignalized);});

			MIsSignalized=false;

			return(IsSignalized);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------