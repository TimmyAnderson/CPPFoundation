//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/ISocketTCPWrapper.h>
#include "CSocketTCPServerManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPServerManagerMessageResponseSocketAccept final : public CSocketTCPServerManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			ISPSocketTCPWrapper									MSocketTCPWrapper;
			CSocketTCPAddress									MDestinationAddress;

		public:
			CSocketTCPServerManagerMessageResponseSocketAccept& operator=(const CSocketTCPServerManagerMessageResponseSocketAccept& Other);
			CSocketTCPServerManagerMessageResponseSocketAccept& operator=(CSocketTCPServerManagerMessageResponseSocketAccept&& Other);

		public:
			virtual CString ToString(void) const override;
			ISPSocketTCPWrapper GetSocketTCPWrapper(void) const noexcept;
			const CSocketTCPAddress& GetDestinationAddress(void) const noexcept;

		public:
			CSocketTCPServerManagerMessageResponseSocketAccept(ISPSocketTCPWrapper SocketTCPWrapper, const CSocketTCPAddress& DestinationAddress);
			CSocketTCPServerManagerMessageResponseSocketAccept(const CSocketTCPServerManagerMessageResponseSocketAccept& Other);
			CSocketTCPServerManagerMessageResponseSocketAccept(CSocketTCPServerManagerMessageResponseSocketAccept&& Other);
			virtual ~CSocketTCPServerManagerMessageResponseSocketAccept(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPServerManagerMessageResponseSocketAccept=CSharedPointer<CSocketTCPServerManagerMessageResponseSocketAccept>;
	using														CCSPSocketTCPServerManagerMessageResponseSocketAccept=CSharedPointer<const CSocketTCPServerManagerMessageResponseSocketAccept>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------