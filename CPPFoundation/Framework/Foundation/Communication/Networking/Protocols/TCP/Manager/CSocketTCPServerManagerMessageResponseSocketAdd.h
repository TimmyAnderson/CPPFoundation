//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPServer.h>
#include "CSocketTCPServerManagerMessageResponse.h"
#include "CSocketTCPServerManagerMessageContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPServerManagerMessageResponseSocketAdd final : public CSocketTCPServerManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketTCPServerManagerMessageContext			MMessageContext;
			bool												MOperationSucceeded;
			CSPSocketTCPServer									MSocket;

		public:
			CSocketTCPServerManagerMessageResponseSocketAdd& operator=(const CSocketTCPServerManagerMessageResponseSocketAdd& Other);
			CSocketTCPServerManagerMessageResponseSocketAdd& operator=(CSocketTCPServerManagerMessageResponseSocketAdd&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;
			CCSPSocketTCPServerManagerMessageContext GetMessageContext(void) const noexcept;
			bool GetOperationSucceeded(void) const noexcept;
			CSPSocketTCPServer GetSocket(void) const noexcept;

		public:
			CSocketTCPServerManagerMessageResponseSocketAdd(CCSPSocketTCPServerManagerMessageContext MessageContext, bool OperationSucceeded, CSPSocketTCPServer Socket);
			CSocketTCPServerManagerMessageResponseSocketAdd(const CSocketTCPServerManagerMessageResponseSocketAdd& Other);
			CSocketTCPServerManagerMessageResponseSocketAdd(CSocketTCPServerManagerMessageResponseSocketAdd&& Other) noexcept;
			virtual ~CSocketTCPServerManagerMessageResponseSocketAdd(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPServerManagerMessageResponseSocketAdd=CSharedPointer<CSocketTCPServerManagerMessageResponseSocketAdd>;
	using														CCSPSocketTCPServerManagerMessageResponseSocketAdd=CSharedPointer<const CSocketTCPServerManagerMessageResponseSocketAdd>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------