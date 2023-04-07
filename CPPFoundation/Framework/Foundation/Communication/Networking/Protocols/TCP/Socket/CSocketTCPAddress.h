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
	class CSocketTCPAddress final : public CSocketAddress
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSocketIPEndpoint									MIPEndpoint;

		public:
			CSocketTCPAddress& operator=(const CSocketTCPAddress& Other);
			CSocketTCPAddress& operator=(CSocketTCPAddress&& Other);
			bool operator==(const CSocketTCPAddress& Other) const;
			bool operator!=(const CSocketTCPAddress& Other) const;

		public:
			static bool ParseIPv4TCPAddress(const CString& Value, CSocketTCPAddress& Result);
			static bool ParseIPv6TCPAddress(const CString& Value, CSocketTCPAddress& Result);

		public:
			virtual CString ToString(void) const override;
			virtual bool Equals(const CSocketAddress& Other) const override;

		public:
			const CSocketIPEndpoint& GetIPEndpoint(void) const noexcept;

		public:
			CSocketTCPAddress(void);
			CSocketTCPAddress(const CSocketIPEndpoint& IPEndpoint);
			CSocketTCPAddress(CSocketIPEndpoint&& IPEndpoint);
			CSocketTCPAddress(const CSocketTCPAddress& Other);
			CSocketTCPAddress(CSocketTCPAddress&& Other);
			virtual ~CSocketTCPAddress(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPAddress=CSharedPointer<CSocketTCPAddress>;
	using														CCSPSocketTCPAddress=CSharedPointer<const CSocketTCPAddress>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------