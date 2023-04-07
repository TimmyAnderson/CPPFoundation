//----------------------------------------------------------------------------------------------------------------------
#include "CTimeout.h"
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
	CTimeout													CTimeout::ZERO_TIMEOUT=CTimeout(0);
	CTimeout													CTimeout::INFINITE_TIMEOUT=CTimeout();
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CTimeout::CTimeout(void)
		: MIsInfinite(true), MTimeoutInMS()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout::CTimeout(const CTimeout& Other)
		: MIsInfinite(Other.MIsInfinite), MTimeoutInMS(Other.MTimeoutInMS)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout::CTimeout(int64 TimeoutInMS)
		: MIsInfinite(false), MTimeoutInMS(TimeoutInMS)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout::~CTimeout(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CTimeout& CTimeout::operator=(const CTimeout& Other)
	{
		MIsInfinite=Other.MIsInfinite;
		MTimeoutInMS=Other.MTimeoutInMS;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CTimeout::operator+(int64 Value)
	{
		if (MIsInfinite==true)
		{
			return(CTimeout(Value));
		}
		else
		{
			return(CTimeout(MTimeoutInMS+Value));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool operator==(const CTimeout& Left, const CTimeout& Right)
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
			if (Left.MTimeoutInMS==Right.MTimeoutInMS)
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
	bool operator!=(const CTimeout& Left, const CTimeout& Right)
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
			if (Left.MTimeoutInMS!=Right.MTimeoutInMS)
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
	bool operator<(const CTimeout& Left, const CTimeout& Right)
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
			if (Left.MTimeoutInMS<Right.MTimeoutInMS)
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
	bool operator<=(const CTimeout& Left, const CTimeout& Right)
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
			if (Left.MTimeoutInMS<=Right.MTimeoutInMS)
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
	bool operator>(const CTimeout& Left, const CTimeout& Right)
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
			if (Left.MTimeoutInMS>Right.MTimeoutInMS)
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
	bool operator>=(const CTimeout& Left, const CTimeout& Right)
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
			if (Left.MTimeoutInMS>=Right.MTimeoutInMS)
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
	const CTimeout& CTimeout::GetZero(void)
	{
		return(ZERO_TIMEOUT);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CTimeout& CTimeout::GetInfinite(void)
	{
		return(INFINITE_TIMEOUT);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CTimeout::Min(const CTimeout& Left, const CTimeout& Right)
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
			if (Left.MTimeoutInMS<=Right.MTimeoutInMS)
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
	CTimeout CTimeout::Max(const CTimeout& Left, const CTimeout& Right)
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
			if (Left.MTimeoutInMS>=Right.MTimeoutInMS)
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
	CTimeout CTimeout::Min(initializer_list<CTimeout> Timeouts)
	{
		CTimeout											MinTimeout=GetInfinite();

		for(const CTimeout& Timeout : Timeouts)
		{
			MinTimeout=Min(MinTimeout,Timeout);
		}

		return(MinTimeout);
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CTimeout::Max(initializer_list<CTimeout> Timeouts)
	{
		CTimeout											MaxTimeout=GetZero();

		for(const CTimeout& Timeout : Timeouts)
		{
			MaxTimeout=Max(MaxTimeout,Timeout);
		}

		return(MaxTimeout);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CTimeout::ToString(void) const
	{
		if (IsInfinite()==true)
		{
			return(CString("TIMEOUT [INFINITE]"));
		}
		else
		{
			return(CString::Format("TIMEOUT [",MTimeoutInMS,"]"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CTimeout::GetTimeoutInMS(void) const noexcept
	{
		return(MTimeoutInMS);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTimeout::IsInfinite(void) const noexcept
	{
		return(MIsInfinite);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTimeout::IsZero(void) const noexcept
	{
		if (MIsInfinite==false && MTimeoutInMS==0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------