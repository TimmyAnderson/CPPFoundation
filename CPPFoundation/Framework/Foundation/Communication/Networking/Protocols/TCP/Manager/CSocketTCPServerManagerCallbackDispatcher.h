//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketID.h>
#include <Framework/Foundation/Events/CEventThread.h>
#include "ISocketTCPServerManagerCallback.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPServerManagerCallbackDispatcher final : private CEventThread<CCSPSocketTCPServerManagerMessageResponse,void>
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CSocketTCPServerManagerCallbackDispatcher& operator=(const CSocketTCPServerManagerCallbackDispatcher& Other)=delete;

		private:
			void ProcessMessageResponseCallback(const CEventContext& EventContext, CCSPSocketTCPServerManagerMessageResponse MessageResponse);

		public:
			void AddEvent(const CEventID& EventID, ISocketTCPServerManagerCallback& Callback);
			void RemoveEvent(const CEventID& EventID);
			bool HasEvent(const CEventID& EventID) const;
			void ClearEvents(void);

		public:
			void StartDispatcher(void);
			void StopDispatcher(void) noexcept;
			void DispatchEvent(CCSPSocketTCPServerManagerMessageResponse MessageResponse);

		public:
			CSocketTCPServerManagerCallbackDispatcher(CLogWriter& LogWriter);
			CSocketTCPServerManagerCallbackDispatcher(const CSocketTCPServerManagerCallbackDispatcher& Other)=delete;
			virtual ~CSocketTCPServerManagerCallbackDispatcher(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPServerManagerCallbackDispatcher=CSharedPointer<CSocketTCPServerManagerCallbackDispatcher>;
	using														CCSPSocketTCPServerManagerCallbackDispatcher=CSharedPointer<const CSocketTCPServerManagerCallbackDispatcher>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------