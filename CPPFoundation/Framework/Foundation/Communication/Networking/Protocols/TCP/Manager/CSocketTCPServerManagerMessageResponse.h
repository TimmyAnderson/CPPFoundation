//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketID.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CSocketTCPServerManagerMessage.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPServerManagerMessageResponse : public CSocketTCPServerManagerMessage
	{
//----------------------------------------------------------------------------------------------------------------------
		protected:
			CSocketID											MSocketID;

		public:
			CSocketTCPServerManagerMessageResponse& operator=(const CSocketTCPServerManagerMessageResponse& Other);
			CSocketTCPServerManagerMessageResponse& operator=(CSocketTCPServerManagerMessageResponse&& Other) noexcept;

		public:
			const CSocketID& GetSocketID(void) const noexcept;

		protected:
			CSocketTCPServerManagerMessageResponse(const CSocketID& SocketID);
			CSocketTCPServerManagerMessageResponse(const CSocketTCPServerManagerMessageResponse& Other);
			CSocketTCPServerManagerMessageResponse(CSocketTCPServerManagerMessageResponse&& Other) noexcept;
			virtual ~CSocketTCPServerManagerMessageResponse(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPServerManagerMessageResponse=CSharedPointer<CSocketTCPServerManagerMessageResponse>;
	using														CCSPSocketTCPServerManagerMessageResponse=CSharedPointer<const CSocketTCPServerManagerMessageResponse>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------