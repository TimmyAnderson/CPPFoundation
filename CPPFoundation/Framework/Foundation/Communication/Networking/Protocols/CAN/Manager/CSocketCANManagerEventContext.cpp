//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANManagerEventContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerEventContext::CSocketCANManagerEventContext(const CEventID& EventID, ISocketCANManagerCallback& Callback)
		: CEventContext(EventID), MCallback(Callback)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerEventContext::CSocketCANManagerEventContext(CEventID&& EventID, ISocketCANManagerCallback& Callback)
		: CEventContext(FUNCTION_MOVE(EventID)), MCallback(Callback)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerEventContext::CSocketCANManagerEventContext(const CSocketCANManagerEventContext& Other)
		: CEventContext(Other), MCallback(Other.MCallback)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerEventContext::CSocketCANManagerEventContext(CSocketCANManagerEventContext&& Other)
		: CEventContext(FUNCTION_MOVE(Other)), MCallback(Other.MCallback)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerEventContext::~CSocketCANManagerEventContext(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerEventContext& CSocketCANManagerEventContext::operator=(const CSocketCANManagerEventContext& Other)
	{
		CEventContext::operator=(Other);

		MCallback=Other.MCallback;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerEventContext& CSocketCANManagerEventContext::operator=(CSocketCANManagerEventContext&& Other)
	{
		CEventContext::operator=(FUNCTION_MOVE(Other));

		MCallback=FUNCTION_MOVE(Other.MCallback);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	ISocketCANManagerCallback& CSocketCANManagerEventContext::GetCallback(void) const noexcept
	{
		return(MCallback);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------