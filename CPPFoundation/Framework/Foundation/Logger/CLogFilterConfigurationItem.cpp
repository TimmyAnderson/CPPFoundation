//----------------------------------------------------------------------------------------------------------------------
#include "CLogFilterConfigurationItem.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CLogFilterConfigurationItem::CLogFilterConfigurationItem(const CLogCategory& LogCategory, bool WriteToLogDebug, bool WriteToLogInformation, bool WriteToLogWarning, bool WriteToLogError, bool WriteToLogCritical)
		: MLogCategory(LogCategory), MWriteToLogDebug(WriteToLogDebug), MWriteToLogInformation(WriteToLogInformation), MWriteToLogWarning(WriteToLogWarning), MWriteToLogError(WriteToLogError), MWriteToLogCritical(WriteToLogCritical)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogFilterConfigurationItem::CLogFilterConfigurationItem(CLogCategory&& LogCategory, bool WriteToLogDebug, bool WriteToLogInformation, bool WriteToLogWarning, bool WriteToLogError, bool WriteToLogCritical)
		: MLogCategory(FUNCTION_MOVE(LogCategory)), MWriteToLogDebug(WriteToLogDebug), MWriteToLogInformation(WriteToLogInformation), MWriteToLogWarning(WriteToLogWarning), MWriteToLogError(WriteToLogError), MWriteToLogCritical(WriteToLogCritical)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogFilterConfigurationItem::CLogFilterConfigurationItem(const CLogFilterConfigurationItem& Other)
		: MLogCategory(Other.MLogCategory), MWriteToLogDebug(Other.MWriteToLogDebug), MWriteToLogInformation(Other.MWriteToLogInformation), MWriteToLogWarning(Other.MWriteToLogWarning), MWriteToLogError(Other.MWriteToLogError), MWriteToLogCritical(Other.MWriteToLogCritical)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogFilterConfigurationItem::CLogFilterConfigurationItem(CLogFilterConfigurationItem&& Other)
		: MLogCategory(FUNCTION_MOVE(Other.MLogCategory)), MWriteToLogDebug(Other.MWriteToLogDebug), MWriteToLogInformation(Other.MWriteToLogInformation), MWriteToLogWarning(Other.MWriteToLogWarning), MWriteToLogError(Other.MWriteToLogError), MWriteToLogCritical(Other.MWriteToLogCritical)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogFilterConfigurationItem::~CLogFilterConfigurationItem(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CLogFilterConfigurationItem& CLogFilterConfigurationItem::operator=(const CLogFilterConfigurationItem& Other)
	{
		MLogCategory=Other.MLogCategory;
		MWriteToLogDebug=Other.MWriteToLogDebug;
		MWriteToLogInformation=Other.MWriteToLogInformation;
		MWriteToLogWarning=Other.MWriteToLogWarning;
		MWriteToLogError=Other.MWriteToLogError;
		MWriteToLogCritical=Other.MWriteToLogCritical;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogFilterConfigurationItem& CLogFilterConfigurationItem::operator=(CLogFilterConfigurationItem&& Other)
	{
		MLogCategory=FUNCTION_MOVE(Other.MLogCategory);
		MWriteToLogDebug=Other.MWriteToLogDebug;
		MWriteToLogInformation=Other.MWriteToLogInformation;
		MWriteToLogWarning=Other.MWriteToLogWarning;
		MWriteToLogError=Other.MWriteToLogError;
		MWriteToLogCritical=Other.MWriteToLogCritical;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CLogCategory& CLogFilterConfigurationItem::GetLogCategory(void) const noexcept
	{
		return(MLogCategory);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CLogFilterConfigurationItem::GetWriteToLogDebug(void) const noexcept
	{
		return(MWriteToLogDebug);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CLogFilterConfigurationItem::GetWriteToLogInformation(void) const noexcept
	{
		return(MWriteToLogInformation);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CLogFilterConfigurationItem::GetWriteToLogWarning(void) const noexcept
	{
		return(MWriteToLogWarning);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CLogFilterConfigurationItem::GetWriteToLogError(void) const noexcept
	{
		return(MWriteToLogError);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CLogFilterConfigurationItem::GetWriteToLogCritical(void) const noexcept
	{
		return(MWriteToLogCritical);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------