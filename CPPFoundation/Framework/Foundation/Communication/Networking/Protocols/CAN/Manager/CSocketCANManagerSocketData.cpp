//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANManagerSocketData.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerSocketData::CSocketCANManagerSocketData(CSPSocketCAN Socket)
		: MSocket(Socket), MSocketState(ESocketCANManagerSocketState::E_OPENED), MWriteOperations()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerSocketData::~CSocketCANManagerSocketData(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketCANManagerSocketData::SocketStateToString(CSocketCANManagerSocketData::ESocketCANManagerSocketState State)
	{
		switch(State)
		{
			case CSocketCANManagerSocketData::ESocketCANManagerSocketState::E_OPENED:
			{
				return("OPENED");
			}
			break;

			case CSocketCANManagerSocketData::ESocketCANManagerSocketState::E_CLOSED:
			{
				return("CLOSED");
			}
			break;

			case CSocketCANManagerSocketData::ESocketCANManagerSocketState::E_FAILED:
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
	CSPSocketCAN CSocketCANManagerSocketData::GetSocket(void) const noexcept
	{
		return(MSocket);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerSocketData::ESocketCANManagerSocketState CSocketCANManagerSocketData::GetSocketState(void) const noexcept
	{
		return(MSocketState);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerSocketData::SetSocketState(CSocketCANManagerSocketData::ESocketCANManagerSocketState SocketState) noexcept
	{
		MSocketState=SocketState;
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerWriteOperationCollection& CSocketCANManagerSocketData::GetWriteOperations(void) noexcept
	{
		return(MWriteOperations);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerSocketData::AddWriteOperation(CCSPSocketCANManagerMessageRequestSocketWrite Operation)
	{
		MWriteOperations.PushBack(Operation);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerSocketData::ClearWriteOperations(void)
	{
		MWriteOperations.Clear();
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------