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
	class CSocketTCPServerManagerMessageResponseSocketError final : public CSocketTCPServerManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CSocketTCPServerManagerMessageResponseSocketError& operator=(const CSocketTCPServerManagerMessageResponseSocketError& Other);
			CSocketTCPServerManagerMessageResponseSocketError& operator=(CSocketTCPServerManagerMessageResponseSocketError&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;

		public:
			CSocketTCPServerManagerMessageResponseSocketError(const CSocketID& SocketID);
			CSocketTCPServerManagerMessageResponseSocketError(const CSocketTCPServerManagerMessageResponseSocketError& Other);
			CSocketTCPServerManagerMessageResponseSocketError(CSocketTCPServerManagerMessageResponseSocketError&& Other) noexcept;
			virtual ~CSocketTCPServerManagerMessageResponseSocketError(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPServerManagerMessageResponseSocketError=CSharedPointer<CSocketTCPServerManagerMessageResponseSocketError>;
	using														CCSPSocketTCPServerManagerMessageResponseSocketError=CSharedPointer<const CSocketTCPServerManagerMessageResponseSocketError>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------