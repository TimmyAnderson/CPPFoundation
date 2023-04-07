//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketID.h>
#include <Framework/Foundation/Events/CEventThread.h>
#include "ISocketCANManagerCallback.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANManagerCallbackDispatcher final : private CEventThread<CCSPSocketCANManagerMessageResponse,void>
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CSocketCANManagerCallbackDispatcher& operator=(const CSocketCANManagerCallbackDispatcher& Other)=delete;

		private:
			void ProcessMessageResponseCallback(const CEventContext& EventContext, CCSPSocketCANManagerMessageResponse MessageResponse);

		public:
			void AddEvent(const CEventID& EventID, ISocketCANManagerCallback& Callback);
			void RemoveEvent(const CEventID& EventID);
			bool HasEvent(const CEventID& EventID) const;
			void ClearEvents(void);

		public:
			void StartDispatcher(void);
			void StopDispatcher(void) noexcept;
			void DispatchEvent(CCSPSocketCANManagerMessageResponse MessageResponse);

		public:
			CSocketCANManagerCallbackDispatcher(CLogWriter& LogWriter);
			CSocketCANManagerCallbackDispatcher(const CSocketCANManagerCallbackDispatcher& Other)=delete;
			virtual ~CSocketCANManagerCallbackDispatcher(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketCANManagerCallbackDispatcher=CSharedPointer<CSocketCANManagerCallbackDispatcher>;
	using														CCSPSocketCANManagerCallbackDispatcher=CSharedPointer<const CSocketCANManagerCallbackDispatcher>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------