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
	class CSocketTCPClientManagerMessageResponseSocketClosed final : public CSocketTCPClientManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CSocketTCPClientManagerMessageResponseSocketClosed& operator=(const CSocketTCPClientManagerMessageResponseSocketClosed& Other);
			CSocketTCPClientManagerMessageResponseSocketClosed& operator=(CSocketTCPClientManagerMessageResponseSocketClosed&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;

		public:
			CSocketTCPClientManagerMessageResponseSocketClosed(const CSocketID& SocketID);
			CSocketTCPClientManagerMessageResponseSocketClosed(const CSocketTCPClientManagerMessageResponseSocketClosed& Other);
			CSocketTCPClientManagerMessageResponseSocketClosed(CSocketTCPClientManagerMessageResponseSocketClosed&& Other) noexcept;
			virtual ~CSocketTCPClientManagerMessageResponseSocketClosed(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPClientManagerMessageResponseSocketClosed=CSharedPointer<CSocketTCPClientManagerMessageResponseSocketClosed>;
	using														CCSPSocketTCPClientManagerMessageResponseSocketClosed=CSharedPointer<const CSocketTCPClientManagerMessageResponseSocketClosed>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------