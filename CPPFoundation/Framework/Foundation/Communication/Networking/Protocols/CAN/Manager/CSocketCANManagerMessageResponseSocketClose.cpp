//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANManagerMessageResponseSocketClose.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketClose::CSocketCANManagerMessageResponseSocketClose(const CSocketID& SocketID)
		: CSocketCANManagerMessageResponse(SocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketClose::CSocketCANManagerMessageResponseSocketClose(const CSocketCANManagerMessageResponseSocketClose& Other)
		: CSocketCANManagerMessageResponse(Other.MSocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketClose::CSocketCANManagerMessageResponseSocketClose(CSocketCANManagerMessageResponseSocketClose&& Other) noexcept
		: CSocketCANManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketClose::~CSocketCANManagerMessageResponseSocketClose(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketClose& CSocketCANManagerMessageResponseSocketClose::operator=(const CSocketCANManagerMessageResponseSocketClose& Other)
	{
		CSocketCANManagerMessageResponse::operator=(Other);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketClose& CSocketCANManagerMessageResponseSocketClose::operator=(CSocketCANManagerMessageResponseSocketClose&& Other) noexcept
	{
		CSocketCANManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketCANManagerMessageResponseSocketClose::ToString(void) const
	{
		return(CString::Format("CAN MANAGER MESSAGE RESPONSE SOCKET CLOSE - SOCKET ID [",MSocketID,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------