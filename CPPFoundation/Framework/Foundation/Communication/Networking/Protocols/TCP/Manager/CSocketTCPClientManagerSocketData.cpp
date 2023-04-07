//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerSocketData.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerSocketData::CSocketTCPClientManagerSocketData(CSPSocketTCPClient Socket, ESocketTCPClientManagerSocketState SocketState, CCSPSocketTCPClientManagerMessageRequestSocketConnect ConnectOperation)
		: MSocket(Socket), MSocketState(SocketState), MConnectOperation(ConnectOperation), MWriteOperations()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerSocketData::~CSocketTCPClientManagerSocketData(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPClientManagerSocketData::SocketStateToString(CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState State)
	{
		switch(State)
		{
			case CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_WAITING_FOR_CONNECTION:
			{
				return("WAITING FOR CONNECTION");
			}
			break;

			case CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_CONNECTED:
			{
				return("CONNECTED");
			}
			break;

			case CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_HALF_CLOSED_READ:
			{
				return("HALF CLOSED READ");
			}
			break;

			case CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_HALF_CLOSED_WRITE:
			{
				return("HALF CLOSED WRITE");
			}
			break;

			case CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_CLOSED:
			{
				return("CLOSED");
			}
			break;

			case CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_FAILED:
			{
				return("FAILED");
			}
			break;

			default:
			{
				return("NONE");
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSPSocketTCPClient CSocketTCPClientManagerSocketData::GetSocket(void) const noexcept
	{
		return(MSocket);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState CSocketTCPClientManagerSocketData::GetSocketState(void) const noexcept
	{
		return(MSocketState);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManagerSocketData::SetSocketState(CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState SocketState) noexcept
	{
		MSocketState=SocketState;
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPClientManagerMessageRequestSocketConnect CSocketTCPClientManagerSocketData::GetConnectOperation(void) const noexcept
	{
		return(MConnectOperation);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerWriteOperationCollection& CSocketTCPClientManagerSocketData::GetWriteOperations(void) noexcept
	{
		return(MWriteOperations);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketTCPClientManagerWriteOperationCollection& CSocketTCPClientManagerSocketData::GetWriteOperations(void) const noexcept
	{
		return(MWriteOperations);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManagerSocketData::AddWriteOperation(CCSPSocketTCPClientManagerMessageRequestSocketWrite Operation)
	{
		MWriteOperations.PushBack(Operation);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManagerSocketData::ClearWriteOperations(void)
	{
		MWriteOperations.Clear();
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------