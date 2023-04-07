//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPClient.h>
#include "CSocketTCPClientManagerMessageResponse.h"
#include "CSocketTCPClientManagerMessageContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPClientManagerMessageResponseSocketAdd final : public CSocketTCPClientManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketTCPClientManagerMessageContext			MMessageContext;
			bool												MOperationSucceeded;
			CSPSocketTCPClient									MSocket;

		public:
			CSocketTCPClientManagerMessageResponseSocketAdd& operator=(const CSocketTCPClientManagerMessageResponseSocketAdd& Other);
			CSocketTCPClientManagerMessageResponseSocketAdd& operator=(CSocketTCPClientManagerMessageResponseSocketAdd&& Other);

		public:
			virtual CString ToString(void) const override;
			CCSPSocketTCPClientManagerMessageContext GetMessageContext(void) const noexcept;
			bool GetOperationSucceeded(void) const noexcept;
			CSPSocketTCPClient GetSocket(void) const noexcept;

		public:
			CSocketTCPClientManagerMessageResponseSocketAdd(CCSPSocketTCPClientManagerMessageContext MessageContext, bool OperationSucceeded, CSPSocketTCPClient Socket);
			CSocketTCPClientManagerMessageResponseSocketAdd(const CSocketTCPClientManagerMessageResponseSocketAdd& Other);
			CSocketTCPClientManagerMessageResponseSocketAdd(CSocketTCPClientManagerMessageResponseSocketAdd&& Other);
			virtual ~CSocketTCPClientManagerMessageResponseSocketAdd(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPClientManagerMessageResponseSocketAdd=CSharedPointer<CSocketTCPClientManagerMessageResponseSocketAdd>;
	using														CCSPSocketTCPClientManagerMessageResponseSocketAdd=CSharedPointer<const CSocketTCPClientManagerMessageResponseSocketAdd>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------