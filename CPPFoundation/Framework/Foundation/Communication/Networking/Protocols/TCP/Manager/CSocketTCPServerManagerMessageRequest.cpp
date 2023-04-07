//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPServerManagerMessageRequest.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageRequest::CSocketTCPServerManagerMessageRequest(const CSocketID& SocketID)
		: MSocketID(SocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageRequest::CSocketTCPServerManagerMessageRequest(const CSocketTCPServerManagerMessageRequest& Other)
		: MSocketID(Other.MSocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageRequest::CSocketTCPServerManagerMessageRequest(CSocketTCPServerManagerMessageRequest&& Other) noexcept
		: MSocketID(FUNCTION_MOVE(Other.MSocketID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageRequest::~CSocketTCPServerManagerMessageRequest(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageRequest& CSocketTCPServerManagerMessageRequest::operator=(const CSocketTCPServerManagerMessageRequest& Other)
	{
		MSocketID=Other.MSocketID;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageRequest& CSocketTCPServerManagerMessageRequest::operator=(CSocketTCPServerManagerMessageRequest&& Other) noexcept
	{
		MSocketID=FUNCTION_MOVE(Other.MSocketID);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketID& CSocketTCPServerManagerMessageRequest::GetSocketID(void) const noexcept
	{
		return(MSocketID);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------