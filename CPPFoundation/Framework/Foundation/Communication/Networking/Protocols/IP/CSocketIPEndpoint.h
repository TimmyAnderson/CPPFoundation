//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketEndpoint.h>
#include "CSocketIPAddress.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketIPEndpoint final : public CSocketEndpoint
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			static const Size									NUMBER_OF_IPV4_ENDPOINT_SEGMENTS;
			static const Char									IPV4_PORT_SERPARATOR;
			static const Char									IPV6_PORT_SERPARATOR;
			static const Char									IPV6_ADDRESS_OPEN_BRACKET;
			static const Char									IPV6_ADDRESS_CLOSE_BRACKET;

		private:
			CSocketIPAddress									MIPAddress;
			uint16												MPort;

		public:
			CSocketIPEndpoint& operator=(const CSocketIPEndpoint& Other);
			CSocketIPEndpoint& operator=(CSocketIPEndpoint&& Other) noexcept;
			bool operator==(const CSocketIPEndpoint& Other) const;
			bool operator!=(const CSocketIPEndpoint& Other) const;

		public:
			static CSocketIPEndpoint CreateLocalHostIPv4Endpoint(uint16 Port);
			static CSocketIPEndpoint CreateLocalHostIPv6Endpoint(uint16 Port);
			static bool ParseIPv4Endpoint(const CString& Value, CSocketIPEndpoint& Result);
			static bool ParseIPv6Endpoint(const CString& Value, CSocketIPEndpoint& Result);

		public:
			virtual CString ToString(void) const override;
			virtual bool Equals(const CSocketEndpoint& Other) const override;

		public:
			const CSocketIPAddress& GetIPAddress(void) const noexcept;
			uint16 GetPort(void) const noexcept;

		public:
			CSocketIPEndpoint(void);
			CSocketIPEndpoint(const CSocketIPAddress& IPAddress, uint16 Port);
			CSocketIPEndpoint(CSocketIPAddress&& IPAddress, uint16 Port);
			CSocketIPEndpoint(const CSocketIPEndpoint& Other);
			CSocketIPEndpoint(CSocketIPEndpoint&& Other) noexcept;
			virtual ~CSocketIPEndpoint(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketIPEndpoint=CSharedPointer<CSocketIPEndpoint>;
	using														CCSPSocketIPEndpoint=CSharedPointer<const CSocketIPEndpoint>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------