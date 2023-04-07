//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketAddress.h>
#include <Framework/Foundation/Communication/Networking/Protocols/IP/CSocketIPEndpoint.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPAddress final : public CSocketAddress
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSocketIPEndpoint									MIPEndpoint;

		public:
			CSocketUDPAddress& operator=(const CSocketUDPAddress& Other);
			CSocketUDPAddress& operator=(CSocketUDPAddress&& Other);
			bool operator==(const CSocketUDPAddress& Other) const;
			bool operator!=(const CSocketUDPAddress& Other) const;

		public:
			static bool ParseIPv4UDPAddress(const CString& Value, CSocketUDPAddress& Result);
			static bool ParseIPv6UDPAddress(const CString& Value, CSocketUDPAddress& Result);

		public:
			virtual CString ToString(void) const override;
			virtual bool Equals(const CSocketAddress& Other) const override;

		public:
			const CSocketIPEndpoint& GetIPEndpoint(void) const noexcept;

		public:
			CSocketUDPAddress(void);
			CSocketUDPAddress(const CSocketIPEndpoint& IPEndpoint);
			CSocketUDPAddress(CSocketIPEndpoint&& IPEndpoint);
			CSocketUDPAddress(const CSocketUDPAddress& Other);
			CSocketUDPAddress(CSocketUDPAddress&& Other);
			virtual ~CSocketUDPAddress(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDPAddress=CSharedPointer<CSocketUDPAddress>;
	using														CCSPSocketUDPAddress=CSharedPointer<const CSocketUDPAddress>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------