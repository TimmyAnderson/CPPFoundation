//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CDequeue.h>
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Manager/CSocketUDPManagerMessageRequestSocketWrite.h>
#include <Framework/Foundation/Time/CTimeout.h>
#include "CSocketUDPResponseItemData.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPResponseItem final : public CPPFoundation::Foundation::CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			using												CSocketUDPResponseItemDataCollection=CPPFoundation::Foundation::CVector<CSocketUDPResponseItemData>;

		private:
			CPPFoundation::Foundation::CTimeout					MTimeout;
			CPPFoundation::Foundation::CSocketID					MSocketID;
			CPPFoundation::Foundation::CSocketUDPAddress			MDestinationAddress;
			CSocketUDPResponseItemDataCollection				MResponseItemDataCollection;

		public:
			CPPFoundation::Foundation::CTimeout GetTimeout(void) const noexcept;
			CPPFoundation::Foundation::CSPSocketUDPManagerMessageRequestSocketWrite CreateWriteRequest(CPPFoundation::Foundation::CCSPByteBuffer RequestData) const;

		public:
			CPPFoundation::Foundation::CSharedPointer<CSocketUDPResponseItem> CreateCopyWithModifiedAddress(const CPPFoundation::Foundation::CSocketUDPAddress& DestinationAddress) const;

		public:
			CSocketUDPResponseItem(const CPPFoundation::Foundation::CTimeout& Timeout, const CPPFoundation::Foundation::CSocketID& SocketID, const CPPFoundation::Foundation::CSocketUDPAddress& DestinationAddress, const CSocketUDPResponseItemDataCollection& ResponseItemDataCollection);
			virtual ~CSocketUDPResponseItem(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDPResponseItem=CPPFoundation::Foundation::CSharedPointer<CSocketUDPResponseItem>;
	using														CSocketUDPResponseItemCollection=CPPFoundation::Foundation::CDequeue<CSPSocketUDPResponseItem>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------