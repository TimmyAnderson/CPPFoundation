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
	enum class ESocketIPAddressType : uint8
	{
//----------------------------------------------------------------------------------------------------------------------
		E_UNDEFINED=0,
		E_IP_V4=1,
		E_IP_V6=2,
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline CString& operator<<(CString& Text, ESocketIPAddressType Value)
	{
		switch(Value)
		{
			case ESocketIPAddressType::E_UNDEFINED:
			{
				Text+="UNDEFINED";
			}
			break;

			case ESocketIPAddressType::E_IP_V4:
			{
				Text+="IP V4";
			}
			break;

			case ESocketIPAddressType::E_IP_V6:
			{
				Text+="E_IP_V6";
			}
			break;

			default:
			{
				Text+="UNKNOWN";
			}
		}

		return(Text);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline bool IsValidValue(ESocketIPAddressType Value)
	{
		switch(Value)
		{
			case ESocketIPAddressType::E_UNDEFINED:
			case ESocketIPAddressType::E_IP_V4:
			case ESocketIPAddressType::E_IP_V6:
			{
				return(true);
			}

			default:
			{
				return(false);
			}
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------