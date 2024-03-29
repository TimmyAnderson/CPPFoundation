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
	enum class EFileSeekMode : uint8
	{
//----------------------------------------------------------------------------------------------------------------------
		E_BEGIN=0x01,
		E_CURRENT=0x02,
		E_END=0x03
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline CString& operator<<(CString& Text, EFileSeekMode Value)
	{
		switch(Value)
		{
			case EFileSeekMode::E_BEGIN:
			{
				Text+="BEGIN";
			}
			break;

			case EFileSeekMode::E_CURRENT:
			{
				Text+="CURRENT";
			}
			break;

			case EFileSeekMode::E_END:
			{
				Text+="END";
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
	inline bool IsValidValue(EFileSeekMode Value)
	{
		switch(Value)
		{
			case EFileSeekMode::E_BEGIN:
			case EFileSeekMode::E_CURRENT:
			case EFileSeekMode::E_END:
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
	inline bool ParseValue(const CString& TextValue, EFileSeekMode& Value)
	{
		CString													AdjustedTextValue=CString::ToUpperString(TextValue);

		if (AdjustedTextValue=="BEGIN")
		{
			Value=EFileSeekMode::E_BEGIN;

			return(true);
		}
		else if (AdjustedTextValue=="CURRENT")
		{
			Value=EFileSeekMode::E_CURRENT;

			return(true);
		}
		else if (AdjustedTextValue=="END")
		{
			Value=EFileSeekMode::E_END;

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