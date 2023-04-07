//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPServerManagerEventContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerEventContext::CSocketTCPServerManagerEventContext(const CEventID& EventID, ISocketTCPServerManagerCallback& Callback)
		: CEventContext(EventID), MCallback(Callback)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerEventContext::CSocketTCPServerManagerEventContext(CEventID&& EventID, ISocketTCPServerManagerCallback& Callback)
		: CEventContext(FUNCTION_MOVE(EventID)), MCallback(Callback)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerEventContext::CSocketTCPServerManagerEventContext(const CSocketTCPServerManagerEventContext& Other)
		: CEventContext(Other), MCallback(Other.MCallback)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerEventContext::CSocketTCPServerManagerEventContext(CSocketTCPServerManagerEventContext&& Other)
		: CEventContext(FUNCTION_MOVE(Other)), MCallback(Other.MCallback)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerEventContext::~CSocketTCPServerManagerEventContext(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerEventContext& CSocketTCPServerManagerEventContext::operator=(const CSocketTCPServerManagerEventContext& Other)
	{
		CEventContext::operator=(Other);

		MCallback=Other.MCallback;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerEventContext& CSocketTCPServerManagerEventContext::operator=(CSocketTCPServerManagerEventContext&& Other)
	{
		CEventContext::operator=(FUNCTION_MOVE(Other));

		MCallback=FUNCTION_MOVE(Other.MCallback);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	ISocketTCPServerManagerCallback& CSocketTCPServerManagerEventContext::GetCallback(void) const noexcept
	{
		return(MCallback);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------