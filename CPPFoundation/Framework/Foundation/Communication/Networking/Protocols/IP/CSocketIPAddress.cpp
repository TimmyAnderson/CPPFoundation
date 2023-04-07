//----------------------------------------------------------------------------------------------------------------------
#include "CSocketIPAddress.h"
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Exceptions/CArgumentException.h>
#include <Framework/Foundation/Strings/CIntegerFormatter.h>
#include <Framework/Foundation/Parsing/CParserHelper.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	const Size													CSocketIPAddress::MAXIMUM_NUMBER_OF_IPV6_ADDRESS_DOUBLE_SEPARATOR_SEGMENTS=2;
	const Size													CSocketIPAddress::IPV6_ADDRESS_MAXIMUM_SEGMENT_SIZE=4;
	const Char													CSocketIPAddress::IPV4_ADDRESS_SERPARATOR='.';
	const Char													CSocketIPAddress::IPV6_ADDRESS_SERPARATOR=':';
	const CString												CSocketIPAddress::IPV6_ADDRESS_DOUBLE_SERPARATOR="::";
//----------------------------------------------------------------------------------------------------------------------
	const CSocketIPAddress										CSocketIPAddress::LOCAL_HOST_IPV4_ADDRESS(127,0,0,1);
	const CSocketIPAddress										CSocketIPAddress::LOCAL_HOST_IPV6_ADDRESS({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1});
