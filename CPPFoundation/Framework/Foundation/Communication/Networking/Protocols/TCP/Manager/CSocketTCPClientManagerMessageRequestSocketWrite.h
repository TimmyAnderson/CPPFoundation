//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Time/CExpirationTime.h>
#include "CSocketTCPClientManagerMessageRequest.h"
#include "CSocketTCPClientManagerMessageContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPClientManagerMessageRequestSocketWrite final : public CSocketTCPClientManagerMessageRequest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketTCPClientManagerMessageContext			MMessageContext;
			CCSPByteBuffer										MData;
			CExpirationTime										MWriteExpirationTime;

		public:
			CSocketTCPClientManagerMessageRequestSocketWrite& operator=(const CSocketTCPClientManagerMessageRequestSocketWrite& Other);
			CSocketTCPClientManagerMessageRequestSocketWrite& operator=(CSocketTCPClientManagerMessageRequestSocketWrite&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;
			virtual CCSPSocketTCPClientManagerMessageResponse CreateErrorResponse(void) const override;
			CCSPSocketTCPClientManagerMessageContext GetMessageContext(void) const noexcept;
			CCSPByteBuffer GetData(void) const noexcept;
			const CExpirationTime& GetWriteExpirationTime(void) const noexcept;

		public:
			CSocketTCPClientManagerMessageRequestSocketWrite(const CSocketID& SocketID, CCSPSocketTCPClientManagerMessageContext MessageContext, CCSPByteBuffer Data, const CExpirationTime& WriteExpirationTime);
			CSocketTCPClientManagerMessageRequestSocketWrite(const CSocketTCPClientManagerMessageRequestSocketWrite& Other);
			CSocketTCPClientManagerMessageRequestSocketWrite(CSocketTCPClientManagerMessageRequestSocketWrite&& Other) noexcept;
			virtual ~CSocketTCPClientManagerMessageRequestSocketWrite(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPClientManagerMessageRequestSocketWrite=CSharedPointer<CSocketTCPClientManagerMessageRequestSocketWrite>;
	using														CCSPSocketTCPClientManagerMessageRequestSocketWrite=CSharedPointer<const CSocketTCPClientManagerMessageRequestSocketWrite>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------