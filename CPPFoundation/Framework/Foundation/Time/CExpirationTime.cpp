//----------------------------------------------------------------------------------------------------------------------
#include "CExpirationTime.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CExpirationTime												CExpirationTime::ZERO_EXPIRATION_TIME=CExpirationTime(0);
	CExpirationTime												CExpirationTime::INFINITE_EXPIRATION_TIME=CExpirationTime();
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CExpirationTime::CExpirationTime(void)
		: MIsInfinite(true), MExpirationTimeInMS(0)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CExpirationTime::CExpirationTime(const CExpirationTime& Other)
		: MIsInfinite(Other.MIsInfinite), MExpirationTimeInMS(Other.MExpirationTimeInMS)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CExpirationTime::CExpirationTime(CSteadyClock::Milliseconds TimeoutInMS, CSteadyClock::Milliseconds CurrentTime)
		: MIsInfinite(false), MExpirationTimeInMS(CurrentTime+TimeoutInMS)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CExpirationTime::CExpirationTime(const CTimeout& Timeout)
		: MIsInfinite(Timeout.IsInfinite()), MExpirationTimeInMS(CSteadyClock::GetCurrentTimeInMilliseconds()+Timeout.GetTimeoutInMS())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CExpirationTime::~CExpirationTime(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CExpirationTime& CExpirationTime::operator=(const CExpirationTime& Other)
	{
		MIsInfinite=Other.MIsInfinite;
		MExpirationTimeInMS=Other.MExpirationTimeInMS;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool operator==(const CExpirationTime& Left, const CExpirationTime& Right)
	{
		if (Left.MIsInfinite==true && Right.MIsInfinite==true)
		{
			return(true);
		}
		else if (Left.MIsInfinite==true)
		{
			return(false);
		}
		else if (Right.MIsInfinite==true)
		{
			return(false);
		}
		else
		{
			if (Left.MExpirationTimeInMS==Right.MExpirationTimeInMS)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool operator!=(const CExpirationTime& Left, const CExpirationTime& Right)
	{
		if (Left.MIsInfinite==true && Right.MIsInfinite==true)
		{
			return(false);
		}
		else if (Left.MIsInfinite==true)
		{
			return(true);
		}
		else if (Right.MIsInfinite==true)
		{
			return(true);
		}
		else
		{
			if (Left.MExpirationTimeInMS!=Right.MExpirationTimeInMS)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool operator<(const CExpirationTime& Left, const CExpirationTime& Right)
	{
		if (Left.MIsInfinite==true && Right.MIsInfinite==true)
		{
			return(false);
		}
		else if (Left.MIsInfinite==true)
		{
			return(false);
		}
		else if (Right.MIsInfinite==true)
		{
			return(true);
		}
		else
		{
			if (Left.MExpirationTimeInMS<Right.MExpirationTimeInMS)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool operator<=(const CExpirationTime& Left, const CExpirationTime& Right)
	{
		if (Left.MIsInfinite==true && Right.MIsInfinite==true)
		{
			return(true);
		}
		else if (Left.MIsInfinite==true)
		{
			return(false);
		}
		else if (Right.MIsInfinite==true)
		{
			return(true);
		}
		else
		{
			if (Left.MExpirationTimeInMS<=Right.MExpirationTimeInMS)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool operator>(const CExpirationTime& Left, const CExpirationTime& Right)
	{
		if (Left.MIsInfinite==true && Right.MIsInfinite==true)
		{
			return(false);
		}
		else if (Left.MIsInfinite==true)
		{
			return(true);
		}
		else if (Right.MIsInfinite==true)
		{
			return(false);
		}
		else
		{
			if (Left.MExpirationTimeInMS>Right.MExpirationTimeInMS)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool operator>=(const CExpirationTime& Left, const CExpirationTime& Right)
	{
		if (Left.MIsInfinite==true && Right.MIsInfinite==true)
		{
			return(true);
		}
		else if (Left.MIsInfinite==true)
		{
			return(true);
		}
		else if (Right.MIsInfinite==true)
		{
			return(false);
		}
		else
		{
			if (Left.MExpirationTimeInMS>=Right.MExpirationTimeInMS)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CExpirationTime& CExpirationTime::GetZero(void)
	{
		return(ZERO_EXPIRATION_TIME);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CExpirationTime& CExpirationTime::GetInfinite(void)
	{
		return(INFINITE_EXPIRATION_TIME);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CExpirationTime CExpirationTime::Min(const CExpirationTime& Left, const CExpirationTime& Right)
	{
		if (Left.MIsInfinite==true)
		{
			return(Right);
		}
		else if (Right.MIsInfinite==true)
		{
			return(Left);
		}
		else
		{
			if (Left.MExpirationTimeInMS<=Right.MExpirationTimeInMS)
			{
				return(Left);
			}
			else
			{
				return(Right);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CExpirationTime CExpirationTime::Max(const CExpirationTime& Left, const CExpirationTime& Right)
	{
		if (Left.MIsInfinite==true)
		{
			return(Left);
		}
		else if (Right.MIsInfinite==true)
		{
			return(Right);
		}
		else
		{
			if (Left.MExpirationTimeInMS>=Right.MExpirationTimeInMS)
			{
				return(Left);
			}
			else
			{
				return(Right);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CExpirationTime CExpirationTime::Min(initializer_list<CExpirationTime> ExpirationTimes)
	{
		CExpirationTime											MinExpirationTime=GetInfinite();

		for(const CExpirationTime& ExpirationTime : ExpirationTimes)
		{
			MinExpirationTime=Min(MinExpirationTime,ExpirationTime);
		}

		return(MinExpirationTime);
	}
//----------------------------------------------------------------------------------------------------------------------
	CExpirationTime CExpirationTime::Max(initializer_list<CExpirationTime> ExpirationTimes)
	{
		CExpirationTime											MaxExpirationTime=GetZero();

		for(const CExpirationTime& ExpirationTime : ExpirationTimes)
		{
			MaxExpirationTime=Max(MaxExpirationTime,ExpirationTime);
		}

		return(MaxExpirationTime);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CExpirationTime::ToString(void) const
	{
		if (IsInfinite()==true)
		{
			return(CString("EXPIRATION TIME [INFINITE]"));
		}
		else
		{
			return(CString::Format("EXPIRATION TIME [",MExpirationTimeInMS,"]"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CExpirationTime::IsInfinite(void) const noexcept
	{
		return(MIsInfinite);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSteadyClock::Milliseconds CExpirationTime::GetExpirationTime(void) const noexcept
	{
		return(MExpirationTimeInMS);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CExpirationTime::Reset(void)
	{
		MIsInfinite=true;
		MExpirationTimeInMS=0;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CExpirationTime::Reset(const CExpirationTime& Other)
	{
		MIsInfinite=Other.MIsInfinite;
		MExpirationTimeInMS=Other.MExpirationTimeInMS;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CExpirationTime::Reset(CSteadyClock::Milliseconds TimeoutInMS)
	{
		MIsInfinite=false;
		MExpirationTimeInMS=(CSteadyClock::GetCurrentTimeInMilliseconds()+TimeoutInMS);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CExpirationTime::Reset(const CTimeout& Timeout)
	{
		MIsInfinite=Timeout.IsInfinite();
		MExpirationTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds()+Timeout.GetTimeoutInMS();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CExpirationTime::AddTimeout(CTimeout Timeout)
	{
		if (MIsInfinite==false && Timeout.IsInfinite()==false)
		{
			MExpirationTimeInMS+=Timeout.GetTimeoutInMS();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CExpirationTime::CalculateTimeout(CSteadyClock::Milliseconds CurrentTimeInMS) const
	{
		if (MIsInfinite==true)
		{
			return(CTimeout::GetInfinite());
		}
		else
		{
			CSteadyClock::Milliseconds							DifferenceInMS=MExpirationTimeInMS-CurrentTimeInMS;

			if (DifferenceInMS>=0)
			{
				CTimeout										Timeout(DifferenceInMS);

				return(Timeout);
			}
			else
			{
				return(CTimeout::GetZero());
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CExpirationTime::HasExpired(CSteadyClock::Milliseconds CurrentTimeInMS) const
	{
		if (MIsInfinite==true)
		{
			return(false);
		}
		else
		{
			if (CurrentTimeInMS>=MExpirationTimeInMS)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------