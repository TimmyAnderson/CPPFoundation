//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Types/CSharedPointer.h>
#include <Framework/Foundation/Types/CFunction.h>
#include <Framework/Foundation/Types/CMethod.h>
#include <Framework/Foundation/Types/ICallableObject.h>
#include "CEventID.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CEventContext : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CEventID											MEventID;

		public:
			CEventContext& operator=(const CEventContext& Other);
			CEventContext& operator=(CEventContext&& Other) noexcept;

		public:
			const CEventID& GetEventID(void) const noexcept;

		public:
			CEventContext(const CEventID& EventID);
			CEventContext(CEventID&& EventID);
			CEventContext(const CEventContext& Other);
			CEventContext(CEventContext&& Other) noexcept;
			virtual ~CEventContext(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPEventContext=CSharedPointer<CEventContext>;
	using														CCSPEventContext=CSharedPointer<const CEventContext>;
	template<typename TEventType, typename TReturnType>
	using														CEventCallbackFunction=CFunction<TReturnType(const CEventContext&, TEventType)>;
	template<typename TClassType, typename TEventType, typename TReturnType>
	using														CEventCallbackMethod=CMethod<TClassType,TReturnType(const CEventContext&, TEventType)>;
	template<typename TEventType, typename TReturnType>
	using														CSPEventCallback=CSharedPointer<ICallableObject<TReturnType(const CEventContext&, TEventType)>>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------