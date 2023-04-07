//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPManagerSocketData.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerSocketData::CSocketUDPManagerSocketData(CSPSocketUDP Socket)
		: MSocket(Socket), MSocketState(ESocketUDPManagerSocketState::E_OPENED), MWriteOperations()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerSocketData::~CSocketUDPManagerSocketData(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketUDPManagerSocketData::SocketStateToString(CSocketUDPManagerSocketData::ESocketUDPManagerSocketState State)
	{
		switch(State)
		{
			case CSocketUDPManagerSocketData::ESocketUDPManagerSocketState::E_OPENED:
			{
				return("OPENED");
			}
			break;

			case CSocketUDPManagerSocketData::ESocketUDPManagerSocketState::E_CLOSED:
			{
				return("CLOSED");
			}
			break;

			case CSocketUDPManagerSocketData::ESocketUDPManagerSocketState::E_FAILED:
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
	CSPSocketUDP CSocketUDPManagerSocketData::GetSocket(void) const noexcept
	{
		return(MSocket);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerSocketData::ESocketUDPManagerSocketState CSocketUDPManagerSocketData::GetSocketState(void) const noexcept
	{
		return(MSocketState);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerSocketData::SetSocketState(CSocketUDPManagerSocketData::ESocketUDPManagerSocketState SocketState) noexcept
	{
		MSocketState=SocketState;
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerWriteOperationCollection& CSocketUDPManagerSocketData::GetWriteOperations(void) noexcept
	{
		return(MWriteOperations);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerSocketData::AddWriteOperation(CCSPSocketUDPManagerMessageRequestSocketWrite Operation)
	{
		MWriteOperations.PushBack(Operation);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerSocketData::ClearWriteOperations(void)
	{
		MWriteOperations.Clear();
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------