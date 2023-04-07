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
	class CSocketTCPClientManagerMessageRequestSocketRemove final : public CSocketTCPClientManagerMessageRequest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketTCPClientManagerMessageContext			MMessageContext;

		public:
			CSocketTCPClientManagerMessageRequestSocketRemove& operator=(const CSocketTCPClientManagerMessageRequestSocketRemove& Other);
			CSocketTCPClientManagerMessageRequestSocketRemove& operator=(CSocketTCPClientManagerMessageRequestSocketRemove&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;
			virtual CCSPSocketTCPClientManagerMessageResponse CreateErrorResponse(void) const override;
			CCSPSocketTCPClientManagerMessageContext GetMessageContext(void) const noexcept;

		public:
			CSocketTCPClientManagerMessageRequestSocketRemove(const CSocketID& SocketID, CCSPSocketTCPClientManagerMessageContext MessageContext);
			CSocketTCPClientManagerMessageRequestSocketRemove(const CSocketTCPClientManagerMessageRequestSocketRemove& Other);
			CSocketTCPClientManagerMessageRequestSocketRemove(CSocketTCPClientManagerMessageRequestSocketRemove&& Other) noexcept;
			virtual ~CSocketTCPClientManagerMessageRequestSocketRemove(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPClientManagerMessageRequestSocketRemove=CSharedPointer<CSocketTCPClientManagerMessageRequestSocketRemove>;
	using														CCSPSocketTCPClientManagerMessageRequestSocketRemove=CSharedPointer<const CSocketTCPClientManagerMessageRequestSocketRemove>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------