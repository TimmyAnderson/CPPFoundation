//----------------------------------------------------------------------------------------------------------------------
#include "CLogFilterConfiguration.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CLogFilterConfiguration::CLogFilterConfiguration(bool WriteUnknownLogsLevelDebug, bool WriteUnknownLogsLevelInformation, bool WriteUnknownLogsLevelWarning, bool WriteUnknownLogsLevelError, bool WriteUnknownLogsLevelCritical, const CLogFilterConfigurationItemCollection& LogFilterConfigurationItemCollection)
		: MWriteUnknownLogsLevelDebug(WriteUnknownLogsLevelDebug), MWriteUnknownLogsLevelInformation(WriteUnknownLogsLevelInformation), MWriteUnknownLogsLevelWarning(WriteUnknownLogsLevelWarning), MWriteUnknownLogsLevelError(WriteUnknownLogsLevelError), MWriteUnknownLogsLevelCritical(WriteUnknownLogsLevelCritical), MLogFilterConfigurationItemCollection(LogFilterConfigurationItemCollection)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogFilterConfiguration::CLogFilterConfiguration(bool WriteUnknownLogsLevelDebug, bool WriteUnknownLogsLevelInformation, bool WriteUnknownLogsLevelWarning, bool WriteUnknownLogsLevelError, bool WriteUnknownLogsLevelCritical, CLogFilterConfigurationItemCollection&& LogFilterConfigurationItemCollection)
		: MWriteUnknownLogsLevelDebug(WriteUnknownLogsLevelDebug), MWriteUnknownLogsLevelInformation(WriteUnknownLogsLevelInformation), MWriteUnknownLogsLevelWarning(WriteUnknownLogsLevelWarning), MWriteUnknownLogsLevelError(WriteUnknownLogsLevelError), MWriteUnknownLogsLevelCritical(WriteUnknownLogsLevelCritical), MLogFilterConfigurationItemCollection(FUNCTION_MOVE(LogFilterConfigurationItemCollection))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogFilterConfiguration::CLogFilterConfiguration(const CLogFilterConfiguration& Other)
		: MWriteUnknownLogsLevelDebug(Other.MWriteUnknownLogsLevelDebug), MWriteUnknownLogsLevelInformation(Other.MWriteUnknownLogsLevelInformation), MWriteUnknownLogsLevelWarning(Other.MWriteUnknownLogsLevelWarning), MWriteUnknownLogsLevelError(Other.MWriteUnknownLogsLevelError), MWriteUnknownLogsLevelCritical(Other.MWriteUnknownLogsLevelCritical), MLogFilterConfigurationItemCollection(Other.MLogFilterConfigurationItemCollection)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogFilterConfiguration::CLogFilterConfiguration(CLogFilterConfiguration&& Other) noexcept
		: MWriteUnknownLogsLevelDebug(Other.MWriteUnknownLogsLevelDebug), MWriteUnknownLogsLevelInformation(Other.MWriteUnknownLogsLevelInformation), MWriteUnknownLogsLevelWarning(Other.MWriteUnknownLogsLevelWarning), MWriteUnknownLogsLevelError(Other.MWriteUnknownLogsLevelError), MWriteUnknownLogsLevelCritical(Other.MWriteUnknownLogsLevelCritical), MLogFilterConfigurationItemCollection(FUNCTION_MOVE(Other.MLogFilterConfigurationItemCollection))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogFilterConfiguration::~CLogFilterConfiguration(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CLogFilterConfiguration& CLogFilterConfiguration::operator=(const CLogFilterConfiguration& Other)
	{
		MWriteUnknownLogsLevelDebug=Other.MWriteUnknownLogsLevelDebug;
		MWriteUnknownLogsLevelInformation=Other.MWriteUnknownLogsLevelInformation;
		MWriteUnknownLogsLevelWarning=Other.MWriteUnknownLogsLevelWarning;
		MWriteUnknownLogsLevelError=Other.MWriteUnknownLogsLevelError;
		MWriteUnknownLogsLevelCritical=Other.MWriteUnknownLogsLevelCritical;
		MLogFilterConfigurationItemCollection=Other.MLogFilterConfigurationItemCollection;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogFilterConfiguration& CLogFilterConfiguration::operator=(CLogFilterConfiguration&& Other) noexcept
	{
		MWriteUnknownLogsLevelDebug=Other.MWriteUnknownLogsLevelDebug;
		MWriteUnknownLogsLevelInformation=Other.MWriteUnknownLogsLevelInformation;
		MWriteUnknownLogsLevelWarning=Other.MWriteUnknownLogsLevelWarning;
		MWriteUnknownLogsLevelError=Other.MWriteUnknownLogsLevelError;
		MWriteUnknownLogsLevelCritical=Other.MWriteUnknownLogsLevelCritical;
		MLogFilterConfigurationItemCollection=FUNCTION_MOVE(Other.MLogFilterConfigurationItemCollection);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CLogFilterConfiguration::GetWriteUnknownLogsLevelDebug(void) const noexcept
	{
		return(MWriteUnknownLogsLevelDebug);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CLogFilterConfiguration::GetWriteUnknownLogsLevelInformation(void) const noexcept
	{
		return(MWriteUnknownLogsLevelInformation);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CLogFilterConfiguration::GetWriteUnknownLogsLevelWarning(void) const noexcept
	{
		return(MWriteUnknownLogsLevelWarning);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CLogFilterConfiguration::GetWriteUnknownLogsLevelError(void) const noexcept
	{
		return(MWriteUnknownLogsLevelError);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CLogFilterConfiguration::GetWriteUnknownLogsLevelCritical(void) const noexcept
	{
		return(MWriteUnknownLogsLevelCritical);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CLogFilterConfiguration::CLogFilterConfigurationItemCollection& CLogFilterConfiguration::GetLogFilterConfigurationItemCollection(void) const noexcept
	{
		return(MLogFilterConfigurationItemCollection);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------