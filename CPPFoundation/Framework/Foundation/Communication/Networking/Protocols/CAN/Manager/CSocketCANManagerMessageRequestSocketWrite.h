//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANAddress.h>
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
	class CSocketCANManagerMessageRequestSocketWrite final : public CSocketCANManagerMessageRequest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketCANManagerMessageContext					MMessageContext;
			CSocketCANAddress									MDestinationAddress;
			CCSPByteBuffer										MData;
			CExpirationTime										MWriteExpirationTime;

		public:
			CSocketCANManagerMessageRequestSocketWrite& operator=(const CSocketCANManagerMessageRequestSocketWrite& Other);
			CSocketCANManagerMessageRequestSocketWrite& operator=(CSocketCANManagerMessageRequestSocketWrite&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;
			virtual CCSPSocketCANManagerMessageResponse CreateErrorResponse(void) const override;
			CCSPSocketCANManagerMessageContext GetMessageContext(void) const noexcept;
			const CSocketCANAddress& GetDestinationAddress(void) const noexcept;
			CCSPByteBuffer GetData(void) const noexcept;
			const CExpirationTime& GetWriteExpirationTime(void) const noexcept;

		public:
			CSocketCANManagerMessageRequestSocketWrite(const CSocketID& SocketID, CCSPSocketCANManagerMessageContext MessageContext, const CSocketCANAddress& DestinationAddress, CCSPByteBuffer Data, const CExpirationTime& WriteExpirationTime);
			CSocketCANManagerMessageRequestSocketWrite(const CSocketCANManagerMessageRequestSocketWrite& Other);
			CSocketCANManagerMessageRequestSocketWrite(CSocketCANManagerMessageRequestSocketWrite&& Other) noexcept;
			virtual ~CSocketCANManagerMessageRequestSocketWrite(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketCANManagerMessageRequestSocketWrite=CSharedPointer<CSocketCANManagerMessageRequestSocketWrite>;
	using														CCSPSocketCANManagerMessageRequestSocketWrite=CSharedPointer<const CSocketCANManagerMessageRequestSocketWrite>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------