//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CTSDequeue.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Manager/CSocketUDPManager.h>
#include <Framework/Foundation/Threads/CManualResetEvent.h>
#include <Framework/Foundation/Threads/CMutex.h>
#include <Framework/Foundation/Threads/CThread.h>
#include "CSocketUDPResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPResponseManager final : public CPPFoundation::Foundation::CThread
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												CResponseTSQueue=CPPFoundation::Foundation::CTSDequeue<CSPSocketUDPResponse>;

		private:
			CPPFoundation::Foundation::CMutex						MMutex;
			CPPFoundation::Foundation::CSPSocketUDPManager			MUDPManager;
			CSocketUDPResponseCollection						MResponseCollection;
			CResponseTSQueue									MResponseTSQueue;

		public:
			CSocketUDPResponseManager& operator=(const CSocketUDPResponseManager&)=delete;

		private:
			void ProcessNewResponses(void);
			void ProcessResponses(void);

		protected:
			virtual void ThreadMethod(bool EventSet) override;
			virtual CPPFoundation::Foundation::CTimeout GetTimeout(void) override;
			virtual void ThreadSafeInitializationEvent(void) override;
			virtual void ThreadSafeUninitializationEvent(void) override;

		public:
			void StartThread(void);
			void StopThread(void) noexcept;
			void SendResponse(CSPSocketUDPResponse Response);

		public:
			CSocketUDPResponseManager(CPPFoundation::Foundation::CLogWriter& LogWriter, CPPFoundation::Foundation::CSPSocketUDPManager UDPManager);
			CSocketUDPResponseManager(const CSocketUDPResponseManager&)=delete;
			virtual ~CSocketUDPResponseManager(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDPResponseManager=CPPFoundation::Foundation::CSharedPointer<CSocketUDPResponseManager>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------