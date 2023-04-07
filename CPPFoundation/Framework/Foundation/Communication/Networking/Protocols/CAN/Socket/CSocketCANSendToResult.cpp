//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANSendToResult.h"
#include <Framework/Foundation/Exceptions/CArgumentException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANSendToResult::CSocketCANSendToResult(void)
		: MAddress(), MData(), MOffset(0), MNumberOfSentBytes(0)

	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANSendToResult::~CSocketCANSendToResult(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketCANSendToResult::GetNumberOfSentBytes(void) const noexcept
	{
		return(MNumberOfSentBytes);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketAddress& CSocketCANSendToResult::GetAddress(void) const noexcept
	{
		return(MAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPByteBuffer CSocketCANSendToResult::GetData(void) const noexcept
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketCANSendToResult::GetOffset(void) const noexcept
	{
		return(MOffset);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANSendToResult::SetResult(const CSocketAddress& Address, CCSPByteBuffer Data, Size Offset, Size NumberOfSentBytes)
	{
		if (Address.IsTypeOf<CSocketCANAddress>()==false)
		{
			throw(CArgumentException(CString::Format("ARGUMENT [",MACRO_VARIABLE_TO_STRING(Address),"] has INVALID VALUE TYPE !")));
		}

		MAddress=Address.DynamicCastReference<CSocketCANAddress>();
		MData=Data;
		MOffset=Offset;
		MNumberOfSentBytes=NumberOfSentBytes;
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketCANAddress& CSocketCANSendToResult::GetCANAddress(void) const noexcept
	{
		return(MAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------