//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CMap.h>
#include <Framework/Foundation/Collections/CTSDequeue.h>
#include <Framework/Foundation/Communication/Networking/Sockets/ISocketWaitObject.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPClient.h>
#include <Framework/Foundation/Threads/CManualResetEvent.h>
#include <Framework/Foundation/Threads/CMutex.h>
#include <Framework/Foundation/Threads/CThread.h>
#include "CSocketTCPClientManagerMessageRequest.h"
#include "CSocketTCPClientManagerCallbackDispatcher.h"
#include "CSocketTCPClientManagerMessageRequestSocketAdd.h"
#include "CSocketTCPClientManagerMessageRequestSocketConnect.h"
#include "CSocketTCPClientManagerMessageRequestSocketShutdown.h"
#include "CSocketTCPClientManagerMessageRequestSocketRemove.h"
#include "CSocketTCPClientManagerMessageRequestSocketWrite.h"
#include "CSocketTCPClientManagerSocketData.h"
#include "CSocketTCPClientManagerWriteOperation.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPClientManager final : public CThread
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												CSocketCollection=CMap<CSocketID,CSocketTCPClientManagerSocketData>;
			using												CRequestTSCollection=CTSDequeue<CCSPSocketTCPClientManagerMessageRequest>;
		
		private:
			const CLogCategory									MLogCategorySocketManager;
			mutable CMutex										MSocketManagerMutex;
			CManualResetEvent									MExitEvent;
			CSocketTCPClientManagerCallbackDispatcher			MCallbackDispatcher;
			CSocketCollection									MSocketCollection;
			CRequestTSCollection								MRequestTSCollection;
			ISPSocketWaitObject									MWaitObject;
			CSPByteBuffer										MReadBuffer;

		public:
			CSocketTCPClientManager& operator=(const CSocketTCPClientManager& Other)=delete;

		private:
			const CLogCategory& GetLogCategorySocketManager(void) const noexcept;
			void FireEvent(CCSPSocketTCPClientManagerMessageResponse MessageResponse) noexcept;
			void SetThreadExitFlag(void);
			bool HasThreadExitFlagSet(void);

		private:
			void ChangeSocketState(CSocketTCPClientManagerSocketData& SocketData, CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState State, CSPSocketTCPClientManagerMessageResponse MessageResponse);
			void ChangeSocketStateToFailedState(CSocketTCPClientManagerSocketData& SocketData);
			void RemoveExpiredWriteOperations(void);
			bool WriteToSockets(void);
			bool ReadFromSockets(void);
			void WaitForSocketEvents(bool PeekWait);
			void CancelAllWriteOperations(const CSocketID& SocketID);

		private:
			void ProcessOperations(void);
			void ProcessSocketAdd(CCSPSocketTCPClientManagerMessageRequestSocketAdd Request);
			void ProcessSocketRemove(CCSPSocketTCPClientManagerMessageRequestSocketRemove Request);
			void ProcessSocketConnect(CCSPSocketTCPClientManagerMessageRequestSocketConnect Request);
			void ProcessSocketShutdown(CCSPSocketTCPClientManagerMessageRequestSocketShutdown Request);
			void ProcessSocketWrite(CCSPSocketTCPClientManagerMessageRequestSocketWrite Request);

		protected:
			virtual void ThreadMethod(bool EventSet) override;
			virtual CTimeout GetTimeout(void) override;
			virtual void ThreadSafeInitializationEvent(void) override;
			virtual void ThreadSafeUninitializationEvent(void) override;

		public:
			void AddEvent(const CEventID& EventID, ISocketTCPClientManagerCallback& Callback);
			void RemoveEvent(const CEventID& EventID);
			bool HasEvent(const CEventID& EventID) const;

		public:
			void StartThread(void);
			void StopThread(void) noexcept;
			void SendRequest(CCSPSocketTCPClientManagerMessageRequest MessageRequest);
			Size GetMaximumNumberOfSockets(void);

		public:
			CSocketTCPClientManager(CLogWriter& LogWriter, Size ReadBufferSize);
			CSocketTCPClientManager(const CSocketTCPClientManager& Other)=delete;
			virtual ~CSocketTCPClientManager(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPClientManager=CSharedPointer<CSocketTCPClientManager>;
	using														CCSPSocketTCPClientManager=CSharedPointer<const CSocketTCPClientManager>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------