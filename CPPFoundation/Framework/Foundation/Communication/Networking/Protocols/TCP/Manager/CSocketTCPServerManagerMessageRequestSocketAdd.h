//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPServer.h>
#include "CSocketTCPServerManagerMessageRequest.h"
#include "CSocketTCPServerManagerMessageContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPServerManagerMessageRequestSocketAdd final : public CSocketTCPServerManagerMessageRequest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketTCPServerManagerMessageContext			MMessageContext;
			CSPSocketTCPServer									MSocket;

		public:
			CSocketTCPServerManagerMessageRequestSocketAdd& operator=(const CSocketTCPServerManagerMessageRequestSocketAdd& Other);
			CSocketTCPServerManagerMessageRequestSocketAdd& operator=(CSocketTCPServerManagerMessageRequestSocketAdd&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;
			virtual CCSPSocketTCPServerManagerMessageResponse CreateErrorResponse(void) const override;
			CCSPSocketTCPServerManagerMessageContext GetMessageContext(void) const noexcept;
			CSPSocketTCPServer GetSocket(void) const noexcept;

		public:
			CSocketTCPServerManagerMessageRequestSocketAdd(CCSPSocketTCPServerManagerMessageContext MessageContext, CSPSocketTCPServer Socket);
			CSocketTCPServerManagerMessageRequestSocketAdd(const CSocketTCPServerManagerMessageRequestSocketAdd& Other);
			CSocketTCPServerManagerMessageRequestSocketAdd(CSocketTCPServerManagerMessageRequestSocketAdd&& Other) noexcept;
			virtual ~CSocketTCPServerManagerMessageRequestSocketAdd(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPServerManagerMessageRequestSocketAdd=CSharedPointer<CSocketTCPServerManagerMessageRequestSocketAdd>;
	using														CCSPSocketTCPServerManagerMessageRequestSocketAdd=CSharedPointer<const CSocketTCPServerManagerMessageRequestSocketAdd>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------