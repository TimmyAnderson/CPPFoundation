//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPServerManagerMessage.h"
#include "CSocketTCPServerManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPServerManagerMessageRequest : public CSocketTCPServerManagerMessage
	{
//----------------------------------------------------------------------------------------------------------------------
		protected:
			CSocketID											MSocketID;

		public:
			CSocketTCPServerManagerMessageRequest& operator=(const CSocketTCPServerManagerMessageRequest& Other);
			CSocketTCPServerManagerMessageRequest& operator=(CSocketTCPServerManagerMessageRequest&& Other) noexcept;

		public:
			virtual CCSPSocketTCPServerManagerMessageResponse CreateErrorResponse(void) const=0;

		public:
			const CSocketID& GetSocketID(void) const noexcept;

		protected:
			CSocketTCPServerManagerMessageRequest(const CSocketID& SocketID);
			CSocketTCPServerManagerMessageRequest(const CSocketTCPServerManagerMessageRequest& Other);
			CSocketTCPServerManagerMessageRequest(CSocketTCPServerManagerMessageRequest&& Other) noexcept;
			virtual ~CSocketTCPServerManagerMessageRequest(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPServerManagerMessageRequest=CSharedPointer<CSocketTCPServerManagerMessageRequest>;
	using														CCSPSocketTCPServerManagerMessageRequest=CSharedPointer<const CSocketTCPServerManagerMessageRequest>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------