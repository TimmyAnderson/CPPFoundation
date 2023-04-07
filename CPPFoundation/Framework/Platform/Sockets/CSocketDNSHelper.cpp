//----------------------------------------------------------------------------------------------------------------------
#include "CSocketDNSHelper.h"
#if defined(PLATFORM_WINDOWS)
#include <WS2tcpip.h>
#elif defined(PLATFORM_LINUX)
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#else
#error UNSUPPORTED PLATFORM !
#endif
#include <cstring>
#include <Framework/Foundation/Exceptions/CSocketException.h>
#include "CSocketError.h"
#include "CSocketAddressHelper.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Platform
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace std;
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPAddress> CSocketDNSHelper::ConvertDNSAddressToIPAddress(const CSocketDNSAddress& DNSAddress, ESocketDNSAddressType AddressType, ESocketDNSProtocolType ProtocolType)
	{
#if defined(PLATFORM_WINDOWS)
		CVector<CSocketIPAddress>								IPAddressCollection;
		ADDRINFOA												Filter;

		memset(&Filter,0,sizeof(Filter));

		if (AddressType==ESocketDNSAddressType::E_UNSPECIFIED)
		{
			Filter.ai_family=AF_UNSPEC;
		}
		else if (AddressType==ESocketDNSAddressType::E_IP_V4)
		{
			Filter.ai_family=AF_INET;
		}
		else if (AddressType==ESocketDNSAddressType::E_IP_V6)
		{
			Filter.ai_family=AF_INET6;
		}

		if (ProtocolType==ESocketDNSProtocolType::E_UNSPECIFIED)
		{
			Filter.ai_socktype=0;
			Filter.ai_protocol=0;
		}
		else if (ProtocolType==ESocketDNSProtocolType::E_TCP)
		{
			Filter.ai_socktype=SOCK_STREAM;
			Filter.ai_protocol=IPPROTO_TCP;
		}
		else if (ProtocolType==ESocketDNSProtocolType::E_UDP)
		{
			Filter.ai_socktype=SOCK_DGRAM;
			Filter.ai_protocol=IPPROTO_UDP;
		}

		PADDRINFOA												AddressInfo;
		int														Result=getaddrinfo(DNSAddress.GetDNSAddress().GetCharArray(),nullptr,&Filter,&AddressInfo);

		if (Result==0)
		{
			PADDRINFOA											AddressInfoIterator=AddressInfo;

			try
			{
				while(true)
				{
					if (AddressInfoIterator->ai_family==AF_INET)
					{
						sockaddr_in*							RawSocketAddress=reinterpret_cast<sockaddr_in*>(AddressInfoIterator->ai_addr);
						CSocketIPAddress						IPAddress(CSocketAddressHelper::ConvertFromPlatformAddressIPv4(*RawSocketAddress));

						IPAddressCollection.Add(FUNCTION_MOVE(IPAddress));
					}
					else if (AddressInfoIterator->ai_family==AF_INET6)
					{
						sockaddr_in6*							RawSocketAddress=reinterpret_cast<sockaddr_in6*>(AddressInfoIterator->ai_addr);
						CSocketIPAddress						IPAddress(CSocketAddressHelper::ConvertFromPlatformAddressIPv6(*RawSocketAddress));

						IPAddressCollection.Add(FUNCTION_MOVE(IPAddress));
					}

					if (AddressInfoIterator->ai_next!=nullptr)
					{
						AddressInfoIterator=AddressInfoIterator->ai_next;
					}
					else
					{
						break;
					}
				}
			}
			catch(...)
			{
				freeaddrinfo(AddressInfo);
				throw;
			}

			freeaddrinfo(AddressInfo);

			return(IPAddressCollection);
		}
		else
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("DNS FAILED to CONVERT DNS ADDRESS to IP ADDRESS !",ErrorCode,SocketExceptionCode));
		}
