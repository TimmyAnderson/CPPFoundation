//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Strings/CString.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	enum class ESocketTCPShutdownFlags : uint8
	{
//----------------------------------------------------------------------------------------------------------------------
		E_NONE=0x00,
		E_READ=0x01,
		E_WRITE=0x02,
		E_READ_WRITE=E_READ | E_WRITE,
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline ESocketTCPShutdownFlags operator|(ESocketTCPShutdownFlags Value1, ESocketTCPShutdownFlags Value2)
	{
		uint8													RawValue1=static_cast<uint8>(Value1);
		uint8													RawValue2=static_cast<uint8>(Value2);
		uint8													RawResult=RawValue1 | RawValue2;
		ESocketTCPShutdownFlags									Result=static_cast<ESocketTCPShutdownFlags>(RawResult);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	inline ESocketTCPShutdownFlags operator&(ESocketTCPShutdownFlags Value1, ESocketTCPShutdownFlags Value2)
	{
		uint8													RawValue1=static_cast<uint8>(Value1);
		uint8													RawValue2=static_cast<uint8>(Value2);
		uint8													RawResult=RawValue1 & RawValue2;
		ESocketTCPShutdownFlags									Result=static_cast<ESocketTCPShutdownFlags>(RawResult);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline CString& operator<<(CString& Text, ESocketTCPShutdownFlags Value)
	{
		CString													TextValue;

		if (Value==ESocketTCPShutdownFlags::E_NONE)
		{
			TextValue="NONE";
		}
		else
		{
			if ((Value & ESocketTCPShutdownFlags::E_READ)!=ESocketTCPShutdownFlags::E_NONE)
			{
				if (TextValue.IsEmpty()==false)
				{
					TextValue+=" | ";
				}

				TextValue+="READ";
			}

			if ((Value & ESocketTCPShutdownFlags::E_WRITE)!=ESocketTCPShutdownFlags::E_NONE)
			{
				if (TextValue.IsEmpty()==false)
				{
					TextValue+=" | ";
				}

				TextValue+="WRITE";
			}
		}

		Text+=TextValue;

		return(Text);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------