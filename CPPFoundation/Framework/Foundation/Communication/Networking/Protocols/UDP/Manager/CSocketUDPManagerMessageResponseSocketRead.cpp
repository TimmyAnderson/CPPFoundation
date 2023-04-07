//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPManagerMessageResponseSocketRead.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketRead::CSocketUDPManagerMessageResponseSocketRead(const CSocketID& SocketID, const CSocketUDPAddress& SourceAddress, CCSPByteBuffer Data)
		: CSocketUDPManagerMessageResponse(SocketID), MSourceAddress(SourceAddress), MData(Data)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketRead::CSocketUDPManagerMessageResponseSocketRead(const CSocketUDPManagerMessageResponseSocketRead& Other)
		: CSocketUDPManagerMessageResponse(Other.MSocketID), MSourceAddress(Other.MSourceAddress), MData(Other.MData)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketRead::CSocketUDPManagerMessageResponseSocketRead(CSocketUDPManagerMessageResponseSocketRead&& Other)
		: CSocketUDPManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID)), MSourceAddress(FUNCTION_MOVE(Other.MSourceAddress)), MData(FUNCTION_MOVE(Other.MData))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketRead::~CSocketUDPManagerMessageResponseSocketRead(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketRead& CSocketUDPManagerMessageResponseSocketRead::operator=(const CSocketUDPManagerMessageResponseSocketRead& Other)
	{
		CSocketUDPManagerMessageResponse::operator=(Other);

		MSourceAddress=Other.MSourceAddress;
		MData=Other.MData;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketRead& CSocketUDPManagerMessageResponseSocketRead::operator=(CSocketUDPManagerMessageResponseSocketRead&& Other)
	{
		CSocketUDPManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		MSourceAddress=FUNCTION_MOVE(Other.MSourceAddress);
		MData=FUNCTION_MOVE(Other.MData);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketUDPManagerMessageResponseSocketRead::ToString(void) const
	{
		return(CString::Format("UDP MANAGER MESSAGE RESPONSE SOCKET READ - SOCKET ID [",MSocketID,"] SOURCE ADDRESS [",MSourceAddress,"] DATA [",MData,"] LENGTH [",MData->GetLength(),"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketUDPAddress& CSocketUDPManagerMessageResponseSocketRead::GetSourceAddress(void) const noexcept
	{
		return(MSourceAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPByteBuffer CSocketUDPManagerMessageResponseSocketRead::GetData(void) const noexcept
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------