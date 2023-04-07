//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Objects/CObject.h>
#include "CLogFilterConfigurationItem.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CLogFilterConfiguration final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			using												CLogFilterConfigurationItemCollection=CVector<CLogFilterConfigurationItem>;

		private:
			bool												MWriteUnknownLogsLevelDebug;
			bool												MWriteUnknownLogsLevelInformation;
			bool												MWriteUnknownLogsLevelWarning;
			bool												MWriteUnknownLogsLevelError;
			bool												MWriteUnknownLogsLevelCritical;
			CLogFilterConfigurationItemCollection				MLogFilterConfigurationItemCollection;

		public:
			CLogFilterConfiguration& operator=(const CLogFilterConfiguration& Other);
			CLogFilterConfiguration& operator=(CLogFilterConfiguration&& Other) noexcept;

		public:
			bool GetWriteUnknownLogsLevelDebug(void) const noexcept;
			bool GetWriteUnknownLogsLevelInformation(void) const noexcept;
			bool GetWriteUnknownLogsLevelWarning(void) const noexcept;
			bool GetWriteUnknownLogsLevelError(void) const noexcept;
			bool GetWriteUnknownLogsLevelCritical(void) const noexcept;
			const CLogFilterConfigurationItemCollection& GetLogFilterConfigurationItemCollection(void) const noexcept;

		public:
			CLogFilterConfiguration(bool WriteUnknownLogsLevelDebug, bool WriteUnknownLogsLevelInformation, bool WriteUnknownLogsLevelWarning, bool WriteUnknownLogsLevelError, bool WriteUnknownLogsLevelCritical, const CLogFilterConfigurationItemCollection& LogFilterConfigurationItemCollection);
			CLogFilterConfiguration(bool WriteUnknownLogsLevelDebug, bool WriteUnknownLogsLevelInformation, bool WriteUnknownLogsLevelWarning, bool WriteUnknownLogsLevelError, bool WriteUnknownLogsLevelCritical, CLogFilterConfigurationItemCollection&& LogFilterConfigurationItemCollection);
			CLogFilterConfiguration(const CLogFilterConfiguration& Other);
			CLogFilterConfiguration(CLogFilterConfiguration&& Other) noexcept;
			virtual ~CLogFilterConfiguration(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------