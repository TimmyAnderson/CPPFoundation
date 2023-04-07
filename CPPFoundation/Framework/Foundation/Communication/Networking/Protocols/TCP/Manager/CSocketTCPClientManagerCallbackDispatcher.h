//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketID.h>
#include <Framework/Foundation/Events/CEventThread.h>
#include "ISocketTCPClientManagerCallback.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPClientManagerCallbackDispatcher final : private CEventThread<CCSPSocketTCPClientManagerMessageResponse,void>
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CSocketTCPClientManagerCallbackDispatcher& operator=(const CSocketTCPClientManagerCallbackDispatcher& Other)=delete;

		private:
			void ProcessMessageResponseCallback(const CEventContext& EventContext, CCSPSocketTCPClientManagerMessageResponse MessageResponse);

		public:
			void AddEvent(const CEventID& EventID, ISocketTCPClientManagerCallback& Callback);
			void RemoveEvent(const CEventID& EventID);
			bool HasEvent(const CEventID& EventID) const;
			void ClearEvents(void);

		public:
			void StartDispatcher(void);
			void StopDispatcher(void) noexcept;
			void DispatchEvent(CCSPSocketTCPClientManagerMessageResponse MessageResponse);

		public:
			CSocketTCPClientManagerCallbackDispatcher(CLogWriter& LogWriter);
			CSocketTCPClientManagerCallbackDispatcher(const CSocketTCPClientManagerCallbackDispatcher& Other)=delete;
			virtual ~CSocketTCPClientManagerCallbackDispatcher(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPClientManagerCallbackDispatcher=CSharedPointer<CSocketTCPClientManagerCallbackDispatcher>;
	using														CCSPSocketTCPClientManagerCallbackDispatcher=CSharedPointer<const CSocketTCPClientManagerCallbackDispatcher>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------