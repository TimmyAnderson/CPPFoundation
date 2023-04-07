//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPSendToResult.h"
#include <Framework/Foundation/Exceptions/CArgumentException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPSendToResult::CSocketUDPSendToResult(void)
		: MAddress(), MData(), MOffset(), MNumberOfSentBytes()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPSendToResult::~CSocketUDPSendToResult(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketAddress& CSocketUDPSendToResult::GetAddress(void) const noexcept
	{
		return(MAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPByteBuffer CSocketUDPSendToResult::GetData(void) const noexcept
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketUDPSendToResult::GetOffset(void) const noexcept
	{
		return(MOffset);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketUDPSendToResult::GetNumberOfSentBytes(void) const noexcept
	{
		return(MNumberOfSentBytes);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPSendToResult::SetResult(const CSocketAddress& Address, CCSPByteBuffer Data, Size Offset, Size NumberOfSentBytes)
	{
		if (Address.IsTypeOf<CSocketUDPAddress>()==false)
		{
			throw(CArgumentException(CString::Format("ARGUMENT [",MACRO_VARIABLE_TO_STRING(Address),"] has INVALID VALUE TYPE !")));
		}

		MAddress=Address.DynamicCastReference<CSocketUDPAddress>();
		MData=Data;
		MOffset=Offset;
		MNumberOfSentBytes=NumberOfSentBytes;
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketUDPAddress& CSocketUDPSendToResult::GetUDPAddress(void) const noexcept
	{
		return(MAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------