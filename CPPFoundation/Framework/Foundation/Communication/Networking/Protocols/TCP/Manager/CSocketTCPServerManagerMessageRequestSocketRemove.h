//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPServerManagerMessageRequest.h"
#include "CSocketTCPServerManagerMessageContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPServerManagerMessageRequestSocketRemove final : public CSocketTCPServerManagerMessageRequest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketTCPServerManagerMessageContext			MMessageContext;

		public:
			CSocketTCPServerManagerMessageRequestSocketRemove& operator=(const CSocketTCPServerManagerMessageRequestSocketRemove& Other);
			CSocketTCPServerManagerMessageRequestSocketRemove& operator=(CSocketTCPServerManagerMessageRequestSocketRemove&& Other);

		public:
			virtual CString ToString(void) const override;
			virtual CCSPSocketTCPServerManagerMessageResponse CreateErrorResponse(void) const override;
			CCSPSocketTCPServerManagerMessageContext GetMessageContext(void) const noexcept;

		public:
			CSocketTCPServerManagerMessageRequestSocketRemove(const CSocketID& SocketID, CCSPSocketTCPServerManagerMessageContext MessageContext);
			CSocketTCPServerManagerMessageRequestSocketRemove(const CSocketTCPServerManagerMessageRequestSocketRemove& Other);
			CSocketTCPServerManagerMessageRequestSocketRemove(CSocketTCPServerManagerMessageRequestSocketRemove&& Other);
			virtual ~CSocketTCPServerManagerMessageRequestSocketRemove(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPServerManagerMessageRequestSocketRemove=CSharedPointer<CSocketTCPServerManagerMessageRequestSocketRemove>;
	using														CCSPSocketTCPServerManagerMessageRequestSocketRemove=CSharedPointer<const CSocketTCPServerManagerMessageRequestSocketRemove>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------