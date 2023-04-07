//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPManagerEventContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerEventContext::CSocketUDPManagerEventContext(const CEventID& EventID, ISocketUDPManagerCallback& Callback)
		: CEventContext(EventID), MCallback(Callback)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerEventContext::CSocketUDPManagerEventContext(CEventID&& EventID, ISocketUDPManagerCallback& Callback)
		: CEventContext(FUNCTION_MOVE(EventID)), MCallback(Callback)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerEventContext::CSocketUDPManagerEventContext(const CSocketUDPManagerEventContext& Other)
		: CEventContext(Other), MCallback(Other.MCallback)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerEventContext::CSocketUDPManagerEventContext(CSocketUDPManagerEventContext&& Other) noexcept
		: CEventContext(FUNCTION_MOVE(Other)), MCallback(Other.MCallback)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerEventContext::~CSocketUDPManagerEventContext(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerEventContext& CSocketUDPManagerEventContext::operator=(const CSocketUDPManagerEventContext& Other)
	{
		CEventContext::operator=(Other);

		MCallback=Other.MCallback;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerEventContext& CSocketUDPManagerEventContext::operator=(CSocketUDPManagerEventContext&& Other) noexcept
	{
		CEventContext::operator=(FUNCTION_MOVE(Other));

		MCallback=FUNCTION_MOVE(Other.MCallback);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	ISocketUDPManagerCallback& CSocketUDPManagerEventContext::GetCallback(void) const noexcept
	{
		return(MCallback);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------