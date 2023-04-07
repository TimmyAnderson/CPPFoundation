//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/CSocketUDPAddress.h>
#include "CSocketUDPManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPManagerMessageResponseSocketRead final : public CSocketUDPManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSocketUDPAddress									MSourceAddress;
			CCSPByteBuffer										MData;

		public:
			CSocketUDPManagerMessageResponseSocketRead& operator=(const CSocketUDPManagerMessageResponseSocketRead& Other);
			CSocketUDPManagerMessageResponseSocketRead& operator=(CSocketUDPManagerMessageResponseSocketRead&& Other);

		public:
			virtual CString ToString(void) const override;
			const CSocketUDPAddress& GetSourceAddress(void) const noexcept;
			CCSPByteBuffer GetData(void) const noexcept;

		public:
			CSocketUDPManagerMessageResponseSocketRead(const CSocketID& SocketID, const CSocketUDPAddress& SourceAddress, CCSPByteBuffer Data);
			CSocketUDPManagerMessageResponseSocketRead(const CSocketUDPManagerMessageResponseSocketRead& Other);
			CSocketUDPManagerMessageResponseSocketRead(CSocketUDPManagerMessageResponseSocketRead&& Other);
			virtual ~CSocketUDPManagerMessageResponseSocketRead(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDPManagerMessageResponseSocketRead=CSharedPointer<CSocketUDPManagerMessageResponseSocketRead>;
	using														CCSPSocketUDPManagerMessageResponseSocketRead=CSharedPointer<const CSocketUDPManagerMessageResponseSocketRead>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------