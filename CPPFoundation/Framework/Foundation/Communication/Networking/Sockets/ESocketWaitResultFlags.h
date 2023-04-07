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
	enum class ESocketWaitResultFlags : uint8
	{
//----------------------------------------------------------------------------------------------------------------------
		E_NONE=0x00,
		E_READ=0x01,
		E_WRITE=0x02,
		E_CLOSE=0x04,
		E_ERROR=0x08,
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline ESocketWaitResultFlags& operator|=(ESocketWaitResultFlags& Value1, ESocketWaitResultFlags Value2)
	{
		uint8													RawValue1=static_cast<uint8>(Value1);
		uint8													RawValue2=static_cast<uint8>(Value2);
		uint8													RawResult=static_cast<uint8>(RawValue1 | RawValue2);

		Value1=static_cast<ESocketWaitResultFlags>(RawResult);

		return(Value1);
	}
//----------------------------------------------------------------------------------------------------------------------
	inline ESocketWaitResultFlags operator&(ESocketWaitResultFlags Value1, ESocketWaitResultFlags Value2)
	{
		uint8													RawValue1=static_cast<uint8>(Value1);
		uint8													RawValue2=static_cast<uint8>(Value2);
		uint8													RawResult=static_cast<uint8>(RawValue1 & RawValue2);
		ESocketWaitResultFlags									Result=static_cast<ESocketWaitResultFlags>(RawResult);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline CString& operator<<(CString& Text, ESocketWaitResultFlags Value)
	{
		CString													TextValue;

		if (Value==ESocketWaitResultFlags::E_NONE)
		{
			TextValue="NONE";
		}
		else
		{
			if ((Value & ESocketWaitResultFlags::E_READ)!=ESocketWaitResultFlags::E_NONE)
			{
				if (TextValue.IsEmpty()==false)
				{
					TextValue+=" | ";
				}

				TextValue+="READ";
			}

			if ((Value & ESocketWaitResultFlags::E_WRITE)!=ESocketWaitResultFlags::E_NONE)
			{
				if (TextValue.IsEmpty()==false)
				{
					TextValue+=" | ";
				}

				TextValue+="WRITE";
			}

			if ((Value & ESocketWaitResultFlags::E_CLOSE)!=ESocketWaitResultFlags::E_NONE)
			{
				if (TextValue.IsEmpty()==false)
				{
					TextValue+=" | ";
				}

				TextValue+="CLOSE";
			}

			if ((Value & ESocketWaitResultFlags::E_ERROR)!=ESocketWaitResultFlags::E_NONE)
			{
				if (TextValue.IsEmpty()==false)
				{
					TextValue+=" | ";
				}

				TextValue+="ERROR";
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