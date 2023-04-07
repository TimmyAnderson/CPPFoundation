//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CMap.h>
#include <Framework/Foundation/Collections/CTSDequeue.h>
#include <Framework/Foundation/Communication/Networking/Sockets/ISocketWaitObject.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/CSocketUDP.h>
#include <Framework/Foundation/Exceptions/CSocketException.h>
#include <Framework/Foundation/Threads/CManualResetEvent.h>
#include <Framework/Foundation/Threads/CMutex.h>
#include <Framework/Foundation/Threads/CThread.h>
#include "CSocketUDPManagerMessageRequest.h"
#include "CSocketUDPManagerCallbackDispatcher.h"
#include "CSocketUDPManagerMessageRequestSocketAdd.h"
#include "CSocketUDPManagerMessageRequestSocketRemove.h"
#include "CSocketUDPManagerMessageRequestSocketWrite.h"
#include "CSocketUDPManagerSocketData.h"
#include "CSocketUDPManagerWriteOperation.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPManager final : public CThread
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												CSocketCollection=CMap<CSocketID,CSocketUDPManagerSocketData>;
			using												CRequestTSCollection=CTSDequeue<CCSPSocketUDPManagerMessageRequest>;
		
		private:
			const CLogCategory									MLogCategorySocketManager;
			mutable CMutex										MSocketManagerMutex;
			CManualResetEvent									MExitEvent;
			CSocketUDPManagerCallbackDispatcher					MCallbackDispatcher;
			CSocketCollection									MSocketCollection;
			CRequestTSCollection								MRequestTSCollection;
			ISPSocketWaitObject									MWaitObject;
			CSPByteBuffer										MReadBuffer;

		public:
			CSocketUDPManager& operator=(const CSocketUDPManager& Other)=delete;

		private:
			bool IsFatalReadError(ESocketExceptionCode Value);
			bool IsFatalWriteError(ESocketExceptionCode Value);
			bool IsFatalWaitError(ESocketExceptionCode Value);

		private:
			const CLogCategory& GetLogCategorySocketManager(void) const noexcept;
			void FireEvent(CCSPSocketUDPManagerMessageResponse MessageResponse) noexcept;
			void SetThreadExitFlag(void);
			bool HasThreadExitFlagSet(void);

		private:
			void ChangeSocketState(CSocketUDPManagerSocketData& SocketData, CSocketUDPManagerSocketData::ESocketUDPManagerSocketState State, CSPSocketUDPManagerMessageResponse MessageResponse);
			void ChangeSocketStateToFailedState(CSocketUDPManagerSocketData& SocketData);
			void RemoveExpiredWriteOperations(void);
			void WriteToSockets(void);
			void ReadFromSockets(void);
			void WaitForSocketEvents(void);
			void CancelAllWriteOperations(const CSocketID& SocketID);

		private:
			void ProcessOperations(void);
			void ProcessSocketAdd(CCSPSocketUDPManagerMessageRequestSocketAdd Request);
			void ProcessSocketRemove(CCSPSocketUDPManagerMessageRequestSocketRemove Request);
			void ProcessSocketWrite(CCSPSocketUDPManagerMessageRequestSocketWrite Request);

		protected:
			virtual void ThreadMethod(bool EventSet) override;
			virtual CTimeout GetTimeout(void) override;
			virtual void ThreadSafeInitializationEvent(void) override;
			virtual void ThreadSafeUninitializationEvent(void) override;

		public:
			void AddEvent(const CEventID& EventID, ISocketUDPManagerCallback& Callback);
			void RemoveEvent(const CEventID& EventID);
			bool HasEvent(const CEventID& EventID) const;

		public:
			void StartThread(void);
			void StopThread(void) noexcept;
			void SendRequest(CCSPSocketUDPManagerMessageRequest MessageRequest);
			Size GetMaximumNumberOfSockets(void);

		public:
			CSocketUDPManager(CLogWriter& LogWriter, Size ReadBufferSize=2000);
			CSocketUDPManager(const CSocketUDPManager& Other)=delete;
			virtual ~CSocketUDPManager(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDPManager=CSharedPointer<CSocketUDPManager>;
	using														CCSPSocketUDPManager=CSharedPointer<const CSocketUDPManager>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------