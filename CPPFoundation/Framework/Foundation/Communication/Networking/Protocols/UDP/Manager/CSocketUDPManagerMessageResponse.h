//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketID.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CSocketUDPManagerMessage.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPManagerMessageResponse : public CSocketUDPManagerMessage
	{
//----------------------------------------------------------------------------------------------------------------------
		protected:
			CSocketID											MSocketID;

		public:
			CSocketUDPManagerMessageResponse& operator=(const CSocketUDPManagerMessageResponse& Other);
			CSocketUDPManagerMessageResponse& operator=(CSocketUDPManagerMessageResponse&& Other) noexcept;

		public:
			const CSocketID& GetSocketID(void) const noexcept;

		protected:
			CSocketUDPManagerMessageResponse(const CSocketID& SocketID);
			CSocketUDPManagerMessageResponse(const CSocketUDPManagerMessageResponse& Other);
			CSocketUDPManagerMessageResponse(CSocketUDPManagerMessageResponse&& Other) noexcept;
			virtual ~CSocketUDPManagerMessageResponse(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDPManagerMessageResponse=CSharedPointer<CSocketUDPManagerMessageResponse>;
	using														CCSPSocketUDPManagerMessageResponse=CSharedPointer<const CSocketUDPManagerMessageResponse>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------