//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANSendToParameters.h"
#include <Framework/Foundation/Exceptions/CArgumentException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANSendToParameters::CSocketCANSendToParameters(const CSocketAddress& Address, CCSPByteBuffer Data, Size Offset, Size NumberOfBytesToSend)
		: MAddress(Address.DynamicCastReference<CSocketCANAddress>()), MData(Data), MOffset(Offset), MNumberOfBytesToSend(NumberOfBytesToSend)
	{
		if (Address.IsTypeOf<CSocketCANAddress>()==false)
		{
			throw(CArgumentException(CString::Format("ARGUMENT [",MACRO_VARIABLE_TO_STRING(Address),"] has INVALID VALUE TYPE !")));
		}

		Data.VerifyNotNULL(MACRO_VARIABLE_TO_STRING(Data));

		if (Offset>=Data->GetLength())
		{
			throw(CArgumentException(CString::Format("ARGUMENT [",MACRO_VARIABLE_TO_STRING(Offset),"] has INVALID VALUE !")));
		}

		if (NumberOfBytesToSend==0 || (Offset+NumberOfBytesToSend)>Data->GetLength())
		{
			throw(CArgumentException(CString::Format("ARGUMENT [",MACRO_VARIABLE_TO_STRING(NumberOfBytesToSend),"] has INVALID VALUE !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANSendToParameters::~CSocketCANSendToParameters(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketAddress& CSocketCANSendToParameters::GetAddress(void) const noexcept
	{
		return(MAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPByteBuffer CSocketCANSendToParameters::GetData(void) const noexcept
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketCANSendToParameters::GetOffset(void) const noexcept
	{
		return(MOffset);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketCANSendToParameters::GetNumberOfBytesToSend(void) const noexcept
	{
		return(MNumberOfBytesToSend);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketCANAddress& CSocketCANSendToParameters::GetCANAddress(void) const noexcept
	{
		return(MAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------