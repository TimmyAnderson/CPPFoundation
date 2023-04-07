//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageResponseSocketWrite.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketWrite::CSocketTCPClientManagerMessageResponseSocketWrite(const CSocketID& SocketID, CCSPSocketTCPClientManagerMessageContext MessageContext, bool OperationSucceeded, CCSPByteBuffer Data, Size NumberOfBytesWritten)
		: CSocketTCPClientManagerMessageResponse(SocketID), MMessageContext(MessageContext), MOperationSucceeded(OperationSucceeded), MData(Data), MNumberOfBytesWritten(NumberOfBytesWritten)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketWrite::CSocketTCPClientManagerMessageResponseSocketWrite(const CSocketTCPClientManagerMessageResponseSocketWrite& Other)
		: CSocketTCPClientManagerMessageResponse(Other.MSocketID), MMessageContext(Other.MMessageContext), MOperationSucceeded(Other.MOperationSucceeded), MData(Other.MData), MNumberOfBytesWritten(Other.MNumberOfBytesWritten)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketWrite::CSocketTCPClientManagerMessageResponseSocketWrite(CSocketTCPClientManagerMessageResponseSocketWrite&& Other)
		: CSocketTCPClientManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext)), MOperationSucceeded(Other.MOperationSucceeded), MData(FUNCTION_MOVE(Other.MData)), MNumberOfBytesWritten(Other.MNumberOfBytesWritten)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketWrite::~CSocketTCPClientManagerMessageResponseSocketWrite(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketWrite& CSocketTCPClientManagerMessageResponseSocketWrite::operator=(const CSocketTCPClientManagerMessageResponseSocketWrite& Other)
	{
		CSocketTCPClientManagerMessageResponse::operator=(Other);

		MMessageContext=Other.MMessageContext;
		MOperationSucceeded=Other.MOperationSucceeded;
		MData=Other.MData;
		MNumberOfBytesWritten=Other.MNumberOfBytesWritten;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketWrite& CSocketTCPClientManagerMessageResponseSocketWrite::operator=(CSocketTCPClientManagerMessageResponseSocketWrite&& Other)
	{
		CSocketTCPClientManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);
		MOperationSucceeded=Other.MOperationSucceeded;
		MData=FUNCTION_MOVE(Other.MData);
		MNumberOfBytesWritten=Other.MNumberOfBytesWritten;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPClientManagerMessageResponseSocketWrite::ToString(void) const
	{
		return(CString::Format("TCP CLIENT MANAGER MESSAGE RESPONSE SOCKET WRITE - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"] OPERATION SUCCEEDED [",MOperationSucceeded,"] DATA [",MData,"] LENGTH [",MData->GetLength(),"] NUMBER of BYTES WRITTEN [",MNumberOfBytesWritten,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPClientManagerMessageContext CSocketTCPClientManagerMessageResponseSocketWrite::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPClientManagerMessageResponseSocketWrite::GetOperationSucceeded(void) const noexcept
	{
		return(MOperationSucceeded);
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPByteBuffer CSocketTCPClientManagerMessageResponseSocketWrite::GetData(void) const noexcept
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketTCPClientManagerMessageResponseSocketWrite::GetNumberOfBytesWritten(void) const noexcept
	{
		return(MNumberOfBytesWritten);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------