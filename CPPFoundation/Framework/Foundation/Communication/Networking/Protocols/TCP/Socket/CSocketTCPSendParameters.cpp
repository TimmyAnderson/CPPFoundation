//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPSendParameters.h"
#include <Framework/Foundation/Exceptions/CArgumentException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPSendParameters::CSocketTCPSendParameters(CCSPByteBuffer Data, Size Offset, Size NumberOfBytesToSend)
		: MData(Data), MOffset(Offset), MNumberOfBytesToSend(NumberOfBytesToSend)
	{
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
	CSocketTCPSendParameters::~CSocketTCPSendParameters(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CCSPByteBuffer CSocketTCPSendParameters::GetData(void) const noexcept
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketTCPSendParameters::GetOffset(void) const noexcept
	{
		return(MOffset);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketTCPSendParameters::GetNumberOfBytesToSend(void) const noexcept
	{
		return(MNumberOfBytesToSend);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------