//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocket.h>
#include "CSocketCANManagerMessageContext.h"
#include "CSocketCANManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANManagerMessageResponseSocketRemove final : public CSocketCANManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketCANManagerMessageContext					MMessageContext;
			bool												MOperationSucceeded;

		public:
			CSocketCANManagerMessageResponseSocketRemove& operator=(const CSocketCANManagerMessageResponseSocketRemove& Other);
			CSocketCANManagerMessageResponseSocketRemove& operator=(CSocketCANManagerMessageResponseSocketRemove&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;
			CCSPSocketCANManagerMessageContext GetMessageContext(void) const noexcept;
			bool GetOperationSucceeded(void) const noexcept;

		public:
			CSocketCANManagerMessageResponseSocketRemove(const CSocketID& SocketID, CCSPSocketCANManagerMessageContext MessageContext, bool OperationSucceeded);
			CSocketCANManagerMessageResponseSocketRemove(const CSocketCANManagerMessageResponseSocketRemove& Other);
			CSocketCANManagerMessageResponseSocketRemove(CSocketCANManagerMessageResponseSocketRemove&& Other) noexcept;
			virtual ~CSocketCANManagerMessageResponseSocketRemove(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketCANManagerMessageResponseSocketRemove=CSharedPointer<CSocketCANManagerMessageResponseSocketRemove>;
	using														CCSPSocketCANManagerMessageResponseSocketRemove=CSharedPointer<const CSocketCANManagerMessageResponseSocketRemove>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------