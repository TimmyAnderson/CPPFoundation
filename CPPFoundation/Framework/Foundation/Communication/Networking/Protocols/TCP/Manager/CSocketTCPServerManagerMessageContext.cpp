//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPServerManagerMessageContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageContext::CSocketTCPServerManagerMessageContext(const CSocketTCPServerManagerMessageID& MessageID)
		: MMessageID(MessageID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageContext::CSocketTCPServerManagerMessageContext(CSocketTCPServerManagerMessageID&& MessageID)
		: MMessageID(FUNCTION_MOVE(MessageID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageContext::CSocketTCPServerManagerMessageContext(const CSocketTCPServerManagerMessageContext& Other)
		: MMessageID(Other.MMessageID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageContext::CSocketTCPServerManagerMessageContext(CSocketTCPServerManagerMessageContext&& Other) noexcept
		: MMessageID(FUNCTION_MOVE(Other.MMessageID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageContext::~CSocketTCPServerManagerMessageContext(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPServerManagerMessageContext::ToString(void) const
	{
		return(CString::Format("MESSAGE ID [",MMessageID,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageContext& CSocketTCPServerManagerMessageContext::operator=(const CSocketTCPServerManagerMessageContext& Other)
	{
		MMessageID=Other.MMessageID;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageContext& CSocketTCPServerManagerMessageContext::operator=(CSocketTCPServerManagerMessageContext&& Other) noexcept
	{
		MMessageID=FUNCTION_MOVE(Other.MMessageID);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketTCPServerManagerMessageID& CSocketTCPServerManagerMessageContext::GetMessageID(void) const noexcept
	{
		return(MMessageID);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------