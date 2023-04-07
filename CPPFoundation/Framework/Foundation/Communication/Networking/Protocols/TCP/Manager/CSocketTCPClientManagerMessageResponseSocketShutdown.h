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
	class CSocketTCPClientManagerMessageResponseSocketShutdown final : public CSocketTCPClientManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketTCPClientManagerMessageContext			MMessageContext;
			bool												MOperationSucceeded;

		public:
			CSocketTCPClientManagerMessageResponseSocketShutdown& operator=(const CSocketTCPClientManagerMessageResponseSocketShutdown& Other);
			CSocketTCPClientManagerMessageResponseSocketShutdown& operator=(CSocketTCPClientManagerMessageResponseSocketShutdown&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;
			CCSPSocketTCPClientManagerMessageContext GetMessageContext(void) const noexcept;
			bool GetOperationSucceeded(void) const noexcept;

		public:
			CSocketTCPClientManagerMessageResponseSocketShutdown(const CSocketID& SocketID, CCSPSocketTCPClientManagerMessageContext MessageContext, bool OperationSucceeded);
			CSocketTCPClientManagerMessageResponseSocketShutdown(const CSocketTCPClientManagerMessageResponseSocketShutdown& Other);
			CSocketTCPClientManagerMessageResponseSocketShutdown(CSocketTCPClientManagerMessageResponseSocketShutdown&& Other) noexcept;
			virtual ~CSocketTCPClientManagerMessageResponseSocketShutdown(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPClientManagerMessageResponseSocketShutdown=CSharedPointer<CSocketTCPClientManagerMessageResponseSocketShutdown>;
	using														CCSPSocketTCPClientManagerMessageResponseSocketShutdown=CSharedPointer<const CSocketTCPClientManagerMessageResponseSocketShutdown>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------