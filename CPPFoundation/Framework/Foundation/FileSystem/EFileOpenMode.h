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
	enum class EFileOpenMode : uint8
	{
//----------------------------------------------------------------------------------------------------------------------
		// CREATES a new file or TRUNCATES an existing file.
		E_CREATE=0x01,
		// CREATES a new file or FAILS if file exists.
		E_CREATE_NEW=0x02,
		// OPEN an existing file or FAILS if file exists.
		E_OPEN=0x03,
		// OPEN an existing file or CREATES a new file.
		E_OPEN_OR_CREATE=0x04,
		// OPEN and TRUNCATE an existing file or FAILS if file does not exist.
		E_OPEN_AND_TRUNCATE=0x05
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline CString& operator<<(CString& Text, EFileOpenMode Value)
	{
		switch(Value)
		{
			case EFileOpenMode::E_CREATE:
			{
				Text+="CREATE";
			}
			break;

			case EFileOpenMode::E_CREATE_NEW:
			{
				Text+="CREATE NEW";
			}
			break;

			case EFileOpenMode::E_OPEN:
			{
				Text+="OPEN";
			}
			break;

			case EFileOpenMode::E_OPEN_OR_CREATE:
			{
				Text+="OPEN OR CREATE";
			}
			break;

			case EFileOpenMode::E_OPEN_AND_TRUNCATE:
			{
				Text+="OPEN AND TRUNCATE";
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
	inline bool IsValidValue(EFileOpenMode Value)
	{
		switch(Value)
		{
			case EFileOpenMode::E_CREATE:
			case EFileOpenMode::E_CREATE_NEW:
			case EFileOpenMode::E_OPEN:
			case EFileOpenMode::E_OPEN_OR_CREATE:
			case EFileOpenMode::E_OPEN_AND_TRUNCATE:
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
	inline bool ParseValue(const CString& TextValue, EFileOpenMode& Value)
	{
		CString													AdjustedTextValue=CString::ToUpperString(TextValue);

		if (AdjustedTextValue=="CREATE")
		{
			Value=EFileOpenMode::E_CREATE;

			return(true);
		}
		else if (AdjustedTextValue=="CREATE NEW")
		{
			Value=EFileOpenMode::E_CREATE_NEW;

			return(true);
		}
		else if (AdjustedTextValue=="OPEN")
		{
			Value=EFileOpenMode::E_OPEN;

			return(true);
		}
		else if (AdjustedTextValue=="OPEN OR CREATE")
		{
			Value=EFileOpenMode::E_OPEN_OR_CREATE;

			return(true);
		}
		else if (AdjustedTextValue=="OPEN AND TRUNCATE")
		{
			Value=EFileOpenMode::E_OPEN_AND_TRUNCATE;

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