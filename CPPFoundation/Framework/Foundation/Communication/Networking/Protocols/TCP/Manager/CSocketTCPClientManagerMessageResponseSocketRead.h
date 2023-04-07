//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPClientManagerMessageResponseSocketRead final : public CSocketTCPClientManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPByteBuffer										MData;

		public:
			CSocketTCPClientManagerMessageResponseSocketRead& operator=(const CSocketTCPClientManagerMessageResponseSocketRead& Other);
			CSocketTCPClientManagerMessageResponseSocketRead& operator=(CSocketTCPClientManagerMessageResponseSocketRead&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;
			CCSPByteBuffer GetData(void) const noexcept;

		public:
			CSocketTCPClientManagerMessageResponseSocketRead(const CSocketID& SocketID, CCSPByteBuffer Data);
			CSocketTCPClientManagerMessageResponseSocketRead(const CSocketTCPClientManagerMessageResponseSocketRead& Other);
			CSocketTCPClientManagerMessageResponseSocketRead(CSocketTCPClientManagerMessageResponseSocketRead&& Other) noexcept;
			virtual ~CSocketTCPClientManagerMessageResponseSocketRead(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPClientManagerMessageResponseSocketRead=CSharedPointer<CSocketTCPClientManagerMessageResponseSocketRead>;
	using														CCSPSocketTCPClientManagerMessageResponseSocketRead=CSharedPointer<const CSocketTCPClientManagerMessageResponseSocketRead>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------