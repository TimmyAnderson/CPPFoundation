//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Types/CFunction.h>
#include "CLogSource.h"
#include "CLogCategory.h"
#include "CLogRecord.h"
#include "ILogFilter.h"
//----------------------------------------------------------------------------------------------------------------------
// MACRO PREVENTS from EXCEPTION THROWING. EXCEPTIONS are IGNORED.
#define MACRO_WRITE_TO_LOG(LogWriter, LogCategory, LogLevel, FunctionName, LineNumber, LogRecord)\
try\
{\
if (LogWriter.CanWriteToLog(LogCategory,LogLevel)==true)\
{\
	LogWriter.WriteToLog(LogCategory,LogLevel,FunctionName,LineNumber,LogRecord);\
}\
}\
catch(...)\
{\
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CLogWriter : public virtual CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			const CLogSource									MLogSource;
			const ISPLogFilter									MLogFilter;

		protected:
			virtual void InternalWriteToLog(const CLogCategory& LogCategory, ELogRecordLevel LogLevel, const Char* FunctionName, Size LineNumber, const CLogRecord& LogRecord)=0;

		public:
			const CLogSource& GetLogSource(void) const noexcept;

		public:
			bool CanWriteToLog(const CLogCategory& LogCategory, ELogRecordLevel LogLevel) const noexcept;
			void WriteToLog(const CLogCategory& LogCategory, ELogRecordLevel LogLevel, const Char* FunctionName, Size LineNumber, const CLogRecord& LogRecord) noexcept;
			void WriteToLog(const CLogCategory& LogCategory, ELogRecordLevel LogLevel, const Char* FunctionName, Size LineNumber, const CFunction<CLogRecord(void)>& LogRecordCallback) noexcept;

		public:
			CLogWriter(const CLogSource& LogSource, ISPLogFilter LogFilter=ISPLogFilter());
			virtual ~CLogWriter(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------