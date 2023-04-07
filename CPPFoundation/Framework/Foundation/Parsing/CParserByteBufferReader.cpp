//----------------------------------------------------------------------------------------------------------------------
#include "CParserByteBufferReader.h"
#include <Framework/Foundation/Exceptions/CParserException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CParserByteBufferReader::CParserByteBufferReader(void)
		: MBuffer(), MPosition(0)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserByteBufferReader::CParserByteBufferReader(const CByteBuffer& Buffer)
		: MBuffer(Buffer), MPosition(0)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserByteBufferReader::CParserByteBufferReader(CByteBuffer&& Buffer)
		: MBuffer(FUNCTION_MOVE(Buffer)), MPosition(0)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserByteBufferReader::CParserByteBufferReader(const CParserByteBufferReader& Other)
		: MBuffer(Other.MBuffer), MPosition(Other.MPosition)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserByteBufferReader::CParserByteBufferReader(CParserByteBufferReader&& Other) noexcept
		: MBuffer(FUNCTION_MOVE(Other.MBuffer)), MPosition(FUNCTION_MOVE(Other.MPosition))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserByteBufferReader::~CParserByteBufferReader(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CParserByteBufferReader& CParserByteBufferReader::operator=(const CParserByteBufferReader& Other)
	{
		MBuffer=Other.MBuffer;
		MPosition=Other.MPosition;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserByteBufferReader& CParserByteBufferReader::operator=(CParserByteBufferReader&& Other) noexcept
	{
		MBuffer=FUNCTION_MOVE(Other.MBuffer);
		MPosition=FUNCTION_MOVE(Other.MPosition);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8& CParserByteBufferReader::operator[](Size Index)
	{
		return(MBuffer[Index]);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8 CParserByteBufferReader::operator[](Size Index) const
	{
		return(MBuffer[Index]);
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserByteBufferReader& CParserByteBufferReader::operator++(void)
	{
		CheckLength(1);

		MPosition++;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserByteBufferReader& CParserByteBufferReader::operator+=(Size Length)
	{
		CheckLength(Length);

		MPosition+=Length;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CParserByteBufferReader::ToString(void) const
	{
		return(MBuffer.ToString());
	}
//----------------------------------------------------------------------------------------------------------------------
	const CByteBuffer& CParserByteBufferReader::GetBuffer(void) const noexcept
	{
		return(MBuffer);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CParserByteBufferReader::GetPosition(void) const
	{
		return(MPosition);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CParserByteBufferReader::GetLength(void) const
	{
		return(MBuffer.GetLength()-MPosition);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CParserByteBufferReader::GetTotalLength(void) const
	{
		return(MBuffer.GetLength());
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CParserByteBufferReader::HasLength(Size Length) const
	{
		if (Length<=GetLength())
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferReader::CheckLength(Size Length) const
	{
		if (Length>GetLength())
		{
			throw(CParserException("BYTE BUFFER READER is OUT of BOUNDS !"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferReader::CheckLength(Size Length, const CString& ExceptionMessage) const
	{
		if (Length>GetLength())
		{
			throw(CParserException(ExceptionMessage));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferReader::CheckLength(Size Length, const CException& Exception) const
	{
		if (Length>GetLength())
		{
			throw(Exception);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8 CParserByteBufferReader::GetActual(void) const
	{
		uint8													Value=MBuffer[MPosition];

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8 CParserByteBufferReader::GetActual(Size Index) const
	{
		uint8													Value=MBuffer[MPosition+Index];

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8 CParserByteBufferReader::GetActualAndInc(void)
	{
		uint8													Value=MBuffer[MPosition];

		MPosition++;

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CParserByteBufferReader::GetActualArray(Size Length) const
	{
		CByteBuffer												Buffer=MBuffer.Copy(MPosition,Length);

		return(Buffer);
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CParserByteBufferReader::GetActualArrayAndInc(Size Length)
	{
		CByteBuffer												Buffer=MBuffer.Copy(MPosition,Length);

		MPosition+=Length;

		return(Buffer);
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CParserByteBufferReader::GetRemainingArray(void) const
	{
		Size													Length=MBuffer.GetLength()-MPosition;

		if (Length>0)
		{
			CByteBuffer											Buffer=MBuffer.Copy(MPosition,Length);

			return(Buffer);
		}
		else
		{
			return(CByteBuffer());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CParserByteBufferReader::GetRemainingArrayAndInc(void)
	{
		Size													Length=MBuffer.GetLength()-MPosition;

		if (Length>0)
		{
			CByteBuffer											Buffer=MBuffer.Copy(MPosition,Length);

			MPosition+=Length;

			return(Buffer);
		}
		else
		{
			return(CByteBuffer());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferReader::Insert(uint8 Item, Size Index)
	{
		if (Index<MPosition)
		{
			throw(CParserException("BYTE BUFFER READER is OUT of BOUNDS !"));
		}

		MBuffer.Insert(Item,Index);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferReader::Erase(Size Index)
	{
		if (Index<MPosition)
		{
			throw(CParserException("BYTE BUFFER READER is OUT of BOUNDS !"));
		}

		MBuffer.Erase(Index);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferReader::Erase(Size Index, Size Length)
	{
		if (Index<MPosition)
		{
			throw(CParserException("BYTE BUFFER READER is OUT of BOUNDS !"));
		}

		if ((Index+Length)>=MBuffer.GetLength())
		{
			throw(CParserException("BYTE BUFFER READER is OUT of BOUNDS !"));
		}

		MBuffer.Erase(Index,Length);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int8 CParserByteBufferReader::DeserializeInt8(EParserEndianness Endianness, bool IncrementPosition)
	{
		int8													Value=CParserHelper::DeserializeInt8(MBuffer,MPosition,Endianness);

		if (IncrementPosition==true)
		{
			MPosition+=sizeof(int8);
		}

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8 CParserByteBufferReader::DeserializeUInt8(EParserEndianness Endianness, bool IncrementPosition)
	{
		uint8													Value=CParserHelper::DeserializeUInt8(MBuffer,MPosition,Endianness);

		if (IncrementPosition==true)
		{
			MPosition+=sizeof(uint8);
		}

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	int16 CParserByteBufferReader::DeserializeInt16(EParserEndianness Endianness, bool IncrementPosition)
	{
		int16													Value=CParserHelper::DeserializeInt16(MBuffer,MPosition,Endianness);

		if (IncrementPosition==true)
		{
			MPosition+=sizeof(int16);
		}

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint16 CParserByteBufferReader::DeserializeUInt16(EParserEndianness Endianness, bool IncrementPosition)
	{
		uint16													Value=CParserHelper::DeserializeUInt16(MBuffer,MPosition,Endianness);

		if (IncrementPosition==true)
		{
			MPosition+=sizeof(uint16);
		}

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CParserByteBufferReader::DeserializeInt32(EParserEndianness Endianness, bool IncrementPosition)
	{
		int32													Value=CParserHelper::DeserializeInt32(MBuffer,MPosition,Endianness);

		if (IncrementPosition==true)
		{
			MPosition+=sizeof(int32);
		}

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint32 CParserByteBufferReader::DeserializeUInt32(EParserEndianness Endianness, bool IncrementPosition)
	{
		uint32													Value=CParserHelper::DeserializeUInt32(MBuffer,MPosition,Endianness);

		if (IncrementPosition==true)
		{
			MPosition+=sizeof(uint32);
		}

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CParserByteBufferReader::DeserializeInt64(EParserEndianness Endianness, bool IncrementPosition)
	{
		int64													Value=CParserHelper::DeserializeInt64(MBuffer,MPosition,Endianness);

		if (IncrementPosition==true)
		{
			MPosition+=sizeof(int64);
		}

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint64 CParserByteBufferReader::DeserializeUInt64(EParserEndianness Endianness, bool IncrementPosition)
	{
		uint64													Value=CParserHelper::DeserializeUInt64(MBuffer,MPosition,Endianness);

		if (IncrementPosition==true)
		{
			MPosition+=sizeof(uint64);
		}

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	float32 CParserByteBufferReader::DeserializeFloat32(EParserEndianness Endianness, bool IncrementPosition)
	{
		float32													Value=CParserHelper::DeserializeFloat32(MBuffer,MPosition,Endianness);

		if (IncrementPosition==true)
		{
			MPosition+=sizeof(float32);
		}

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	float64 CParserByteBufferReader::DeserializeFloat64(EParserEndianness Endianness, bool IncrementPosition)
	{
		float64													Value=CParserHelper::DeserializeFloat64(MBuffer,MPosition,Endianness);

		if (IncrementPosition==true)
		{
			MPosition+=sizeof(float80);
		}

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	float80 CParserByteBufferReader::DeserializeFloat80(EParserEndianness Endianness, bool IncrementPosition)
	{
		float80													Value=CParserHelper::DeserializeFloat80(MBuffer,MPosition,Endianness);

		if (IncrementPosition==true)
		{
			MPosition+=sizeof(float80);
		}

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CParserByteBufferReader::DeserializeSize(EParserEndianness Endianness, bool IncrementPosition)
	{
		Size													Value=CParserHelper::DeserializeSize(MBuffer,MPosition,Endianness);

		if (IncrementPosition==true)
		{
			MPosition+=sizeof(Size);
		}

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------