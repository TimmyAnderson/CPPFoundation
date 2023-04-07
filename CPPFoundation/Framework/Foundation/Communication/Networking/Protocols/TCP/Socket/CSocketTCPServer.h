//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocket.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPAddress.h>
#include "ISocketTCPWrapper.h"
#include "CSocketTCPClient.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPServerManager;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPServer final : public CSocket
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			ISPSocketTCPWrapper									MSocketWrapper;

		public:
			CSocketTCPServer& operator=(const CSocketTCPServer& Other)=delete;

		public:
			virtual int32 GetSocketHandler(void) const noexcept override;
			virtual ISPSocketWrapper GetSocketWrapper(void) const noexcept override;

		public:
			void BindToAddress(const CSocketTCPAddress& Address);
			ISPSocketTCPWrapper Accept(CSocketTCPAddress& Address);
			void Listen(Size MaximumNumberOfPendingConnections);
			void Shutdown(ESocketTCPShutdownFlags ShutdownFlags);
			int32 GetSendBufferSize(void);
			void SetSendBufferSize(int32 SendBufferSize);
			int32 GetReceiveBufferSize(void);
			void SetReceiveBufferSize(int32 ReceiveBufferSize);

		public:
			CSocketTCPServer(CLogWriter& LogWriter, const CSocketID& SocketID);
			CSocketTCPServer(const CSocketTCPServer& Other)=delete;
			virtual ~CSocketTCPServer(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPServer=CSharedPointer<CSocketTCPServer>;
	using														CCSPSocketTCPServer=CSharedPointer<const CSocketTCPServer>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------