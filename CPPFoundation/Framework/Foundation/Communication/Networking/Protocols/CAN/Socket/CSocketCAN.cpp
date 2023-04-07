//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCAN.h"
#include <Framework/Platform/Sockets/CSocketWrapperCAN.h>
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
	CSocketCAN::CSocketCAN(CLogWriter& LogWriter, const CSocketID& SocketID)
		: CSocket(LogWriter,SocketID), MSocketWrapper(new CSocketWrapperCAN())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCAN::~CSocketCAN(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketCAN::GetNetworkInterfaceName(int32 NetworkInterfaceIndex)
	{
		try
		{
			// It's safer to create SOCKET INSTANCE on every CALL than to create a SINGLETON INSTANCE that can be corrupted making the FUNCTION UNUSABLE.
			CSocketWrapperCAN									SocketWrapper;
			CString												NetworkInterfaceName=SocketWrapper.GetNetworkInterfaceName(NetworkInterfaceIndex);

			return(NetworkInterfaceName);
		}
		catch(const CSocketException& E)
		{
			throw(CSocketException(CString::Format("SOCKET FAILED to GET NETWORK INTERFACE NAME ! EXCEPTION [",E.GetMessage(),"] !"),E));
		}
		catch(...)
		{
			throw(CSocketException(CString::Format("SOCKET FAILED to GET NETWORK INTERFACE NAME !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSocketCAN::GetNetworkInterfaceIndex(const CString& NetworkInterfaceName)
	{
		try
		{
			// It's safer to create SOCKET INSTANCE on every FUNCTION CALL than to create a SINGLETON INSTANCE that can be corrupted making the FUNCTION UNUSABLE.
			CSocketWrapperCAN									SocketWrapper;
			int32												NetworkInterfaceIndex=SocketWrapper.GetNetworkInterfaceIndex(NetworkInterfaceName);

			return(NetworkInterfaceIndex);
		}
		catch(const CSocketException& E)
		{
			throw(CSocketException(CString::Format("SOCKET FAILED to GET NETWORK INTERFACE INDEX ! EXCEPTION [",E.GetMessage(),"] !"),E));
		}
		catch(...)
		{
			throw(CSocketException(CString::Format("SOCKET FAILED to GET NETWORK INTERFACE INDEX !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int32 CSocketCAN::GetSocketHandler(void) const noexcept
	{
		return(MSocketWrapper->GetSocketHandler());
	}
//----------------------------------------------------------------------------------------------------------------------
	ISPSocketWrapper CSocketCAN::GetSocketWrapper(void) const noexcept
	{
		return(MSocketWrapper);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCAN::BindToAddress(const CSocketCANAddress& Address)
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
	void CSocketCAN::SendTo(const CSocketCANSendToParameters& Parameters, CSocketCANSendToResult& Result)
	{
		try
		{
			MSocketWrapper->SendTo(Parameters,Result);

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] SUCCESSFULLY SENT [",Result.GetNumberOfSentBytes(),"] BYTES to ADDRESS [",Parameters.GetCANAddress(),"] !")));
		}
		catch(const CSocketException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SEND DATA to ADDRESS [",Parameters.GetCANAddress(),"] !"),E));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SEND DATA to ADDRESS [",Parameters.GetCANAddress(),"] ! EXCEPTION [",E.GetMessage(),"] !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SEND DATA to ADDRESS [",Parameters.GetCANAddress(),"] !"),CUnknownException()));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to SEND DATA to ADDRESS [",Parameters.GetCANAddress(),"] !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCAN::ReceiveFrom(const CSocketCANReceiveFromParameters& Parameters, CSocketCANReceiveFromResult& Result)
	{
		try
		{
			MSocketWrapper->ReceiveFrom(Parameters,Result);

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] SUCCESSFULLY RECEIVED [",Result.GetNumberOfReceivedBytes(),"] BYTES from ADDRESS [",Result.GetCANAddress(),"] !")));
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
	CString CSocketCAN::GetNetworkInterfaceNameForSocket(int32 NetworkInterfaceIndex)
	{
		try
		{
			CString												NetworkInterfaceName=MSocketWrapper->GetNetworkInterfaceName(NetworkInterfaceIndex);

			return(NetworkInterfaceName);
		}
		catch(const CSocketException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to GET NETWORK INTERFACE NAME !"),E));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to GET NETWORK INTERFACE NAME ! EXCEPTION [",E.GetMessage(),"] !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to GET NETWORK INTERFACE NAME !"),CUnknownException()));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to GET NETWORK INTERFACE NAME !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSocketCAN::GetNetworkInterfaceIndexForSocket(const CString& NetworkInterfaceName)
	{
		try
		{
			int32												NetworkInterfaceIndex=MSocketWrapper->GetNetworkInterfaceIndex(NetworkInterfaceName);

			return(NetworkInterfaceIndex);
		}
		catch(const CSocketException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to GET NETWORK INTERFACE INDEX !"),E));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to GET NETWORK INTERFACE INDEX ! EXCEPTION [",E.GetMessage(),"] !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocket(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",GetSocketID(),"] FAILED to GET NETWORK INTERFACE INDEX !"),CUnknownException()));

			throw(CSocketException(CString::Format("SOCKET [",GetSocketID(),"] FAILED to GET NETWORK INTERFACE INDEX !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------