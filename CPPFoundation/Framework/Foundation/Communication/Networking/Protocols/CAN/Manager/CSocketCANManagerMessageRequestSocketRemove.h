//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCAN.h>
#include <Framework/Foundation/Time/CExpirationTime.h>
#include "CSocketCANManagerMessageContext.h"
#include "CSocketCANManagerMessageRequest.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANManagerMessageRequestSocketRemove final : public CSocketCANManagerMessageRequest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketCANManagerMessageContext					MMessageContext;

		public:
			CSocketCANManagerMessageRequestSocketRemove& operator=(const CSocketCANManagerMessageRequestSocketRemove& Other);
			CSocketCANManagerMessageRequestSocketRemove& operator=(CSocketCANManagerMessageRequestSocketRemove&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;
			virtual CCSPSocketCANManagerMessageResponse CreateErrorResponse(void) const override;
			CCSPSocketCANManagerMessageContext GetMessageContext(void) const noexcept;

		public:
			CSocketCANManagerMessageRequestSocketRemove(const CSocketID& SocketID, CCSPSocketCANManagerMessageContext MessageContext);
			CSocketCANManagerMessageRequestSocketRemove(const CSocketCANManagerMessageRequestSocketRemove& Other);
			CSocketCANManagerMessageRequestSocketRemove(CSocketCANManagerMessageRequestSocketRemove&& Other) noexcept;
			virtual ~CSocketCANManagerMessageRequestSocketRemove(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketCANManagerMessageRequestSocketRemove=CSharedPointer<CSocketCANManagerMessageRequestSocketRemove>;
	using														CCSPSocketCANManagerMessageRequestSocketRemove=CSharedPointer<const CSocketCANManagerMessageRequestSocketRemove>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------