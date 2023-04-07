//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageResponseSocketRead.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketRead::CSocketTCPClientManagerMessageResponseSocketRead(const CSocketID& SocketID, CCSPByteBuffer Data)
		: CSocketTCPClientManagerMessageResponse(SocketID), MData(Data)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketRead::CSocketTCPClientManagerMessageResponseSocketRead(const CSocketTCPClientManagerMessageResponseSocketRead& Other)
		: CSocketTCPClientManagerMessageResponse(Other.MSocketID), MData(Other.MData)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketRead::CSocketTCPClientManagerMessageResponseSocketRead(CSocketTCPClientManagerMessageResponseSocketRead&& Other) noexcept
		: CSocketTCPClientManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID)), MData(FUNCTION_MOVE(Other.MData))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketRead::~CSocketTCPClientManagerMessageResponseSocketRead(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketRead& CSocketTCPClientManagerMessageResponseSocketRead::operator=(const CSocketTCPClientManagerMessageResponseSocketRead& Other)
	{
		CSocketTCPClientManagerMessageResponse::operator=(Other);

		MData=Other.MData;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketRead& CSocketTCPClientManagerMessageResponseSocketRead::operator=(CSocketTCPClientManagerMessageResponseSocketRead&& Other) noexcept
	{
		CSocketTCPClientManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		MData=FUNCTION_MOVE(Other.MData);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPClientManagerMessageResponseSocketRead::ToString(void) const
	{
		return(CString::Format("TCP CLIENT MANAGER MESSAGE RESPONSE SOCKET READ - SOCKET ID [",MSocketID,"] DATA [",MData,"] LENGTH [",MData->GetLength(),"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPByteBuffer CSocketTCPClientManagerMessageResponseSocketRead::GetData(void) const noexcept
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------