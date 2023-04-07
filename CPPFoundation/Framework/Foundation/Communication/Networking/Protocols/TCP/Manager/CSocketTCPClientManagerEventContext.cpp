//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerEventContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerEventContext::CSocketTCPClientManagerEventContext(const CEventID& EventID, ISocketTCPClientManagerCallback& Callback)
		: CEventContext(EventID), MCallback(Callback)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerEventContext::CSocketTCPClientManagerEventContext(CEventID&& EventID, ISocketTCPClientManagerCallback& Callback)
		: CEventContext(FUNCTION_MOVE(EventID)), MCallback(Callback)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerEventContext::CSocketTCPClientManagerEventContext(const CSocketTCPClientManagerEventContext& Other)
		: CEventContext(Other), MCallback(Other.MCallback)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerEventContext::CSocketTCPClientManagerEventContext(CSocketTCPClientManagerEventContext&& Other) noexcept
		: CEventContext(FUNCTION_MOVE(Other)), MCallback(Other.MCallback)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerEventContext::~CSocketTCPClientManagerEventContext(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerEventContext& CSocketTCPClientManagerEventContext::operator=(const CSocketTCPClientManagerEventContext& Other)
	{
		CEventContext::operator=(Other);

		MCallback=Other.MCallback;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerEventContext& CSocketTCPClientManagerEventContext::operator=(CSocketTCPClientManagerEventContext&& Other) noexcept
	{
		CEventContext::operator=(FUNCTION_MOVE(Other));

		MCallback=FUNCTION_MOVE(Other.MCallback);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	ISocketTCPClientManagerCallback& CSocketTCPClientManagerEventContext::GetCallback(void) const noexcept
	{
		return(MCallback);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------