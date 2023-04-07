//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <thread>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Logger/CLogWriter.h>
#include <Framework/Foundation/Time/CExpirationTime.h>
#include "CAtomicSlim.h"
#include "CAutoResetMultiEvent.h"
#include "CManualResetEvent.h"
#include "CMutex.h"
#include "EThreadState.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CThread : public virtual CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			static const uint64									DEFAULT_START_TIMEOUT_IN_MS=3*1000;
			static const uint64									DEFAULT_STOP_TIMEOUT_IN_MS=10*1000;
			static const Size									THREAD_EXIT_EVENT_INDEX=0;
			static const Size									THREAD_EVENT_INDEX=1;

		private:
			static const CManualResetEvent						EVENT_INFINITE_SLEEP;

		private:
			CLogWriter&											MLogWriter;
			const CLogCategory									MLogCategoryThread;
			const CString										MThreadName;
			mutable CMutex										MThreadMutex;
			CAtomicSlim<EThreadState>							MThreadState;
			CAtomicSlim<bool>									MThreadStopInProgress;
			CAutoResetMultiEvent<2>								MThreadEvents;
			CManualResetEvent									MThreadStartedEvent;
			CManualResetEvent									MThreadExitingEvent;
			CManualResetEvent									MThreadExitedEvent;
			uint64												MThreadBlockingCounter;
			CExpirationTime										MThreadBlockingExpirationTime;
			bool												MThreadLogWaitTime;
			std::thread											MThread;

		public:
			static void Sleep(uint64 TimeoutInMS);
			static void SleepInfinite(void);
			static CString GetCurrentThreadID(void);

		private:
			void InternalThreadMethod(void);
			void ResetBlockingCounter(void);
			void CheckForBlocking(void);
			void ExecuteThreadCode(void);

		protected:
			virtual void ThreadMethod(bool EventSet)=0;
			virtual CTimeout GetTimeout(void)=0;

		protected:
			void InternalStartThread(CObject* Parameter=nullptr);
			void InternalStopThread(CObject* Parameter=nullptr, uint64 StopTimeoutInMS=DEFAULT_STOP_TIMEOUT_IN_MS) noexcept;
			void InternalDestructor(void);

		protected:
			const CString& GetThreadName(void) const noexcept;
			CLogWriter& GetLogWriter(void) const noexcept;
			const CLogCategory& GetLogCategoryThread(void) const noexcept;
			EThreadState GetThreadState(void) const noexcept;
			void SetEvent(void);
			bool HasThreadStopping(void) const noexcept;
			bool HasThreadExiting(void) const;
			bool HasThreadExiting(const CTimeout& Timeout) const;
			void FinishThread(void) noexcept;

		protected:
			virtual void ThreadStopRequestedEvent(void);
			virtual void ThreadSafeInitializationEvent(void);
			virtual void ThreadSafeUninitializationEvent(void);
			virtual void ThreadStartingEvent(CObject* Parameter);
			virtual void ThreadStartedEvent(CObject* Parameter);
			virtual void ThreadStoppingEvent(CObject* Parameter);
			virtual void ThreadStoppedEvent(CObject* Parameter);

		public:
			bool IsThreadRunning(void) const;
			bool IsThreadJoinable(void) const;

		public:
			CThread(CLogWriter& LogWriter, const CString& ThreadName, bool ThreadLogWaitTime=false);
			virtual ~CThread(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------