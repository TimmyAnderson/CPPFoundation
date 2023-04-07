//----------------------------------------------------------------------------------------------------------------------
#include <type_traits>
#include <Framework/Foundation/Types/CPrimitiveType.h>
#include <Framework/Platform/Global/Macros.h>
#include "CParserHelper.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace std;
	using namespace CPPFoundation::Platform;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const Size													CParserHelper::NIBBLE_SIZE_IN_BITS=4;
	const Size													CParserHelper::NIBBLE_MASK=0x0F;
	const Size													CParserHelper::BCD_MIN_VALUE=0;
	const Size													CParserHelper::BCD_MAX_VALUE=99;
	const Size													CParserHelper::BCD_MIN_NUMERIC_VALUE=0;
	const Size													CParserHelper::BCD_MAX_NUMERIC_VALUE=9;
	const Size													CParserHelper::BCD_TO_DECADIC_VALUE_CONVERSION=10;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const Size													CParserHelper::BITS_PER_BYTE=8;
	const Size													CParserHelper::BYTE_MAGNITUDE=256;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::CheckLength(Size BufferLength, Size Index, Size Length)
	{
		if (BufferLength<(Index+Length))
		{
			throw(CParserException("BUFFER is too SHORT !"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::CheckLength(const CByteBuffer& Buffer, Size Index, Size Length)
	{
		CheckLength(Buffer.GetLength(),Index,Length);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::GetBitsCheckArguments(Size StartPositionInBits, Size LengthInBits, Size BitLength)
	{
		if (StartPositionInBits>=BitLength)
		{
			throw(CParserException(CString::Format("VALUE StartPositionInBits [",StartPositionInBits,"] is OUTSIDE RANGE <0,",(BitLength-1),"> !")));
		}

		if (LengthInBits==0 || LengthInBits>BitLength)
		{
			throw(CParserException(CString::Format("VALUE LengthInBits [",LengthInBits,"] is OUTSIDE RANGE <1,",BitLength,"> !")));
		}

		if ((StartPositionInBits+LengthInBits)>BitLength)
		{
			throw(CParserException(CString::Format("EXPRESSION (StartPositionInBits+LengthInBits) [",StartPositionInBits,",",LengthInBits,"] is LONGER than MAXIMUM allowed LENGTH [",BitLength,"] !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeInt8(uint8* Buffer, Size BufferLength, int8 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<int8>(Buffer,BufferLength,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeUInt8(uint8* Buffer, Size BufferLength, uint8 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<uint8>(Buffer,BufferLength,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeInt16(uint8* Buffer, Size BufferLength, int16 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<int16>(Buffer,BufferLength,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeUInt16(uint8* Buffer, Size BufferLength, uint16 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<uint16>(Buffer,BufferLength,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeInt32(uint8* Buffer, Size BufferLength, int32 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<int32>(Buffer,BufferLength,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeUInt32(uint8* Buffer, Size BufferLength, uint32 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<uint32>(Buffer,BufferLength,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeInt64(uint8* Buffer, Size BufferLength, int64 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<int64>(Buffer,BufferLength,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeUInt64(uint8* Buffer, Size BufferLength, uint64 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<uint64>(Buffer,BufferLength,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeFloat32(uint8* Buffer, Size BufferLength, float32 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<float32>(Buffer,BufferLength,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeFloat64(uint8* Buffer, Size BufferLength, float64 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<float64>(Buffer,BufferLength,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeFloat80(uint8* Buffer, Size BufferLength, float80 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<float80>(Buffer,BufferLength,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeSize(uint8* Buffer, Size BufferLength, Size Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<Size>(Buffer,BufferLength,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeInt8(CByteBuffer& Buffer, int8 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<int8>(Buffer,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeUInt8(CByteBuffer& Buffer, uint8 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<uint8>(Buffer,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeInt16(CByteBuffer& Buffer, int16 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<int16>(Buffer,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeUInt16(CByteBuffer& Buffer, uint16 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<uint16>(Buffer,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeInt32(CByteBuffer& Buffer, int32 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<int32>(Buffer,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeUInt32(CByteBuffer& Buffer, uint32 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<uint32>(Buffer,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeInt64(CByteBuffer& Buffer, int64 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<int64>(Buffer,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeUInt64(CByteBuffer& Buffer, uint64 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<uint64>(Buffer,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeFloat32(CByteBuffer& Buffer, float32 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<float32>(Buffer,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeFloat64(CByteBuffer& Buffer, float64 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<float64>(Buffer,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeFloat80(CByteBuffer& Buffer, float80 Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<float80>(Buffer,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::SerializeSize(CByteBuffer& Buffer, Size Value, Size Index, EParserEndianness Endianness)
	{
		InternalSerialize<Size>(Buffer,Value,Index,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int8 CParserHelper::DeserializeInt8(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<int8>(Buffer,BufferLength,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8 CParserHelper::DeserializeUInt8(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<uint8>(Buffer,BufferLength,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	int16 CParserHelper::DeserializeInt16(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<int16>(Buffer,BufferLength,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint16 CParserHelper::DeserializeUInt16(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<uint16>(Buffer,BufferLength,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CParserHelper::DeserializeInt32(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<int32>(Buffer,BufferLength,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint32 CParserHelper::DeserializeUInt32(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<uint32>(Buffer,BufferLength,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CParserHelper::DeserializeInt64(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<int64>(Buffer,BufferLength,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint64 CParserHelper::DeserializeUInt64(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<uint64>(Buffer,BufferLength,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	float32 CParserHelper::DeserializeFloat32(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<float32>(Buffer,BufferLength,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	float64 CParserHelper::DeserializeFloat64(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<float64>(Buffer,BufferLength,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	float80 CParserHelper::DeserializeFloat80(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<float80>(Buffer,BufferLength,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CParserHelper::DeserializeSize(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<Size>(Buffer,BufferLength,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int8 CParserHelper::DeserializeInt8(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<int8>(Buffer,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8 CParserHelper::DeserializeUInt8(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<uint8>(Buffer,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	int16 CParserHelper::DeserializeInt16(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<int16>(Buffer,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint16 CParserHelper::DeserializeUInt16(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<uint16>(Buffer,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CParserHelper::DeserializeInt32(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<int32>(Buffer,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint32 CParserHelper::DeserializeUInt32(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<uint32>(Buffer,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CParserHelper::DeserializeInt64(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<int64>(Buffer,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint64 CParserHelper::DeserializeUInt64(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<uint64>(Buffer,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	float32 CParserHelper::DeserializeFloat32(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<float32>(Buffer,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	float64 CParserHelper::DeserializeFloat64(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<float64>(Buffer,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	float80 CParserHelper::DeserializeFloat80(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<float80>(Buffer,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CParserHelper::DeserializeSize(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness)
	{
		return(InternalDeserialize<Size>(Buffer,Index,Endianness));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CParserHelper::HasBitInt8(int8 Value, Size PositionInBits)
	{
		if (GetBitsInt8(Value,PositionInBits,1)!=0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CParserHelper::HasBitUInt8(uint8 Value, Size PositionInBits)
	{
		if (GetBitsUInt8(Value,PositionInBits,1)!=0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CParserHelper::HasBitInt16(int16 Value, Size PositionInBits)
	{
		if (GetBitsInt16(Value,PositionInBits,1)!=0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CParserHelper::HasBitUInt16(uint16 Value, Size PositionInBits)
	{
		if (GetBitsUInt16(Value,PositionInBits,1)!=0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CParserHelper::HasBitInt32(int32 Value, Size PositionInBits)
	{
		if (GetBitsInt32(Value,PositionInBits,1)!=0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CParserHelper::HasBitUInt32(uint32 Value, Size PositionInBits)
	{
		if (GetBitsUInt32(Value,PositionInBits,1)!=0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CParserHelper::HasBitInt64(int64 Value, Size PositionInBits)
	{
		if (GetBitsInt64(Value,PositionInBits,1)!=0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CParserHelper::HasBitUInt64(uint64 Value, Size PositionInBits)
	{
		if (GetBitsUInt64(Value,PositionInBits,1)!=0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CParserHelper::HasBitSize(Size Value, Size PositionInBits)
	{
		if (GetBitsSize(Value,PositionInBits,1)!=0)
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
	int8 CParserHelper::GetBitInt8(int8 Value, Size PositionInBits)
	{
		return(GetBitsInt8(Value,PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8 CParserHelper::GetBitUInt8(uint8 Value, Size PositionInBits)
	{
		return(GetBitsUInt8(Value,PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	int16 CParserHelper::GetBitInt16(int16 Value, Size PositionInBits)
	{
		return(GetBitsInt16(Value,PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint16 CParserHelper::GetBitUInt16(uint16 Value, Size PositionInBits)
	{
		return(GetBitsUInt16(Value,PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CParserHelper::GetBitInt32(int32 Value, Size PositionInBits)
	{
		return(GetBitsInt32(Value,PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint32 CParserHelper::GetBitUInt32(uint32 Value, Size PositionInBits)
	{
		return(GetBitsUInt32(Value,PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CParserHelper::GetBitInt64(int64 Value, Size PositionInBits)
	{
		return(GetBitsInt64(Value,PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint64 CParserHelper::GetBitUInt64(uint64 Value, Size PositionInBits)
	{
		return(GetBitsUInt64(Value,PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CParserHelper::GetBitSize(Size Value, Size PositionInBits)
	{
		return(GetBitsSize(Value,PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int8 CParserHelper::GetBitsInt8(int8 Value, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalGetBits(Value,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8 CParserHelper::GetBitsUInt8(uint8 Value, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalGetBits(Value,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	int16 CParserHelper::GetBitsInt16(int16 Value, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalGetBits(Value,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint16 CParserHelper::GetBitsUInt16(uint16 Value, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalGetBits(Value,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CParserHelper::GetBitsInt32(int32 Value, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalGetBits(Value,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint32 CParserHelper::GetBitsUInt32(uint32 Value, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalGetBits(Value,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CParserHelper::GetBitsInt64(int64 Value, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalGetBits(Value,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint64 CParserHelper::GetBitsUInt64(uint64 Value, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalGetBits(Value,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CParserHelper::GetBitsSize(Size Value, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalGetBits(Value,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int8 CParserHelper::OrBitInt8(int8 Value, bool OrValue, Size PositionInBits)
	{
		return(OrBitsInt8(Value,static_cast<int8>((OrValue==true) ? 1 : 0),PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8 CParserHelper::OrBitUInt8(uint8 Value, bool OrValue, Size PositionInBits)
	{
		return(OrBitsUInt8(Value,static_cast<uint8>((OrValue==true) ? 1 : 0),PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	int16 CParserHelper::OrBitInt16(int16 Value, bool OrValue, Size PositionInBits)
	{
		return(OrBitsInt16(Value,static_cast<int16>((OrValue==true) ? 1 : 0),PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint16 CParserHelper::OrBitUInt16(uint16 Value, bool OrValue, Size PositionInBits)
	{
		return(OrBitsUInt16(Value,static_cast<uint16>((OrValue==true) ? 1 : 0),PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CParserHelper::OrBitInt32(int32 Value, bool OrValue, Size PositionInBits)
	{
		return(OrBitsInt32(Value,static_cast<int32>((OrValue==true) ? 1 : 0),PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint32 CParserHelper::OrBitUInt32(uint32 Value, bool OrValue, Size PositionInBits)
	{
		return(OrBitsUInt32(Value,static_cast<uint32>((OrValue==true) ? 1 : 0),PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CParserHelper::OrBitInt64(int64 Value, bool OrValue, Size PositionInBits)
	{
		return(OrBitsInt64(Value,static_cast<int64>((OrValue==true) ? 1 : 0),PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint64 CParserHelper::OrBitUInt64(uint64 Value, bool OrValue, Size PositionInBits)
	{
		return(OrBitsUInt64(Value,static_cast<uint64>((OrValue==true) ? 1 : 0),PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CParserHelper::OrBitSize(Size Value, bool OrValue, Size PositionInBits)
	{
		return(OrBitsSize(Value,static_cast<Size>((OrValue==true) ? 1 : 0),PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int8 CParserHelper::OrBitsInt8(int8 Value, int8 OrValue, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalOrBits(Value,OrValue,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8 CParserHelper::OrBitsUInt8(uint8 Value, uint8 OrValue, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalOrBits(Value,OrValue,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	int16 CParserHelper::OrBitsInt16(int16 Value, int16 OrValue, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalOrBits(Value,OrValue,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint16 CParserHelper::OrBitsUInt16(uint16 Value, uint16 OrValue, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalOrBits(Value,OrValue,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CParserHelper::OrBitsInt32(int32 Value, int32 OrValue, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalOrBits(Value,OrValue,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint32 CParserHelper::OrBitsUInt32(uint32 Value, uint32 OrValue, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalOrBits(Value,OrValue,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CParserHelper::OrBitsInt64(int64 Value, int64 OrValue, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalOrBits(Value,OrValue,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint64 CParserHelper::OrBitsUInt64(uint64 Value, uint64 OrValue, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalOrBits(Value,OrValue,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CParserHelper::OrBitsSize(Size Value, Size OrValue, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalOrBits(Value,OrValue,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int8 CParserHelper::SetBitInt8(int8 Value, bool SetValue, Size PositionInBits)
	{
		return(SetBitsInt8(Value,static_cast<int8>((SetValue==true) ? 1 : 0),PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8 CParserHelper::SetBitUInt8(uint8 Value, bool SetValue, Size PositionInBits)
	{
		return(SetBitsUInt8(Value,static_cast<uint8>((SetValue==true) ? 1 : 0),PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	int16 CParserHelper::SetBitInt16(int16 Value, bool SetValue, Size PositionInBits)
	{
		return(SetBitsInt16(Value,static_cast<int16>((SetValue==true) ? 1 : 0),PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint16 CParserHelper::SetBitUInt16(uint16 Value, bool SetValue, Size PositionInBits)
	{
		return(SetBitsUInt16(Value,static_cast<uint16>((SetValue==true) ? 1 : 0),PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CParserHelper::SetBitInt32(int32 Value, bool SetValue, Size PositionInBits)
	{
		return(SetBitsInt32(Value,static_cast<int32>((SetValue==true) ? 1 : 0),PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint32 CParserHelper::SetBitUInt32(uint32 Value, bool SetValue, Size PositionInBits)
	{
		return(SetBitsUInt32(Value,static_cast<uint32>((SetValue==true) ? 1 : 0),PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CParserHelper::SetBitInt64(int64 Value, bool SetValue, Size PositionInBits)
	{
		return(SetBitsInt64(Value,static_cast<int64>((SetValue==true) ? 1 : 0),PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint64 CParserHelper::SetBitUInt64(uint64 Value, bool SetValue, Size PositionInBits)
	{
		return(SetBitsUInt64(Value,static_cast<uint64>((SetValue==true) ? 1 : 0),PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CParserHelper::SetBitSize(Size Value, bool SetValue, Size PositionInBits)
	{
		return(SetBitsSize(Value,static_cast<Size>((SetValue==true) ? 1 : 0),PositionInBits,1));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int8 CParserHelper::SetBitsInt8(int8 Value, int8 SetValue, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalSetBits(Value,SetValue,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8 CParserHelper::SetBitsUInt8(uint8 Value, uint8 SetValue, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalSetBits(Value,SetValue,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	int16 CParserHelper::SetBitsInt16(int16 Value, int16 SetValue, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalSetBits(Value,SetValue,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint16 CParserHelper::SetBitsUInt16(uint16 Value, uint16 SetValue, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalSetBits(Value,SetValue,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CParserHelper::SetBitsInt32(int32 Value, int32 SetValue, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalSetBits(Value,SetValue,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint32 CParserHelper::SetBitsUInt32(uint32 Value, uint32 SetValue, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalSetBits(Value,SetValue,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CParserHelper::SetBitsInt64(int64 Value, int64 SetValue, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalSetBits(Value,SetValue,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint64 CParserHelper::SetBitsUInt64(uint64 Value, uint64 SetValue, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalSetBits(Value,SetValue,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CParserHelper::SetBitsSize(Size Value, Size SetValue, Size StartPositionInBits, Size LengthInBits)
	{
		return(InternalSetBits(Value,SetValue,StartPositionInBits,LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int8 CParserHelper::GetLengthInBytesInt8(int8 LengthInBits)
	{
		return(InternalGetLengthInBytes(LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8 CParserHelper::GetLengthInBytesUInt8(uint8 LengthInBits)
	{
		return(InternalGetLengthInBytes(LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	int16 CParserHelper::GetLengthInBytesInt16(int16 LengthInBits)
	{
		return(InternalGetLengthInBytes(LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint16 CParserHelper::GetLengthInBytesUInt16(uint16 LengthInBits)
	{
		return(InternalGetLengthInBytes(LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CParserHelper::GetLengthInBytesInt32(int32 LengthInBits)
	{
		return(InternalGetLengthInBytes(LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint32 CParserHelper::GetLengthInBytesUInt32(uint32 LengthInBits)
	{
		return(InternalGetLengthInBytes(LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CParserHelper::GetLengthInBytesInt64(int64 LengthInBits)
	{
		return(InternalGetLengthInBytes(LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint64 CParserHelper::GetLengthInBytesUInt64(uint64 LengthInBits)
	{
		return(InternalGetLengthInBytes(LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CParserHelper::GetLengthInBytesSize(Size LengthInBits)
	{
		return(InternalGetLengthInBytes(LengthInBits));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	uint8 CParserHelper::ConvertToBCD(uint8 Value)
	{
		if (Value>BCD_MAX_VALUE)
		{
			throw(CParserException(CString::Format("VALUE is OUT of RANGE <",BCD_MIN_VALUE,",",BCD_MAX_VALUE,"> !")));
		}

		uint8												HighValue=(Value/BCD_TO_DECADIC_VALUE_CONVERSION);
		uint8												LowValue=(Value%BCD_TO_DECADIC_VALUE_CONVERSION);
		uint8												Result=static_cast<uint8>((HighValue << NIBBLE_SIZE_IN_BITS)+LowValue);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8 CParserHelper::ConvertFromBCD(uint8 Value)
	{
		uint8												HighNibble=static_cast<uint8>(Value >> NIBBLE_SIZE_IN_BITS);
		uint8												LowNibble=static_cast<uint8>(Value & NIBBLE_MASK);

		if (HighNibble>BCD_MAX_NUMERIC_VALUE)
		{
			throw(CParserException(CString::Format("HIGH NIBBLE is OUT of RANGE <",BCD_MIN_NUMERIC_VALUE,",",BCD_MAX_NUMERIC_VALUE,"> !")));
		}

		if (LowNibble>BCD_MAX_NUMERIC_VALUE)
		{
			throw(CParserException(CString::Format("LOW NIBBLE is OUT of RANGE <",BCD_MIN_NUMERIC_VALUE,",",BCD_MAX_NUMERIC_VALUE,"> !")));
		}

		uint8												Result=static_cast<uint8>((HighNibble*BCD_TO_DECADIC_VALUE_CONVERSION)+LowNibble);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	[[noreturn]] void CParserHelper::ThrowLengthException(Size ExpectedLength)
	{
		throw(CParserException(CString::Format("PACKET too SHORT. At least [",ExpectedLength,"] BYTES EXPECTED !")));
	}
//----------------------------------------------------------------------------------------------------------------------
	[[noreturn]] void CParserHelper::ThrowUnexpectedLengthException(Size Length)
	{
		throw(CParserException(CString::Format("PACKET has an UNEXPECTED LENGTH containing [",Length,"] BYTES !")));
	}
//----------------------------------------------------------------------------------------------------------------------
	[[noreturn]] void CParserHelper::ThrowNotNULLException(const Char* ValueName)
	{
		throw(CParserException(CString::Format("SHARED POINTER [",ValueName,"] has NULL VALUE !")));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CParserHelper::CheckLength(Size ActualLength, Size ExpectedLength)
	{
		if (ActualLength<ExpectedLength)
		{
			ThrowLengthException(ExpectedLength);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------