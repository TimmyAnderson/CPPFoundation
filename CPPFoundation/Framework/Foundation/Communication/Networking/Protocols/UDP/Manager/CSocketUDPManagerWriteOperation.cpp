//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPManagerWriteOperation.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerWriteOperation::CSocketUDPManagerWriteOperation(CCSPSocketUDPManagerMessageRequestSocketWrite Packet)
		: MPacket(Packet), MNumberOfBytesToWrite(Packet->GetData()->GetLength()), MNumberOfBytesWritten(0)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerWriteOperation::~CSocketUDPManagerWriteOperation(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketUDPManagerMessageRequestSocketWrite CSocketUDPManagerWriteOperation::GetPacket(void) const noexcept
	{
		return(MPacket);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketUDPManagerWriteOperation::GetNumberOfBytesToWrite(void) const noexcept
	{
		return(MNumberOfBytesToWrite);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketUDPManagerWriteOperation::GetNumberOfBytesWritten(void) const noexcept
	{
		return(MNumberOfBytesWritten);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerWriteOperation::AddNumberOfBytesWritten(Size Value) noexcept
	{
		MNumberOfBytesWritten+=Value;
		MNumberOfBytesToWrite-=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------