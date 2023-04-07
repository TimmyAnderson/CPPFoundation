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
	enum class ESocketExceptionCode : uint8
	{
//----------------------------------------------------------------------------------------------------------------------
		E_UNKNOWN=0,
		E_NETWORK_DOWN=1,
		E_NETWORK_IS_UNREACHABLE=2,
		E_NETWORK_RESET=3,
		E_CONNECTION_ABORTED=4,
		E_CONNECTION_RESET=5,
		E_NO_BUFFER_SPACE_AVAILABLE=6,
		E_SOCKET_IS_ALREADY_CONNECTED=7,
		E_SOCKET_IS_NOT_CONNECTED=8,
		E_SOCKET_IS_SHUTDOWN=9,
		E_TOO_MANY_REFERENCES=10,
		E_CONNECTION_TIMEOUT=11,
		E_CONNECTION_REFUSED=12,
		E_HOST_IS_DOWN=13,
		E_HOST_IS_UNREACHABLE=14,
		E_SOCKET_OPERATION_ON_NON_SOCKET=15,
		E_DESTINATION_ADDRESS_IS_REQUIRED=16,
		E_MESSAGE_TOO_LONG=17,
		E_WRONG_PROTOCOL_TYPE_FOR_SOCKET=18,
		E_WRONG_PROTOCOL_OPTION=19,
		E_PROTOCOL_NOT_SUPPORTED=20,
		E_SOCKET_TYPE_NOT_SUPPORTED=21,
		E_OPERATION_NOT_SUPPORTED_ON_TRANSPORT_ENDPOINT=22,
		E_PROTOCOL_FAMILY_NOT_SUPPORTED=23,
		E_ADDRESS_FAMILY_NOT_SUPPORTED_BY_PROTOCOL=24,
		E_ADDRESS_ALREADY_IN_USE=25,
		E_CAN_NOT_ASSIGN_REQUESTED_ADDRESS=26,
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline CString& operator<<(CString& Text, ESocketExceptionCode Value)
	{
		switch(Value)
		{
			case ESocketExceptionCode::E_UNKNOWN:
			{
				Text+="UNKNOWN";
			}
			break;

			case ESocketExceptionCode::E_NETWORK_DOWN:
			{
				Text+="NETWORK DOWN";
			}
			break;

			case ESocketExceptionCode::E_NETWORK_IS_UNREACHABLE:
			{
				Text+="NETWORK IS UNREACHABLE";
			}
			break;

			case ESocketExceptionCode::E_NETWORK_RESET:
			{
				Text+="NETWORK RESET";
			}
			break;

			case ESocketExceptionCode::E_CONNECTION_ABORTED:
			{
				Text+="CONNECTION ABORTED";
			}
			break;

			case ESocketExceptionCode::E_CONNECTION_RESET:
			{
				Text+="CONNECTION RESET";
			}
			break;

			case ESocketExceptionCode::E_NO_BUFFER_SPACE_AVAILABLE:
			{
				Text+="NO BUFFER SPACE AVAILABLE";
			}
			break;

			case ESocketExceptionCode::E_SOCKET_IS_ALREADY_CONNECTED:
			{
				Text+="SOCKET IS ALREADY CONNECTED";
			}
			break;

			case ESocketExceptionCode::E_SOCKET_IS_NOT_CONNECTED:
			{
				Text+="SOCKET IS NOT CONNECTED";
			}
			break;

			case ESocketExceptionCode::E_SOCKET_IS_SHUTDOWN:
			{
				Text+="SOCKET IS SHUTDOWN";
			}
			break;

			case ESocketExceptionCode::E_TOO_MANY_REFERENCES:
			{
				Text+="TOO MANY REFERENCES";
			}
			break;

			case ESocketExceptionCode::E_CONNECTION_TIMEOUT:
			{
				Text+="CONNECTION TIMEOUT";
			}
			break;

			case ESocketExceptionCode::E_CONNECTION_REFUSED:
			{
				Text+="CONNECTION REFUSED";
			}
			break;

			case ESocketExceptionCode::E_HOST_IS_DOWN:
			{
				Text+="HOST IS DOWN";
			}
			break;

			case ESocketExceptionCode::E_HOST_IS_UNREACHABLE:
			{
				Text+="HOST IS UNREACHABLE";
			}
			break;

			case ESocketExceptionCode::E_SOCKET_OPERATION_ON_NON_SOCKET:
			{
				Text+="SOCKET OPERATION ON NON SOCKET";
			}
			break;

			case ESocketExceptionCode::E_DESTINATION_ADDRESS_IS_REQUIRED:
			{
				Text+="DESTINATION ADDRESS IS REQUIRED";
			}
			break;

			case ESocketExceptionCode::E_MESSAGE_TOO_LONG:
			{
				Text+="MESSAGE TOO LONG";
			}
			break;

			case ESocketExceptionCode::E_WRONG_PROTOCOL_TYPE_FOR_SOCKET:
			{
				Text+="WRONG PROTOCOL TYPE FOR SOCKET";
			}
			break;

			case ESocketExceptionCode::E_WRONG_PROTOCOL_OPTION:
			{
				Text+="WRONG PROTOCOL OPTION";
			}
			break;

			case ESocketExceptionCode::E_PROTOCOL_NOT_SUPPORTED:
			{
				Text+="PROTOCOL NOT SUPPORTED";
			}
			break;

			case ESocketExceptionCode::E_SOCKET_TYPE_NOT_SUPPORTED:
			{
				Text+="SOCKET TYPE NOT SUPPORTED";
			}
			break;

			case ESocketExceptionCode::E_OPERATION_NOT_SUPPORTED_ON_TRANSPORT_ENDPOINT:
			{
				Text+="OPERATION NOT SUPPORTED ON TRANSPORT ENDPOINT";
			}
			break;

			case ESocketExceptionCode::E_PROTOCOL_FAMILY_NOT_SUPPORTED:
			{
				Text+="PROTOCOL FAMILY NOT SUPPORTED";
			}
			break;

			case ESocketExceptionCode::E_ADDRESS_FAMILY_NOT_SUPPORTED_BY_PROTOCOL:
			{
				Text+="ADDRESS FAMILY NOT SUPPORTED BY PROTOCOL";
			}
			break;

			case ESocketExceptionCode::E_ADDRESS_ALREADY_IN_USE:
			{
				Text+="ADDRESS ALREADY IN USE";
			}
			break;

			case ESocketExceptionCode::E_CAN_NOT_ASSIGN_REQUESTED_ADDRESS:
			{
				Text+="CAN NOT ASSIGN REQUESTED ADDRESS";
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
	inline bool IsValidValue(ESocketExceptionCode Value)
	{
		switch(Value)
		{
			case ESocketExceptionCode::E_UNKNOWN:
			case ESocketExceptionCode::E_NETWORK_DOWN:
			case ESocketExceptionCode::E_NETWORK_IS_UNREACHABLE:
			case ESocketExceptionCode::E_NETWORK_RESET:
			case ESocketExceptionCode::E_CONNECTION_ABORTED:
			case ESocketExceptionCode::E_CONNECTION_RESET:
			case ESocketExceptionCode::E_NO_BUFFER_SPACE_AVAILABLE:
			case ESocketExceptionCode::E_SOCKET_IS_ALREADY_CONNECTED:
			case ESocketExceptionCode::E_SOCKET_IS_NOT_CONNECTED:
			case ESocketExceptionCode::E_SOCKET_IS_SHUTDOWN:
			case ESocketExceptionCode::E_TOO_MANY_REFERENCES:
			case ESocketExceptionCode::E_CONNECTION_TIMEOUT:
			case ESocketExceptionCode::E_CONNECTION_REFUSED:
			case ESocketExceptionCode::E_HOST_IS_DOWN:
			case ESocketExceptionCode::E_HOST_IS_UNREACHABLE:
			case ESocketExceptionCode::E_SOCKET_OPERATION_ON_NON_SOCKET:
			case ESocketExceptionCode::E_DESTINATION_ADDRESS_IS_REQUIRED:
			case ESocketExceptionCode::E_MESSAGE_TOO_LONG:
			case ESocketExceptionCode::E_WRONG_PROTOCOL_TYPE_FOR_SOCKET:
			case ESocketExceptionCode::E_WRONG_PROTOCOL_OPTION:
			case ESocketExceptionCode::E_PROTOCOL_NOT_SUPPORTED:
			case ESocketExceptionCode::E_SOCKET_TYPE_NOT_SUPPORTED:
			case ESocketExceptionCode::E_OPERATION_NOT_SUPPORTED_ON_TRANSPORT_ENDPOINT:
			case ESocketExceptionCode::E_PROTOCOL_FAMILY_NOT_SUPPORTED:
			case ESocketExceptionCode::E_ADDRESS_FAMILY_NOT_SUPPORTED_BY_PROTOCOL:
			case ESocketExceptionCode::E_ADDRESS_ALREADY_IN_USE:
			case ESocketExceptionCode::E_CAN_NOT_ASSIGN_REQUESTED_ADDRESS:
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