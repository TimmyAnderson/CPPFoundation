//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPManagerMessageResponseSocketWrite.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketWrite::CSocketUDPManagerMessageResponseSocketWrite(const CSocketID& SocketID, CCSPSocketUDPManagerMessageContext MessageContext, bool OperationSucceeded, const CSocketUDPAddress& DestinationAddress, CCSPByteBuffer Data, Size NumberOfBytesWritten)
		: CSocketUDPManagerMessageResponse(SocketID), MMessageContext(MessageContext), MOperationSucceeded(OperationSucceeded), MDestinationAddress(DestinationAddress), MData(Data), MNumberOfBytesWritten(NumberOfBytesWritten)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketWrite::CSocketUDPManagerMessageResponseSocketWrite(const CSocketUDPManagerMessageResponseSocketWrite& Other)
		: CSocketUDPManagerMessageResponse(Other.MSocketID), MMessageContext(Other.MMessageContext), MOperationSucceeded(Other.MOperationSucceeded), MDestinationAddress(Other.MDestinationAddress), MData(Other.MData), MNumberOfBytesWritten(Other.MNumberOfBytesWritten)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketWrite::CSocketUDPManagerMessageResponseSocketWrite(CSocketUDPManagerMessageResponseSocketWrite&& Other)
		: CSocketUDPManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext)), MOperationSucceeded(Other.MOperationSucceeded), MDestinationAddress(FUNCTION_MOVE(Other.MDestinationAddress)), MData(FUNCTION_MOVE(Other.MData)), MNumberOfBytesWritten(Other.MNumberOfBytesWritten)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketWrite::~CSocketUDPManagerMessageResponseSocketWrite(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketWrite& CSocketUDPManagerMessageResponseSocketWrite::operator=(const CSocketUDPManagerMessageResponseSocketWrite& Other)
	{
		CSocketUDPManagerMessageResponse::operator=(Other);

		MMessageContext=Other.MMessageContext;
		MOperationSucceeded=Other.MOperationSucceeded;
		MDestinationAddress=Other.MDestinationAddress;
		MData=Other.MData;
		MNumberOfBytesWritten=Other.MNumberOfBytesWritten;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketWrite& CSocketUDPManagerMessageResponseSocketWrite::operator=(CSocketUDPManagerMessageResponseSocketWrite&& Other)
	{
		CSocketUDPManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);
		MOperationSucceeded=Other.MOperationSucceeded;
		MDestinationAddress=FUNCTION_MOVE(Other.MDestinationAddress);
		MData=FUNCTION_MOVE(Other.MData);
		MNumberOfBytesWritten=Other.MNumberOfBytesWritten;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketUDPManagerMessageResponseSocketWrite::ToString(void) const
	{
		return(CString::Format("UDP MANAGER MESSAGE RESPONSE SOCKET WRITE - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"] OPERATION SUCCEEDED [",MOperationSucceeded,"] DESTINATION ADDRESS [",MDestinationAddress,"] DATA [",MData,"] LENGTH [",MData->GetLength(),"] NUMBER of BYTES WRITTEN [",MNumberOfBytesWritten,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketUDPManagerMessageContext CSocketUDPManagerMessageResponseSocketWrite::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketUDPManagerMessageResponseSocketWrite::GetOperationSucceeded(void) const noexcept
	{
		return(MOperationSucceeded);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketUDPAddress& CSocketUDPManagerMessageResponseSocketWrite::GetDestinationAddress(void) const noexcept
	{
		return(MDestinationAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPByteBuffer CSocketUDPManagerMessageResponseSocketWrite::GetData(void) const noexcept
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketUDPManagerMessageResponseSocketWrite::GetNumberOfBytesWritten(void) const noexcept
	{
		return(MNumberOfBytesWritten);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------