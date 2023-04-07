//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageRequestSocketWrite.h"
#include "CSocketTCPClientManagerMessageResponseSocketWrite.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketWrite::CSocketTCPClientManagerMessageRequestSocketWrite(const CSocketID& SocketID, CCSPSocketTCPClientManagerMessageContext MessageContext, CCSPByteBuffer Data, const CExpirationTime& WriteExpirationTime)
		: CSocketTCPClientManagerMessageRequest(SocketID), MMessageContext(MessageContext), MData(Data), MWriteExpirationTime(WriteExpirationTime)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketWrite::CSocketTCPClientManagerMessageRequestSocketWrite(const CSocketTCPClientManagerMessageRequestSocketWrite& Other)
		: CSocketTCPClientManagerMessageRequest(Other.MSocketID), MMessageContext(Other.MMessageContext), MData(Other.MData), MWriteExpirationTime(Other.MWriteExpirationTime)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketWrite::CSocketTCPClientManagerMessageRequestSocketWrite(CSocketTCPClientManagerMessageRequestSocketWrite&& Other) noexcept
		: CSocketTCPClientManagerMessageRequest(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext)), MData(FUNCTION_MOVE(Other.MData)), MWriteExpirationTime(Other.MWriteExpirationTime)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketWrite::~CSocketTCPClientManagerMessageRequestSocketWrite(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketWrite& CSocketTCPClientManagerMessageRequestSocketWrite::operator=(const CSocketTCPClientManagerMessageRequestSocketWrite& Other)
	{
		CSocketTCPClientManagerMessageRequest::operator=(Other);

		MMessageContext=Other.MMessageContext;
		MData=Other.MData;
		MWriteExpirationTime=Other.MWriteExpirationTime;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketWrite& CSocketTCPClientManagerMessageRequestSocketWrite::operator=(CSocketTCPClientManagerMessageRequestSocketWrite&& Other) noexcept
	{
		CSocketTCPClientManagerMessageRequest::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);
		MData=FUNCTION_MOVE(Other.MData);
		MWriteExpirationTime=FUNCTION_MOVE(Other.MWriteExpirationTime);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPClientManagerMessageRequestSocketWrite::ToString(void) const
	{
		return(CString::Format("TCP CLIENT MANAGER MESSAGE REQUEST SOCKET WRITE - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"] DATA [",MData,"] LENGTH [",MData->GetLength(),"] WRITE EXPIRATION TIME [",MWriteExpirationTime,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPClientManagerMessageResponse CSocketTCPClientManagerMessageRequestSocketWrite::CreateErrorResponse(void) const
	{
		return(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketWrite(MSocketID,MMessageContext,false,nullptr,0)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPClientManagerMessageContext CSocketTCPClientManagerMessageRequestSocketWrite::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPByteBuffer CSocketTCPClientManagerMessageRequestSocketWrite::GetData(void) const noexcept
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CExpirationTime& CSocketTCPClientManagerMessageRequestSocketWrite::GetWriteExpirationTime(void) const noexcept
	{
		return(MWriteExpirationTime);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------