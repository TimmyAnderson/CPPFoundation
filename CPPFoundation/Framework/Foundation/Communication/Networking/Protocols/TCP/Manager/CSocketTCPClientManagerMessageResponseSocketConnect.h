//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPAddress.h>
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
	class CSocketTCPClientManagerMessageResponseSocketConnect final : public CSocketTCPClientManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketTCPClientManagerMessageContext			MMessageContext;
			bool												MOperationSucceeded;
			CSPSocket											MSocket;
			CSocketTCPAddress									MDestinationAddress;

		public:
			CSocketTCPClientManagerMessageResponseSocketConnect& operator=(const CSocketTCPClientManagerMessageResponseSocketConnect& Other);
			CSocketTCPClientManagerMessageResponseSocketConnect& operator=(CSocketTCPClientManagerMessageResponseSocketConnect&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;
			CCSPSocketTCPClientManagerMessageContext GetMessageContext(void) const noexcept;
			bool GetOperationSucceeded(void) const noexcept;
			CSPSocket GetSocket(void) const noexcept;
			const CSocketTCPAddress& GetDestinationAddress(void) const noexcept;

		public:
			CSocketTCPClientManagerMessageResponseSocketConnect(CCSPSocketTCPClientManagerMessageContext MessageContext, bool OperationSucceeded, CSPSocket Socket, const CSocketTCPAddress& DestinationAddress);
			CSocketTCPClientManagerMessageResponseSocketConnect(const CSocketTCPClientManagerMessageResponseSocketConnect& Other);
			CSocketTCPClientManagerMessageResponseSocketConnect(CSocketTCPClientManagerMessageResponseSocketConnect&& Other) noexcept;
			virtual ~CSocketTCPClientManagerMessageResponseSocketConnect(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPClientManagerMessageResponseSocketConnect=CSharedPointer<CSocketTCPClientManagerMessageResponseSocketConnect>;
	using														CCSPSocketTCPClientManagerMessageResponseSocketConnect=CSharedPointer<const CSocketTCPClientManagerMessageResponseSocketConnect>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------