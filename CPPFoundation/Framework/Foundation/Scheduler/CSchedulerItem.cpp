//----------------------------------------------------------------------------------------------------------------------
#include "CSchedulerItem.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerItem::CSchedulerItem(const CSchedulerItemID& ID, const CSchedulerTimeInterval& ValidityInterval, CSPSchedulerTimePeriod TimePeriod)
		: MID(ID), MValidityInterval(ValidityInterval), MTimePeriod(TimePeriod), MNextSchedulerItemExecutionTime()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerItem::~CSchedulerItem(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CSchedulerItem::IsItemWithinValidInterval(const CSchedulerTime& Time) const
	{
		if (MValidityInterval.GetBeginTime().GetHasValue()==true)
		{
			if (Time<MValidityInterval.GetBeginTime().GetValue())
			{
				return(false);
			}
		}

		if (MValidityInterval.GetEndTime().GetHasValue()==true)
		{
			if (Time>MValidityInterval.GetEndTime().GetValue())
			{
				return(false);
			}
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSchedulerItem::HasItemExpired(const CSchedulerTime& Time) const
	{
		if (MValidityInterval.GetEndTime().GetHasValue()==true)
		{
			if (Time>MValidityInterval.GetEndTime().GetValue())
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSchedulerItem::ToString(void) const
	{
		return(CString::Format("SCHEDULER TIME - ID [",MID,"] VALIDITY INTERVAL [",MValidityInterval,"] TIME PERIOD [",MTimePeriod,"] NEXT SCHEDULER ITEM EXECUTION TIME [",MNextSchedulerItemExecutionTime,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSchedulerItemID& CSchedulerItem::GetID(void) const noexcept
	{
		return(MID);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSchedulerTimeInterval& CSchedulerItem::GetValidityInterval(void) const noexcept
	{
		return(MValidityInterval);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPSchedulerTimePeriod CSchedulerItem::GetTimePeriod(void) const noexcept
	{
		return(MTimePeriod);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSchedulerTime& CSchedulerItem::GetNextSchedulerItemExecutionTime(void) const noexcept
	{
		return(MNextSchedulerItemExecutionTime);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CSchedulerItem::HasNextSchedulerTimeExpired(const CSchedulerTime& Time, const CTimeout& MaximumTimeDifference, bool& ExecuteSchedulerItem)
	{
		ExecuteSchedulerItem=false;

		if (IsItemWithinValidInterval(Time)==true)
		{
			if (Time>=MNextSchedulerItemExecutionTime)
			{
				CTimeout										TimeDifference=(Time-MNextSchedulerItemExecutionTime);

				if (TimeDifference<MaximumTimeDifference)
				{
					ExecuteSchedulerItem=true;
				}

				return(true);
			}
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSchedulerItem::ResetExecutionTimeout(const CSchedulerTime& Time)
	{
		MNextSchedulerItemExecutionTime=MTimePeriod->CalculateNextSchedulerTime(Time);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSchedulerItem::RecalculateNextSchedulerTime(const CSchedulerTime& Time)
	{
		if (IsItemWithinValidInterval(Time)==true)
		{
			CSchedulerTime										NewTime=Time;

			NewTime.AddMilliseconds(1);

			MNextSchedulerItemExecutionTime=MTimePeriod->CalculateNextSchedulerTime(NewTime);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CSchedulerItem::GetTimeout(const CSchedulerTime& Time, const CTimeout& MaximumTimeout) const
	{
		if (IsItemWithinValidInterval(Time)==true)
		{
			CTimeout											Timeout=CDateTime::ConvertTicksToTimeout(MNextSchedulerItemExecutionTime.GetDateTime()-Time.GetDateTime());

			if (Timeout>MaximumTimeout)
			{
				Timeout=MaximumTimeout;
			}

			return(Timeout);
		}
		else
		{
			if (HasItemExpired(Time)==true)
			{
				return(CTimeout::GetInfinite());
			}
			else
			{
				if (MValidityInterval.GetBeginTime().GetHasValue()==true)
				{
					CTimeout									Timeout=CDateTime::ConvertTicksToTimeout(MValidityInterval.GetBeginTime().GetValue().GetDateTime()-Time.GetDateTime());

					if (Timeout>MaximumTimeout)
					{
						Timeout=MaximumTimeout;
					}

					return(Timeout);
				}
				else
				{
					throw(CInvalidOperationException("VALIDITY INTERVAL MUST HAVE BEGIN TIME SET !"));
				}
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------