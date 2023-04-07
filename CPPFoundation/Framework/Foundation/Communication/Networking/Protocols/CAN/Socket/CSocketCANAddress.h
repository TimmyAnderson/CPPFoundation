//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketAddress.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANAddress final : public CSocketAddress
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			int32												MNetworkInterfaceIndex;
			uint32												MProtocolClassAddressReceiveID;
			uint32												MProtocolClassAddressSendID;

		public:
			CSocketCANAddress& operator=(const CSocketCANAddress& Other);
			CSocketCANAddress& operator=(CSocketCANAddress&& Other) noexcept;
			bool operator==(const CSocketCANAddress& Other) const;
			bool operator!=(const CSocketCANAddress& Other) const;

		public:
			virtual CString ToString(void) const override;
			virtual bool Equals(const CSocketAddress& Other) const override;

		public:
			int32 GetNetworkInterfaceIndex(void) const noexcept;
			uint32 GetProtocolClassAddressReceiveID(void) const noexcept;
			uint32 GetProtocolClassAddressSendID(void) const noexcept;

		public:
			CSocketCANAddress(void);
			CSocketCANAddress(int32 NetworkInterfaceIndex, uint32 ProtocolClassAddressReceiveID=0, uint32 ProtocolClassAddressSendID=0);
			CSocketCANAddress(const CSocketCANAddress& Other);
			CSocketCANAddress(CSocketCANAddress&& Other) noexcept;
			virtual ~CSocketCANAddress(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketCANAddress=CSharedPointer<CSocketCANAddress>;
	using														CCSPSocketCANAddress=CSharedPointer<const CSocketCANAddress>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------