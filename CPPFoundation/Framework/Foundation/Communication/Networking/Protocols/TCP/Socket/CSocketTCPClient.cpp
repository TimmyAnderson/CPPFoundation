//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClient.h"
#include <Framework/Platform/Sockets/CSocketWrapperTCP.h>
#include <Framework/Foundation/Exceptions/CSocketException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Platform;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClient::CSocketTCPClient(CLogWriter& LogWriter, const CSocketID& SocketID, ISPSocketTCPWrapper SocketTCPWrapper)
		: CSocket(LogWriter,SocketID), MSocketWrapper(SocketTCPWrapper)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClient::CSocketTCPClient(CLogWriter& LogWriter, const CSocketID& SocketID)
		: CSocket(LogWriter,SocketID), MSocketWrapper(new CSocketWrapperTCP())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClient::~CSocketTCPClient(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int32 CSocketTCPClient::GetSocketHandler(void) const noexcept
	{
		return(MSocketWrapper->GetSocketHandler());
	}
//----------------------------------------------------------------------------------------------------------------------
	ISPSocketWrapper CSocketTCPClient::GetSocketWrapper(void) const noexcept
	{
		return(MSocketWrapper);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPClient::ConnectToAddress(const CSocketTCPAddress& Address)
	{
		try
		{
			bool												Connected=MSocketWrapper->ConnectToAddress(Address);

			if (Connected==true)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] SUCCESSFULLY CONNECTED to ADDRESS [",Address,"] !")));
			}
			else
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] is CONNECTING to ADDRESS [",Address,"] !")));
			}

			return(Connected);
		}
		catch(const CSocketException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to CONNECT to ADDRESS [",Address,"] !"),E));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to CONNECT to ADDRESS [",Address,"] ! EXCEPTION [",E.GetMessage(),"] !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to CONNECT to ADDRESS [",Address,"] !"),CUnknownException()));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to CONNECT to ADDRESS [",Address,"] !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClient::Shutdown(ESocketTCPShutdownFlags ShutdownFlags)
	{
		try
		{
			MSocketWrapper->Shutdown(ShutdownFlags);

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] SUCCESSFULLY SHUTDOWN SOCKET !")));
		}
		catch(const CSocketException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SHUTDOWN SOCKET !"),E));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SHUTDOWN SOCKET ! EXCEPTION [",E.GetMessage(),"] !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SHUTDOWN SOCKET !"),CUnknownException()));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SHUTDOWN SOCKET !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClient::Send(const CSocketTCPSendParameters& Parameters, CSocketTCPSendResult& Result)
	{
		try
		{
			MSocketWrapper->Send(Parameters,Result);

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] SUCCESSFULLY SENT [",Result.GetNumberOfSentBytes(),"] BYTES !")));
		}
		catch(const CSocketException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SEND DATA !"),E));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SEND DATA ! EXCEPTION [",E.GetMessage(),"] !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SEND DATA !"),CUnknownException()));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SEND DATA !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClient::Receive(const CSocketTCPReceiveParameters& Parameters, CSocketTCPReceiveResult& Result)
	{
		try
		{
			MSocketWrapper->Receive(Parameters,Result);

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] SUCCESSFULLY RECEIVED [",Result.GetNumberOfReceivedBytes(),"] BYTES !")));
		}
		catch(const CSocketException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to RECEIVE DATA !"),E));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to RECEIVE DATA ! EXCEPTION [",E.GetMessage(),"] !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to RECEIVE DATA !"),CUnknownException()));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to RECEIVE DATA !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSocketTCPClient::GetSendBufferSize(void)
	{
		try
		{
			int32												SendBufferSize=MSocketWrapper->GetSendBufferSize();

			return(SendBufferSize);
		}
		catch(const CSocketException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to GET SEND BUFFER SIZE !"),E));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to GET SEND BUFFER SIZE ! EXCEPTION [",E.GetMessage(),"] !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to GET SEND BUFFER SIZE !"),CUnknownException()));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to GET SEND BUFFER SIZE !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClient::SetSendBufferSize(int32 SendBufferSize)
	{
		try
		{
			MSocketWrapper->SetSendBufferSize(SendBufferSize);
		}
		catch(const CSocketException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SET SEND BUFFER SIZE !"),E));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SET SEND BUFFER SIZE ! EXCEPTION [",E.GetMessage(),"] !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SET SEND BUFFER SIZE !"),CUnknownException()));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SET SEND BUFFER SIZE !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSocketTCPClient::GetReceiveBufferSize(void)
	{
		try
		{
			int32												ReceiveBufferSize=MSocketWrapper->GetReceiveBufferSize();

			return(ReceiveBufferSize);
		}
		catch(const CSocketException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to GET RECEIVE BUFFER SIZE !"),E));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to GET RECEIVE BUFFER SIZE ! EXCEPTION [",E.GetMessage(),"] !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to GET RECEIVE BUFFER SIZE !"),CUnknownException()));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to GET RECEIVE BUFFER SIZE !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClient::SetReceiveBufferSize(int32 ReceiveBufferSize)
	{
		try
		{
			MSocketWrapper->SetReceiveBufferSize(ReceiveBufferSize);
		}
		catch(const CSocketException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SET RECEIVE BUFFER SIZE !"),E));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SET RECEIVE BUFFER SIZE ! EXCEPTION [",E.GetMessage(),"] !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SET RECEIVE BUFFER SIZE !"),CUnknownException()));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SET RECEIVE BUFFER SIZE !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------