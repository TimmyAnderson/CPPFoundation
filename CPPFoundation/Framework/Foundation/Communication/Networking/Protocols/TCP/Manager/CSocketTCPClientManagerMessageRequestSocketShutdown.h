//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageRequest.h"
#include "CSocketTCPClientManagerMessageContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPClientManagerMessageRequestSocketShutdown final : public CSocketTCPClientManagerMessageRequest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketTCPClientManagerMessageContext			MMessageContext;

		public:
			CSocketTCPClientManagerMessageRequestSocketShutdown& operator=(const CSocketTCPClientManagerMessageRequestSocketShutdown& Other);
			CSocketTCPClientManagerMessageRequestSocketShutdown& operator=(CSocketTCPClientManagerMessageRequestSocketShutdown&& Other);

		public:
			virtual CString ToString(void) const override;
			virtual CCSPSocketTCPClientManagerMessageResponse CreateErrorResponse(void) const override;
			CCSPSocketTCPClientManagerMessageContext GetMessageContext(void) const noexcept;

		public:
			CSocketTCPClientManagerMessageRequestSocketShutdown(const CSocketID& SocketID, CCSPSocketTCPClientManagerMessageContext MessageContext);
			CSocketTCPClientManagerMessageRequestSocketShutdown(const CSocketTCPClientManagerMessageRequestSocketShutdown& Other);
			CSocketTCPClientManagerMessageRequestSocketShutdown(CSocketTCPClientManagerMessageRequestSocketShutdown&& Other);
			virtual ~CSocketTCPClientManagerMessageRequestSocketShutdown(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPClientManagerMessageRequestSocketShutdown=CSharedPointer<CSocketTCPClientManagerMessageRequestSocketShutdown>;
	using														CCSPSocketTCPClientManagerMessageRequestSocketShutdown=CSharedPointer<const CSocketTCPClientManagerMessageRequestSocketShutdown>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------