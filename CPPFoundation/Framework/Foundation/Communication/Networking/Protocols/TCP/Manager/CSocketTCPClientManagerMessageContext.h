//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/StateMachines/StateMachines/CStateMachineID.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CSocketTCPClientManagerMessageID.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPClientManagerMessageContext : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSocketTCPClientManagerMessageID					MMessageID;
			CStateMachineID										MStateMachineID;

		public:
			CSocketTCPClientManagerMessageContext& operator=(const CSocketTCPClientManagerMessageContext& Other);
			CSocketTCPClientManagerMessageContext& operator=(CSocketTCPClientManagerMessageContext&& Other);

		public:
			virtual CString ToString(void) const override;

		public:
			const CSocketTCPClientManagerMessageID& GetMessageID(void) const noexcept;
			const CStateMachineID& GetStateMachineID(void) const noexcept;

		public:
			CSocketTCPClientManagerMessageContext(const CSocketTCPClientManagerMessageID& MessageID);
			CSocketTCPClientManagerMessageContext(CSocketTCPClientManagerMessageID&& MessageID);
			CSocketTCPClientManagerMessageContext(const CSocketTCPClientManagerMessageID& MessageID, const CStateMachineID& StateMachineID);
			CSocketTCPClientManagerMessageContext(CSocketTCPClientManagerMessageID&& MessageID, const CStateMachineID& StateMachineID);
			CSocketTCPClientManagerMessageContext(const CSocketTCPClientManagerMessageContext& Other);
			CSocketTCPClientManagerMessageContext(CSocketTCPClientManagerMessageContext&& Other);
			virtual ~CSocketTCPClientManagerMessageContext(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CCSPSocketTCPClientManagerMessageContext=CSharedPointer<const CSocketTCPClientManagerMessageContext>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------