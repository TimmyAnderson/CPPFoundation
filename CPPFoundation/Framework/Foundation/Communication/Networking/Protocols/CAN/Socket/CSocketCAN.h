//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocket.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANAddress.h>
#include "ISocketCANWrapper.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANManager;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCAN final : public CSocket
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			ISPSocketCANWrapper									MSocketWrapper;

		public:
			CSocketCAN& operator=(const CSocketCAN& Other)=delete;

		public:
			static CString GetNetworkInterfaceName(int32 NetworkInterfaceIndex);
			static int32 GetNetworkInterfaceIndex(const CString& NetworkInterfaceName);

		public:
			virtual int32 GetSocketHandler(void) const noexcept override;
			virtual ISPSocketWrapper GetSocketWrapper(void) const noexcept override;

		public:
			void BindToAddress(const CSocketCANAddress& Address);
			void SendTo(const CSocketCANSendToParameters& Parameters, CSocketCANSendToResult& Result);
			void ReceiveFrom(const CSocketCANReceiveFromParameters& Parameters, CSocketCANReceiveFromResult& Result);
			CString GetNetworkInterfaceNameForSocket(int32 NetworkInterfaceIndex);
			int32 GetNetworkInterfaceIndexForSocket(const CString& NetworkInterfaceName);

		public:
			CSocketCAN(CLogWriter& LogWriter, const CSocketID& SocketID);
			CSocketCAN(const CSocketCAN& Other)=delete;
			virtual ~CSocketCAN(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketCAN=CSharedPointer<CSocketCAN>;
	using														CCSPSocketCAN=CSharedPointer<const CSocketCAN>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------