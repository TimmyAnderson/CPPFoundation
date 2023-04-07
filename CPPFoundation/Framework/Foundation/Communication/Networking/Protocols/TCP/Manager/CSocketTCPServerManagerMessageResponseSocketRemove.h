//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPServerManagerMessageResponse.h"
#include "CSocketTCPServerManagerMessageContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPServerManagerMessageResponseSocketRemove final : public CSocketTCPServerManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketTCPServerManagerMessageContext			MMessageContext;
			bool												MOperationSucceeded;

		public:
			CSocketTCPServerManagerMessageResponseSocketRemove& operator=(const CSocketTCPServerManagerMessageResponseSocketRemove& Other);
			CSocketTCPServerManagerMessageResponseSocketRemove& operator=(CSocketTCPServerManagerMessageResponseSocketRemove&& Other);

		public:
			virtual CString ToString(void) const override;
			CCSPSocketTCPServerManagerMessageContext GetMessageContext(void) const noexcept;
			bool GetOperationSucceeded(void) const noexcept;

		public:
			CSocketTCPServerManagerMessageResponseSocketRemove(const CSocketID& SocketID, CCSPSocketTCPServerManagerMessageContext MessageContext, bool OperationSucceeded);
			CSocketTCPServerManagerMessageResponseSocketRemove(const CSocketTCPServerManagerMessageResponseSocketRemove& Other);
			CSocketTCPServerManagerMessageResponseSocketRemove(CSocketTCPServerManagerMessageResponseSocketRemove&& Other);
			virtual ~CSocketTCPServerManagerMessageResponseSocketRemove(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPServerManagerMessageResponseSocketRemove=CSharedPointer<CSocketTCPServerManagerMessageResponseSocketRemove>;
	using														CCSPSocketTCPServerManagerMessageResponseSocketRemove=CSharedPointer<const CSocketTCPServerManagerMessageResponseSocketRemove>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------