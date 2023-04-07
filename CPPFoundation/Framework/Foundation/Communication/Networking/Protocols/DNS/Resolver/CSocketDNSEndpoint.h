//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketEndpoint.h>
#include "CSocketDNSAddress.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketDNSEndpoint final : public CSocketEndpoint
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			static const Size									NUMBER_OF_DNS_ENDPOINT_SEGMENTS;
			static const Char									DNS_ADDRESS_PORT_SERPARATOR;

		private:
			CSocketDNSAddress									MDNSAddress;
			uint16												MPort;

		public:
			CSocketDNSEndpoint& operator=(const CSocketDNSEndpoint& Other);
			CSocketDNSEndpoint& operator=(CSocketDNSEndpoint&& Other) noexcept;
			bool operator==(const CSocketDNSEndpoint& Other) const;
			bool operator!=(const CSocketDNSEndpoint& Other) const;

		public:
			static CSocketDNSEndpoint CreateLocalHostEndpoint(uint16 Port);
			static bool ParseDNSEndpoint(const CString& Value, CSocketDNSEndpoint& Result);

		public:
			virtual CString ToString(void) const override;
			virtual bool Equals(const CSocketEndpoint& Other) const override;

		public:
			const CSocketDNSAddress& GetDNSAddress(void) const noexcept;
			uint16 GetPort(void) const noexcept;

		public:
			CSocketDNSEndpoint(void);
			CSocketDNSEndpoint(const CSocketDNSAddress& DNSAddress, uint16 Port);
			CSocketDNSEndpoint(CSocketDNSAddress&& DNSAddress, uint16 Port);
			CSocketDNSEndpoint(const CSocketDNSEndpoint& Other);
			CSocketDNSEndpoint(CSocketDNSEndpoint&& Other) noexcept;
			virtual ~CSocketDNSEndpoint(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketDNSEndpoint=CSharedPointer<CSocketDNSEndpoint>;
	using														CCSPSocketDNSEndpoint=CSharedPointer<const CSocketDNSEndpoint>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------