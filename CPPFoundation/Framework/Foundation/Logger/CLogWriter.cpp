//----------------------------------------------------------------------------------------------------------------------
#include "CLogWriter.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CLogWriter::CLogWriter(const CLogSource& LogSource, ISPLogFilter LogFilter)
		: MLogSource(LogSource), MLogFilter(LogFilter)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogWriter::~CLogWriter(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CLogSource& CLogWriter::GetLogSource(void) const noexcept
	{
		return(MLogSource);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CLogWriter::CanWriteToLog(const CLogCategory& LogCategory, ELogRecordLevel LogLevel) const noexcept
	{
		try
		{
			if (MLogFilter!=nullptr)
			{
				return(MLogFilter->CanWriteToLog(LogCategory,LogLevel));
			}
			else
			{
				return(true);
			}
		}
		catch(...)
		{
			// EXCEPTIONS are IGNORED.
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CLogWriter::WriteToLog(const CLogCategory& LogCategory, ELogRecordLevel LogLevel, const Char* FunctionName, Size LineNumber, const CLogRecord& LogRecord) noexcept
	{
		try
		{
			InternalWriteToLog(LogCategory,LogLevel,FunctionName,LineNumber,LogRecord);
		}
		catch(...)
		{
			// EXCEPTIONS are IGNORED.
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CLogWriter::WriteToLog(const CLogCategory& LogCategory, ELogRecordLevel LogLevel, const Char* FunctionName, Size LineNumber, const CFunction<CLogRecord(void)>& LogRecordCallback) noexcept
	{
		try
		{
			InternalWriteToLog(LogCategory,LogLevel,FunctionName,LineNumber,LogRecordCallback());
		}
		catch(...)
		{
			// EXCEPTIONS are IGNORED.
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------