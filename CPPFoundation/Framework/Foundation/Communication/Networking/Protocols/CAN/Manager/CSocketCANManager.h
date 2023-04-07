//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CMap.h>
#include <Framework/Foundation/Collections/CList.h>
#include <Framework/Foundation/Collections/CTSDequeue.h>
#include <Framework/Foundation/Communication/Networking/Sockets/ISocketWaitObject.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCAN.h>
#include <Framework/Foundation/Threads/CManualResetEvent.h>
#include <Framework/Foundation/Threads/CMutex.h>
#include <Framework/Foundation/Threads/CThread.h>
#include "CSocketCANManagerMessageRequest.h"
#include "CSocketCANManagerCallbackDispatcher.h"
#include "CSocketCANManagerMessageRequestSocketAdd.h"
#include "CSocketCANManagerMessageRequestSocketRemove.h"
#include "CSocketCANManagerMessageRequestSocketWrite.h"
#include "CSocketCANManagerSocketData.h"
#include "CSocketCANManagerWriteOperation.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANManager final : public CThread
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												CSocketCollection=CMap<CSocketID,CSocketCANManagerSocketData>;
			using												CRequestTSCollection=CTSDequeue<CCSPSocketCANManagerMessageRequest>;
		
		private:
			const CLogCategory									MLogCategorySocketManager;
			mutable CMutex										MSocketManagerMutex;
			CManualResetEvent									MExitEvent;
			CSocketCANManagerCallbackDispatcher					MCallbackDispatcher;
			CSocketCollection									MSocketCollection;
			CRequestTSCollection								MRequestTSCollection;
			ISPSocketWaitObject									MWaitObject;
			CSPByteBuffer										MReadBuffer;

		public:
			CSocketCANManager& operator=(const CSocketCANManager& Other)=delete;

		private:
			const CLogCategory& GetLogCategorySocketManager(void) const noexcept;
			void FireEvent(CCSPSocketCANManagerMessageResponse MessageResponse) noexcept;
			void SetThreadExitFlag(void);
			bool HasThreadExitFlagSet(void);

		private:
			void ChangeSocketState(CSocketCANManagerSocketData& SocketData, CSocketCANManagerSocketData::ESocketCANManagerSocketState State, CSPSocketCANManagerMessageResponse MessageResponse);
			void ChangeSocketStateToFailedState(CSocketCANManagerSocketData& SocketData);
			void RemoveExpiredWriteOperations(void);
			void WriteToSockets(void);
			void ReadFromSockets(void);
			void WaitForSocketEvents(void);
			void CancelAllWriteOperations(const CSocketID& SocketID);

		private:
			void ProcessOperations(void);
			void ProcessSocketAdd(CCSPSocketCANManagerMessageRequestSocketAdd Request);
			void ProcessSocketRemove(CCSPSocketCANManagerMessageRequestSocketRemove Request);
			void ProcessSocketWrite(CCSPSocketCANManagerMessageRequestSocketWrite Request);

		protected:
			virtual void ThreadMethod(bool EventSet) override;
			virtual CTimeout GetTimeout(void) override;
			virtual void ThreadSafeInitializationEvent(void) override;
			virtual void ThreadSafeUninitializationEvent(void) override;

		public:
			void AddEvent(const CEventID& EventID, ISocketCANManagerCallback& Callback);
			void RemoveEvent(const CEventID& EventID);
			bool HasEvent(const CEventID& EventID) const;

		public:
			void StartThread(void);
			void StopThread(void) noexcept;
			void SendRequest(CCSPSocketCANManagerMessageRequest MessageRequest);
			Size GetMaximumNumberOfSockets(void);

		public:
			CSocketCANManager(CLogWriter& LogWriter, Size ReadBufferSize=2000);
			CSocketCANManager(const CSocketCANManager& Other)=delete;
			virtual ~CSocketCANManager(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketCANManager=CSharedPointer<CSocketCANManager>;
	using														CCSPSocketCANManager=CSharedPointer<const CSocketCANManager>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------