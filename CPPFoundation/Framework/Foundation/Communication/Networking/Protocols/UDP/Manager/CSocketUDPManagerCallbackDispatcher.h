//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketID.h>
#include <Framework/Foundation/Events/CEventThread.h>
#include "ISocketUDPManagerCallback.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPManagerCallbackDispatcher final : private CEventThread<CCSPSocketUDPManagerMessageResponse,void>
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CSocketUDPManagerCallbackDispatcher& operator=(const CSocketUDPManagerCallbackDispatcher& Other)=delete;

		private:
			void ProcessMessageResponseCallback(const CEventContext& EventContext, CCSPSocketUDPManagerMessageResponse MessageResponse);

		public:
			void AddEvent(const CEventID& EventID, ISocketUDPManagerCallback& Callback);
			void RemoveEvent(const CEventID& EventID);
			bool HasEvent(const CEventID& EventID) const;
			void ClearEvents(void);

		public:
			void StartDispatcher(void);
			void StopDispatcher(void) noexcept;
			void DispatchEvent(CCSPSocketUDPManagerMessageResponse MessageResponse);

		public:
			CSocketUDPManagerCallbackDispatcher(CLogWriter& LogWriter);
			CSocketUDPManagerCallbackDispatcher(const CSocketUDPManagerCallbackDispatcher& Other)=delete;
			virtual ~CSocketUDPManagerCallbackDispatcher(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDPManagerCallbackDispatcher=CSharedPointer<CSocketUDPManagerCallbackDispatcher>;
	using														CCSPSocketUDPManagerCallbackDispatcher=CSharedPointer<const CSocketUDPManagerCallbackDispatcher>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------