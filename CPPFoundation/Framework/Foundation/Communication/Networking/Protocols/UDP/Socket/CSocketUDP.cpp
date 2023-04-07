//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDP.h"
#include <Framework/Platform/Sockets/CSocketWrapperUDP.h>
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
	CSocketUDP::CSocketUDP(CLogWriter& LogWriter, const CSocketID& SocketID)
		: CSocket(LogWriter,SocketID), MSocketWrapper(new CSocketWrapperUDP())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDP::~CSocketUDP(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int32 CSocketUDP::GetSocketHandler(void) const noexcept
	{
		return(MSocketWrapper->GetSocketHandler());
	}
//----------------------------------------------------------------------------------------------------------------------
	ISPSocketWrapper CSocketUDP::GetSocketWrapper(void) const noexcept
	{
		return(MSocketWrapper);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDP::BindToAddress(const CSocketUDPAddress& Address)
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
	void CSocketUDP::SendTo(const CSocketUDPSendToParameters& Parameters, CSocketUDPSendToResult& Result)
	{
		try
		{
			MSocketWrapper->SendTo(Parameters,Result);

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] SUCCESSFULLY SENT [",Result.GetNumberOfSentBytes(),"] BYTES to ADDRESS [",Parameters.GetUDPAddress(),"] !")));
		}
		catch(const CSocketException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SEND DATA to ADDRESS [",Parameters.GetUDPAddress(),"] !"),E));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SEND DATA to ADDRESS [",Parameters.GetUDPAddress(),"] ! EXCEPTION [",E.GetMessage(),"] !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SEND DATA to ADDRESS [",Parameters.GetUDPAddress(),"] !"),CUnknownException()));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SEND DATA to ADDRESS [",Parameters.GetUDPAddress(),"] !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDP::ReceiveFrom(const CSocketUDPReceiveFromParameters& Parameters, CSocketUDPReceiveFromResult& Result)
	{
		try
		{
			MSocketWrapper->ReceiveFrom(Parameters,Result);

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] SUCCESSFULLY RECEIVED [",Result.GetNumberOfReceivedBytes(),"] BYTES from ADDRESS [",Result.GetUDPAddress(),"] !")));
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
	int32 CSocketUDP::GetSendBufferSize(void)
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
	void CSocketUDP::SetSendBufferSize(int32 SendBufferSize)
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
	int32 CSocketUDP::GetReceiveBufferSize(void)
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
	void CSocketUDP::SetReceiveBufferSize(int32 ReceiveBufferSize)
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