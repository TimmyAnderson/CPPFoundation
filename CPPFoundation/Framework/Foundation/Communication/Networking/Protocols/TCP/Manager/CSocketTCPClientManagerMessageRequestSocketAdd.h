//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
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
	class CSocketTCPClientManagerMessageRequestSocketAdd final : public CSocketTCPClientManagerMessageRequest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketTCPClientManagerMessageContext			MMessageContext;
			CSPSocketTCPClient									MSocket;

		public:
			CSocketTCPClientManagerMessageRequestSocketAdd& operator=(const CSocketTCPClientManagerMessageRequestSocketAdd& Other);
			CSocketTCPClientManagerMessageRequestSocketAdd& operator=(CSocketTCPClientManagerMessageRequestSocketAdd&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;
			virtual CCSPSocketTCPClientManagerMessageResponse CreateErrorResponse(void) const override;
			CCSPSocketTCPClientManagerMessageContext GetMessageContext(void) const noexcept;
			CSPSocketTCPClient GetSocket(void) const noexcept;

		public:
			CSocketTCPClientManagerMessageRequestSocketAdd(CCSPSocketTCPClientManagerMessageContext MessageContext, CSPSocketTCPClient Socket);
			CSocketTCPClientManagerMessageRequestSocketAdd(const CSocketTCPClientManagerMessageRequestSocketAdd& Other);
			CSocketTCPClientManagerMessageRequestSocketAdd(CSocketTCPClientManagerMessageRequestSocketAdd&& Other) noexcept;
			virtual ~CSocketTCPClientManagerMessageRequestSocketAdd(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPClientManagerMessageRequestSocketAdd=CSharedPointer<CSocketTCPClientManagerMessageRequestSocketAdd>;
	using														CCSPSocketTCPClientManagerMessageRequestSocketAdd=CSharedPointer<const CSocketTCPClientManagerMessageRequestSocketAdd>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------