//----------------------------------------------------------------------------------------------------------------------
#include "CSocketDNSResolverManagerMessageContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageContext::CSocketDNSResolverManagerMessageContext(const CSocketDNSResolverManagerMessageID& MessageID)
		: MMessageID(MessageID), MStateMachineID(CStateMachineID::CreateEmptyStateMachineID())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageContext::CSocketDNSResolverManagerMessageContext(CSocketDNSResolverManagerMessageID&& MessageID)
		: MMessageID(FUNCTION_MOVE(MessageID)), MStateMachineID(CStateMachineID::CreateEmptyStateMachineID())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageContext::CSocketDNSResolverManagerMessageContext(const CSocketDNSResolverManagerMessageID& MessageID, const CStateMachineID& StateMachineID)
		: MMessageID(MessageID), MStateMachineID(StateMachineID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageContext::CSocketDNSResolverManagerMessageContext(CSocketDNSResolverManagerMessageID&& MessageID, const CStateMachineID& StateMachineID)
		: MMessageID(FUNCTION_MOVE(MessageID)), MStateMachineID(StateMachineID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageContext::CSocketDNSResolverManagerMessageContext(const CSocketDNSResolverManagerMessageContext& Other)
		: MMessageID(Other.MMessageID), MStateMachineID(Other.MStateMachineID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageContext::CSocketDNSResolverManagerMessageContext(CSocketDNSResolverManagerMessageContext&& Other)
		: MMessageID(FUNCTION_MOVE(Other.MMessageID)), MStateMachineID(FUNCTION_MOVE(Other.MStateMachineID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageContext::~CSocketDNSResolverManagerMessageContext(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketDNSResolverManagerMessageContext::ToString(void) const
	{
		return(CString::Format("MESSAGE ID [",MMessageID,"] STATE MACHINE ID [",MStateMachineID,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageContext& CSocketDNSResolverManagerMessageContext::operator=(const CSocketDNSResolverManagerMessageContext& Other)
	{
		MMessageID=Other.MMessageID;
		MStateMachineID=Other.MStateMachineID;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageContext& CSocketDNSResolverManagerMessageContext::operator=(CSocketDNSResolverManagerMessageContext&& Other)
	{
		MMessageID=FUNCTION_MOVE(Other.MMessageID);
		MStateMachineID=FUNCTION_MOVE(Other.MStateMachineID);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketDNSResolverManagerMessageID& CSocketDNSResolverManagerMessageContext::GetMessageID(void) const noexcept
	{
		return(MMessageID);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CStateMachineID& CSocketDNSResolverManagerMessageContext::GetStateMachineID(void) const noexcept
	{
		return(MStateMachineID);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------