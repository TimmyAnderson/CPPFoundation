//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/StateMachines/StateMachines/CStateMachineID.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CSocketDNSResolverManagerMessageID.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketDNSResolverManagerMessageContext : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSocketDNSResolverManagerMessageID					MMessageID;
			CStateMachineID										MStateMachineID;

		public:
			CSocketDNSResolverManagerMessageContext& operator=(const CSocketDNSResolverManagerMessageContext& Other);
			CSocketDNSResolverManagerMessageContext& operator=(CSocketDNSResolverManagerMessageContext&& Other);

		public:
			virtual CString ToString(void) const override;

		public:
			const CSocketDNSResolverManagerMessageID& GetMessageID(void) const noexcept;
			const CStateMachineID& GetStateMachineID(void) const noexcept;

		public:
			CSocketDNSResolverManagerMessageContext(const CSocketDNSResolverManagerMessageID& MessageID);
			CSocketDNSResolverManagerMessageContext(CSocketDNSResolverManagerMessageID&& MessageID);
			CSocketDNSResolverManagerMessageContext(const CSocketDNSResolverManagerMessageID& MessageID, const CStateMachineID& StateMachineID);
			CSocketDNSResolverManagerMessageContext(CSocketDNSResolverManagerMessageID&& MessageID, const CStateMachineID& StateMachineID);
			CSocketDNSResolverManagerMessageContext(const CSocketDNSResolverManagerMessageContext& Other);
			CSocketDNSResolverManagerMessageContext(CSocketDNSResolverManagerMessageContext&& Other);
			virtual ~CSocketDNSResolverManagerMessageContext(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CCSPSocketDNSResolverManagerMessageContext=CSharedPointer<const CSocketDNSResolverManagerMessageContext>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------