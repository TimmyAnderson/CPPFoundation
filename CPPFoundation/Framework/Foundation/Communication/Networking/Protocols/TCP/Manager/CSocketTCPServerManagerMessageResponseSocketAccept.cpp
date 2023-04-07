//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPServerManagerMessageResponseSocketAccept.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketAccept::CSocketTCPServerManagerMessageResponseSocketAccept(ISPSocketTCPWrapper SocketTCPWrapper, const CSocketTCPAddress& DestinationAddress)
		: CSocketTCPServerManagerMessageResponse(CSocketID("")), MSocketTCPWrapper(SocketTCPWrapper), MDestinationAddress(DestinationAddress)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketAccept::CSocketTCPServerManagerMessageResponseSocketAccept(const CSocketTCPServerManagerMessageResponseSocketAccept& Other)
		: CSocketTCPServerManagerMessageResponse(Other.MSocketID), MSocketTCPWrapper(Other.MSocketTCPWrapper), MDestinationAddress(Other.MDestinationAddress)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketAccept::CSocketTCPServerManagerMessageResponseSocketAccept(CSocketTCPServerManagerMessageResponseSocketAccept&& Other)
		: CSocketTCPServerManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID)), MSocketTCPWrapper(FUNCTION_MOVE(Other.MSocketTCPWrapper)), MDestinationAddress(FUNCTION_MOVE(Other.MDestinationAddress))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketAccept::~CSocketTCPServerManagerMessageResponseSocketAccept(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketAccept& CSocketTCPServerManagerMessageResponseSocketAccept::operator=(const CSocketTCPServerManagerMessageResponseSocketAccept& Other)
	{
		CSocketTCPServerManagerMessageResponse::operator=(Other);

		MSocketTCPWrapper=Other.MSocketTCPWrapper;
		MDestinationAddress=Other.MDestinationAddress;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketAccept& CSocketTCPServerManagerMessageResponseSocketAccept::operator=(CSocketTCPServerManagerMessageResponseSocketAccept&& Other)
	{
		CSocketTCPServerManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		MSocketTCPWrapper=FUNCTION_MOVE(Other.MSocketTCPWrapper);
		MDestinationAddress=FUNCTION_MOVE(Other.MDestinationAddress);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPServerManagerMessageResponseSocketAccept::ToString(void) const
	{
		return(CString::Format("TCP SERVER MANAGER MESSAGE RESPONSE SOCKET ACCEPT - SOCKET ID [",MSocketID,"] SOCKET TCP WRAPPER [",MSocketTCPWrapper,"] DESTINATION ADDRESS [",MDestinationAddress,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	ISPSocketTCPWrapper CSocketTCPServerManagerMessageResponseSocketAccept::GetSocketTCPWrapper(void) const noexcept
	{
		return(MSocketTCPWrapper);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketTCPAddress& CSocketTCPServerManagerMessageResponseSocketAccept::GetDestinationAddress(void) const noexcept
	{
		return(MDestinationAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------