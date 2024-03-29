//----------------------------------------------------------------------------------------------------------------------
#include "CID.h"
#include <Framework/Foundation/Types/CPrimitiveType.h>
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
	const Size													CID::MAXIMUM_VALUE=999999999L;
	const Size													CID::PAD_SIZE(CString(MAXIMUM_VALUE).GetLength());
//----------------------------------------------------------------------------------------------------------------------
	CMutex														CID::MMutex;
	CRandom<uint64>												CID::MRandom(CPrimitiveType<uint64>::Min(),MAXIMUM_VALUE);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CID::CID(const CString& ID)
		: MID(new CString(ID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CID::CID(CString&& ID)
		: MID(new CString(FUNCTION_MOVE(ID)))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CID::CID(CCSPString ID)
		: MID(ID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CID::CID(const CID& Other)
		: MID(Other.MID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CID::CID(CID&& Other) noexcept
		: MID(FUNCTION_MOVE(Other.MID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CID::~CID(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CID& CID::operator=(const CID& Other)
	{
		MID=Other.MID;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CID& CID::operator=(CID&& Other) noexcept
	{
		MID=FUNCTION_MOVE(Other.MID);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool operator==(const CID& Left, const CID& Right)
	{
		if (Left.MID->operator==(*(Right.MID))==true)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool operator!=(const CID& Left, const CID& Right)
	{
		if (Left.MID->operator!=(*(Right.MID))==true)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool operator<(const CID& Left, const CID& Right)
	{
		if (Left.MID->operator<(*(Right.MID))==true)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool operator<=(const CID& Left, const CID& Right)
	{
		if (Left.MID->operator<=(*(Right.MID))==true)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool operator>(const CID& Left, const CID& Right)
	{
		if (Left.MID->operator>(*(Right.MID))==true)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool operator>=(const CID& Left, const CID& Right)
	{
		if (Left.MID->operator>=(*(Right.MID))==true)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CID CID::CreateID(void)
	{
		CLock											Lock(MMutex);
		{
			CString										Value(MRandom.GetRandomValue(),EIntegerFormat::E_NONE,PAD_SIZE,true);

			return(CID(Value));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CID CID::CreateEmptyID(void)
	{
		return(CID(CString()));
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CID::CreateEmptyIDAsString(void)
	{
		return(CString());
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CID::ToString(void) const
	{
		return(GetID());
	}
//----------------------------------------------------------------------------------------------------------------------
	CID::CCSPString CID::GetRawID(void) const noexcept
	{
		return(MID);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CString& CID::GetID(void) const noexcept
	{
		return(*MID);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CID::IsEmpty(void) const noexcept
	{
		return(MID->IsEmpty());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------