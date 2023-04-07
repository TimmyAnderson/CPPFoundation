//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include "CLogCategory.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CLogFilterConfigurationItem final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CLogCategory										MLogCategory;
			bool												MWriteToLogDebug;
			bool												MWriteToLogInformation;
			bool												MWriteToLogWarning;
			bool												MWriteToLogError;
			bool												MWriteToLogCritical;

		public:
			CLogFilterConfigurationItem& operator=(const CLogFilterConfigurationItem& Other);
			CLogFilterConfigurationItem& operator=(CLogFilterConfigurationItem&& Other);

		public:
			const CLogCategory& GetLogCategory(void) const noexcept;
			bool GetWriteToLogDebug(void) const noexcept;
			bool GetWriteToLogInformation(void) const noexcept;
			bool GetWriteToLogWarning(void) const noexcept;
			bool GetWriteToLogError(void) const noexcept;
			bool GetWriteToLogCritical(void) const noexcept;

		public:
			CLogFilterConfigurationItem(const CLogCategory& LogCategory, bool WriteToLogDebug, bool WriteToLogInformation, bool WriteToLogWarning, bool WriteToLogError, bool WriteToLogCritical);
			CLogFilterConfigurationItem(CLogCategory&& LogCategory, bool WriteToLogDebug, bool WriteToLogInformation, bool WriteToLogWarning, bool WriteToLogError, bool WriteToLogCritical);
			CLogFilterConfigurationItem(const CLogFilterConfigurationItem& Other);
			CLogFilterConfigurationItem(CLogFilterConfigurationItem&& Other);
			virtual ~CLogFilterConfigurationItem(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------