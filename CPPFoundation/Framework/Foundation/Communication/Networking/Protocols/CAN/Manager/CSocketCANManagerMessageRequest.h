//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANManagerMessage.h"
#include "CSocketCANManagerMessageResponse.h"
#include "CSocketCANManagerMessageContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANManagerMessageRequest : public CSocketCANManagerMessage
	{
//----------------------------------------------------------------------------------------------------------------------
		protected:
			CSocketID											MSocketID;

		public:
			CSocketCANManagerMessageRequest& operator=(const CSocketCANManagerMessageRequest& Other);
			CSocketCANManagerMessageRequest& operator=(CSocketCANManagerMessageRequest&& Other) noexcept;

		public:
			virtual CCSPSocketCANManagerMessageResponse CreateErrorResponse(void) const=0;

		public:
			const CSocketID& GetSocketID(void) const noexcept;

		protected:
			CSocketCANManagerMessageRequest(const CSocketID& SocketID);
			CSocketCANManagerMessageRequest(const CSocketCANManagerMessageRequest& Other);
			CSocketCANManagerMessageRequest(CSocketCANManagerMessageRequest&& Other) noexcept;
			virtual ~CSocketCANManagerMessageRequest(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketCANManagerMessageRequest=CSharedPointer<CSocketCANManagerMessageRequest>;
	using														CCSPSocketCANManagerMessageRequest=CSharedPointer<const CSocketCANManagerMessageRequest>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------