#elif defined(PLATFORM_LINUX)
		using													PADDRINFOA=addrinfo*;

		CVector<CSocketIPAddress>								IPAddressCollection;
		addrinfo												Filter;

		memset(&Filter,0,sizeof(Filter));

		if (AddressType==ESocketDNSAddressType::E_UNSPECIFIED)
		{
			Filter.ai_family=AF_UNSPEC;
		}
		else if (AddressType==ESocketDNSAddressType::E_IP_V4)
		{
			Filter.ai_family=AF_INET;
		}
		else if (AddressType==ESocketDNSAddressType::E_IP_V6)
		{
			Filter.ai_family=AF_INET6;
		}

		if (ProtocolType==ESocketDNSProtocolType::E_UNSPECIFIED)
		{
			Filter.ai_socktype=0;
			Filter.ai_protocol=0;
		}
		else if (ProtocolType==ESocketDNSProtocolType::E_TCP)
		{
			Filter.ai_socktype=SOCK_STREAM;
			Filter.ai_protocol=IPPROTO_TCP;
		}
		else if (ProtocolType==ESocketDNSProtocolType::E_UDP)
		{
			Filter.ai_socktype=SOCK_DGRAM;
			Filter.ai_protocol=IPPROTO_UDP;
		}

		PADDRINFOA												AddressInfo;
		int														Result=getaddrinfo(DNSAddress.GetDNSAddress().GetCharArray(),nullptr,&Filter,&AddressInfo);

		if (Result==0)
		{
			PADDRINFOA											AddressInfoIterator=AddressInfo;

			try
			{
				while(true)
				{
					if (AddressInfoIterator->ai_family==AF_INET)
					{
						sockaddr_in*							RawSocketAddress=reinterpret_cast<sockaddr_in*>(AddressInfoIterator->ai_addr);
						CSocketIPAddress						IPAddress(CSocketAddressHelper::ConvertFromPlatformAddressIPv4(*RawSocketAddress));

						IPAddressCollection.Add(FUNCTION_MOVE(IPAddress));
					}
					else if (AddressInfoIterator->ai_family==AF_INET6)
					{
						sockaddr_in6*							RawSocketAddress=reinterpret_cast<sockaddr_in6*>(AddressInfoIterator->ai_addr);
						CSocketIPAddress						IPAddress(CSocketAddressHelper::ConvertFromPlatformAddressIPv6(*RawSocketAddress));

						IPAddressCollection.Add(FUNCTION_MOVE(IPAddress));
					}

					if (AddressInfoIterator->ai_next!=nullptr)
					{
						AddressInfoIterator=AddressInfoIterator->ai_next;
					}
					else
					{
						break;
					}
				}
			}
			catch(...)
			{
				freeaddrinfo(AddressInfo);
				throw;
			}

			freeaddrinfo(AddressInfo);

			return(IPAddressCollection);
		}
		else
		{
			if (Result==EAI_SYSTEM)
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("DNS FAILED to CONVERT DNS ADDRESS to IP ADDRESS !",ErrorCode,SocketExceptionCode));
			}
			else
			{
				CString											Error;
				const Char*										ErrorText=gai_strerror(Result);

				if (ErrorText!=nullptr)
				{
					Error=ErrorText;
				}

				throw(CSocketException(CString::Format("DNS FAILED to CONVERT DNS ADDRESS to IP ADDRESS ! ERROR [",Error,"] !")));
			}
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSAddress CSocketDNSHelper::ConvertIPAddressToDNSAddress(const CSocketIPAddress& IPAddress, bool DNSAddressRequired)
	{
#if defined(PLATFORM_WINDOWS)
		sockaddr*												SocketAddress=nullptr;
		sockaddr_in												SocketAddressIPv4;
		sockaddr_in6											SocketAddressIPv6;
		socklen_t												SocketAddressLength=0;

		if (IPAddress.GetAddressType()==ESocketIPAddressType::E_IP_V4)
		{
			SocketAddressIPv4=CSocketAddressHelper::ConvertToPlatformAddressIPv4(IPAddress);
			SocketAddress=reinterpret_cast<sockaddr*>(&SocketAddressIPv4);
			SocketAddressLength=sizeof(sockaddr_in);
		}
		else if (IPAddress.GetAddressType()==ESocketIPAddressType::E_IP_V6)
		{
			SocketAddressIPv6=CSocketAddressHelper::ConvertToPlatformAddressIPv6(IPAddress);
			SocketAddress=reinterpret_cast<sockaddr*>(&SocketAddressIPv6);
			SocketAddressLength=sizeof(sockaddr_in6);
		}
		else
		{
			throw(CSocketException("DNS FAILED to CONVERT IP ADDRESS to DNS ADDRESS ! UNSUPPORTED IP ADDRESS TYPE !"));
		}

		Char													DNSAddressBuffer[NI_MAXHOST];
		int														Flags=0;

		if (DNSAddressRequired==true)
		{
			Flags|=NI_NAMEREQD;
		}

		int														Result=getnameinfo(SocketAddress,SocketAddressLength,DNSAddressBuffer,sizeof(DNSAddressBuffer),nullptr,0,Flags);

		if (Result==0)
		{
			CString												DNSAddressString(DNSAddressBuffer);
			CSocketDNSAddress									DNSAddress(FUNCTION_MOVE(DNSAddressString));

			return(DNSAddress);
		}
		else
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("DNS FAILED to CONVERT IP ADDRESS to DNS ADDRESS !",ErrorCode,SocketExceptionCode));
		}
