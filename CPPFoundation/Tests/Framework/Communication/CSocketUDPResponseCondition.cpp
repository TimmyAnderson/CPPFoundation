//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPResponseCondition.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPResponseCondition::CSocketUDPResponseCondition(bool UseSocketID, const CSocketID& SocketID, bool UseAddress, const CSocketUDPAddress& Address, const CConditionDataCollection& ConditionDataCollection, bool UseReceivedSocketAddress, CSPSocketUDPResponse Response)
		: MUseSocketID(UseSocketID), MSocketID(SocketID), MUseAddress(UseAddress), MAddress(Address), MConditionDataCollection(ConditionDataCollection), MNumberOfBytesInConditionDataCollection(CalculateNumberOfBytes(ConditionDataCollection)), MUseReceivedSocketAddress(UseReceivedSocketAddress), MResponse(Response)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPResponseCondition::~CSocketUDPResponseCondition(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketUDPResponseCondition::CalculateNumberOfBytes(const CSocketUDPResponseCondition::CConditionDataCollection& ConditionDataCollection) noexcept
	{
		Size													NumberOfBytes=0;

		for(const CSocketUDPResponseConditionData& ConditionData : ConditionDataCollection)
		{
			NumberOfBytes+=ConditionData.GetBytesToCompare().GetLength();
		}

		return(NumberOfBytes);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketUDPResponseCondition::GetUseSocketID(void) const noexcept
	{
		return(MUseSocketID);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketID& CSocketUDPResponseCondition::GetSocketID(void) const noexcept
	{
		return(MSocketID);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketUDPResponseCondition::GetUseAddress(void) const noexcept
	{
		return(MUseAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketUDPAddress& CSocketUDPResponseCondition::GetAddress(void) const noexcept
	{
		return(MAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketUDPResponseCondition::CConditionDataCollection& CSocketUDPResponseCondition::GetConditionDataCollection(void) const noexcept
	{
		return(MConditionDataCollection);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketUDPResponseCondition::GetUseReceivedSocketAddress(void) const noexcept
	{
		return(MUseReceivedSocketAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPSocketUDPResponse CSocketUDPResponseCondition::GetResponse(void) const noexcept
	{
		return(MResponse);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketUDPResponseCondition::CheckCondition(const CSocketID& SocketID, const CSocketUDPAddress Address, CCSPByteBuffer Data) const noexcept
	{
		if (MUseSocketID==true)
		{
			if (MSocketID!=SocketID)
			{
				return(false);
			}
		}

		if (MUseAddress==true)
		{
			if (MAddress!=Address)
			{
				return(false);
			}
		}

		if (Data->GetLength()>MNumberOfBytesInConditionDataCollection)
		{
			return(false);
		}

		Size													RequestDataIndex=0;

		for(const CSocketUDPResponseConditionData& ConditionData : MConditionDataCollection)
		{
			Size												ConditionDataSize=ConditionData.GetBytesToCompare().GetLength();
			ESocketUDPResponseConditionDataComparisonMode		ComparisonMode=ConditionData.GetComparisonMode();

			if (ComparisonMode==ESocketUDPResponseConditionDataComparisonMode::E_DATA)
			{
				if ((RequestDataIndex+ConditionDataSize)>Data->GetLength())
				{
					return(false);
				}

				for(Size Index=0;Index<ConditionDataSize;Index++,RequestDataIndex++)
				{
					uint8										DataByte=(*Data)[RequestDataIndex];
					uint8										CompareToDataByte=ConditionData.GetBytesToCompare()[Index];

					if (DataByte!=CompareToDataByte)
					{
						return(false);
					}
				}
			}
			else if (ComparisonMode==ESocketUDPResponseConditionDataComparisonMode::E_ANY_VALUE)
			{
				if ((RequestDataIndex+ConditionDataSize)>Data->GetLength())
				{
					return(false);
				}

				RequestDataIndex+=ConditionDataSize;
			}
			else if (ComparisonMode==ESocketUDPResponseConditionDataComparisonMode::E_ANY_VALUE_INCLUDING_NO_DATA)
			{
				// EMPTY.
			}
			else
			{
				return(false);
			}
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------