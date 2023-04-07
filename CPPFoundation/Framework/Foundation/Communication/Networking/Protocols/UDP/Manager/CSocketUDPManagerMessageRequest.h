//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPManagerMessage.h"
#include "CSocketUDPManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPManagerMessageRequest : public CSocketUDPManagerMessage
	{
//----------------------------------------------------------------------------------------------------------------------
		protected:
			CSocketID											MSocketID;

		public:
			CSocketUDPManagerMessageRequest& operator=(const CSocketUDPManagerMessageRequest& Other);
			CSocketUDPManagerMessageRequest& operator=(CSocketUDPManagerMessageRequest&& Other) noexcept;

		public:
			virtual CCSPSocketUDPManagerMessageResponse CreateErrorResponse(void) const=0;

		public:
			const CSocketID& GetSocketID(void) const noexcept;

		protected:
			CSocketUDPManagerMessageRequest(const CSocketID& SocketID);
			CSocketUDPManagerMessageRequest(const CSocketUDPManagerMessageRequest& Other);
			CSocketUDPManagerMessageRequest(CSocketUDPManagerMessageRequest&& Other) noexcept;
			virtual ~CSocketUDPManagerMessageRequest(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDPManagerMessageRequest=CSharedPointer<CSocketUDPManagerMessageRequest>;
	using														CCSPSocketUDPManagerMessageRequest=CSharedPointer<const CSocketUDPManagerMessageRequest>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------