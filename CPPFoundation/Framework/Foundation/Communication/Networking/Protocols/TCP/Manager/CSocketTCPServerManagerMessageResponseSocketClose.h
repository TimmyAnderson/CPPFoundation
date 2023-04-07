//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPServerManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPServerManagerMessageResponseSocketClose final : public CSocketTCPServerManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CSocketTCPServerManagerMessageResponseSocketClose& operator=(const CSocketTCPServerManagerMessageResponseSocketClose& Other);
			CSocketTCPServerManagerMessageResponseSocketClose& operator=(CSocketTCPServerManagerMessageResponseSocketClose&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;

		public:
			CSocketTCPServerManagerMessageResponseSocketClose(const CSocketID& SocketID);
			CSocketTCPServerManagerMessageResponseSocketClose(const CSocketTCPServerManagerMessageResponseSocketClose& Other);
			CSocketTCPServerManagerMessageResponseSocketClose(CSocketTCPServerManagerMessageResponseSocketClose&& Other) noexcept;
			virtual ~CSocketTCPServerManagerMessageResponseSocketClose(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPServerManagerMessageResponseSocketClose=CSharedPointer<CSocketTCPServerManagerMessageResponseSocketClose>;
	using														CCSPSocketTCPServerManagerMessageResponseSocketClose=CSharedPointer<const CSocketTCPServerManagerMessageResponseSocketClose>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------