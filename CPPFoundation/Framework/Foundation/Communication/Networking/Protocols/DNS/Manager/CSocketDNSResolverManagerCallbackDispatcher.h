//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Events/CEventThread.h>
#include "ISocketDNSResolverManagerCallback.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketDNSResolverManagerCallbackDispatcher final : public CEventThread<CCSPSocketDNSResolverManagerMessageResponse,void>
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			ISocketDNSResolverManagerCallback&					MCallback;

		public:
			CSocketDNSResolverManagerCallbackDispatcher& operator=(const CSocketDNSResolverManagerCallbackDispatcher& Other)=delete;

		public:
			void ProcessMessageResponseCallback(const CEventContext& EventContext, CCSPSocketDNSResolverManagerMessageResponse MessageResponse);

		public:
			CSocketDNSResolverManagerCallbackDispatcher(CLogWriter& LogWriter, ISocketDNSResolverManagerCallback& Callback);
			CSocketDNSResolverManagerCallbackDispatcher(const CSocketDNSResolverManagerCallbackDispatcher& Other)=delete;
			virtual ~CSocketDNSResolverManagerCallbackDispatcher(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketDNSResolverManagerCallbackDispatcher=CSharedPointer<CSocketDNSResolverManagerCallbackDispatcher>;
	using														CCSPSocketDNSResolverManagerCallbackDispatcher=CSharedPointer<const CSocketDNSResolverManagerCallbackDispatcher>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------