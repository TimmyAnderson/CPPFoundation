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
	class CSocketTCPClientManagerMessageResponseSocketError final : public CSocketTCPClientManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CSocketTCPClientManagerMessageResponseSocketError& operator=(const CSocketTCPClientManagerMessageResponseSocketError& Other);
			CSocketTCPClientManagerMessageResponseSocketError& operator=(CSocketTCPClientManagerMessageResponseSocketError&& Other);

		public:
			virtual CString ToString(void) const override;

		public:
			CSocketTCPClientManagerMessageResponseSocketError(const CSocketID& SocketID);
			CSocketTCPClientManagerMessageResponseSocketError(const CSocketTCPClientManagerMessageResponseSocketError& Other);
			CSocketTCPClientManagerMessageResponseSocketError(CSocketTCPClientManagerMessageResponseSocketError&& Other);
			virtual ~CSocketTCPClientManagerMessageResponseSocketError(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPClientManagerMessageResponseSocketError=CSharedPointer<CSocketTCPClientManagerMessageResponseSocketError>;
	using														CCSPSocketTCPClientManagerMessageResponseSocketError=CSharedPointer<const CSocketTCPClientManagerMessageResponseSocketError>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------