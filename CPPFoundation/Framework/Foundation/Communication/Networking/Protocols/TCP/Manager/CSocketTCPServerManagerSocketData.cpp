//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPServerManagerSocketData.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerSocketData::CSocketTCPServerManagerSocketData(CSPSocketTCPServer Socket)
		: MSocket(Socket), MSocketState(ESocketTCPServerManagerSocketState::E_OPENED)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerSocketData::~CSocketTCPServerManagerSocketData(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPServerManagerSocketData::SocketStateToString(CSocketTCPServerManagerSocketData::ESocketTCPServerManagerSocketState State)
	{
		switch(State)
		{
			case CSocketTCPServerManagerSocketData::ESocketTCPServerManagerSocketState::E_OPENED:
			{
				return("OPENED");
			}
			break;

			case CSocketTCPServerManagerSocketData::ESocketTCPServerManagerSocketState::E_CLOSED:
			{
				return("CLOSED");
			}
			break;

			case CSocketTCPServerManagerSocketData::ESocketTCPServerManagerSocketState::E_FAILED:
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
	CSPSocketTCPServer CSocketTCPServerManagerSocketData::GetSocket(void) const noexcept
	{
		return(MSocket);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerSocketData::ESocketTCPServerManagerSocketState CSocketTCPServerManagerSocketData::GetSocketState(void) const noexcept
	{
		return(MSocketState);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManagerSocketData::SetSocketState(CSocketTCPServerManagerSocketData::ESocketTCPServerManagerSocketState SocketState) noexcept
	{
		MSocketState=SocketState;
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------