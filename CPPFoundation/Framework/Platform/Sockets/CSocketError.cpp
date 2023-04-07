//----------------------------------------------------------------------------------------------------------------------
#include "CSocketError.h"
#if defined(PLATFORM_WINDOWS)
#include <WS2tcpip.h>
#include <WinError.h>
#elif defined(PLATFORM_LINUX)
#else
#error UNSUPPORTED PLATFORM !
#endif
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Platform
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int32 CSocketError::SocketGetLastErrorCode(void)
	{
#if defined(PLATFORM_WINDOWS)
		int32													SocketErrorCode=static_cast<int32>(WSAGetLastError());

		return(SocketErrorCode);
#elif defined(PLATFORM_LINUX)
		int32													SocketErrorCode=static_cast<int32>(errno);

		return(SocketErrorCode);
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	ESocketExceptionCode CSocketError::GetSocketExceptionCode(int32 ErrorCode)
	{
#if defined(PLATFORM_WINDOWS)
		switch(ErrorCode)
		{
			case WSAENETDOWN:
			{
				return(ESocketExceptionCode::E_NETWORK_DOWN);
			}

			case WSAENETUNREACH:
			{
				return(ESocketExceptionCode::E_NETWORK_IS_UNREACHABLE);
			}

			case WSAENETRESET:
			{
				return(ESocketExceptionCode::E_NETWORK_RESET);
			}

			case WSAECONNABORTED:
			{
				return(ESocketExceptionCode::E_CONNECTION_ABORTED);
			}

			case WSAECONNRESET:
			{
				return(ESocketExceptionCode::E_CONNECTION_RESET);
			}

			case WSAENOBUFS:
			{
				return(ESocketExceptionCode::E_NO_BUFFER_SPACE_AVAILABLE);
			}

			case WSAEISCONN:
			{
				return(ESocketExceptionCode::E_SOCKET_IS_ALREADY_CONNECTED);
			}

			case WSAENOTCONN:
			{
				return(ESocketExceptionCode::E_SOCKET_IS_NOT_CONNECTED);
			}

			case WSAESHUTDOWN:
			{
				return(ESocketExceptionCode::E_SOCKET_IS_SHUTDOWN);
			}

			case WSAETOOMANYREFS:
			{
				return(ESocketExceptionCode::E_TOO_MANY_REFERENCES);
			}

			case WSAETIMEDOUT:
			{
				return(ESocketExceptionCode::E_CONNECTION_TIMEOUT);
			}

			case WSAECONNREFUSED:
			{
				return(ESocketExceptionCode::E_CONNECTION_REFUSED);
			}

			case WSAEHOSTDOWN:
			{
				return(ESocketExceptionCode::E_HOST_IS_DOWN);
			}

			case WSAEHOSTUNREACH:
			{
				return(ESocketExceptionCode::E_HOST_IS_UNREACHABLE);
			}

			case WSAENOTSOCK:
			{
				return(ESocketExceptionCode::E_SOCKET_OPERATION_ON_NON_SOCKET);
			}

			case WSAEDESTADDRREQ:
			{
				return(ESocketExceptionCode::E_DESTINATION_ADDRESS_IS_REQUIRED);
			}

			case WSAEMSGSIZE:
			{
				return(ESocketExceptionCode::E_MESSAGE_TOO_LONG);
			}

			case WSAEPROTOTYPE:
			{
				return(ESocketExceptionCode::E_WRONG_PROTOCOL_TYPE_FOR_SOCKET);
			}

			case WSAENOPROTOOPT:
			{
				return(ESocketExceptionCode::E_WRONG_PROTOCOL_OPTION);
			}

			case WSAEPROTONOSUPPORT:
			{
				return(ESocketExceptionCode::E_PROTOCOL_NOT_SUPPORTED);
			}

			case WSAESOCKTNOSUPPORT:
			{
				return(ESocketExceptionCode::E_SOCKET_TYPE_NOT_SUPPORTED);
			}

			case WSAEOPNOTSUPP:
			{
				return(ESocketExceptionCode::E_OPERATION_NOT_SUPPORTED_ON_TRANSPORT_ENDPOINT);
			}

			case WSAEPFNOSUPPORT:
			{
				return(ESocketExceptionCode::E_PROTOCOL_FAMILY_NOT_SUPPORTED);
			}

			case WSAEAFNOSUPPORT:
			{
				return(ESocketExceptionCode::E_ADDRESS_FAMILY_NOT_SUPPORTED_BY_PROTOCOL);
			}

			case WSAEADDRINUSE:
			{
				return(ESocketExceptionCode::E_ADDRESS_ALREADY_IN_USE);
			}

			case WSAEADDRNOTAVAIL:
			{
				return(ESocketExceptionCode::E_CAN_NOT_ASSIGN_REQUESTED_ADDRESS);
			}

			default:
			{
				return(ESocketExceptionCode::E_UNKNOWN);
			}
		}
#elif defined(PLATFORM_LINUX)
		switch(ErrorCode)
		{
			case ENETDOWN:
			{
				return(ESocketExceptionCode::E_NETWORK_DOWN);
			}

			case ENETUNREACH:
			{
				return(ESocketExceptionCode::E_NETWORK_IS_UNREACHABLE);
			}

			case ENETRESET:
			{
				return(ESocketExceptionCode::E_NETWORK_RESET);
			}

			case ECONNABORTED:
			{
				return(ESocketExceptionCode::E_CONNECTION_ABORTED);
			}

			case ECONNRESET:
			{
				return(ESocketExceptionCode::E_CONNECTION_RESET);
			}

			case ENOBUFS:
			{
				return(ESocketExceptionCode::E_NO_BUFFER_SPACE_AVAILABLE);
			}

			case EISCONN:
			{
				return(ESocketExceptionCode::E_SOCKET_IS_ALREADY_CONNECTED);
			}

			case ENOTCONN:
			{
				return(ESocketExceptionCode::E_SOCKET_IS_NOT_CONNECTED);
			}

			case ESHUTDOWN:
			{
				return(ESocketExceptionCode::E_SOCKET_IS_SHUTDOWN);
			}

			case ETOOMANYREFS:
			{
				return(ESocketExceptionCode::E_TOO_MANY_REFERENCES);
			}

			case ETIMEDOUT:
			{
				return(ESocketExceptionCode::E_CONNECTION_TIMEOUT);
			}

			case ECONNREFUSED:
			{
				return(ESocketExceptionCode::E_CONNECTION_REFUSED);
			}

			case EHOSTDOWN:
			{
				return(ESocketExceptionCode::E_HOST_IS_DOWN);
			}

			case EHOSTUNREACH:
			{
				return(ESocketExceptionCode::E_HOST_IS_UNREACHABLE);
			}

			case ENOTSOCK:
			{
				return(ESocketExceptionCode::E_SOCKET_OPERATION_ON_NON_SOCKET);
			}

			case EDESTADDRREQ:
			{
				return(ESocketExceptionCode::E_DESTINATION_ADDRESS_IS_REQUIRED);
			}

			case EMSGSIZE:
			{
				return(ESocketExceptionCode::E_MESSAGE_TOO_LONG);
			}

			case EPROTOTYPE:
			{
				return(ESocketExceptionCode::E_WRONG_PROTOCOL_TYPE_FOR_SOCKET);
			}

			case ENOPROTOOPT:
			{
				return(ESocketExceptionCode::E_WRONG_PROTOCOL_OPTION);
			}

			case EPROTONOSUPPORT:
			{
				return(ESocketExceptionCode::E_PROTOCOL_NOT_SUPPORTED);
			}

			case ESOCKTNOSUPPORT:
			{
				return(ESocketExceptionCode::E_SOCKET_TYPE_NOT_SUPPORTED);
			}

			case EOPNOTSUPP:
			{
				return(ESocketExceptionCode::E_OPERATION_NOT_SUPPORTED_ON_TRANSPORT_ENDPOINT);
			}

			case EPFNOSUPPORT:
			{
				return(ESocketExceptionCode::E_PROTOCOL_FAMILY_NOT_SUPPORTED);
			}

			case EAFNOSUPPORT:
			{
				return(ESocketExceptionCode::E_ADDRESS_FAMILY_NOT_SUPPORTED_BY_PROTOCOL);
			}

			case EADDRINUSE:
			{
				return(ESocketExceptionCode::E_ADDRESS_ALREADY_IN_USE);
			}

			case EADDRNOTAVAIL:
			{
				return(ESocketExceptionCode::E_CAN_NOT_ASSIGN_REQUESTED_ADDRESS);
			}

			default:
			{
				return(ESocketExceptionCode::E_UNKNOWN);
			}
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------