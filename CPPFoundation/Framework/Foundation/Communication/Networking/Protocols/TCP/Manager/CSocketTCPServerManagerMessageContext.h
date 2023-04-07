//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CSocketTCPServerManagerMessageID.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPServerManagerMessageContext : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSocketTCPServerManagerMessageID					MMessageID;

		public:
			CSocketTCPServerManagerMessageContext& operator=(const CSocketTCPServerManagerMessageContext& Other);
			CSocketTCPServerManagerMessageContext& operator=(CSocketTCPServerManagerMessageContext&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;

		public:
			const CSocketTCPServerManagerMessageID& GetMessageID(void) const noexcept;

		public:
			CSocketTCPServerManagerMessageContext(const CSocketTCPServerManagerMessageID& MessageID);
			CSocketTCPServerManagerMessageContext(CSocketTCPServerManagerMessageID&& MessageID);
			CSocketTCPServerManagerMessageContext(const CSocketTCPServerManagerMessageContext& Other);
			CSocketTCPServerManagerMessageContext(CSocketTCPServerManagerMessageContext&& Other) noexcept;
			virtual ~CSocketTCPServerManagerMessageContext(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CCSPSocketTCPServerManagerMessageContext=CSharedPointer<const CSocketTCPServerManagerMessageContext>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------