//----------------------------------------------------------------------------------------------------------------------
	const Size													CSocketIPAddress::IPV4_ADDRESS_LENGTH_IN_BYTES=4;
	const Size													CSocketIPAddress::IPV6_ADDRESS_LENGTH_IN_BYTES=16;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPAddress::CSocketIPAddress(void)
		: MAddressType(ESocketIPAddressType::E_UNDEFINED), MAddress()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPAddress::CSocketIPAddress(uint8 AddressSegment1, uint8 AddressSegment2, uint8 AddressSegment3, uint8 AddressSegment4)
		: MAddressType(ESocketIPAddressType::E_IP_V4), MAddress({AddressSegment1,AddressSegment2,AddressSegment3,AddressSegment4})
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPAddress::CSocketIPAddress(const CByteBuffer& Address)
		: MAddressType(ESocketIPAddressType::E_UNDEFINED), MAddress(Address)
	{
		if (MAddress.GetLength()==IPV4_ADDRESS_LENGTH_IN_BYTES)
		{
			MAddressType=ESocketIPAddressType::E_IP_V4;
		}
		else if (MAddress.GetLength()==IPV6_ADDRESS_LENGTH_IN_BYTES)
		{
			MAddressType=ESocketIPAddressType::E_IP_V6;
		}
		else
		{
			throw(CArgumentException("IP ADDRESS has INVALID SIZE !"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPAddress::CSocketIPAddress(CByteBuffer&& Address)
		: MAddressType(ESocketIPAddressType::E_UNDEFINED), MAddress(FUNCTION_MOVE(Address))
	{
		if (MAddress.GetLength()==IPV4_ADDRESS_LENGTH_IN_BYTES)
		{
			MAddressType=ESocketIPAddressType::E_IP_V4;
		}
		else if (MAddress.GetLength()==IPV6_ADDRESS_LENGTH_IN_BYTES)
		{
			MAddressType=ESocketIPAddressType::E_IP_V6;
		}
		else
		{
			throw(CArgumentException("IP ADDRESS has INVALID SIZE !"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPAddress::CSocketIPAddress(const CSocketIPAddress& Other)
		: MAddressType(Other.MAddressType), MAddress(Other.MAddress)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPAddress::CSocketIPAddress(CSocketIPAddress&& Other) noexcept
		: MAddressType(Other.MAddressType), MAddress(FUNCTION_MOVE(Other.MAddress))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPAddress::~CSocketIPAddress(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPAddress& CSocketIPAddress::operator=(const CSocketIPAddress& Other)
	{
		MAddressType=Other.MAddressType;
		MAddress=Other.MAddress;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPAddress& CSocketIPAddress::operator=(CSocketIPAddress&& Other) noexcept
	{
		MAddressType=Other.MAddressType;
		MAddress=FUNCTION_MOVE(Other.MAddress);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketIPAddress::operator==(const CSocketIPAddress& Other) const
	{
		if (MAddressType!=Other.MAddressType)
		{
			return(false);
		}

		if (MAddress.GetLength()!=Other.MAddress.GetLength())
		{
			return(false);
		}

		for(Size Index=0;Index<MAddress.GetLength();Index++)
		{
			if (MAddress[Index]!=Other.MAddress[Index])
			{
				return(false);
			}
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketIPAddress::operator!=(const CSocketIPAddress& Other) const
	{
		return(!(*this==Other));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPAddress CSocketIPAddress::CreateLocalHostIPv4Address(void)
	{
		return(LOCAL_HOST_IPV4_ADDRESS);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPAddress CSocketIPAddress::CreateLocalHostIPv6Address(void)
	{
		return(LOCAL_HOST_IPV6_ADDRESS);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketIPAddress::ParseIPv4Address(const CString& Value, CSocketIPAddress& Result)
	{
		if (Value.GetLength()==0)
		{
			return(false);
		}

		CByteBuffer												AddressBuffer;
		CUInt8Formatter											Formatter;
		CVector<CString::SSplitIndex>							Segments=Value.SplitToIndexes(IPV4_ADDRESS_SERPARATOR,true);

		if (Segments.GetLength()!=IPV4_ADDRESS_LENGTH_IN_BYTES)
		{
			return(false);
		}

		for(Size SegmentIndex=0;SegmentIndex<Segments.GetLength();SegmentIndex++)
		{
			uint8												AddressSegment;

			if (Formatter.Parse(Value,Segments[SegmentIndex].GetPosition(),Segments[SegmentIndex].GetPosition()+Segments[SegmentIndex].GetLength(),AddressSegment)==true)
			{
				AddressBuffer.Add(AddressSegment);
			}
			else
			{
				return(false);
			}
		}

		Result=CSocketIPAddress(FUNCTION_MOVE(AddressBuffer));

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketIPAddress::ParseIPv6Address(const CString& Value, CSocketIPAddress& Result)
	{
		if (Value.GetLength()==0)
		{
			return(false);
		}

		CByteBuffer												AddressBuffer;
		CUInt16Formatter										Formatter(EIntegerFormat::E_HEXADECIMAL);
		CVector<CString>										Splits=Value.Split(IPV6_ADDRESS_DOUBLE_SERPARATOR,false);
		Size													DoubleSeparatorPosition=0;

		if (Splits.GetLength()>MAXIMUM_NUMBER_OF_IPV6_ADDRESS_DOUBLE_SEPARATOR_SEGMENTS)
		{
			return(false);
		}

		for(Size Index=0;Index<Splits.GetLength();Index++)
		{
			if (Splits[Index].GetLength()>0)
			{
				CVector<CString::SSplitIndex>					Segments=Splits[Index].SplitToIndexes(IPV6_ADDRESS_SERPARATOR,false);

				for(Size SegmentIndex=0;SegmentIndex<Segments.GetLength();SegmentIndex++)
				{
					if (Segments[SegmentIndex].GetLength()>IPV6_ADDRESS_MAXIMUM_SEGMENT_SIZE)
					{
						return(false);
					}

					uint16										AddressSegment;

					if (Formatter.Parse(Splits[Index],Segments[SegmentIndex].GetPosition(),Segments[SegmentIndex].GetPosition()+Segments[SegmentIndex].GetLength(),AddressSegment)==true)
					{
						Size									Length=AddressBuffer.GetLength();

						AddressBuffer.Add(uint8(0),sizeof(uint16));

						CParserHelper::SerializeUInt16(AddressBuffer,AddressSegment,Length,EParserEndianness::E_BIG_ENDIAN);
					}
					else
					{
						return(false);
					}
				}
			}

			if (Index==0)
			{
				DoubleSeparatorPosition=AddressBuffer.GetLength();
			}
		}

		if (AddressBuffer.GetLength()>IPV6_ADDRESS_LENGTH_IN_BYTES)
		{
			return(false);
		}
		else if (AddressBuffer.GetLength()==IPV6_ADDRESS_LENGTH_IN_BYTES && Splits.GetLength()>1)
		{
			return(false);
		}

		if (Splits.GetLength()>1)
		{
			Size												NumberOfZeros=IPV6_ADDRESS_LENGTH_IN_BYTES-AddressBuffer.GetLength();

			for(Size ZeroIndex=0;ZeroIndex<NumberOfZeros;ZeroIndex++)
			{
				AddressBuffer.Insert(0,DoubleSeparatorPosition);
			}
		}

		Result=CSocketIPAddress(FUNCTION_MOVE(AddressBuffer));

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketIPAddress::ToString(void) const
	{
		if (MAddressType==ESocketIPAddressType::E_IP_V4)
		{
			CString												Address;

			Address.SetCapacity(16);

			for(Size Index=0;Index<MAddress.GetLength();Index++)
			{
				if (Index!=0)
				{
					Address+=IPV4_ADDRESS_SERPARATOR;
				}

				Address+=CString(MAddress[Index]);
			}

			return(Address);
		}
		else if (MAddressType==ESocketIPAddressType::E_IP_V6)
		{
			CString												Address;

			Address.SetCapacity(40);

			for(Size Index=0;Index<MAddress.GetLength();Index+=2)
			{
				if (Index!=0)
				{
					Address+=IPV6_ADDRESS_SERPARATOR;
				}

				uint16											Value=CParserHelper::DeserializeUInt16(MAddress,Index,EParserEndianness::E_BIG_ENDIAN);

				Address+=ToHexaDecimalString(Value);
			}

			return(Address);
		}
		else
		{
			return("");
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketIPAddress::Equals(const CSocketAddress& Other) const
	{
		if (Other.IsTypeOf<CSocketIPAddress>()==false)
		{
			return(false);
		}

		const CSocketIPAddress&									TypedOther=Other.DynamicCastReference<CSocketIPAddress>();

		return((*this==TypedOther));
	}
//----------------------------------------------------------------------------------------------------------------------
	ESocketIPAddressType CSocketIPAddress::GetAddressType(void) const noexcept
	{
		return(MAddressType);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CByteBuffer& CSocketIPAddress::GetAddress(void) const noexcept
	{
		return(MAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------