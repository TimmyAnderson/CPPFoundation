//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/StateMachines/StateMachines/CStateMachineID.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CSocketCANManagerMessageID.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANManagerMessageContext : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSocketCANManagerMessageID							MMessageID;
			CStateMachineID										MStateMachineID;

		public:
			CSocketCANManagerMessageContext& operator=(const CSocketCANManagerMessageContext& Other);
			CSocketCANManagerMessageContext& operator=(CSocketCANManagerMessageContext&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;

		public:
			const CSocketCANManagerMessageID& GetMessageID(void) const noexcept;
			const CStateMachineID& GetStateMachineID(void) const noexcept;

		public:
			CSocketCANManagerMessageContext(const CSocketCANManagerMessageID& MessageID);
			CSocketCANManagerMessageContext(CSocketCANManagerMessageID&& MessageID);
			CSocketCANManagerMessageContext(const CSocketCANManagerMessageID& MessageID, const CStateMachineID& StateMachineID);
			CSocketCANManagerMessageContext(CSocketCANManagerMessageID&& MessageID, const CStateMachineID& StateMachineID);
			CSocketCANManagerMessageContext(const CSocketCANManagerMessageContext& Other);
			CSocketCANManagerMessageContext(CSocketCANManagerMessageContext&& Other) noexcept;
			virtual ~CSocketCANManagerMessageContext(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CCSPSocketCANManagerMessageContext=CSharedPointer<const CSocketCANManagerMessageContext>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------