#elif defined(PLATFORM_LINUX)
		sockaddr*												SocketAddress=nullptr;
		sockaddr_in												SocketAddressIPv4;
		sockaddr_in6											SocketAddressIPv6;
		socklen_t												SocketAddressLength=0;

		if (IPAddress.GetAddressType()==ESocketIPAddressType::E_IP_V4)
		{
			SocketAddressIPv4=CSocketAddressHelper::ConvertToPlatformAddressIPv4(IPAddress);
			SocketAddress=reinterpret_cast<sockaddr*>(&SocketAddressIPv4);
			SocketAddressLength=sizeof(sockaddr_in);
		}
		else if (IPAddress.GetAddressType()==ESocketIPAddressType::E_IP_V6)
		{
			SocketAddressIPv6=CSocketAddressHelper::ConvertToPlatformAddressIPv6(IPAddress);
			SocketAddress=reinterpret_cast<sockaddr*>(&SocketAddressIPv6);
			SocketAddressLength=sizeof(sockaddr_in6);
		}
		else
		{
			throw(CSocketException("DNS FAILED to CONVERT IP ADDRESS to DNS ADDRESS ! UNSUPPORTED IP ADDRESS TYPE !"));
		}

		Char													DNSAddressBuffer[NI_MAXHOST];
		int														Flags=0;

		if (DNSAddressRequired==true)
		{
			Flags|=NI_NAMEREQD;
		}

		int														Result=getnameinfo(SocketAddress,SocketAddressLength,DNSAddressBuffer,sizeof(DNSAddressBuffer),nullptr,0,Flags);

		if (Result==0)
		{
			CString												DNSAddressString(DNSAddressBuffer);
			CSocketDNSAddress									DNSAddress(FUNCTION_MOVE(DNSAddressString));

			return(DNSAddress);
		}
		else
		{
			if (Result==EAI_AGAIN)
			{
				if (DNSAddressRequired==true)
				{
					int32										ErrorCode=CSocketError::SocketGetLastErrorCode();
					ESocketExceptionCode						SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

					throw(CSocketException("DNS FAILED to CONVERT IP ADDRESS to DNS ADDRESS !",ErrorCode,SocketExceptionCode));
				}
				else
				{
					CSocketDNSAddress							DNSAddress(IPAddress.ToString());

					return(DNSAddress);
				}
			}
			else if (Result==EAI_SYSTEM)
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("DNS FAILED to CONVERT IP ADDRESS to DNS ADDRESS !",ErrorCode,SocketExceptionCode));
			}
			else
			{
				CString											Error;
				const Char*										ErrorText=gai_strerror(Result);

				if (ErrorText!=nullptr)
				{
					Error=ErrorText;
				}

				throw(CSocketException(CString::Format("DNS FAILED to CONVERT IP ADDRESS to DNS ADDRESS ! ERROR [",Error,"] !")));
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