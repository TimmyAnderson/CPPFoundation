//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/StateMachines/StateMachines/CStateMachineID.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CSocketUDPManagerMessageID.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPManagerMessageContext : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSocketUDPManagerMessageID							MMessageID;
			CStateMachineID										MStateMachineID;

		public:
			CSocketUDPManagerMessageContext& operator=(const CSocketUDPManagerMessageContext& Other);
			CSocketUDPManagerMessageContext& operator=(CSocketUDPManagerMessageContext&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;

		public:
			const CSocketUDPManagerMessageID& GetMessageID(void) const noexcept;
			const CStateMachineID& GetStateMachineID(void) const noexcept;

		public:
			CSocketUDPManagerMessageContext(const CSocketUDPManagerMessageID& MessageID);
			CSocketUDPManagerMessageContext(CSocketUDPManagerMessageID&& MessageID);
			CSocketUDPManagerMessageContext(const CSocketUDPManagerMessageID& MessageID, const CStateMachineID& StateMachineID);
			CSocketUDPManagerMessageContext(CSocketUDPManagerMessageID&& MessageID, const CStateMachineID& StateMachineID);
			CSocketUDPManagerMessageContext(const CSocketUDPManagerMessageContext& Other);
			CSocketUDPManagerMessageContext(CSocketUDPManagerMessageContext&& Other) noexcept;
			virtual ~CSocketUDPManagerMessageContext(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDPManagerMessageContext=CSharedPointer<CSocketUDPManagerMessageContext>;
	using														CCSPSocketUDPManagerMessageContext=CSharedPointer<const CSocketUDPManagerMessageContext>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------