//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocket.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPAddress.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/ISocketTCPWrapper.h>
#include "ISocketTCPWrapper.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPClientManager;
	class CSocketTCPServer;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPClient final : public CSocket
	{
//----------------------------------------------------------------------------------------------------------------------
		friend CSocketTCPServer;

		private:
			ISPSocketTCPWrapper									MSocketWrapper;

		public:
			CSocketTCPClient& operator=(const CSocketTCPClient& Other)=delete;

		public:
			virtual int32 GetSocketHandler(void) const noexcept override;
			virtual ISPSocketWrapper GetSocketWrapper(void) const noexcept override;

		public:
			bool ConnectToAddress(const CSocketTCPAddress& Address);
			void Shutdown(ESocketTCPShutdownFlags ShutdownFlags);
			void Send(const CSocketTCPSendParameters& Parameters, CSocketTCPSendResult& OperationResult);
			void Receive(const CSocketTCPReceiveParameters& Parameters, CSocketTCPReceiveResult& OperationResult);
			int32 GetSendBufferSize(void);
			void SetSendBufferSize(int32 SendBufferSize);
			int32 GetReceiveBufferSize(void);
			void SetReceiveBufferSize(int32 ReceiveBufferSize);

		public:
			CSocketTCPClient(CLogWriter& LogWriter, const CSocketID& SocketID, ISPSocketTCPWrapper SocketTCPWrapper);
			CSocketTCPClient(CLogWriter& LogWriter, const CSocketID& SocketID);
			CSocketTCPClient(const CSocketTCPClient& Other)=delete;
			virtual ~CSocketTCPClient(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPClient=CSharedPointer<CSocketTCPClient>;
	using														CCSPSocketTCPClient=CSharedPointer<const CSocketTCPClient>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------