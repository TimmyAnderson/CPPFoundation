//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPReceiveFromParameters.h"
#include <Framework/Foundation/Exceptions/CArgumentException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPReceiveFromParameters::CSocketUDPReceiveFromParameters(CSPByteBuffer Data, Size Offset, Size NumberOfBytesToReceive)
		: MData(Data), MOffset(Offset), MNumberOfBytesToReceive(NumberOfBytesToReceive)
	{
		Data.VerifyNotNULL(MACRO_VARIABLE_TO_STRING(Data));

		if (Offset>=Data->GetLength())
		{
			throw(CArgumentException(CString::Format("ARGUMENT [",MACRO_VARIABLE_TO_STRING(Offset),"] has INVALID VALUE !")));
		}

		if (NumberOfBytesToReceive==0 || (Offset+NumberOfBytesToReceive)>Data->GetLength())
		{
			throw(CArgumentException(CString::Format("ARGUMENT [",MACRO_VARIABLE_TO_STRING(NumberOfBytesToReceive),"] has INVALID VALUE !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPReceiveFromParameters::~CSocketUDPReceiveFromParameters(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSPByteBuffer CSocketUDPReceiveFromParameters::GetData(void) const noexcept
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketUDPReceiveFromParameters::GetOffset(void) const noexcept
	{
		return(MOffset);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketUDPReceiveFromParameters::GetNumberOfBytesToReceive(void) const noexcept
	{
		return(MNumberOfBytesToReceive);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------