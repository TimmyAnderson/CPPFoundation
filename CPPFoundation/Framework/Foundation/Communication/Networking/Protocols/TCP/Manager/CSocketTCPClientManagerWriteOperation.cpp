//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerWriteOperation.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerWriteOperation::CSocketTCPClientManagerWriteOperation(CCSPSocketTCPClientManagerMessageRequestSocketWrite Packet)
		: MPacket(Packet), MNumberOfBytesToWrite(Packet->GetData()->GetLength()), MNumberOfBytesWritten(0)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerWriteOperation::~CSocketTCPClientManagerWriteOperation(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPClientManagerMessageRequestSocketWrite CSocketTCPClientManagerWriteOperation::GetPacket(void) const noexcept
	{
		return(MPacket);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPClientManagerWriteOperation::WriteOperationCompleted(void) const noexcept
	{
		if (GetNumberOfBytesToWrite()<=0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketTCPClientManagerWriteOperation::GetNumberOfBytesToWrite(void) const noexcept
	{
		return(MNumberOfBytesToWrite);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketTCPClientManagerWriteOperation::GetNumberOfBytesWritten(void) const noexcept
	{
		return(MNumberOfBytesWritten);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManagerWriteOperation::AddNumberOfBytesWritten(Size Value) noexcept
	{
		MNumberOfBytesWritten+=Value;
		MNumberOfBytesToWrite-=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------