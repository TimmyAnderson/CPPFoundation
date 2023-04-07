//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPManagerMessageResponseSocketError final : public CSocketUDPManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CSocketUDPManagerMessageResponseSocketError& operator=(const CSocketUDPManagerMessageResponseSocketError& Other);
			CSocketUDPManagerMessageResponseSocketError& operator=(CSocketUDPManagerMessageResponseSocketError&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;

		public:
			CSocketUDPManagerMessageResponseSocketError(const CSocketID& SocketID);
			CSocketUDPManagerMessageResponseSocketError(const CSocketUDPManagerMessageResponseSocketError& Other);
			CSocketUDPManagerMessageResponseSocketError(CSocketUDPManagerMessageResponseSocketError&& Other) noexcept;
			virtual ~CSocketUDPManagerMessageResponseSocketError(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDPManagerMessageResponseSocketError=CSharedPointer<CSocketUDPManagerMessageResponseSocketError>;
	using														CCSPSocketUDPManagerMessageResponseSocketError=CSharedPointer<const CSocketUDPManagerMessageResponseSocketError>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------