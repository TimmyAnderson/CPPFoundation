//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANManagerMessageResponseSocketError.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketError::CSocketCANManagerMessageResponseSocketError(const CSocketID& SocketID)
		: CSocketCANManagerMessageResponse(SocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketError::CSocketCANManagerMessageResponseSocketError(const CSocketCANManagerMessageResponseSocketError& Other)
		: CSocketCANManagerMessageResponse(Other.MSocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketError::CSocketCANManagerMessageResponseSocketError(CSocketCANManagerMessageResponseSocketError&& Other) noexcept
		: CSocketCANManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketError::~CSocketCANManagerMessageResponseSocketError(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketError& CSocketCANManagerMessageResponseSocketError::operator=(const CSocketCANManagerMessageResponseSocketError& Other)
	{
		CSocketCANManagerMessageResponse::operator=(Other);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketError& CSocketCANManagerMessageResponseSocketError::operator=(CSocketCANManagerMessageResponseSocketError&& Other) noexcept
	{
		CSocketCANManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketCANManagerMessageResponseSocketError::ToString(void) const
	{
		return(CString::Format("CAN MANAGER MESSAGE RESPONSE SOCKET ERROR - SOCKET ID [",MSocketID,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------