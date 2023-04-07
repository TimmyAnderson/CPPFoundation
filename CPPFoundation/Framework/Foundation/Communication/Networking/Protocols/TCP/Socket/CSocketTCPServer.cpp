//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPServer.h"
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
	CSocketTCPServer::CSocketTCPServer(CLogWriter& LogWriter, const CSocketID& SocketID)
		: CSocket(LogWriter,SocketID), MSocketWrapper(new CSocketWrapperTCP())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServer::~CSocketTCPServer(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int32 CSocketTCPServer::GetSocketHandler(void) const noexcept
	{
		return(MSocketWrapper->GetSocketHandler());
	}
//----------------------------------------------------------------------------------------------------------------------
	ISPSocketWrapper CSocketTCPServer::GetSocketWrapper(void) const noexcept
	{
		return(MSocketWrapper);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServer::BindToAddress(const CSocketTCPAddress& Address)
	{
		try
		{
			MSocketWrapper->BindToAddress(Address);

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] SUCCESSFULLY BOUND to ADDRESS [",Address.ToString(),"] !")));
		}
		catch(const CSocketException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to BIND to ADDRESS [",Address.ToString(),"] !"),E));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to BIND to ADDRESS [",Address.ToString(),"] ! EXCEPTION [",E.GetMessage(),"] !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to BIND to ADDRESS [",Address.ToString(),"] !"),CUnknownException()));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to BIND to ADDRESS [",Address.ToString(),"] !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServer::Listen(Size MaximumNumberOfPendingConnections)
	{
		try
		{
			MSocketWrapper->Listen(MaximumNumberOfPendingConnections);

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] SUCCESSFULLY LISTENED for SOCKET !")));
		}
		catch(const CSocketException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to LISTEN for SOCKET !"),E));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to LISTEN for SOCKET ! EXCEPTION [",E.GetMessage(),"] !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to LISTEN for SOCKET !"),CUnknownException()));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to LISTEN for SOCKET !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	ISPSocketTCPWrapper CSocketTCPServer::Accept(CSocketTCPAddress& Address)
	{
		try
		{
			ISPSocketTCPWrapper									SocketWrapper=MSocketWrapper->Accept(Address);

			if (SocketWrapper!=nullptr)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] SUCCESSFULLY ACCEPTED SOCKET !")));

				return(SocketWrapper);
			}
			else
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to ACCEPT SOCKET !")));

				return(nullptr);
			}
		}
		catch(const CSocketException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to ACCEPT SOCKET !"),E));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to ACCEPT SOCKET ! EXCEPTION [",E.GetMessage(),"] !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to ACCEPT SOCKET !"),CUnknownException()));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to ACCEPT SOCKET !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServer::Shutdown(ESocketTCPShutdownFlags ShutdownFlags)
	{
		try
		{
			MSocketWrapper->Shutdown(ShutdownFlags);

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] SUCCESSFULLY SHUTDOWN SOCKET !")));
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
	int32 CSocketTCPServer::GetSendBufferSize(void)
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
	void CSocketTCPServer::SetSendBufferSize(int32 SendBufferSize)
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
	int32 CSocketTCPServer::GetReceiveBufferSize(void)
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
	void CSocketTCPServer::SetReceiveBufferSize(int32 ReceiveBufferSize)
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