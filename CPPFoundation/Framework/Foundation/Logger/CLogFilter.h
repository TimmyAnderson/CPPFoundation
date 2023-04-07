//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CMap.h>
#include <Framework/Foundation/Collections/CVector.h>
#include "ILogFilter.h"
#include "CLogFilterConfiguration.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CLogFilter final : public ILogFilter
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												CLogFilterConfigurationCollection=CVector<CLogFilterConfigurationItem>;
			using												CLogFilterMap=CMap<Size,CLogFilterConfigurationCollection>;

		private:
			bool												MWriteUnknownLogsLevelDebug;
			bool												MWriteUnknownLogsLevelInformation;
			bool												MWriteUnknownLogsLevelWarning;
			bool												MWriteUnknownLogsLevelError;
			bool												MWriteUnknownLogsLevelCritical;
			CLogFilterMap										MLogFilterMap;

		public:
			virtual bool CanWriteToLog(const CLogCategory& LogCategory, ELogRecordLevel LogLevel) const noexcept override;

		public:
			CLogFilter(const CLogFilterConfiguration& Configuration);
			virtual ~CLogFilter(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------