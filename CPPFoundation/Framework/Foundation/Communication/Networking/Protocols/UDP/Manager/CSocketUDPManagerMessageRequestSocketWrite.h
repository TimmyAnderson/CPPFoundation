//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/CSocketUDPAddress.h>
#include <Framework/Foundation/Time/CExpirationTime.h>
#include "CSocketUDPManagerMessageContext.h"
#include "CSocketUDPManagerMessageRequest.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPManagerMessageRequestSocketWrite final : public CSocketUDPManagerMessageRequest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketUDPManagerMessageContext					MMessageContext;
			CSocketUDPAddress									MDestinationAddress;
			CCSPByteBuffer										MData;
			CExpirationTime										MWriteExpirationTime;

		public:
			CSocketUDPManagerMessageRequestSocketWrite& operator=(const CSocketUDPManagerMessageRequestSocketWrite& Other);
			CSocketUDPManagerMessageRequestSocketWrite& operator=(CSocketUDPManagerMessageRequestSocketWrite&& Other);

		public:
			virtual CString ToString(void) const override;
			virtual CCSPSocketUDPManagerMessageResponse CreateErrorResponse(void) const override;
			CCSPSocketUDPManagerMessageContext GetMessageContext(void) const noexcept;
			const CSocketUDPAddress& GetDestinationAddress(void) const noexcept;
			CCSPByteBuffer GetData(void) const noexcept;
			const CExpirationTime& GetWriteExpirationTime(void) const noexcept;

		public:
			CSocketUDPManagerMessageRequestSocketWrite(const CSocketID& SocketID, CCSPSocketUDPManagerMessageContext MessageContext, const CSocketUDPAddress& DestinationAddress, CCSPByteBuffer Data, const CExpirationTime& WriteExpirationTime);
			CSocketUDPManagerMessageRequestSocketWrite(const CSocketID& SocketID, CCSPSocketUDPManagerMessageContext MessageContext, CSocketUDPAddress&& DestinationAddress, CCSPByteBuffer Data, const CExpirationTime& WriteExpirationTime);
			CSocketUDPManagerMessageRequestSocketWrite(const CSocketUDPManagerMessageRequestSocketWrite& Other);
			CSocketUDPManagerMessageRequestSocketWrite(CSocketUDPManagerMessageRequestSocketWrite&& Other);
			virtual ~CSocketUDPManagerMessageRequestSocketWrite(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDPManagerMessageRequestSocketWrite=CSharedPointer<CSocketUDPManagerMessageRequestSocketWrite>;
	using														CCSPSocketUDPManagerMessageRequestSocketWrite=CSharedPointer<const CSocketUDPManagerMessageRequestSocketWrite>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------