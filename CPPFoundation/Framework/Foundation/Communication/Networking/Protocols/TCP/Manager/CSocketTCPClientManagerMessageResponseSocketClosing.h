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
	class CSocketTCPClientManagerMessageResponseSocketClosing final : public CSocketTCPClientManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			enum class EClosingEnd : uint8
			{
//----------------------------------------------------------------------------------------------------------------------
				E_READ=1,
				E_WRITE=2,
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private:
			EClosingEnd											MClosingEnd;

		public:
			CSocketTCPClientManagerMessageResponseSocketClosing& operator=(const CSocketTCPClientManagerMessageResponseSocketClosing& Other);
			CSocketTCPClientManagerMessageResponseSocketClosing& operator=(CSocketTCPClientManagerMessageResponseSocketClosing&& Other);

		public:
			virtual CString ToString(void) const override;
			EClosingEnd GetClosingEnd(void) const noexcept;

		public:
			CSocketTCPClientManagerMessageResponseSocketClosing(const CSocketID& SocketID, EClosingEnd ClosingEnd);
			CSocketTCPClientManagerMessageResponseSocketClosing(const CSocketTCPClientManagerMessageResponseSocketClosing& Other);
			CSocketTCPClientManagerMessageResponseSocketClosing(CSocketTCPClientManagerMessageResponseSocketClosing&& Other);
			virtual ~CSocketTCPClientManagerMessageResponseSocketClosing(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPClientManagerMessageResponseSocketClosing=CSharedPointer<CSocketTCPClientManagerMessageResponseSocketClosing>;
	using														CCSPSocketTCPClientManagerMessageResponseSocketClosing=CSharedPointer<const CSocketTCPClientManagerMessageResponseSocketClosing>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------