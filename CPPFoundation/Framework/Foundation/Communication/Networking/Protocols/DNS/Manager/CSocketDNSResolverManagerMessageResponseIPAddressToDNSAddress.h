//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/DNS/Resolver/CSocketDNSAddress.h>
#include "CSocketDNSResolverManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress final : public CSocketDNSResolverManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSocketDNSAddress									MDNSAddress;

		public:
			CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress& operator=(const CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress& Other);
			CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress& operator=(CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;

		public:
			const CSocketDNSAddress& GetDNSAddress(void) const noexcept;

		public:
			CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress(CCSPSocketDNSResolverManagerMessageContext MessageContext, bool OperationSucceeded, const CSocketDNSAddress& DNSAddress);
			CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress(CCSPSocketDNSResolverManagerMessageContext MessageContext, bool OperationSucceeded, CSocketDNSAddress&& DNSAddress);
			CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress(const CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress& Other);
			CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress(CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress&& Other) noexcept;
			virtual ~CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress=CSharedPointer<CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress>;
	using														CCSPSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress=CSharedPointer<const CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------