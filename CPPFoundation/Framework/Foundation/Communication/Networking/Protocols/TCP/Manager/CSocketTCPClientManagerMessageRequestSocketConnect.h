//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPAddress.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPClient.h>
#include "CSocketTCPClientManagerMessageRequest.h"
#include "CSocketTCPClientManagerMessageContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPClientManagerMessageRequestSocketConnect final : public CSocketTCPClientManagerMessageRequest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketTCPClientManagerMessageContext			MMessageContext;
			CSPSocketTCPClient									MSocket;
			CSocketTCPAddress									MDestinationAddress;

		public:
			CSocketTCPClientManagerMessageRequestSocketConnect& operator=(const CSocketTCPClientManagerMessageRequestSocketConnect& Other);
			CSocketTCPClientManagerMessageRequestSocketConnect& operator=(CSocketTCPClientManagerMessageRequestSocketConnect&& Other);

		public:
			virtual CString ToString(void) const override;
			virtual CCSPSocketTCPClientManagerMessageResponse CreateErrorResponse(void) const override;
			CCSPSocketTCPClientManagerMessageContext GetMessageContext(void) const noexcept;
			CSPSocketTCPClient GetSocket(void) const noexcept;
			const CSocketTCPAddress& GetDestinationAddress(void) const noexcept;

		public:
			CSocketTCPClientManagerMessageRequestSocketConnect(CCSPSocketTCPClientManagerMessageContext MessageContext, CSPSocketTCPClient Socket, const CSocketTCPAddress& DestinationAddress);
			CSocketTCPClientManagerMessageRequestSocketConnect(const CSocketTCPClientManagerMessageRequestSocketConnect& Other);
			CSocketTCPClientManagerMessageRequestSocketConnect(CSocketTCPClientManagerMessageRequestSocketConnect&& Other);
			virtual ~CSocketTCPClientManagerMessageRequestSocketConnect(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPClientManagerMessageRequestSocketConnect=CSharedPointer<CSocketTCPClientManagerMessageRequestSocketConnect>;
	using														CCSPSocketTCPClientManagerMessageRequestSocketConnect=CSharedPointer<const CSocketTCPClientManagerMessageRequestSocketConnect>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------