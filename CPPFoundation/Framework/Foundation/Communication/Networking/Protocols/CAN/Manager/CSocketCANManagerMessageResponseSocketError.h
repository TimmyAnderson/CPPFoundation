//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANManagerMessageResponseSocketError final : public CSocketCANManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CSocketCANManagerMessageResponseSocketError& operator=(const CSocketCANManagerMessageResponseSocketError& Other);
			CSocketCANManagerMessageResponseSocketError& operator=(CSocketCANManagerMessageResponseSocketError&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;

		public:
			CSocketCANManagerMessageResponseSocketError(const CSocketID& SocketID);
			CSocketCANManagerMessageResponseSocketError(const CSocketCANManagerMessageResponseSocketError& Other);
			CSocketCANManagerMessageResponseSocketError(CSocketCANManagerMessageResponseSocketError&& Other) noexcept;
			virtual ~CSocketCANManagerMessageResponseSocketError(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketCANManagerMessageResponseSocketError=CSharedPointer<CSocketCANManagerMessageResponseSocketError>;
	using														CCSPSocketCANManagerMessageResponseSocketError=CSharedPointer<const CSocketCANManagerMessageResponseSocketError>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------