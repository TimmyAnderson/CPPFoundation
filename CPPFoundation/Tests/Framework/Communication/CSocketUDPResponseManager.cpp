//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPResponseManager.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPResponseManager::CSocketUDPResponseManager(CLogWriter& LogWriter, CSPSocketUDPManager UDPManager)
		: CThread(LogWriter,"UDP RESPONSE MANAGER"), MMutex(), MUDPManager(UDPManager), MResponseCollection(), MResponseTSQueue()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPResponseManager::~CSocketUDPResponseManager(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPResponseManager::ProcessNewResponses(void)
	{
		CSPSocketUDPResponse									Response;

		while(MResponseTSQueue.PopFront(Response)==true)
		{
			if (HasThreadExiting()==true)
			{
				return;
			}

			Response->Reset();
			MResponseCollection.Add(Response);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPResponseManager::ProcessResponses(void)
	{
		CSteadyClock::Milliseconds								CurrentTime=CSteadyClock::GetCurrentTimeInMilliseconds();

		for(Size Index=0;Index<MResponseCollection.GetLength();Index++)
		{
			if (HasThreadExiting()==true)
			{
				return;
			}

			CSPSocketUDPResponse								Response=MResponseCollection[Index];
			
			if (Response->HasCurrentResponseItemExpired(CurrentTime)==true)
			{
				CSPSocketUDPResponseItem						ResponseItem=Response->GetCurrentResponseItem();
				CSPSocketUDPManagerMessageRequestSocketWrite	MessageRequest=ResponseItem->CreateWriteRequest(Response->GetRequestData());

				MUDPManager->SendRequest(MessageRequest);

				if (Response->HasNextResponseItem()==true)
				{
					Response->RemoveCurrentResponseItem();
				}
				else
				{
					MResponseCollection.Erase(Index--);
				}
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPResponseManager::ThreadMethod(bool)
	{
		ProcessNewResponses();

		ProcessResponses();
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CSocketUDPResponseManager::GetTimeout(void)
	{
		CSteadyClock::Milliseconds								CurrentTime=CSteadyClock::GetCurrentTimeInMilliseconds();
		CTimeout												Timeout=CTimeout::GetInfinite();

		for(CSPSocketUDPResponse Response : MResponseCollection)
		{
			CTimeout											ResponseTimeout=Response->GetCurrentExpirationTimeout(CurrentTime);

			Timeout=CTimeout::Min(Timeout,ResponseTimeout);
		}

		return(Timeout);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPResponseManager::ThreadSafeInitializationEvent(void)
	{
		MResponseCollection.Clear();
		MResponseTSQueue.Clear();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPResponseManager::ThreadSafeUninitializationEvent(void)
	{
		MResponseCollection.Clear();
		MResponseTSQueue.Clear();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPResponseManager::StartThread(void)
	{
		CLock													Lock(MMutex);
		{
			InternalStartThread();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPResponseManager::StopThread(void) noexcept
	{
		CLock													Lock(MMutex);
		{
			InternalStopThread();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPResponseManager::SendResponse(CSPSocketUDPResponse MessageRequest)
	{
		CLock													Lock(MMutex);
		{
			MResponseTSQueue.PushBack(MessageRequest);
			SetEvent();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------