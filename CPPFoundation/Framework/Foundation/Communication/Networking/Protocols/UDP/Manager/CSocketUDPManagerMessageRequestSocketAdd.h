//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/CSocketUDP.h>
#include "CSocketUDPManagerMessageContext.h"
#include "CSocketUDPManagerMessageRequest.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPManagerMessageRequestSocketAdd final : public CSocketUDPManagerMessageRequest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketUDPManagerMessageContext					MMessageContext;
			CSPSocketUDP										MSocket;

		public:
			CSocketUDPManagerMessageRequestSocketAdd& operator=(const CSocketUDPManagerMessageRequestSocketAdd& Other);
			CSocketUDPManagerMessageRequestSocketAdd& operator=(CSocketUDPManagerMessageRequestSocketAdd&& Other);

		public:
			virtual CString ToString(void) const override;
			virtual CCSPSocketUDPManagerMessageResponse CreateErrorResponse(void) const override;
			CCSPSocketUDPManagerMessageContext GetMessageContext(void) const noexcept;
			CSPSocketUDP GetSocket(void) const noexcept;

		public:
			CSocketUDPManagerMessageRequestSocketAdd(CCSPSocketUDPManagerMessageContext MessageContext, CSPSocketUDP Socket);
			CSocketUDPManagerMessageRequestSocketAdd(const CSocketUDPManagerMessageRequestSocketAdd& Other);
			CSocketUDPManagerMessageRequestSocketAdd(CSocketUDPManagerMessageRequestSocketAdd&& Other);
			virtual ~CSocketUDPManagerMessageRequestSocketAdd(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDPManagerMessageRequestSocketAdd=CSharedPointer<CSocketUDPManagerMessageRequestSocketAdd>;
	using														CCSPSocketUDPManagerMessageRequestSocketAdd=CSharedPointer<const CSocketUDPManagerMessageRequestSocketAdd>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------