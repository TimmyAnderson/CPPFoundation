//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CMap.h>
#include <Framework/Foundation/Collections/CTSDequeue.h>
#include <Framework/Foundation/Communication/Networking/Sockets/ISocketWaitObject.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPServer.h>
#include <Framework/Foundation/Threads/CManualResetEvent.h>
#include <Framework/Foundation/Threads/CMutex.h>
#include <Framework/Foundation/Threads/CThread.h>
#include "CSocketTCPServerManagerMessageRequest.h"
#include "CSocketTCPServerManagerCallbackDispatcher.h"
#include "CSocketTCPServerManagerMessageRequestSocketAdd.h"
#include "CSocketTCPServerManagerMessageRequestSocketRemove.h"
#include "CSocketTCPServerManagerSocketData.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPServerManager final : public CThread
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												CSocketCollection=CMap<CSocketID,CSocketTCPServerManagerSocketData>;
			using												CRequestTSCollection=CTSDequeue<CCSPSocketTCPServerManagerMessageRequest>;
		
		private:
			const CLogCategory									MLogCategorySocketManager;
			mutable CMutex										MSocketManagerMutex;
			CManualResetEvent									MExitEvent;
			CSocketTCPServerManagerCallbackDispatcher			MCallbackDispatcher;
			CSocketCollection									MSocketCollection;
			CRequestTSCollection								MRequestTSCollection;
			ISPSocketWaitObject									MWaitObject;

		public:
			CSocketTCPServerManager& operator=(const CSocketTCPServerManager& Other)=delete;

		private:
			const CLogCategory& GetLogCategorySocketManager(void) const noexcept;
			void FireEvent(CCSPSocketTCPServerManagerMessageResponse MessageResponse);
			void SetThreadExitFlag(void);
			bool HasThreadExitFlagSet(void);

		private:
			void ChangeSocketState(CSocketTCPServerManagerSocketData& SocketData, CSocketTCPServerManagerSocketData::ESocketTCPServerManagerSocketState State, CSPSocketTCPServerManagerMessageResponse MessageResponse);
			void ChangeSocketStateToFailedState(CSocketTCPServerManagerSocketData& SocketData);
			void AcceptSocket(CSPSocketTCPServer Socket);
			void WaitForSocketEvents(void);

		private:
			void ProcessOperations(void);
			void ProcessSocketAdd(CCSPSocketTCPServerManagerMessageRequestSocketAdd Request);
			void ProcessSocketRemove(CCSPSocketTCPServerManagerMessageRequestSocketRemove Request);

		protected:
			virtual void ThreadMethod(bool EventSet) override;
			virtual CTimeout GetTimeout(void) override;
			virtual void ThreadSafeInitializationEvent(void) override;
			virtual void ThreadSafeUninitializationEvent(void) override;

		public:
			void AddEvent(const CEventID& EventID, ISocketTCPServerManagerCallback& Callback);
			void RemoveEvent(const CEventID& EventID);
			bool HasEvent(const CEventID& EventID) const;

		public:
			void StartThread(void);
			void StopThread(void) noexcept;
			void SendRequest(CCSPSocketTCPServerManagerMessageRequest MessageRequest);
			Size GetMaximumNumberOfSockets(void);

		public:
			CSocketTCPServerManager(CLogWriter& LogWriter);
			CSocketTCPServerManager(const CSocketTCPServerManager& Other)=delete;
			virtual ~CSocketTCPServerManager(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPServerManager=CSharedPointer<CSocketTCPServerManager>;
	using														CCSPSocketTCPServerManager=CSharedPointer<const CSocketTCPServerManager>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------