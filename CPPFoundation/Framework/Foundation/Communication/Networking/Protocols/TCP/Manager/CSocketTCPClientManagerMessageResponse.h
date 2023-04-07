//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketID.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CSocketTCPClientManagerMessage.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPClientManagerMessageResponse : public CSocketTCPClientManagerMessage
	{
//----------------------------------------------------------------------------------------------------------------------
		protected:
			CSocketID											MSocketID;

		public:
			CSocketTCPClientManagerMessageResponse& operator=(const CSocketTCPClientManagerMessageResponse& Other);
			CSocketTCPClientManagerMessageResponse& operator=(CSocketTCPClientManagerMessageResponse&& Other) noexcept;

		public:
			const CSocketID& GetSocketID(void) const noexcept;

		protected:
			CSocketTCPClientManagerMessageResponse(const CSocketID& SocketID);
			CSocketTCPClientManagerMessageResponse(const CSocketTCPClientManagerMessageResponse& Other);
			CSocketTCPClientManagerMessageResponse(CSocketTCPClientManagerMessageResponse&& Other) noexcept;
			virtual ~CSocketTCPClientManagerMessageResponse(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPClientManagerMessageResponse=CSharedPointer<CSocketTCPClientManagerMessageResponse>;
	using														CCSPSocketTCPClientManagerMessageResponse=CSharedPointer<const CSocketTCPClientManagerMessageResponse>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------