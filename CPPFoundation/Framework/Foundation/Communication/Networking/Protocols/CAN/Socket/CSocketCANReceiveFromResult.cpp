//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANReceiveFromResult.h"
#include <Framework/Foundation/Exceptions/CArgumentException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANReceiveFromResult::CSocketCANReceiveFromResult(void)
		: MData(), MOffset(), MNumberOfReceivedBytes(), MAddress()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANReceiveFromResult::~CSocketCANReceiveFromResult(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSPByteBuffer CSocketCANReceiveFromResult::GetData(void) const noexcept
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketCANReceiveFromResult::GetOffset(void) const noexcept
	{
		return(MOffset);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketCANReceiveFromResult::GetNumberOfReceivedBytes(void) const noexcept
	{
		return(MNumberOfReceivedBytes);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketAddress& CSocketCANReceiveFromResult::GetAddress(void) const noexcept
	{
		return(MAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANReceiveFromResult::SetResult(CSPByteBuffer Data, Size Offset, Size NumberOfReceivedBytes, const CSocketAddress& Address)
	{
		if (Address.IsTypeOf<CSocketCANAddress>()==false)
		{
			throw(CArgumentException(CString::Format("ARGUMENT [",MACRO_VARIABLE_TO_STRING(Address),"] has INVALID VALUE TYPE !")));
		}

		MData=Data;
		MOffset=Offset;
		MNumberOfReceivedBytes=NumberOfReceivedBytes;
		MAddress=Address.DynamicCastReference<CSocketCANAddress>();
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketCANAddress& CSocketCANReceiveFromResult::GetCANAddress(void) const noexcept
	{
		return(MAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------