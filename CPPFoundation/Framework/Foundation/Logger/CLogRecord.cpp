//----------------------------------------------------------------------------------------------------------------------
#include "CLogRecord.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CLogRecord::CLogRecord(const CString& LogMessage)
		: MLogType(ELogRecordType::E_TEXT), MLogTime(CDateTime::GetCurrentLocalTime()), MLogMessage(LogMessage)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogRecord::CLogRecord(CString&& LogMessage)
		: MLogType(ELogRecordType::E_TEXT), MLogTime(CDateTime::GetCurrentLocalTime()), MLogMessage(FUNCTION_MOVE(LogMessage))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogRecord::CLogRecord(const CException& Exception)
		: MLogType(ELogRecordType::E_EXCEPTION), MLogTime(CDateTime::GetCurrentLocalTime()), MLogMessage(PrepareExceptionMessage("",Exception))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogRecord::CLogRecord(const CString& LogMessage, const CException& Exception)
		: MLogType(ELogRecordType::E_EXCEPTION), MLogTime(CDateTime::GetCurrentLocalTime()), MLogMessage(PrepareExceptionMessage(LogMessage,Exception))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogRecord::CLogRecord(CString&& LogMessage, const CException& Exception)
		: MLogType(ELogRecordType::E_EXCEPTION), MLogTime(CDateTime::GetCurrentLocalTime()), MLogMessage(PrepareExceptionMessage(FUNCTION_MOVE(LogMessage),Exception))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogRecord::CLogRecord(const CDateTime& LogTime, const CString& LogMessage)
		: MLogType(ELogRecordType::E_TEXT), MLogTime(LogTime), MLogMessage(LogMessage)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogRecord::CLogRecord(const CDateTime& LogTime, CString&& LogMessage)
		: MLogType(ELogRecordType::E_TEXT), MLogTime(LogTime), MLogMessage(FUNCTION_MOVE(LogMessage))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogRecord::CLogRecord(const CDateTime& LogTime, const CString& LogMessage, const CException& Exception)
		: MLogType(ELogRecordType::E_EXCEPTION), MLogTime(LogTime), MLogMessage(PrepareExceptionMessage(LogMessage,Exception))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogRecord::CLogRecord(const CDateTime& LogTime, CString&& LogMessage, const CException& Exception)
		: MLogType(ELogRecordType::E_EXCEPTION), MLogTime(LogTime), MLogMessage(PrepareExceptionMessage(FUNCTION_MOVE(LogMessage),Exception))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogRecord::CLogRecord(ELogRecordType LogType, const CDateTime& LogTime, const CString& LogMessage)
		: MLogType(LogType), MLogTime(LogTime), MLogMessage(LogMessage)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogRecord::CLogRecord(ELogRecordType LogType, const CDateTime& LogTime, CString&& LogMessage)
		: MLogType(LogType), MLogTime(LogTime), MLogMessage(FUNCTION_MOVE(LogMessage))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogRecord::CLogRecord(const CLogRecord& Other)
		: MLogType(Other.MLogType), MLogTime(Other.MLogTime), MLogMessage(Other.MLogMessage)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogRecord::CLogRecord(CLogRecord&& Other)
		: MLogType(FUNCTION_MOVE(Other.MLogType)), MLogTime(FUNCTION_MOVE(Other.MLogTime)), MLogMessage(FUNCTION_MOVE(Other.MLogMessage))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogRecord::~CLogRecord(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CLogRecord& CLogRecord::operator=(const CLogRecord& Other)
	{
		MLogType=Other.MLogType;
		MLogTime=Other.MLogTime;
		MLogMessage=Other.MLogMessage;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogRecord& CLogRecord::operator=(CLogRecord&& Other)
	{
		MLogType=FUNCTION_MOVE(Other.MLogType);
		MLogTime=FUNCTION_MOVE(Other.MLogTime);
		MLogMessage=FUNCTION_MOVE(Other.MLogMessage);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CLogRecord::PrepareExceptionMessage(const CString& LogMessage, const CException& Exception)
	{
		if (LogMessage.IsEmpty()==true)
		{
			CString												Message=CString::Format("EXCEPTION [",Exception.GetMessage(),"] !");

			return(Message);
		}
		else
		{
			CString												Message=CString::Format("MESSAGE [",LogMessage,"] EXCEPTION [",Exception.GetMessage(),"] !");

			return(Message);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CLogRecord::PrepareExceptionMessage(CString&& LogMessage, const CException& Exception)
	{
		if (LogMessage.IsEmpty()==true)
		{
			CString												Message=CString::Format("EXCEPTION [",Exception.GetMessage(),"] !");

			return(Message);
		}
		else
		{
			CString												Message=CString::Format("MESSAGE [",FUNCTION_MOVE(LogMessage),"] EXCEPTION [",Exception.GetMessage(),"] !");

			return(Message);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	ELogRecordType CLogRecord::GetLogType(void) const noexcept
	{
		return(MLogType);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CDateTime& CLogRecord::GetLogTime(void) const noexcept
	{
		return(MLogTime);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CString& CLogRecord::GetLogMessage(void) const noexcept
	{
		return(MLogMessage);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------