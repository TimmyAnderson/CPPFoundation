//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Exceptions/CException.h>
#include <Framework/Foundation/Exceptions/CUnknownException.h>
#include <Framework/Foundation/Time/CDateTime.h>
#include <Framework/Platform/Global/Macros.h>
#include "CLogSource.h"
#include "CLogCategory.h"
#include "ELogRecordType.h"
#include "ELogRecordLevel.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CLogRecord final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			ELogRecordType										MLogType;
			CDateTime											MLogTime;
			CString												MLogMessage;

		public:
			CLogRecord& operator=(const CLogRecord& Other);
			CLogRecord& operator=(CLogRecord&& Other);

		private:
			static CString PrepareExceptionMessage(const CString& LogMessage, const CException& Exception);
			static CString PrepareExceptionMessage(CString&& LogMessage, const CException& Exception);

		public:
			ELogRecordType GetLogType(void) const noexcept;
			const CDateTime& GetLogTime(void) const noexcept;
			const CString& GetLogMessage(void) const noexcept;

		public:
			CLogRecord(const CString& LogMessage);
			CLogRecord(CString&& LogMessage);
			CLogRecord(const CException& Exception);
			CLogRecord(const CString& LogMessage, const CException& Exception);
			CLogRecord(CString&& LogMessage, const CException& Exception);
			CLogRecord(const CDateTime& LogTime, const CString& LogMessage);
			CLogRecord(const CDateTime& LogTime, CString&& LogMessage);
			CLogRecord(const CDateTime& LogTime, const CString& LogMessage, const CException& Exception);
			CLogRecord(const CDateTime& LogTime, CString&& LogMessage, const CException& Exception);
			CLogRecord(ELogRecordType LogType, const CDateTime& LogTime, const CString& LogMessage);
			CLogRecord(ELogRecordType LogType, const CDateTime& LogTime, CString&& LogMessage);
			CLogRecord(const CLogRecord& Other);
			CLogRecord(CLogRecord&& Other);
			virtual ~CLogRecord(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------