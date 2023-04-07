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
	enum class EFilePathSegmentType : uint8
	{
//----------------------------------------------------------------------------------------------------------------------
		E_ROOT=1,
		E_ROOT_DIRECTORY=2,
		E_DIRECTORY_OR_FILENAME=3
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline CString& operator<<(CString& Text, EFilePathSegmentType Value)
	{
		switch(Value)
		{
			case EFilePathSegmentType::E_ROOT:
			{
				Text+="ROOT";
			}
			break;

			case EFilePathSegmentType::E_ROOT_DIRECTORY:
			{
				Text+="ROOT DIRECTORY";
			}
			break;

			case EFilePathSegmentType::E_DIRECTORY_OR_FILENAME:
			{
				Text+="DIRECTORY OR FILENAME";
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
	inline bool IsValidValue(EFilePathSegmentType Value)
	{
		switch(Value)
		{
			case EFilePathSegmentType::E_ROOT:
			case EFilePathSegmentType::E_ROOT_DIRECTORY:
			case EFilePathSegmentType::E_DIRECTORY_OR_FILENAME:
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
	inline bool ParseValue(const CString& TextValue, EFilePathSegmentType& Value)
	{
		CString													AdjustedTextValue=CString::ToUpperString(TextValue);

		if (AdjustedTextValue=="ROOT")
		{
			Value=EFilePathSegmentType::E_ROOT;

			return(true);
		}
		else if (AdjustedTextValue=="ROOT DIRECTORY")
		{
			Value=EFilePathSegmentType::E_ROOT_DIRECTORY;

			return(true);
		}
		else if (AdjustedTextValue=="DIRECTORY OR FILENAME")
		{
			Value=EFilePathSegmentType::E_DIRECTORY_OR_FILENAME;

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