//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPManagerMessageRequestSocketWrite.h"
#include "CSocketUDPManagerMessageResponseSocketWrite.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageRequestSocketWrite::CSocketUDPManagerMessageRequestSocketWrite(const CSocketID& SocketID, CCSPSocketUDPManagerMessageContext MessageContext, const CSocketUDPAddress& DestinationAddress, CCSPByteBuffer Data, const CExpirationTime& WriteExpirationTime)
		: CSocketUDPManagerMessageRequest(SocketID), MMessageContext(MessageContext), MDestinationAddress(DestinationAddress), MData(Data), MWriteExpirationTime(WriteExpirationTime)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageRequestSocketWrite::CSocketUDPManagerMessageRequestSocketWrite(const CSocketID& SocketID, CCSPSocketUDPManagerMessageContext MessageContext, CSocketUDPAddress&& DestinationAddress, CCSPByteBuffer Data, const CExpirationTime& WriteExpirationTime)
		: CSocketUDPManagerMessageRequest(SocketID), MMessageContext(MessageContext), MDestinationAddress(FUNCTION_MOVE(DestinationAddress)), MData(Data), MWriteExpirationTime(WriteExpirationTime)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageRequestSocketWrite::CSocketUDPManagerMessageRequestSocketWrite(const CSocketUDPManagerMessageRequestSocketWrite& Other)
		: CSocketUDPManagerMessageRequest(Other.MSocketID), MMessageContext(Other.MMessageContext), MDestinationAddress(Other.MDestinationAddress), MData(Other.MData), MWriteExpirationTime(Other.MWriteExpirationTime)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageRequestSocketWrite::CSocketUDPManagerMessageRequestSocketWrite(CSocketUDPManagerMessageRequestSocketWrite&& Other)
		: CSocketUDPManagerMessageRequest(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext)), MDestinationAddress(FUNCTION_MOVE(Other.MDestinationAddress)), MData(FUNCTION_MOVE(Other.MData)), MWriteExpirationTime(Other.MWriteExpirationTime)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageRequestSocketWrite::~CSocketUDPManagerMessageRequestSocketWrite(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageRequestSocketWrite& CSocketUDPManagerMessageRequestSocketWrite::operator=(const CSocketUDPManagerMessageRequestSocketWrite& Other)
	{
		CSocketUDPManagerMessageRequest::operator=(Other);

		MMessageContext=Other.MMessageContext;
		MDestinationAddress=Other.MDestinationAddress;
		MData=Other.MData;
		MWriteExpirationTime=Other.MWriteExpirationTime;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageRequestSocketWrite& CSocketUDPManagerMessageRequestSocketWrite::operator=(CSocketUDPManagerMessageRequestSocketWrite&& Other)
	{
		CSocketUDPManagerMessageRequest::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);
		MDestinationAddress=FUNCTION_MOVE(Other.MDestinationAddress);
		MData=FUNCTION_MOVE(Other.MData);
		MWriteExpirationTime=FUNCTION_MOVE(Other.MWriteExpirationTime);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketUDPManagerMessageRequestSocketWrite::ToString(void) const
	{
		return(CString::Format("UDP MANAGER MESSAGE REQUEST SOCKET WRITE - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"] DESTINATION ADDRESS [",MDestinationAddress,"] DATA [",MData,"] LENGTH [",MData->GetLength(),"] WRITE EXPIRATION TIME [",MWriteExpirationTime,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketUDPManagerMessageResponse CSocketUDPManagerMessageRequestSocketWrite::CreateErrorResponse(void) const
	{
		return(CCSPSocketUDPManagerMessageResponse(new CSocketUDPManagerMessageResponseSocketWrite(MSocketID,MMessageContext,false,MDestinationAddress,nullptr,0)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketUDPManagerMessageContext CSocketUDPManagerMessageRequestSocketWrite::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketUDPAddress& CSocketUDPManagerMessageRequestSocketWrite::GetDestinationAddress(void) const noexcept
	{
		return(MDestinationAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPByteBuffer CSocketUDPManagerMessageRequestSocketWrite::GetData(void) const noexcept
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CExpirationTime& CSocketUDPManagerMessageRequestSocketWrite::GetWriteExpirationTime(void) const noexcept
	{
		return(MWriteExpirationTime);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------