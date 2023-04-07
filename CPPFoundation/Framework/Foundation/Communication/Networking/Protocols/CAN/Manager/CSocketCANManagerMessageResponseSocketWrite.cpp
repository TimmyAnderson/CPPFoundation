//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANManagerMessageResponseSocketWrite.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketWrite::CSocketCANManagerMessageResponseSocketWrite(const CSocketID& SocketID, CCSPSocketCANManagerMessageContext MessageContext, bool OperationSucceeded, const CSocketCANAddress& DestinationAddress, CCSPByteBuffer Data, Size NumberOfBytesWritten)
		: CSocketCANManagerMessageResponse(SocketID), MMessageContext(MessageContext), MOperationSucceeded(OperationSucceeded), MDestinationAddress(DestinationAddress), MData(Data), MNumberOfBytesWritten(NumberOfBytesWritten)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketWrite::CSocketCANManagerMessageResponseSocketWrite(const CSocketCANManagerMessageResponseSocketWrite& Other)
		: CSocketCANManagerMessageResponse(Other.MSocketID), MMessageContext(Other.MMessageContext), MOperationSucceeded(Other.MOperationSucceeded), MDestinationAddress(Other.MDestinationAddress), MData(Other.MData), MNumberOfBytesWritten(Other.MNumberOfBytesWritten)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketWrite::CSocketCANManagerMessageResponseSocketWrite(CSocketCANManagerMessageResponseSocketWrite&& Other) noexcept
		: CSocketCANManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext)), MOperationSucceeded(Other.MOperationSucceeded), MDestinationAddress(FUNCTION_MOVE(Other.MDestinationAddress)), MData(FUNCTION_MOVE(Other.MData)), MNumberOfBytesWritten(Other.MNumberOfBytesWritten)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketWrite::~CSocketCANManagerMessageResponseSocketWrite(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketWrite& CSocketCANManagerMessageResponseSocketWrite::operator=(const CSocketCANManagerMessageResponseSocketWrite& Other)
	{
		CSocketCANManagerMessageResponse::operator=(Other);

		MMessageContext=Other.MMessageContext;
		MOperationSucceeded=Other.MOperationSucceeded;
		MDestinationAddress=Other.MDestinationAddress;
		MData=Other.MData;
		MNumberOfBytesWritten=Other.MNumberOfBytesWritten;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketWrite& CSocketCANManagerMessageResponseSocketWrite::operator=(CSocketCANManagerMessageResponseSocketWrite&& Other) noexcept
	{
		CSocketCANManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

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
	CString CSocketCANManagerMessageResponseSocketWrite::ToString(void) const
	{
		return(CString::Format("CAN MANAGER MESSAGE RESPONSE SOCKET WRITE - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"] OPERATION SUCCEEDED [",MOperationSucceeded,"] DESTINATION ADDRESS [",MDestinationAddress,"] DATA [",MData,"] LENGTH [",MData->GetLength(),"] NUMBER of BYTES WRITTEN [",MNumberOfBytesWritten,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketCANManagerMessageContext CSocketCANManagerMessageResponseSocketWrite::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketCANManagerMessageResponseSocketWrite::GetOperationSucceeded(void) const noexcept
	{
		return(MOperationSucceeded);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketCANAddress& CSocketCANManagerMessageResponseSocketWrite::GetDestinationAddress(void) const noexcept
	{
		return(MDestinationAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPByteBuffer CSocketCANManagerMessageResponseSocketWrite::GetData(void) const noexcept
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketCANManagerMessageResponseSocketWrite::GetNumberOfBytesWritten(void) const noexcept
	{
		return(MNumberOfBytesWritten);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------