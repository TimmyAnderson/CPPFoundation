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
	class CSocketCANManagerMessageRequestSocketAdd final : public CSocketCANManagerMessageRequest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketCANManagerMessageContext					MMessageContext;
			CSPSocketCAN										MSocket;

		public:
			CSocketCANManagerMessageRequestSocketAdd& operator=(const CSocketCANManagerMessageRequestSocketAdd& Other);
			CSocketCANManagerMessageRequestSocketAdd& operator=(CSocketCANManagerMessageRequestSocketAdd&& Other);

		public:
			virtual CString ToString(void) const override;
			virtual CCSPSocketCANManagerMessageResponse CreateErrorResponse(void) const override;
			CCSPSocketCANManagerMessageContext GetMessageContext(void) const noexcept;
			CSPSocketCAN GetSocket(void) const noexcept;

		public:
			CSocketCANManagerMessageRequestSocketAdd(CCSPSocketCANManagerMessageContext MessageContext, CSPSocketCAN Socket);
			CSocketCANManagerMessageRequestSocketAdd(const CSocketCANManagerMessageRequestSocketAdd& Other);
			CSocketCANManagerMessageRequestSocketAdd(CSocketCANManagerMessageRequestSocketAdd&& Other);
			virtual ~CSocketCANManagerMessageRequestSocketAdd(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketCANManagerMessageRequestSocketAdd=CSharedPointer<CSocketCANManagerMessageRequestSocketAdd>;
	using														CCSPSocketCANManagerMessageRequestSocketAdd=CSharedPointer<const CSocketCANManagerMessageRequestSocketAdd>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------