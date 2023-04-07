//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANManagerMessageResponseSocketRead.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketRead::CSocketCANManagerMessageResponseSocketRead(const CSocketID& SocketID, const CSocketCANAddress& SourceAddress, CCSPByteBuffer Data)
		: CSocketCANManagerMessageResponse(SocketID), MSourceAddress(SourceAddress), MData(Data)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketRead::CSocketCANManagerMessageResponseSocketRead(const CSocketCANManagerMessageResponseSocketRead& Other)
		: CSocketCANManagerMessageResponse(Other.MSocketID), MSourceAddress(Other.MSourceAddress), MData(Other.MData)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketRead::CSocketCANManagerMessageResponseSocketRead(CSocketCANManagerMessageResponseSocketRead&& Other)
		: CSocketCANManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID)), MSourceAddress(FUNCTION_MOVE(Other.MSourceAddress)), MData(FUNCTION_MOVE(Other.MData))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketRead::~CSocketCANManagerMessageResponseSocketRead(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketRead& CSocketCANManagerMessageResponseSocketRead::operator=(const CSocketCANManagerMessageResponseSocketRead& Other)
	{
		CSocketCANManagerMessageResponse::operator=(Other);

		MSourceAddress=Other.MSourceAddress;
		MData=Other.MData;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketRead& CSocketCANManagerMessageResponseSocketRead::operator=(CSocketCANManagerMessageResponseSocketRead&& Other)
	{
		CSocketCANManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		MSourceAddress=FUNCTION_MOVE(Other.MSourceAddress);
		MData=FUNCTION_MOVE(Other.MData);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketCANManagerMessageResponseSocketRead::ToString(void) const
	{
		return(CString::Format("CAN MANAGER MESSAGE RESPONSE SOCKET READ - SOCKET ID [",MSocketID,"] SOURCE ADDRESS [",MSourceAddress,"] DATA [",MData,"] LENGTH [",MData->GetLength(),"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketCANAddress& CSocketCANManagerMessageResponseSocketRead::GetSourceAddress(void) const noexcept
	{
		return(MSourceAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPByteBuffer CSocketCANManagerMessageResponseSocketRead::GetData(void) const noexcept
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------