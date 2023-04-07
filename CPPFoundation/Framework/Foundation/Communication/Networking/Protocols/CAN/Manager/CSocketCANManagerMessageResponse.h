//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketID.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CSocketCANManagerMessage.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANManagerMessageResponse : public CSocketCANManagerMessage
	{
//----------------------------------------------------------------------------------------------------------------------
		protected:
			CSocketID											MSocketID;

		public:
			CSocketCANManagerMessageResponse& operator=(const CSocketCANManagerMessageResponse& Other);
			CSocketCANManagerMessageResponse& operator=(CSocketCANManagerMessageResponse&& Other) noexcept;

		public:
			const CSocketID& GetSocketID(void) const noexcept;

		protected:
			CSocketCANManagerMessageResponse(const CSocketID& SocketID);
			CSocketCANManagerMessageResponse(const CSocketCANManagerMessageResponse& Other);
			CSocketCANManagerMessageResponse(CSocketCANManagerMessageResponse&& Other) noexcept;
			virtual ~CSocketCANManagerMessageResponse(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketCANManagerMessageResponse=CSharedPointer<CSocketCANManagerMessageResponse>;
	using														CCSPSocketCANManagerMessageResponse=CSharedPointer<const CSocketCANManagerMessageResponse>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------