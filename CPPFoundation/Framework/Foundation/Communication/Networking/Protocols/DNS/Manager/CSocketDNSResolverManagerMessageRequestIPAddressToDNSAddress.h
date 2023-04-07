//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/IP/CSocketIPAddress.h>
#include "CSocketDNSResolverManagerMessageRequest.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress final : public CSocketDNSResolverManagerMessageRequest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSocketIPAddress									MIPAddress;
			bool												MDNSAddressRequired;

		public:
			CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress& operator=(const CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress& Other);
			CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress& operator=(CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress&& Other);

		public:
			virtual CString ToString(void) const override;
			virtual CCSPSocketDNSResolverManagerMessageResponse CreateErrorResponse(void) const override;

		public:
			const CSocketIPAddress& GetIPAddress(void) const noexcept;
			bool GetDNSAddressRequired(void) const noexcept;

		public:
			CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress(CCSPSocketDNSResolverManagerMessageContext MessageContext, const CSocketIPAddress& IPAddress, bool DNSAddressRequired);
			CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress(CCSPSocketDNSResolverManagerMessageContext MessageContext, CSocketIPAddress&& IPAddress, bool DNSAddressRequired);
			CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress(const CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress& Other);
			CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress(CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress&& Other);
			virtual ~CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress=CSharedPointer<CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress>;
	using														CCSPSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress=CSharedPointer<const CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------