//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPManagerMessageContext.h"
#include "CSocketUDPManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPManagerMessageResponseSocketRemove final : public CSocketUDPManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketUDPManagerMessageContext					MMessageContext;
			bool												MOperationSucceeded;

		public:
			CSocketUDPManagerMessageResponseSocketRemove& operator=(const CSocketUDPManagerMessageResponseSocketRemove& Other);
			CSocketUDPManagerMessageResponseSocketRemove& operator=(CSocketUDPManagerMessageResponseSocketRemove&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;
			CCSPSocketUDPManagerMessageContext GetMessageContext(void) const noexcept;
			bool GetOperationSucceeded(void) const noexcept;

		public:
			CSocketUDPManagerMessageResponseSocketRemove(const CSocketID& SocketID, CCSPSocketUDPManagerMessageContext MessageContext, bool OperationSucceeded);
			CSocketUDPManagerMessageResponseSocketRemove(const CSocketUDPManagerMessageResponseSocketRemove& Other);
			CSocketUDPManagerMessageResponseSocketRemove(CSocketUDPManagerMessageResponseSocketRemove&& Other) noexcept;
			virtual ~CSocketUDPManagerMessageResponseSocketRemove(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDPManagerMessageResponseSocketRemove=CSharedPointer<CSocketUDPManagerMessageResponseSocketRemove>;
	using														CCSPSocketUDPManagerMessageResponseSocketRemove=CSharedPointer<const CSocketUDPManagerMessageResponseSocketRemove>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------