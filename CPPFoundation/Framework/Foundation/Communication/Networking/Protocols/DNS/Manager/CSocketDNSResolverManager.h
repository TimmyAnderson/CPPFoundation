//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CDequeue.h>
#include <Framework/Foundation/Communication/Networking/Protocols/DNS/Resolver/CSocketDNSResolver.h>
#include <Framework/Foundation/Threads/CThread.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CSocketDNSResolverManagerCallbackDispatcher.h"
#include "CSocketDNSResolverManagerMessageRequest.h"
#include "CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress.h"
#include "CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress.h"
#include "CSocketDNSResolverManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketDNSResolverManager final : public CThread
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												CRequestTSCollection=CTSDequeue<CCSPSocketDNSResolverManagerMessageRequest>;
			using												CRequestCollection=CDequeue<CCSPSocketDNSResolverManagerMessageRequest>;

		private:
			const CLogCategory									MLogCategoryDNSResolverManager;
			CMutex												MSocketDNSResolverManagerMutex;
			CManualResetEvent									MExitEvent;
			CSocketDNSResolverManagerCallbackDispatcher			MCallbackDispatcher;
			CSocketDNSResolver									MDNSResolver;
			CRequestTSCollection								MRequestTSCollection;
			CRequestCollection									MRequestCollection;

		public:
			CSocketDNSResolverManager& operator=(const CSocketDNSResolverManager& Other)=delete;

		private:
			const CLogCategory& GetLogCategoryDNSResolverManager(void) const noexcept;
			void FireEvent(CCSPSocketDNSResolverManagerMessageResponse MessageResponse) noexcept;

		private:
			void ProcessDNSAddressToIPAddress(CCSPSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress MessageRequest);
			void ProcessIPAddressToDNSAddress(CCSPSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress MessageRequest);
			void ProcessOperations(void);

		protected:
			virtual void ThreadMethod(bool EventSet) override;
			virtual CTimeout GetTimeout(void) override;
			virtual void ThreadSafeInitializationEvent(void) override;
			virtual void ThreadSafeUninitializationEvent(void) override;

		public:
			void StartThread(void);
			void StopThread(void) noexcept;
			void SendRequest(CCSPSocketDNSResolverManagerMessageRequest MessageRequest);

		public:
			CSocketDNSResolverManager(CLogWriter& LogWriter, ISocketDNSResolverManagerCallback& Callback);
			CSocketDNSResolverManager(const CSocketDNSResolverManager& Other)=delete;
			virtual ~CSocketDNSResolverManager(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketDNSResolverManager=CSharedPointer<CSocketDNSResolverManager>;
	using														CCSPSocketDNSResolverManager=CSharedPointer<const CSocketDNSResolverManager>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------