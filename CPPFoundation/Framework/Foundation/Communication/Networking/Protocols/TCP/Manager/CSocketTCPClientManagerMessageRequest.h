//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessage.h"
#include "CSocketTCPClientManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPClientManagerMessageRequest : public CSocketTCPClientManagerMessage
	{
//----------------------------------------------------------------------------------------------------------------------
		protected:
			CSocketID											MSocketID;

		public:
			CSocketTCPClientManagerMessageRequest& operator=(const CSocketTCPClientManagerMessageRequest& Other);
			CSocketTCPClientManagerMessageRequest& operator=(CSocketTCPClientManagerMessageRequest&& Other) noexcept;

		public:
			virtual CCSPSocketTCPClientManagerMessageResponse CreateErrorResponse(void) const=0;

		public:
			const CSocketID& GetSocketID(void) const noexcept;

		protected:
			CSocketTCPClientManagerMessageRequest(const CSocketID& SocketID);
			CSocketTCPClientManagerMessageRequest(const CSocketTCPClientManagerMessageRequest& Other);
			CSocketTCPClientManagerMessageRequest(CSocketTCPClientManagerMessageRequest&& Other) noexcept;
			virtual ~CSocketTCPClientManagerMessageRequest(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPClientManagerMessageRequest=CSharedPointer<CSocketTCPClientManagerMessageRequest>;
	using														CCSPSocketTCPClientManagerMessageRequest=CSharedPointer<const CSocketTCPClientManagerMessageRequest>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------