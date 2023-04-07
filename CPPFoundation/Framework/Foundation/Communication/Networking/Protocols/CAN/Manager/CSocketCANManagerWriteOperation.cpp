//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANManagerWriteOperation.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerWriteOperation::CSocketCANManagerWriteOperation(CCSPSocketCANManagerMessageRequestSocketWrite Packet)
		: MPacket(Packet), MNumberOfBytesToWrite(Packet->GetData()->GetLength()), MNumberOfBytesWritten(0)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerWriteOperation::~CSocketCANManagerWriteOperation(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketCANManagerMessageRequestSocketWrite CSocketCANManagerWriteOperation::GetPacket(void) const noexcept
	{
		return(MPacket);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketCANManagerWriteOperation::GetNumberOfBytesToWrite(void) const noexcept
	{
		return(MNumberOfBytesToWrite);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketCANManagerWriteOperation::GetNumberOfBytesWritten(void) const noexcept
	{
		return(MNumberOfBytesWritten);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerWriteOperation::AddNumberOfBytesWritten(Size Value) noexcept
	{
		MNumberOfBytesWritten+=Value;
		MNumberOfBytesToWrite-=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------