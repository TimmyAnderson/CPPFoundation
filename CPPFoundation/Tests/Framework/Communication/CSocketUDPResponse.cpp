//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPResponse.h"
#include <Framework/Foundation/Exceptions/CArgumentException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPResponse::CSocketUDPResponse(const CSocketUDPResponseItemCollection& ResponseItemCollection)
		: MRequestData(new CByteBuffer()), MResponseItemCollection(ResponseItemCollection), MExpirationTime()
	{
		if (ResponseItemCollection.GetLength()==0)
		{
			throw(CArgumentException("RESPONSE ITEM COLLECTION must NOT be EMPTY !"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPResponse::CSocketUDPResponse(CCSPByteBuffer RequestData, const CSocketUDPResponseItemCollection& ResponseItemCollection)
		: MRequestData(RequestData), MResponseItemCollection(ResponseItemCollection), MExpirationTime()
	{
		if (ResponseItemCollection.GetLength()==0)
		{
			throw(CArgumentException("RESPONSE ITEM COLLECTION must NOT be EMPTY !"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPResponse::~CSocketUDPResponse(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CCSPByteBuffer CSocketUDPResponse::GetRequestData(void) const
	{
		return(MRequestData);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPResponseItemCollection CSocketUDPResponse::CreateResponseItemCollection(void) const
	{
		return(CSocketUDPResponseItemCollection(MResponseItemCollection));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPResponseItemCollection CSocketUDPResponse::CreateResponseItemCollection(const CSocketUDPAddress& DestinationAddress) const
	{
		CSocketUDPResponseItemCollection						ResponseItemCollection;

		for(CSPSocketUDPResponseItem ResponseItem : MResponseItemCollection)
		{
			ResponseItemCollection.PushBack(ResponseItem->CreateCopyWithModifiedAddress(DestinationAddress));
		}

		return(ResponseItemCollection);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPResponse::Reset(void)
	{
		MExpirationTime.Reset(MResponseItemCollection[0]->GetTimeout());
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketUDPResponse::HasNextResponseItem(void) const noexcept
	{
		if (MResponseItemCollection.GetLength()>1)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CSocketUDPResponse::GetCurrentExpirationTimeout(CSteadyClock::Milliseconds CurrentTime) const noexcept
	{
		return(MExpirationTime.CalculateTimeout(CurrentTime));
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketUDPResponse::HasCurrentResponseItemExpired(CSteadyClock::Milliseconds CurrentTime) const noexcept
	{
		return(MExpirationTime.HasExpired(CurrentTime));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPSocketUDPResponseItem CSocketUDPResponse::GetCurrentResponseItem(void) const
	{
		return(*MResponseItemCollection.Begin());
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPResponse::RemoveCurrentResponseItem(void)
	{
		MResponseItemCollection.PopFront();
		MExpirationTime.Reset(MResponseItemCollection[0]->GetTimeout());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------