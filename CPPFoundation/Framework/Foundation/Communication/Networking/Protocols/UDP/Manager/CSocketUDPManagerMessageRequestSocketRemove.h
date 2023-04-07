//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPManagerMessageRequest.h"
#include "CSocketUDPManagerMessageContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPManagerMessageRequestSocketRemove final : public CSocketUDPManagerMessageRequest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketUDPManagerMessageContext					MMessageContext;

		public:
			CSocketUDPManagerMessageRequestSocketRemove& operator=(const CSocketUDPManagerMessageRequestSocketRemove& Other);
			CSocketUDPManagerMessageRequestSocketRemove& operator=(CSocketUDPManagerMessageRequestSocketRemove&& Other);

		public:
			virtual CString ToString(void) const override;
			virtual CCSPSocketUDPManagerMessageResponse CreateErrorResponse(void) const override;
			CCSPSocketUDPManagerMessageContext GetMessageContext(void) const noexcept;

		public:
			CSocketUDPManagerMessageRequestSocketRemove(const CSocketID& SocketID, CCSPSocketUDPManagerMessageContext MessageContext);
			CSocketUDPManagerMessageRequestSocketRemove(const CSocketUDPManagerMessageRequestSocketRemove& Other);
			CSocketUDPManagerMessageRequestSocketRemove(CSocketUDPManagerMessageRequestSocketRemove&& Other);
			virtual ~CSocketUDPManagerMessageRequestSocketRemove(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDPManagerMessageRequestSocketRemove=CSharedPointer<CSocketUDPManagerMessageRequestSocketRemove>;
	using														CCSPSocketUDPManagerMessageRequestSocketRemove=CSharedPointer<const CSocketUDPManagerMessageRequestSocketRemove>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------