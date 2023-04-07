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
	enum class ESocketWaitFlags : uint8
	{
//----------------------------------------------------------------------------------------------------------------------
		E_NONE=0x00,
		E_READ=0x01,
		E_WRITE=0x02,
		E_CLOSE=0x04,
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline ESocketWaitFlags& operator|=(ESocketWaitFlags& Value1, ESocketWaitFlags Value2)
	{
		uint8													RawValue1=static_cast<uint8>(Value1);
		uint8													RawValue2=static_cast<uint8>(Value2);
		uint8													RawResult=static_cast<uint8>(RawValue1 | RawValue2);

		Value1=static_cast<ESocketWaitFlags>(RawResult);

		return(Value1);
	}
//----------------------------------------------------------------------------------------------------------------------
	inline ESocketWaitFlags operator|(ESocketWaitFlags Value1, ESocketWaitFlags Value2)
	{
		uint8													RawValue1=static_cast<uint8>(Value1);
		uint8													RawValue2=static_cast<uint8>(Value2);
		uint8													RawResult=static_cast<uint8>(RawValue1 | RawValue2);
		ESocketWaitFlags										Result=static_cast<ESocketWaitFlags>(RawResult);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	inline ESocketWaitFlags operator&(ESocketWaitFlags Value1, ESocketWaitFlags Value2)
	{
		uint8													RawValue1=static_cast<uint8>(Value1);
		uint8													RawValue2=static_cast<uint8>(Value2);
		uint8													RawResult=static_cast<uint8>(RawValue1 & RawValue2);
		ESocketWaitFlags										Result=static_cast<ESocketWaitFlags>(RawResult);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline CString& operator<<(CString& Text, ESocketWaitFlags Value)
	{
		CString													TextValue;

		if (Value==ESocketWaitFlags::E_NONE)
		{
			TextValue="NONE";
		}
		else
		{
			if ((Value & ESocketWaitFlags::E_READ)!=ESocketWaitFlags::E_NONE)
			{
				if (TextValue.IsEmpty()==false)
				{
					TextValue+=" | ";
				}

				TextValue+="READ";
			}

			if ((Value & ESocketWaitFlags::E_WRITE)!=ESocketWaitFlags::E_NONE)
			{
				if (TextValue.IsEmpty()==false)
				{
					TextValue+=" | ";
				}

				TextValue+="WRITE";
			}

			if ((Value & ESocketWaitFlags::E_CLOSE)!=ESocketWaitFlags::E_NONE)
			{
				if (TextValue.IsEmpty()==false)
				{
					TextValue+=" | ";
				}

				TextValue+="CLOSE";
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