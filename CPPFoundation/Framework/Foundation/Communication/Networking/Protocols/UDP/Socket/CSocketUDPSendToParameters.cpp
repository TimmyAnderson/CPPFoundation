//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPSendToParameters.h"
#include <Framework/Foundation/Exceptions/CArgumentException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPSendToParameters::CSocketUDPSendToParameters(const CSocketAddress& Address, CCSPByteBuffer Data, Size Offset, Size NumberOfBytesToSend)
		: MAddress(Address.DynamicCastReference<CSocketUDPAddress>()), MData(Data), MOffset(Offset), MNumberOfBytesToSend(NumberOfBytesToSend)
	{
		if (Address.IsTypeOf<CSocketUDPAddress>()==false)
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
	CSocketUDPSendToParameters::~CSocketUDPSendToParameters(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketAddress& CSocketUDPSendToParameters::GetAddress(void) const noexcept
	{
		return(MAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPByteBuffer CSocketUDPSendToParameters::GetData(void) const noexcept
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketUDPSendToParameters::GetOffset(void) const noexcept
	{
		return(MOffset);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketUDPSendToParameters::GetNumberOfBytesToSend(void) const noexcept
	{
		return(MNumberOfBytesToSend);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketUDPAddress& CSocketUDPSendToParameters::GetUDPAddress(void) const noexcept
	{
		return(MAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------