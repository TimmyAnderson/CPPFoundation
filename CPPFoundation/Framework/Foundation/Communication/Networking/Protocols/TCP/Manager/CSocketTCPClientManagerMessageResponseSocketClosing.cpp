//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageResponseSocketClosing.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketClosing::CSocketTCPClientManagerMessageResponseSocketClosing(const CSocketID& SocketID, EClosingEnd ClosingEnd)
		: CSocketTCPClientManagerMessageResponse(SocketID), MClosingEnd(ClosingEnd)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketClosing::CSocketTCPClientManagerMessageResponseSocketClosing(const CSocketTCPClientManagerMessageResponseSocketClosing& Other)
		: CSocketTCPClientManagerMessageResponse(Other.MSocketID), MClosingEnd(Other.MClosingEnd)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketClosing::CSocketTCPClientManagerMessageResponseSocketClosing(CSocketTCPClientManagerMessageResponseSocketClosing&& Other)
		: CSocketTCPClientManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID)), MClosingEnd(Other.MClosingEnd)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketClosing::~CSocketTCPClientManagerMessageResponseSocketClosing(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketClosing& CSocketTCPClientManagerMessageResponseSocketClosing::operator=(const CSocketTCPClientManagerMessageResponseSocketClosing& Other)
	{
		CSocketTCPClientManagerMessageResponse::operator=(Other);

		MClosingEnd=Other.MClosingEnd;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketClosing& CSocketTCPClientManagerMessageResponseSocketClosing::operator=(CSocketTCPClientManagerMessageResponseSocketClosing&& Other)
	{
		CSocketTCPClientManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		MClosingEnd=Other.MClosingEnd;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPClientManagerMessageResponseSocketClosing::ToString(void) const
	{
		return(CString::Format("TCP CLIENT MANAGER MESSAGE RESPONSE SOCKET CLOSING - SOCKET ID [",MSocketID,"] CLOSING END [",MClosingEnd,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketClosing::EClosingEnd CSocketTCPClientManagerMessageResponseSocketClosing::GetClosingEnd(void) const noexcept
	{
		return(MClosingEnd);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------