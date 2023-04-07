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
	enum class EFileAccessMode : uint8
	{
//----------------------------------------------------------------------------------------------------------------------
		E_READ=0x01,
		E_WRITE=0x02,
		E_READ_WRITE=E_READ | E_WRITE
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline CString& operator<<(CString& Text, EFileAccessMode Value)
	{
		switch(Value)
		{
			case EFileAccessMode::E_READ:
			{
				Text+="READ";
			}
			break;

			case EFileAccessMode::E_WRITE:
			{
				Text+="WRITE";
			}
			break;

			case EFileAccessMode::E_READ_WRITE:
			{
				Text+="READ WRITE";
			}
			break;

			default:
			{
				Text+="UNKNOWN";
			}
			break;
		}

		return(Text);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline EFileAccessMode operator|(EFileAccessMode Value1, EFileAccessMode Value2)
	{
		uint8													RawValue1=static_cast<uint8>(Value1);
		uint8													RawValue2=static_cast<uint8>(Value2);
		uint8													RawResult=RawValue1 | RawValue2;
		EFileAccessMode											Result=static_cast<EFileAccessMode>(RawResult);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	inline EFileAccessMode operator&(EFileAccessMode Value1, EFileAccessMode Value2)
	{
		uint8													RawValue1=static_cast<uint8>(Value1);
		uint8													RawValue2=static_cast<uint8>(Value2);
		uint8													RawResult=RawValue1 & RawValue2;
		EFileAccessMode											Result=static_cast<EFileAccessMode>(RawResult);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline bool IsValidValue(EFileAccessMode Value)
	{
		switch(Value)
		{
			case EFileAccessMode::E_READ:
			case EFileAccessMode::E_WRITE:
			case EFileAccessMode::E_READ_WRITE:
			{
				return(true);
			}

			default:
			{
				return(true);
			}
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
	inline bool ParseValue(const CString& TextValue, EFileAccessMode& Value)
	{
		CString													AdjustedTextValue=CString::ToUpperString(TextValue);

		if (AdjustedTextValue=="READ")
		{
			Value=EFileAccessMode::E_READ;

			return(true);
		}
		else if (AdjustedTextValue=="WRITE")
		{
			Value=EFileAccessMode::E_WRITE;

			return(true);
		}
		else if (AdjustedTextValue=="READ WRITE")
		{
			Value=EFileAccessMode::E_READ_WRITE;

			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------