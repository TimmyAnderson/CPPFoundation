//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANAddress.h>
#include "CSocketCANManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANManagerMessageResponseSocketRead final : public CSocketCANManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSocketCANAddress									MSourceAddress;
			CCSPByteBuffer										MData;

		public:
			CSocketCANManagerMessageResponseSocketRead& operator=(const CSocketCANManagerMessageResponseSocketRead& Other);
			CSocketCANManagerMessageResponseSocketRead& operator=(CSocketCANManagerMessageResponseSocketRead&& Other);

		public:
			virtual CString ToString(void) const override;
			const CSocketCANAddress& GetSourceAddress(void) const noexcept;
			CCSPByteBuffer GetData(void) const noexcept;

		public:
			CSocketCANManagerMessageResponseSocketRead(const CSocketID& SocketID, const CSocketCANAddress& SourceAddress, CCSPByteBuffer Data);
			CSocketCANManagerMessageResponseSocketRead(const CSocketCANManagerMessageResponseSocketRead& Other);
			CSocketCANManagerMessageResponseSocketRead(CSocketCANManagerMessageResponseSocketRead&& Other);
			virtual ~CSocketCANManagerMessageResponseSocketRead(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketCANManagerMessageResponseSocketRead=CSharedPointer<CSocketCANManagerMessageResponseSocketRead>;
	using														CCSPSocketCANManagerMessageResponseSocketRead=CSharedPointer<const CSocketCANManagerMessageResponseSocketRead>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------