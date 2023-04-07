//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Time/CExpirationTime.h>
#include "CSocketUDPResponseItem.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPResponse final : public CPPFoundation::Foundation::CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CPPFoundation::Foundation::CCSPByteBuffer				MRequestData;
			CSocketUDPResponseItemCollection					MResponseItemCollection;
			CPPFoundation::Foundation::CExpirationTime				MExpirationTime;

		public:
			CPPFoundation::Foundation::CCSPByteBuffer GetRequestData(void) const;
			CSocketUDPResponseItemCollection CreateResponseItemCollection(void) const;
			CSocketUDPResponseItemCollection CreateResponseItemCollection(const CPPFoundation::Foundation::CSocketUDPAddress& DestinationAddress) const;
			void Reset(void);
			bool HasNextResponseItem(void) const noexcept;
			CPPFoundation::Foundation::CTimeout GetCurrentExpirationTimeout(CPPFoundation::Foundation::CSteadyClock::Milliseconds CurrentTime=CPPFoundation::Foundation::CSteadyClock::GetCurrentTimeInMilliseconds()) const noexcept;
			bool HasCurrentResponseItemExpired(CPPFoundation::Foundation::CSteadyClock::Milliseconds CurrentTime=CPPFoundation::Foundation::CSteadyClock::GetCurrentTimeInMilliseconds()) const noexcept;
			CSPSocketUDPResponseItem GetCurrentResponseItem(void) const;
			void RemoveCurrentResponseItem(void);

		public:
			CSocketUDPResponse(const CSocketUDPResponseItemCollection& ResponseItemCollection);
			CSocketUDPResponse(CPPFoundation::Foundation::CCSPByteBuffer RequestData, const CSocketUDPResponseItemCollection& ResponseItemCollection);
			virtual ~CSocketUDPResponse(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDPResponse=CPPFoundation::Foundation::CSharedPointer<CSocketUDPResponse>;
	using														CSocketUDPResponseCollection=CPPFoundation::Foundation::CVector<CSPSocketUDPResponse>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------