//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocket.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/CSocketUDPAddress.h>
#include "ISocketUDPWrapper.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPManager;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDP final : public CSocket
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			ISPSocketUDPWrapper									MSocketWrapper;

		public:
			CSocketUDP& operator=(const CSocketUDP& Other)=delete;

		public:
			virtual int32 GetSocketHandler(void) const noexcept override;
			virtual ISPSocketWrapper GetSocketWrapper(void) const noexcept override;

		public:
			void BindToAddress(const CSocketUDPAddress& Address);
			void SendTo(const CSocketUDPSendToParameters& Parameters, CSocketUDPSendToResult& Result);
			void ReceiveFrom(const CSocketUDPReceiveFromParameters& Parameters, CSocketUDPReceiveFromResult& Result);
			int32 GetSendBufferSize(void);
			void SetSendBufferSize(int32 SendBufferSize);
			int32 GetReceiveBufferSize(void);
			void SetReceiveBufferSize(int32 ReceiveBufferSize);

		public:
			CSocketUDP(CLogWriter& LogWriter, const CSocketID& SocketID);
			CSocketUDP(const CSocketUDP& Other)=delete;
			virtual ~CSocketUDP(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDP=CSharedPointer<CSocketUDP>;
	using														CCSPSocketUDP=CSharedPointer<const CSocketUDP>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------