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
	class CSocketUDPManagerMessageResponseSocketClose final : public CSocketUDPManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CSocketUDPManagerMessageResponseSocketClose& operator=(const CSocketUDPManagerMessageResponseSocketClose& Other);
			CSocketUDPManagerMessageResponseSocketClose& operator=(CSocketUDPManagerMessageResponseSocketClose&& Other);

		public:
			virtual CString ToString(void) const override;

		public:
			CSocketUDPManagerMessageResponseSocketClose(const CSocketID& SocketID);
			CSocketUDPManagerMessageResponseSocketClose(const CSocketUDPManagerMessageResponseSocketClose& Other);
			CSocketUDPManagerMessageResponseSocketClose(CSocketUDPManagerMessageResponseSocketClose&& Other);
			virtual ~CSocketUDPManagerMessageResponseSocketClose(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDPManagerMessageResponseSocketClose=CSharedPointer<CSocketUDPManagerMessageResponseSocketClose>;
	using														CCSPSocketUDPManagerMessageResponseSocketClose=CSharedPointer<const CSocketUDPManagerMessageResponseSocketClose>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------