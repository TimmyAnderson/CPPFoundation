//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Threads/CThread.h>
#include <Framework/Foundation/Collections/CTSDequeue.h>
#include <Framework/Foundation/Logger/CLogWriter.h>
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Threads/CMutex.h>
#include "CEvent.h"
#include "CEventData.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TEventType, typename TReturnType>
	class CEventThread : public CThread
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												CEventDataTSQueue=CTSDequeue<TEventType>;

		private:
			const CLogCategory									MLogCategoryEventThread;
			const CString										MEventThreadName;
			mutable CMutex										MEventThreadMutex;
			mutable CMutex										MEventMutex;
			CEvent<TEventType,TReturnType>						MEvent;
			CEventDataTSQueue									MEventDataTSQueue;

		public:
			CEventThread& operator=(const CEventThread& Other)=delete;

		private:
			void FireEventToAllCallbacks(TEventType EventData)
			{
				CLock											Lock(MEventMutex);
				{
					for(const CPair<const CEventID,CSPEventData<TEventType,TReturnType>>& Pair : MEvent)
					{
						const CEventID&							EventID=Pair.GetFirst();
						CSPEventData<TEventType,TReturnType>	Value=Pair.GetSecond();
						CSPEventCallback<TEventType,TReturnType>	Callback=Value->GetCallback();

						try
						{
							Callback->operator()(*(Value->GetEventContext()),EventData);
						}
						catch(const CException& E)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryEventThread(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("EVENT THREAD [",MEventThreadName,"] DETECTED FAILURE while TRYING to FIRE EVENT [",EventData,"] to CALLBACK [",EventID,"] !"),E));
						}
						catch(...)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryEventThread(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("EVENT THREAD [",MEventThreadName,"] DETECTED FAILURE while TRYING to FIRE EVENT [",EventData,"] to CALLBACK [",EventID,"] !"),CUnknownException()));
						}
					}
				}
			}

			void FireAllEvents(void)
			{
				TEventType										EventData;

				while(true)
				{
					if (HasThreadExiting()==true)
					{
						return;
					}

					if (MEventDataTSQueue.PopFront(EventData)==false)
					{
						break;
					}

					FireEventToAllCallbacks(EventData);
				}
			}

		protected:
			const CLogCategory& GetLogCategoryEventThread(void) const noexcept
			{
				return(MLogCategoryEventThread);
			}

		protected:
			virtual void ThreadMethod(bool) override
			{
				FireAllEvents();
			}

			virtual CTimeout GetTimeout(void) override
			{
				return(CTimeout::GetInfinite());
			}

			virtual void ThreadSafeInitializationEvent(void) override
			{
				MEventDataTSQueue.Clear();

				// VARIABLE 'MEvent' is deliberately NOT CLEARED.
			}

			virtual void ThreadSafeUninitializationEvent(void) override
			{
				MEventDataTSQueue.Clear();

				// VARIABLE 'MEvent' is deliberately NOT CLEARED.
			}

		public:
			void StartThread(void)
			{
				CLock											Lock(MEventThreadMutex);
				{
					InternalStartThread();
				}
			}

			void StopThread(void) noexcept
			{
				try
				{
					CLock										Lock(MEventThreadMutex);
					{
						InternalStopThread();
					}
				}
				catch(...)
				{
					// INGORE EXCEPTIONS.
				}
			}

			void SendEventData(TEventType EventData)
			{
				CLock											Lock(MEventThreadMutex);
				{
					MEventDataTSQueue.PushBack(EventData);
					SetEvent();
				}
			}

			void AddCallbackFunction(CSPEventContext EventContext, const CEventCallbackFunction<TEventType,TReturnType>& Callback)
			{
				CLock											Lock(MEventMutex);
				{
					MEvent.AddCallbackFunction(EventContext,Callback);
				}
			}

			template<typename TClassType>
			void AddCallbackMethod(CSPEventContext EventContext, const CEventCallbackMethod<TClassType,TEventType,TReturnType>& Callback)
			{
				CLock											Lock(MEventMutex);
				{
					MEvent.template AddCallbackMethod<TClassType>(EventContext,Callback);
				}
			}

			bool RemoveCallback(const CEventID& EventID)
			{
				CLock											Lock(MEventMutex);
				{
					return(MEvent.RemoveCallback(EventID));
				}
			}

			bool HasCallback(const CEventID& EventID) const
			{
				CLock											Lock(MEventMutex);
				{
					return(MEvent.HasCallback(EventID));
				}
			}

			void ClearAllCallbacks(void)
			{
				CLock											Lock(MEventMutex);
				{
					MEvent.ClearAllCallbacks();
				}
			}

		public:
			CEventThread(CLogWriter& LogWriter, const CString& EventThreadName)
				: CThread(LogWriter,CString::Format("EVENT THREAD [",EventThreadName,"]")), MLogCategoryEventThread(CString::Format("EVENT THREAD [",EventThreadName,"]")), MEventThreadName(EventThreadName), MEventThreadMutex(), MEventMutex(), MEvent(), MEventDataTSQueue()
			{
			}

			CEventThread(const CEventThread& Other)=delete;

			virtual ~CEventThread(void) override
			{
				StopThread();
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------