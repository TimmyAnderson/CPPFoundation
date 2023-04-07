//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Types/CSharedPointer.h>
#include <Framework/Foundation/Types/ICallableObject.h>
#include "CEventContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TEventType, typename TReturnType>
	class CEventData : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSPEventContext										MEventContext;
			CSPEventCallback<TEventType,TReturnType>			MCallback;

		public:
			CEventData& operator=(const CEventData& Other)
			{
				MEventContext=Other.MEventContext;
				MCallback=Other.MCallback;

				return(*this);
			}

			CEventData& operator=(CEventData&& Other)
			{
				MEventContext=FUNCTION_MOVE(Other.MEventContext);
				MCallback=FUNCTION_MOVE(Other.MCallback);

				return(*this);
			}

		public:
			CSPEventContext GetEventContext(void) const noexcept
			{
				return(MEventContext);
			}

			CSPEventCallback<TEventType,TReturnType> GetCallback(void) const noexcept
			{
				return(MCallback);
			}

		public:
			CEventData(CSPEventContext EventContext, CSPEventCallback<TEventType,TReturnType> Callback)
				: MEventContext(EventContext), MCallback(Callback)
			{
			}

			CEventData(const CEventData& Other)
				: MEventContext(Other.MEventContext), MCallback(Other.MCallback)
			{
			}

			CEventData(CEventData&& Other)
				: MEventContext(FUNCTION_MOVE(Other.MEventContext)), MCallback(FUNCTION_MOVE(Other.MCallback))
			{
			}

			virtual ~CEventData(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TEventType, typename TReturnType>
	using														CSPEventData=CSharedPointer<CEventData<TEventType,TReturnType>>;
	template<typename TEventType, typename TReturnType>
	using														CCSPEventData=CSharedPointer<const CEventData<TEventType,TReturnType>>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------