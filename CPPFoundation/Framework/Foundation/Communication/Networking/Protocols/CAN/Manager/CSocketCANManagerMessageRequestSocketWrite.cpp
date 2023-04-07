//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANManagerMessageRequestSocketWrite.h"
#include "CSocketCANManagerMessageResponseSocketWrite.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageRequestSocketWrite::CSocketCANManagerMessageRequestSocketWrite(const CSocketID& SocketID, CCSPSocketCANManagerMessageContext MessageContext, const CSocketCANAddress& DestinationAddress, CCSPByteBuffer Data, const CExpirationTime& WriteExpirationTime)
		: CSocketCANManagerMessageRequest(SocketID), MMessageContext(MessageContext), MDestinationAddress(DestinationAddress), MData(Data), MWriteExpirationTime(WriteExpirationTime)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageRequestSocketWrite::CSocketCANManagerMessageRequestSocketWrite(const CSocketCANManagerMessageRequestSocketWrite& Other)
		: CSocketCANManagerMessageRequest(Other.MSocketID), MMessageContext(Other.MMessageContext), MDestinationAddress(Other.MDestinationAddress), MData(Other.MData), MWriteExpirationTime(Other.MWriteExpirationTime)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageRequestSocketWrite::CSocketCANManagerMessageRequestSocketWrite(CSocketCANManagerMessageRequestSocketWrite&& Other) noexcept
		: CSocketCANManagerMessageRequest(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext)), MDestinationAddress(FUNCTION_MOVE(Other.MDestinationAddress)), MData(FUNCTION_MOVE(Other.MData)), MWriteExpirationTime(Other.MWriteExpirationTime)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageRequestSocketWrite::~CSocketCANManagerMessageRequestSocketWrite(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageRequestSocketWrite& CSocketCANManagerMessageRequestSocketWrite::operator=(const CSocketCANManagerMessageRequestSocketWrite& Other)
	{
		CSocketCANManagerMessageRequest::operator=(Other);

		MMessageContext=Other.MMessageContext;
		MDestinationAddress=Other.MDestinationAddress;
		MData=Other.MData;
		MWriteExpirationTime=Other.MWriteExpirationTime;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageRequestSocketWrite& CSocketCANManagerMessageRequestSocketWrite::operator=(CSocketCANManagerMessageRequestSocketWrite&& Other) noexcept
	{
		CSocketCANManagerMessageRequest::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);
		MDestinationAddress=FUNCTION_MOVE(Other.MDestinationAddress);
		MData=FUNCTION_MOVE(Other.MData);
		MWriteExpirationTime=FUNCTION_MOVE(Other.MWriteExpirationTime);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketCANManagerMessageRequestSocketWrite::ToString(void) const
	{
		return(CString::Format("CAN MANAGER MESSAGE REQUEST SOCKET WRITE - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"] DESTINATION ADDRESS [",MDestinationAddress,"] DATA [",MData,"] LENGTH [",MData->GetLength(),"] WRITE EXPIRATION TIME [",MWriteExpirationTime,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketCANManagerMessageResponse CSocketCANManagerMessageRequestSocketWrite::CreateErrorResponse(void) const
	{
		return(CCSPSocketCANManagerMessageResponse(new CSocketCANManagerMessageResponseSocketWrite(MSocketID,MMessageContext,false,MDestinationAddress,nullptr,0)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketCANManagerMessageContext CSocketCANManagerMessageRequestSocketWrite::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketCANAddress& CSocketCANManagerMessageRequestSocketWrite::GetDestinationAddress(void) const noexcept
	{
		return(MDestinationAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPByteBuffer CSocketCANManagerMessageRequestSocketWrite::GetData(void) const noexcept
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CExpirationTime& CSocketCANManagerMessageRequestSocketWrite::GetWriteExpirationTime(void) const noexcept
	{
		return(MWriteExpirationTime);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------