//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Collections/CMap.h>
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CEventData.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TEventType, typename TReturnType>
	class CEvent final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												CEventCallbacks=CMap<CEventID,CSPEventData<TEventType,TReturnType>>;
			using												CEventCallbacksIterator=typename CMap<CEventID,CSPEventData<TEventType,TReturnType>>::CMapIterator;
			using												CEventCallbacksIteratorConst=typename CMap<CEventID,CSPEventData<TEventType,TReturnType>>::CMapIteratorConst;

		public:
			using												CEventPair=typename CMap<CEventID,CSPEventData<TEventType,TReturnType>>::CKeyValuePair;

		private:
			CEventCallbacks										MEventCallbacks;

		public:
			void AddCallbackFunction(CSPEventContext EventContext, const CEventCallbackFunction<TEventType,TReturnType>& Callback)
			{
				if (MEventCallbacks.Contains(EventContext->GetEventID())==false)
				{
					CSPEventData<TEventType,TReturnType>		EventData(new CEventData<TEventType,TReturnType>(EventContext,CSharedPointer<CEventCallbackFunction<TEventType,TReturnType>>(new CEventCallbackFunction<TEventType,TReturnType>(Callback))));

					MEventCallbacks.Add(EventContext->GetEventID(),EventData);
				}
				else
				{
					throw(CInvalidOperationException(CString::Format("EVENT already contains CALLABLE OBJECT with ID [",EventContext->GetEventID(),"] !")));
				}
			}

			template<typename TClassType>
			void AddCallbackMethod(CSPEventContext EventContext, const CEventCallbackMethod<TClassType,TEventType,TReturnType>& Callback)
			{
				if (MEventCallbacks.Contains(EventContext->GetEventID())==false)
				{
					CSPEventData<TEventType,TReturnType>		EventData(new CEventData<TEventType,TReturnType>(EventContext,CSharedPointer<CEventCallbackMethod<TClassType,TEventType,TReturnType>>(new CEventCallbackMethod<TClassType,TEventType,TReturnType>(Callback))));

					MEventCallbacks.Add(EventContext->GetEventID(),EventData);
				}
				else
				{
					throw(CInvalidOperationException(CString::Format("EVENT already contains CALLABLE OBJECT with ID [",EventContext->GetEventID(),"] !")));
				}
			}

			bool RemoveCallback(const CEventID& EventID)
			{
				return(MEventCallbacks.Erase(EventID));
			}

			bool HasCallback(const CEventID& EventID) const
			{
				return(MEventCallbacks.Contains(EventID));
			}

			void ClearAllCallbacks(void)
			{
				MEventCallbacks.Clear();
			}

			TReturnType InvokeCallback(CSPEventContext EventContext, TEventType EventData)
			{
				if (MEventCallbacks.Contains(EventContext->GetEventID())==true)
				{
					return(MEventCallbacks[EventContext->GetEventID()]->operator()(EventContext,EventData));
				}
				else
				{
					throw(CInvalidOperationException(CString::Format("EVENT doesn't contain CALLABLE OBJECT with ID [",EventContext->GetEventID(),"] !")));
				}
			}

			// METHOD ignores RETURN VALUES.
			void InvokeAllCallbacks(TEventType EventData)
			{
				for(const CPair<const CEventID,CSPEventData<TEventType,TReturnType>>& Pair : MEventCallbacks)
				{
					CSPEventData<TEventType,TReturnType>		Value=Pair.GetSecond();
					CSPEventCallback<TEventType,TReturnType>	Callback=Value->GetCallback();

					try
					{
						Callback->operator()(Value->GetEventContext(),EventData);
					}
					catch(...)
					{
					}
				}
			}

			CEventCallbacksIterator begin(void)
			{
				return(MEventCallbacks.begin());
			}

			CEventCallbacksIterator end(void)
			{
				return(MEventCallbacks.end());
			}

			CEventCallbacksIteratorConst Begin(void) const
			{
				return(MEventCallbacks.Begin());
			}

			CEventCallbacksIteratorConst End(void) const
			{
				return(MEventCallbacks.End());
			}

		public:
			CEvent(void)
				: MEventCallbacks()
			{
			}

			virtual ~CEvent(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------