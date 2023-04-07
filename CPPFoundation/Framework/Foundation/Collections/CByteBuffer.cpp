//----------------------------------------------------------------------------------------------------------------------
#include "CByteBuffer.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBufferEnumerator::CByteBufferEnumerator(CByteBuffer& Buffer)
		: MBuffer(Buffer), MIsBeforeFirstItem(true), MPosition(0)
	{
		Reset();
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBufferEnumerator::~CByteBufferEnumerator(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::CByteBufferEnumerator::Reset(void)
	{
		MIsBeforeFirstItem=true;
		MPosition=0;
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CByteBuffer::CByteBufferEnumerator::MoveNext(void)
	{
		if (MIsBeforeFirstItem==true)
		{
			MIsBeforeFirstItem=false;

			if (MPosition<MBuffer.GetLength())
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
			if ((MPosition+1)<MBuffer.GetLength())
			{
				MPosition++;

				return(true);
			}
			else
			{
				MPosition=MBuffer.GetLength();

				return(false);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	const uint8& CByteBuffer::CByteBufferEnumerator::GetCurrentConst(void) const
	{
		if (MIsBeforeFirstItem==false && MPosition<MBuffer.GetLength())
		{
			return(MBuffer[MPosition]);
		}
		else
		{
			throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8& CByteBuffer::CByteBufferEnumerator::GetCurrent(void)
	{
		if (MIsBeforeFirstItem==false && MPosition<MBuffer.GetLength())
		{
			return(MBuffer[MPosition]);
		}
		else
		{
			throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBufferEnumeratorConst::CByteBufferEnumeratorConst(const CByteBuffer& Buffer)
		: MBuffer(Buffer), MIsBeforeFirstItem(true), MPosition(0)
	{
		Reset();
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBufferEnumeratorConst::~CByteBufferEnumeratorConst(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::CByteBufferEnumeratorConst::Reset(void)
	{
		MIsBeforeFirstItem=true;
		MPosition=0;
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CByteBuffer::CByteBufferEnumeratorConst::MoveNext(void)
	{
		if (MIsBeforeFirstItem==true)
		{
			MIsBeforeFirstItem=false;

			if (MPosition<MBuffer.GetLength())
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
			if ((MPosition+1)<MBuffer.GetLength())
			{
				MPosition++;

				return(true);
			}
			else
			{
				MPosition=MBuffer.GetLength();

				return(false);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	const uint8& CByteBuffer::CByteBufferEnumeratorConst::GetCurrentConst(void) const
	{
		if (MIsBeforeFirstItem==false && MPosition<MBuffer.GetLength())
		{
			return(MBuffer[MPosition]);
		}
		else
		{
			throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const Size													CByteBuffer::END=static_cast<Size>(-1);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBuffer(void)
		: MBuffer()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBuffer(Size BufferSize)
		: MBuffer()
	{
		Resize(BufferSize);
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBuffer(const CByteBuffer& BufferData, Size BufferSize)
		: MBuffer()
	{
		Size													Length=(BufferData.GetLength()<BufferSize) ? BufferData.GetLength() : BufferSize;

		MBuffer.resize(static_cast<std::vector<uint8>::size_type>(Length));

		for(Size Index=0;Index<Length;Index++)
		{
			MBuffer[Index]=BufferData[Index];
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBuffer(const uint8* BufferData, Size BufferSize)
		: MBuffer()
	{
		MBuffer.resize(static_cast<Size>(BufferSize));

		for(Size Index=0;Index<BufferSize;Index++)
		{
			MBuffer[Index]=BufferData[Index];
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBuffer(const CByteBuffer& Other)
		: MBuffer(Other.MBuffer)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBuffer(CByteBuffer&& Other) noexcept
		: MBuffer(FUNCTION_MOVE(Other.MBuffer))
	{
		Other.Clear();
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBuffer(const CVector<uint8>& Other)
		: MBuffer(Other.MVector)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBuffer(CVector<uint8>&& Other)
		: MBuffer(FUNCTION_MOVE(Other.MVector))
	{
		Other.Clear();
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBuffer(IEnumerable<uint8>& Other)
		: MBuffer()
	{
		CEnumeratorPointer										Enumerator=Other.GetEnumerator();

		while(Enumerator->MoveNext()==true)
		{
			MBuffer.push_back(Enumerator->GetCurrent());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBuffer(const IEnumerableConst<uint8>& Other)
		: MBuffer()
	{
		CEnumeratorConstPointer									Enumerator=Other.GetEnumeratorConst();

		while(Enumerator->MoveNext()==true)
		{
			MBuffer.push_back(Enumerator->GetCurrentConst());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBuffer(std::initializer_list<uint8> Other)
		: MBuffer(Other)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::~CByteBuffer(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer& CByteBuffer::operator=(const CByteBuffer& Other)
	{
		MBuffer=Other.MBuffer;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer& CByteBuffer::operator=(CByteBuffer&& Other) noexcept
	{
		MBuffer=FUNCTION_MOVE(Other.MBuffer);
		Other.Clear();

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer& CByteBuffer::operator=(IEnumerable<uint8>& Other)
	{
		Clear();

		CEnumeratorPointer										Enumerator=Other.GetEnumerator();

		while(Enumerator->MoveNext()==true)
		{
			MBuffer.push_back(Enumerator->GetCurrent());
		}

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer& CByteBuffer::operator=(const IEnumerableConst<uint8>& Other)
	{
		Clear();

		CEnumeratorConstPointer									Enumerator=Other.GetEnumeratorConst();

		while(Enumerator->MoveNext()==true)
		{
			MBuffer.push_back(Enumerator->GetCurrentConst());
		}

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer& CByteBuffer::operator=(std::initializer_list<uint8> Other)
	{
		MBuffer=Other;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8& CByteBuffer::operator[](Size Index)
	{
		CheckIndex(Index,false);

		return(Get(Index));
	}
//----------------------------------------------------------------------------------------------------------------------
	const uint8& CByteBuffer::operator[](Size Index) const
	{
		CheckIndex(Index,false);

		return(Get(Index));
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CByteBuffer::operator==(const CByteBuffer& Other) const
	{
		if (GetLength()!=Other.GetLength())
		{
			return(false);
		}

		for(Size Index=0;Index<GetLength();Index++)
		{
			if ((*this)[Index]!=Other[Index])
			{
				return(false);
			}
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CByteBuffer::operator!=(const CByteBuffer& Other) const
	{
		if (GetLength()!=Other.GetLength())
		{
			return(true);
		}

		for(Size Index=0;Index<GetLength();Index++)
		{
			if ((*this)[Index]!=Other[Index])
			{
				return(true);
			}
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::CheckIndex(Size Index, bool AllowAfterLastPosition) const
	{
		if (AllowAfterLastPosition==false)
		{
			if (Index>=GetLength())
			{
				throw(CValueOutOfRangeException("INDEX is OUT of RANGE !"));
			}
		}
		else
		{
			if (Index>GetLength())
			{
				throw(CValueOutOfRangeException("INDEX is OUT of RANGE !"));
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::CheckLength(Size Length) const
	{
		if (Length>GetLength())
		{
			throw(CValueOutOfRangeException("BUFFER is TOO SHORT !"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::CheckOffset(Size Offset) const
	{
		if (Offset>GetLength() && Offset!=END)
		{
			throw(CValueOutOfRangeException("OFFSET is OUT of RANGE !"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	// Doesn't check BOUNDS. Can be used JUST INTERNALLY within the CLASS.
	uint8& CByteBuffer::Get(Size Index)
	{
		return(MBuffer[static_cast<std::vector<uint8>::size_type>(Index)]);
	}
//----------------------------------------------------------------------------------------------------------------------
	// Doesn't check BOUNDS. Can be used JUST INTERNALLY within the CLASS.
	const uint8& CByteBuffer::Get(Size Index) const
	{
		return(MBuffer[static_cast<std::vector<uint8>::size_type>(Index)]);
	}
//----------------------------------------------------------------------------------------------------------------------
	// Doesn't check BOUNDS. Can be used JUST INTERNALLY within the CLASS.
	void CByteBuffer::Set(Size Index, uint8 Value)
	{
		MBuffer[static_cast<std::vector<uint8>::size_type>(Index)]=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CByteBuffer::ToString(void) const
	{
		return(ToString(true,",",0,GetLength()));
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CEnumeratorPointer CByteBuffer::GetEnumerator(void)
	{
		CEnumeratorPointer										Enumerator=CEnumeratorPointer(new CByteBufferEnumerator(*this));

		return(Enumerator);
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CEnumeratorConstPointer CByteBuffer::GetEnumeratorConst(void) const
	{
		CEnumeratorConstPointer									Enumerator=CEnumeratorConstPointer(new CByteBufferEnumeratorConst(*this));

		return(Enumerator);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CByteBuffer::ToString(Size Offset, Size Length) const
	{
		return(ToString(true,",",Offset,Length));
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CByteBuffer::ToString(bool AddPrefix, const CString& Separator, Size Offset, Size Length) const
	{
		CString													Text;
		EIntegerFormat											Format;

		if (AddPrefix==false)
		{
			Format=EIntegerFormat::E_HEXADECIMAL;
		}
		else
		{
			Format=EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX;
		}

		CUInt8Formatter											Formatter(Format,2,true);

		for(Size Index=0;Index<Length;Index++)
		{
			if ((Index+Offset)>=GetLength())
			{
				break;
			}

			if (Index!=0)
			{
				Text+=Separator;
			}

			Text+=Formatter.ConvertToString((*this)[Index+Offset]);
		}

		return(Text);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CByteBuffer::GetLength(void) const noexcept
	{
		return(static_cast<Size>(MBuffer.size()));
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CByteBuffer::IsEmpty(void) const noexcept
	{
		Size													Length=static_cast<Size>(MBuffer.size());

		if (Length==0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8* CByteBuffer::GetRawData(void) noexcept
	{
		uint8*													RawData=MBuffer.data();
				
		return(RawData);
	}
//----------------------------------------------------------------------------------------------------------------------
	const uint8* CByteBuffer::GetRawData(void) const noexcept
	{
		const uint8*											RawData=MBuffer.data();
				
		return(RawData);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8* CByteBuffer::GetRawData(Size Index)
	{
		CheckIndex(Index,false);

		uint8*													RawData=MBuffer.data()+Index;
				
		return(RawData);
	}
//----------------------------------------------------------------------------------------------------------------------
	const uint8* CByteBuffer::GetRawData(Size Index) const
	{
		CheckIndex(Index,false);

		const uint8*											RawData=MBuffer.data()+Index;
				
		return(RawData);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::Add(uint8 Value)
	{
		MBuffer.push_back(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::Add(uint8 Value, Size Length)
	{
		for(Size Index=0;Index<Length;Index++)
		{
			Add(Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::Add(const CByteBuffer& Buffer)
	{
		Size													Length=Buffer.GetLength();

		for(Size Index=0;Index<Length;Index++)
		{
			MBuffer.push_back(Buffer[Index]);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::Add(const uint8* Buffer, Size Length)
	{
		for(Size Index=0;Index<Length;Index++)
		{
			MBuffer.push_back(Buffer[Index]);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::Insert(uint8 Item, Size Index)
	{
		CheckIndex(Index,true);

		MBuffer.insert(MBuffer.begin()+static_cast<std::vector<uint8>::difference_type>(Index),Item);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::Insert(const CByteBuffer& Buffer, Size Index)
	{
		CheckIndex(Index,true);

		MBuffer.insert(MBuffer.begin()+static_cast<std::vector<uint8>::difference_type>(Index),Buffer.Begin(),Buffer.End());
	}
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::Insert(const uint8* Items, Size Length, Size Index)
	{
		CheckIndex(Index,true);

		MBuffer.insert(MBuffer.begin()+static_cast<std::vector<uint8>::difference_type>(Index),Items,Items+Length);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::Erase(Size Index)
	{
		// INDEX MUST NOT POINT BEHIND the END of VECTOR because METHOD erase() with a SINGLE PARAMETER forbids it.
		CheckIndex(Index,false);

		MBuffer.erase(MBuffer.begin()+static_cast<std::vector<uint8>::difference_type>(Index));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::Erase(Size Index, Size Length)
	{
		// INDEX CAN POINT BEHIND the END of VECTOR if LENGTH is 0 because METHOD erase() with a DOUBLE PARAMETERS allows it.
		CheckLength(Index+Length);

		MBuffer.erase(MBuffer.begin()+static_cast<std::vector<uint8>::difference_type>(Index),MBuffer.begin()+static_cast<std::vector<uint8>::difference_type>(Index)+static_cast<std::vector<uint8>::difference_type>(Length));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::Clear(void) noexcept
	{
		MBuffer.clear();
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CByteBuffer::Copy(Size Length) const
	{
		CheckLength(Length);

		CByteBuffer												CopiedBuffer(Length);

		for(Size Index=0;Index<Length;Index++)
		{
			CopiedBuffer[Index]=Get(Index);
		}

		return(CopiedBuffer);
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CByteBuffer::Copy(Size Index, Size Length) const
	{
		CheckLength(Index+Length);

		CByteBuffer												CopiedBuffer(Length);

		for(Size LocalIndex=0;LocalIndex<Length;LocalIndex++)
		{
			CopiedBuffer[LocalIndex]=Get(Index+LocalIndex);
		}

		return(CopiedBuffer);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::Copy(uint8* Buffer, Size Index, Size Length) const
	{
		CheckLength(Index+Length);

		for(Size LocalIndex=0;LocalIndex<Length;LocalIndex++)
		{
			Buffer[LocalIndex]=Get(Index+LocalIndex);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CByteBuffer::FindFirstIndex(uint8 Value, Size Offset) const
	{
		CheckOffset(Offset);

		Size													Length=GetLength();

		for(Size Index=Offset;Index<Length;Index++)
		{
			if (Value==(*this)[Index])
			{
				return(Index);
			}
		}

		return(END);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CByteBuffer::FindLastIndex(uint8 Value, Size Offset) const
	{
		CheckOffset(Offset);

		Size													Length=GetLength();

		if (Offset==END || Offset==Length)
		{
			Offset=Length-1;
		}

		for(Size Index=Offset;;Index--)
		{
			if (Value==(*this)[Index])
			{
				return(Index);
			}

			if (Index==0)
			{
				break;
			}
		}

		return(END);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::Fill(const CByteBuffer& Buffer)
	{
		Size													Length=Buffer.GetLength();

		CheckLength(Length);

		for(Size Index=0;Index<Length;Index++)
		{
			Set(Index,Buffer.Get(Index));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::Fill(const uint8* Buffer, Size Length)
	{
		CheckLength(Length);

		for(Size Index=0;Index<Length;Index++)
		{
			Set(Index,Buffer[Index]);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::Resize(Size Length)
	{
		MBuffer.resize(static_cast<std::vector<uint8>::size_type>(Length));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::Resize(Size Length, uint8 FillValue)
	{
		MBuffer.resize(static_cast<std::vector<uint8>::size_type>(Length),FillValue);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::SetAll(const uint8& Value)
	{
		Size													Length=GetLength();

		for(Size Index=0;Index<Length;Index++)
		{
			Set(Index,Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CByteBuffer::GetCapacity(void) const noexcept
	{
		Size													Capacity=static_cast<Size>(MBuffer.capacity());

		return(Capacity);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CByteBuffer::ReserveCapacity(Size Capacity)
	{
		MBuffer.reserve(static_cast<typename std::vector<uint8>::size_type>(Capacity));
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBufferIterator CByteBuffer::Begin(void)
	{
		return(MBuffer.begin());
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBufferIterator CByteBuffer::End(void)
	{
		return(MBuffer.end());
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBufferIteratorConst CByteBuffer::Begin(void) const
	{
		return(MBuffer.cbegin());
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBufferIteratorConst CByteBuffer::End(void) const
	{
		return(MBuffer.cend());
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBufferIterator CByteBuffer::begin(void)
	{
		return(MBuffer.begin());
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBufferIterator CByteBuffer::end(void)
	{
		return(MBuffer.end());
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBufferIteratorConst CByteBuffer::begin(void) const
	{
		return(MBuffer.cbegin());
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBufferIteratorConst CByteBuffer::end(void) const
	{
		return(MBuffer.cend());
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBufferReverseIterator CByteBuffer::ReverseBegin(void)
	{
		return(MBuffer.rbegin());
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBufferReverseIterator CByteBuffer::ReverseEnd(void)
	{
		return(MBuffer.rend());
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBufferReverseIteratorConst CByteBuffer::ReverseBegin(void) const
	{
		return(MBuffer.crbegin());
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBufferReverseIteratorConst CByteBuffer::ReverseEnd(void) const
	{
		return(MBuffer.crend());
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBufferReverseIterator CByteBuffer::rbegin(void)
	{
		return(MBuffer.rbegin());
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBufferReverseIterator CByteBuffer::rend(void)
	{
		return(MBuffer.rend());
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBufferReverseIteratorConst CByteBuffer::rbegin(void) const
	{
		return(MBuffer.crbegin());
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer::CByteBufferReverseIteratorConst CByteBuffer::rend(void) const
	{
		return(MBuffer.crend());
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString ConvertToString(const CByteBuffer& StringBytes)
	{
		CString													String;

		String.SetCapacity(StringBytes.GetLength());

		for(uint8 Byte : StringBytes)
		{
			String.Append(static_cast<Char>(Byte));
		}

		return(String);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------