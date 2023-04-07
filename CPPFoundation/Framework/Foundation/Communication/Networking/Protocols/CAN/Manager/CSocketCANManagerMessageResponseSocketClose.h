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
	class CSocketCANManagerMessageResponseSocketClose final : public CSocketCANManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CSocketCANManagerMessageResponseSocketClose& operator=(const CSocketCANManagerMessageResponseSocketClose& Other);
			CSocketCANManagerMessageResponseSocketClose& operator=(CSocketCANManagerMessageResponseSocketClose&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;

		public:
			CSocketCANManagerMessageResponseSocketClose(const CSocketID& SocketID);
			CSocketCANManagerMessageResponseSocketClose(const CSocketCANManagerMessageResponseSocketClose& Other);
			CSocketCANManagerMessageResponseSocketClose(CSocketCANManagerMessageResponseSocketClose&& Other) noexcept;
			virtual ~CSocketCANManagerMessageResponseSocketClose(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketCANManagerMessageResponseSocketClose=CSharedPointer<CSocketCANManagerMessageResponseSocketClose>;
	using														CCSPSocketCANManagerMessageResponseSocketClose=CSharedPointer<const CSocketCANManagerMessageResponseSocketClose>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------