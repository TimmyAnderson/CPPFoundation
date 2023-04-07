//----------------------------------------------------------------------------------------------------------------------
#include <system_error>
#include <chrono>
#include <cstdlib>
#include <sstream>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Platform/Global/CFunctions.h>
#include <Framework/Foundation/Exceptions/CException.h>
#include <Framework/Foundation/Exceptions/CUnknownException.h>
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/Time/CDateTime.h>
#include <Framework/Platform/Global/CConstants.h>
#include "CThread.h"
#include "CLock.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace std;
	using namespace std::chrono;
	using namespace CPPFoundation::Platform;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CManualResetEvent										CThread::EVENT_INFINITE_SLEEP;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CThread::CThread(CLogWriter& LogWriter, const CString& ThreadName, bool ThreadLogWaitTime)
		: MLogWriter(LogWriter), MLogCategoryThread(CString::Format("THREAD [",ThreadName,"]")), MThreadName(ThreadName), MThreadMutex(), MThreadState(EThreadState::E_STOPPED), MThreadStopInProgress(false), MThreadEvents(), MThreadStartedEvent(false), MThreadExitingEvent(false), MThreadExitedEvent(false), MThreadBlockingCounter(0), MThreadBlockingExpirationTime(), MThreadLogWaitTime(ThreadLogWaitTime), MThread()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CThread::~CThread(void)
	{
		if (IsThreadJoinable()==true)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] was NOT STOPPED ! !!!!! FATAL ERROR - PROCESS will be ABORTED !!!!!")));

			abort();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CThread::Sleep(uint64 TimeoutInMS)
	{
		this_thread::sleep_for(duration<uint64,ratio<1,1000>>(TimeoutInMS));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThread::SleepInfinite(void)
	{
		EVENT_INFINITE_SLEEP.Wait();
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CThread::GetCurrentThreadID(void)
	{
		stringstream											Stream;

		Stream << this_thread::get_id();

		CString													ID(Stream.str());

		return(ID);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CThread::InternalThreadMethod(void)
	{
		MThreadState.SetValue(EThreadState::E_RUNNING);

		try
		{
			try
			{
				MThreadStartedEvent.Set();

				CFunctions::SetCurrentThreadName(MThreadName);

				ThreadSafeInitializationEvent();
			}
			catch(const CException& E)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] DETECTED FAILURE in THREAD SAFE INITIALIZATION EVENT !"),E));
				throw;
			}
			catch(...)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] DETECTED FAILURE in THREAD SAFE INITIALIZATION EVENT !"),CUnknownException()));
				throw;
			}

			ExecuteThreadCode();
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] DETECTED FATAL ERROR in THREAD METHOD ! THREAD METHOD will be FINISHED !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] DETECTED FATAL ERROR in THREAD METHOD ! THREAD METHOD will be FINISHED !"),CUnknownException()));
		}

		try
		{
			ThreadSafeUninitializationEvent();
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] DETECTED FAILURE in THREAD SAFE UNINITIALIZATION EVENT !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] DETECTED FAILURE in THREAD SAFE UNINITIALIZATION EVENT !"),CUnknownException()));
		}

		MThreadState.SetValue(EThreadState::E_STOPPED);

		try
		{
			MThreadExitedEvent.Set();
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to SET THREAD EXITED EVENT !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to SET THREAD EXITED EVENT !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThread::ResetBlockingCounter(void)
	{
		MThreadBlockingCounter=0;
		MThreadBlockingExpirationTime.Reset(static_cast<int64>(CConstants::THREAD_BLOCKING_TIMEOUT_IN_MS));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThread::CheckForBlocking(void)
	{
		MThreadBlockingCounter++;

		if (MThreadBlockingCounter>CConstants::THREAD_BLOCKING_LIMIT)
		{
			if (MThreadBlockingExpirationTime.HasExpired()==false)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] can be in INFINITE LOOP !")));
			}

			ResetBlockingCounter();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThread::ExecuteThreadCode(void)
	{
		ResetBlockingCounter();

		while(true)
		{
			CheckForBlocking();

			CTimeout											Timeout=GetTimeout();

			if (MThreadLogWaitTime==true)
			{
				if (Timeout.IsInfinite()==false)
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] TIMEOUT [",Timeout.GetTimeoutInMS(),"] !")));
				}
				else
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] TIMEOUT [INFINITE] !")));
				}
			}

			bool												IsSignalized;
			Size												SignalizedEventIndex;

			if (Timeout.IsInfinite()==false)
			{
				IsSignalized=MThreadEvents.WaitAny(static_cast<uint64>(Timeout.GetTimeoutInMS()),SignalizedEventIndex);
			}
			else
			{
				IsSignalized=MThreadEvents.WaitAny(SignalizedEventIndex);
			}

			if (IsSignalized==true && SignalizedEventIndex==THREAD_EXIT_EVENT_INDEX)
			{
				break;
			}

			EThreadState										ThreadState=MThreadState.GetValue();
			bool												ThreadStopInProgress=MThreadStopInProgress.GetValue();

			if (ThreadState==EThreadState::E_RUNNING && ThreadStopInProgress==true)
			{
				try
				{
					ThreadStopRequestedEvent();
				}
				catch(const CException& E)
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to EXECUTE STOP ACTION !"),E));
				}
				catch(...)
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to EXECUTE STOP ACTION !"),CUnknownException()));
				}

				MThreadState.SetValue(EThreadState::E_STOPPING);
			}

			ThreadMethod(IsSignalized);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CThread::InternalStartThread(CObject* Parameter)
	{
		CLock													Lock(MThreadMutex);
		{
			if (IsThreadJoinable()==true)
			{
				throw(CInvalidOperationException(CString::Format("THREAD [",MThreadName,"] is ALREADY STARTED !")));
			}

			try
			{
				// THREAD EVENTS MUST NOT be RESET HERE, because THREAD EVENTS could have already been set while THREAD was STARTING.

				MThreadStartedEvent.Reset();
				MThreadExitingEvent.Reset();
				MThreadExitedEvent.Reset();

				MThreadStopInProgress.SetValue(false);

				ThreadStartingEvent(Parameter);

				MThread=thread(&CThread::InternalThreadMethod,this);

				if (MThreadStartedEvent.Wait(DEFAULT_START_TIMEOUT_IN_MS)==false)
				{
					throw(CInvalidOperationException(CString::Format("THREAD [",MThreadName,"] FAILED to START within SPECIFIED TIME !")));
				}

				ThreadStartedEvent(Parameter);

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] STARTED SUCCESSFULLY !")));
			}
			catch(const system_error& E)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to START !"),E));
				InternalStopThread(Parameter);
				throw;
			}
			catch(const CException& E)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to START !"),E));

				InternalStopThread(Parameter);
				throw;
			}
			catch(...)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to START !"),CUnknownException()));
				InternalStopThread(Parameter);
				throw;
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThread::InternalStopThread(CObject* Parameter, uint64 StopTimeoutInMS) noexcept
	{
		try
		{
			CLock												Lock(MThreadMutex);
			{
				try
				{
					if (IsThreadJoinable()==true)
					{
						// METHOD SetValue() is NO EXCEPT.
						MThreadStopInProgress.SetValue(true);

						try
						{
							ThreadStoppingEvent(Parameter);
						}
						catch(const CException& E)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] DETECTED FAILURE in STOPPING EVENT !"),E));
						}
						catch(...)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] DETECTED FAILURE in STOPPING EVENT !"),CUnknownException()));
						}

						try
						{
							MThreadExitingEvent.Set();
						}
						catch(const CException& E)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to SET THREAD EXITING EVENT !"),E));
						}
						catch(...)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to SET THREAD EXITING EVENT !"),CUnknownException()));
						}

						try
						{
							// WAKE UP THREAD.
							MThreadEvents.Set(THREAD_EVENT_INDEX);
						}
						catch(const CException& E)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to SET THREAD EVENT !"),E));
						}
						catch(...)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to SET THREAD EVENT !"),CUnknownException()));
						}

						try
						{
							if (MThreadExitedEvent.Wait(StopTimeoutInMS)==false)
							{
								MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to STOP within specified TIME ! CURRENT THREAD will WAIT until THREAD will be STOPPED !")));
							}
						}
						catch(const CException& E)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to STOP or TERMINATE !"),E));
						}
						catch(...)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to STOP or TERMINATE !"),CUnknownException()));
						}

						try
						{
							MThreadEvents.Set(THREAD_EXIT_EVENT_INDEX);
						}
						catch(const CException& E)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to SET THREAD EXIT EVENT !"),E));
						}
						catch(...)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to SET THREAD EXIT EVENT !"),CUnknownException()));
						}

						try
						{
							MThread.join();

							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] STOPPED SUCCESSFULLY !")));
						}
						catch(const system_error& E)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to JOIN THREAD !"),E));
						}
						catch(const CException& E)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to JOIN THREAD !"),E));
						}
						catch(...)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to JOIN THREAD !"),CUnknownException()));
						}

						try
						{
							ThreadStoppedEvent(Parameter);
						}
						catch(const CException& E)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] DETECTED FAILURE in STOPPED EVENT !"),E));
						}
						catch(...)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] DETECTED FAILURE in STOPPED EVENT !"),CUnknownException()));
						}
					}

					// METHOD SetValue() is NO EXCEPT.
					MThreadState.SetValue(EThreadState::E_STOPPED);

					// METHOD SetValue() is NO EXCEPT.
					MThreadStopInProgress.SetValue(false);

					try
					{
						MThreadExitedEvent.Set();
					}
					catch(const CException& E)
					{
						MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to SET THREAD EXITED EVENT !"),E));
					}
					catch(...)
					{
						MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to SET THREAD EXITED EVENT !"),CUnknownException()));
					}

					try
					{
						MThreadEvents.ResetAll();
					}
					catch(const CException& E)
					{
						MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to RESET THREAD EVENTS !"),E));
					}
					catch(...)
					{
						MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to RESET THREAD EVENTS !"),CUnknownException()));
					}

					// METHOD operator=() and CONSTRUCTOR thread() are NO EXCEPT.
					MThread=thread();
				}
				catch(const CException& E)
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to STOP !"),E));
				}
				catch(...)
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to STOP !"),CUnknownException()));
				}
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to STOP !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to STOP !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThread::InternalDestructor(void)
	{
		if (IsThreadJoinable()==true)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] was NOT STOPPED !")));

			InternalStopThread(nullptr);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CString& CThread::GetThreadName(void) const noexcept
	{
		return(MThreadName);
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogWriter& CThread::GetLogWriter(void) const noexcept
	{
		return(MLogWriter);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CLogCategory& CThread::GetLogCategoryThread(void) const noexcept
	{
		return(MLogCategoryThread);
	}
//----------------------------------------------------------------------------------------------------------------------
	EThreadState CThread::GetThreadState(void) const noexcept
	{
		return(MThreadState.GetValue());
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThread::SetEvent(void)
	{
		MThreadEvents.Set(THREAD_EVENT_INDEX);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CThread::HasThreadStopping(void) const noexcept
	{
		if (MThreadState.GetValue()==EThreadState::E_STOPPING)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CThread::HasThreadExiting(void) const
	{
		if (MThreadExitingEvent.Wait(0)==true)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CThread::HasThreadExiting(const CTimeout& Timeout) const
	{
		if (Timeout.IsInfinite()==false)
		{
			if (MThreadExitingEvent.Wait(static_cast<uint64>(Timeout.GetTimeoutInMS()))==true)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
		else
		{
			MThreadExitingEvent.Wait();

			return(true);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThread::FinishThread(void) noexcept
	{
		try
		{
			MThreadEvents.Set(THREAD_EXIT_EVENT_INDEX);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to SET THREAD EXIT EVENT !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryThread(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("THREAD [",MThreadName,"] FAILED to SET THREAD EXIT EVENT !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CThread::ThreadStopRequestedEvent(void)
	{
		FinishThread();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThread::ThreadSafeInitializationEvent(void)
	{
		// EMPTY.
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThread::ThreadSafeUninitializationEvent(void)
	{
		// EMPTY.
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThread::ThreadStartingEvent(CObject* Parameter)
	{
		(void)Parameter;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThread::ThreadStartedEvent(CObject* Parameter)
	{
		(void)Parameter;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThread::ThreadStoppingEvent(CObject* Parameter)
	{
		(void)Parameter;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThread::ThreadStoppedEvent(CObject* Parameter)
	{
		(void)Parameter;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CThread::IsThreadRunning(void) const
	{
		CLock													Lock(MThreadMutex);
		{
			if (MThreadState.GetValue()==EThreadState::E_RUNNING)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CThread::IsThreadJoinable(void) const
	{
		CLock													Lock(MThreadMutex);
		{
			if (MThread.joinable()==true)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------