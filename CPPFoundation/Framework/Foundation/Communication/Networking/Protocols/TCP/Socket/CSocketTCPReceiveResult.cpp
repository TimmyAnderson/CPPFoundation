//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPReceiveResult.h"
#include <Framework/Foundation/Exceptions/CArgumentException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPReceiveResult::CSocketTCPReceiveResult(void)
		: MOperationSucceeded(false), MData(), MOffset(0), MNumberOfReceivedBytes(0)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPReceiveResult::~CSocketTCPReceiveResult(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPReceiveResult::GetOperationSucceeded(void) const noexcept
	{
		return(MOperationSucceeded);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPByteBuffer CSocketTCPReceiveResult::GetData(void) const noexcept
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketTCPReceiveResult::GetOffset(void) const noexcept
	{
		return(MOffset);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketTCPReceiveResult::GetNumberOfReceivedBytes(void) const noexcept
	{
		return(MNumberOfReceivedBytes);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPReceiveResult::SetResult(bool OperationSucceeded, CSPByteBuffer Data, Size Offset, Size NumberOfReceivedBytes)
	{
		MOperationSucceeded=OperationSucceeded;
		MData=Data;
		MOffset=Offset;
		MNumberOfReceivedBytes=NumberOfReceivedBytes;
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------