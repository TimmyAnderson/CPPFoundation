//----------------------------------------------------------------------------------------------------------------------
#include "CLogFilter.h"
#include <Framework/Foundation/Exceptions/CArgumentException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CLogFilter::CLogFilter(const CLogFilterConfiguration& Configuration)
		: MWriteUnknownLogsLevelDebug(Configuration.GetWriteUnknownLogsLevelDebug()), MWriteUnknownLogsLevelInformation(Configuration.GetWriteUnknownLogsLevelInformation()), MWriteUnknownLogsLevelWarning(Configuration.GetWriteUnknownLogsLevelWarning()), MWriteUnknownLogsLevelError(Configuration.GetWriteUnknownLogsLevelError()), MWriteUnknownLogsLevelCritical(Configuration.GetWriteUnknownLogsLevelCritical()), MLogFilterMap()
	{
		Size													Length=Configuration.GetLogFilterConfigurationItemCollection().GetLength();

		if (Length>0)
		{
			for(Size Index1=0;Index1<(Length-1);Index1++)
			{
				for(Size Index2=Index1+1;Index2<Length;Index2++)
				{
					if (Configuration.GetLogFilterConfigurationItemCollection()[Index1].GetLogCategory()==Configuration.GetLogFilterConfigurationItemCollection()[Index2].GetLogCategory())
					{
						throw(CArgumentException("CONFIGURATION contains DUPLICATE ITEMS !"));
					}
				}
			}

			for(const CLogFilterConfigurationItem& ConfigurationItem : Configuration.GetLogFilterConfigurationItemCollection())
			{
				Size											LogCategoryHash=ConfigurationItem.GetLogCategory().GetHash();

				if (MLogFilterMap.Contains(LogCategoryHash)==true)
				{
					CLogFilterConfigurationCollection			LogFilterConfigurationCollection=MLogFilterMap[LogCategoryHash];

					LogFilterConfigurationCollection.Add(ConfigurationItem);
				}
				else
				{
					CLogFilterConfigurationCollection			LogFilterConfigurationCollection;

					LogFilterConfigurationCollection.Add(ConfigurationItem);

					MLogFilterMap.Add(LogCategoryHash,LogFilterConfigurationCollection);
				}
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogFilter::~CLogFilter(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CLogFilter::CanWriteToLog(const CLogCategory& LogCategory, ELogRecordLevel LogLevel) const noexcept
	{
		try
		{
			Size												LogCategoryHash=LogCategory.GetHash();
			CLogFilterMap::CMapIteratorConst					Iterator=MLogFilterMap.Find(LogCategoryHash);

			if (Iterator!=MLogFilterMap.End())
			{
				for(const CLogFilterConfigurationItem& ConfigurationItem : Iterator->GetSecond())
				{
					if (ConfigurationItem.GetLogCategory()==LogCategory)
					{
						switch(LogLevel)
						{
							case ELogRecordLevel::E_NONE:
							{
								return(false);
							}

							case ELogRecordLevel::E_DEBUG:
							{
								return(ConfigurationItem.GetWriteToLogDebug());
							}

							case ELogRecordLevel::E_INFORMATION:
							{
								return(ConfigurationItem.GetWriteToLogInformation());
							}

							case ELogRecordLevel::E_WARNING:
							{
								return(ConfigurationItem.GetWriteToLogWarning());
							}

							case ELogRecordLevel::E_ERROR:
							{
								return(ConfigurationItem.GetWriteToLogError());
							}

							case ELogRecordLevel::E_CRITICAL:
							{
								return(ConfigurationItem.GetWriteToLogCritical());
							}

							default:
							{
								return(false);
							}
						}
					}
				}
			}

			switch(LogLevel)
			{
				case ELogRecordLevel::E_NONE:
				{
					return(false);
				}

				case ELogRecordLevel::E_DEBUG:
				{
					return(MWriteUnknownLogsLevelDebug);
				}

				case ELogRecordLevel::E_INFORMATION:
				{
					return(MWriteUnknownLogsLevelInformation);
				}

				case ELogRecordLevel::E_WARNING:
				{
					return(MWriteUnknownLogsLevelWarning);
				}

				case ELogRecordLevel::E_ERROR:
				{
					return(MWriteUnknownLogsLevelError);
				}

				case ELogRecordLevel::E_CRITICAL:
				{
					return(MWriteUnknownLogsLevelCritical);
				}

				default:
				{
					return(false);
				}
			}
		}
		catch(...)
		{
			// EXCEPTIONS are IGNORED.
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------