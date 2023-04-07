//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageResponse.h"
#include "CSocketTCPClientManagerMessageContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPClientManagerMessageResponseSocketRemove final : public CSocketTCPClientManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketTCPClientManagerMessageContext			MMessageContext;
			bool												MOperationSucceeded;

		public:
			CSocketTCPClientManagerMessageResponseSocketRemove& operator=(const CSocketTCPClientManagerMessageResponseSocketRemove& Other);
			CSocketTCPClientManagerMessageResponseSocketRemove& operator=(CSocketTCPClientManagerMessageResponseSocketRemove&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;
			CCSPSocketTCPClientManagerMessageContext GetMessageContext(void) const noexcept;
			bool GetOperationSucceeded(void) const noexcept;

		public:
			CSocketTCPClientManagerMessageResponseSocketRemove(const CSocketID& SocketID, CCSPSocketTCPClientManagerMessageContext MessageContext, bool OperationSucceeded);
			CSocketTCPClientManagerMessageResponseSocketRemove(const CSocketTCPClientManagerMessageResponseSocketRemove& Other);
			CSocketTCPClientManagerMessageResponseSocketRemove(CSocketTCPClientManagerMessageResponseSocketRemove&& Other) noexcept;
			virtual ~CSocketTCPClientManagerMessageResponseSocketRemove(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPClientManagerMessageResponseSocketRemove=CSharedPointer<CSocketTCPClientManagerMessageResponseSocketRemove>;
	using														CCSPSocketTCPClientManagerMessageResponseSocketRemove=CSharedPointer<const CSocketTCPClientManagerMessageResponseSocketRemove>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------