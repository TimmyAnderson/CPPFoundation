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
	enum class ESocketWaitEvent : uint8
	{
//----------------------------------------------------------------------------------------------------------------------
		E_NONE=0x00,
		E_TIMEOUT=0x01,
		E_SIGNALIZATION_EVENT_SET=0x02,
		E_SOCKET_EVENT_SET=0x04,
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline ESocketWaitEvent& operator|=(ESocketWaitEvent& Value1, ESocketWaitEvent Value2)
	{
		uint8													RawValue1=static_cast<uint8>(Value1);
		uint8													RawValue2=static_cast<uint8>(Value2);
		uint8													RawResult=RawValue1 | RawValue2;

		Value1=static_cast<ESocketWaitEvent>(RawResult);

		return(Value1);
	}
//----------------------------------------------------------------------------------------------------------------------
	inline ESocketWaitEvent operator&(ESocketWaitEvent Value1, ESocketWaitEvent Value2)
	{
		uint8													RawValue1=static_cast<uint8>(Value1);
		uint8													RawValue2=static_cast<uint8>(Value2);
		uint8													RawResult=RawValue1 & RawValue2;
		ESocketWaitEvent										Result=static_cast<ESocketWaitEvent>(RawResult);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline CString& operator<<(CString& Text, ESocketWaitEvent Value)
	{
		CString													TextValue;

		if (Value==ESocketWaitEvent::E_NONE)
		{
			TextValue="NONE";
		}
		else
		{
			if ((Value & ESocketWaitEvent::E_TIMEOUT)!=ESocketWaitEvent::E_NONE)
			{
				if (TextValue.IsEmpty()==false)
				{
					TextValue+=" | ";
				}

				TextValue+="TIMEOUT";
			}

			if ((Value & ESocketWaitEvent::E_SIGNALIZATION_EVENT_SET)!=ESocketWaitEvent::E_NONE)
			{
				if (TextValue.IsEmpty()==false)
				{
					TextValue+=" | ";
				}

				TextValue+="SIGNALIZATION EVENT SET";
			}

			if ((Value & ESocketWaitEvent::E_SOCKET_EVENT_SET)!=ESocketWaitEvent::E_NONE)
			{
				if (TextValue.IsEmpty()==false)
				{
					TextValue+=" | ";
				}

				TextValue+="SOCKET EVENT SET";
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