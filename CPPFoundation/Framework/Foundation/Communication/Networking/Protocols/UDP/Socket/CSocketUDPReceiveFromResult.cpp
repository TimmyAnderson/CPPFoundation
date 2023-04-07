//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPReceiveFromResult.h"
#include <Framework/Foundation/Exceptions/CArgumentException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPReceiveFromResult::CSocketUDPReceiveFromResult(void)
		: MData(), MOffset(0), MNumberOfReceivedBytes(0), MAddress()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPReceiveFromResult::~CSocketUDPReceiveFromResult(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSPByteBuffer CSocketUDPReceiveFromResult::GetData(void) const noexcept
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketUDPReceiveFromResult::GetOffset(void) const noexcept
	{
		return(MOffset);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketUDPReceiveFromResult::GetNumberOfReceivedBytes(void) const noexcept
	{
		return(MNumberOfReceivedBytes);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketAddress& CSocketUDPReceiveFromResult::GetAddress(void) const noexcept
	{
		return(MAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPReceiveFromResult::SetResult(CSPByteBuffer Data, Size Offset, Size NumberOfReceivedBytes, const CSocketAddress& Address)
	{
		if (Address.IsTypeOf<CSocketUDPAddress>()==false)
		{
			throw(CArgumentException(CString::Format("ARGUMENT [",MACRO_VARIABLE_TO_STRING(Address),"] has INVALID VALUE TYPE !")));
		}

		MData=Data;
		MOffset=Offset;
		MNumberOfReceivedBytes=NumberOfReceivedBytes;
		MAddress=Address.DynamicCastReference<CSocketUDPAddress>();
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketUDPAddress& CSocketUDPReceiveFromResult::GetUDPAddress(void) const noexcept
	{
		return(MAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------