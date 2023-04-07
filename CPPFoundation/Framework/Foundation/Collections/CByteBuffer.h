//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <vector>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Strings/CIntegerFormatter.h>
#include <Framework/Foundation/Exceptions/CValueOutOfRangeException.h>
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include "IEnumerable.h"
#include "CIterators.h"
#include "CVector.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CByteBuffer final : public CObject, public IEnumerable<uint8>
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			class CByteBufferEnumerator final : public IEnumerator<uint8>
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					CByteBuffer&								MBuffer;
					bool										MIsBeforeFirstItem;
					Size										MPosition;

				public:
					virtual void Reset(void) override;
					virtual bool MoveNext(void) override;
					virtual const uint8& GetCurrentConst(void) const override;
					virtual uint8& GetCurrent(void) override;

				public:
					CByteBufferEnumerator(CByteBuffer& Buffer);
					virtual ~CByteBufferEnumerator(void) override;
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
			class CByteBufferEnumeratorConst final : public IEnumeratorConst<uint8>
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					const CByteBuffer&							MBuffer;
					bool										MIsBeforeFirstItem;
					Size										MPosition;

				public:
					virtual void Reset(void) override;
					virtual bool MoveNext(void) override;
					virtual const uint8& GetCurrentConst(void) const override;

				public:
					CByteBufferEnumeratorConst(const CByteBuffer& Buffer);
					virtual ~CByteBufferEnumeratorConst(void) override;
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public:
			using												CEnumeratorPointer=CSharedPointer<IEnumerator<uint8>>;
			using												CEnumeratorConstPointer=CSharedPointer<IEnumeratorConst<uint8>>;
			using												CByteBufferIterator=typename std::vector<uint8>::iterator;
			using												CByteBufferIteratorConst=typename std::vector<uint8>::const_iterator;
			using												CByteBufferReverseIterator=typename std::vector<uint8>::reverse_iterator;
			using												CByteBufferReverseIteratorConst=typename std::vector<uint8>::const_reverse_iterator;

		public:
			static const Size									END;

		private:
			std::vector<uint8>									MBuffer;

		public:
			CByteBuffer& operator=(const CByteBuffer& Other);
			CByteBuffer& operator=(CByteBuffer&& Other) noexcept;
			CByteBuffer& operator=(IEnumerable<uint8>& Other);
			CByteBuffer& operator=(const IEnumerableConst<uint8>& Other);
			CByteBuffer& operator=(std::initializer_list<uint8> Other);
			uint8& operator[](Size Index);
			const uint8& operator[](Size Index) const;
			bool operator==(const CByteBuffer& Other) const;
			bool operator!=(const CByteBuffer& Other) const;

		private:
			void CheckIndex(Size Index, bool AllowAfterLastPosition) const;
			void CheckLength(Size Length) const;
			void CheckOffset(Size Offset) const;
			uint8& Get(Size Index);
			const uint8& Get(Size Index) const;
			void Set(Size Index, uint8 Value);

		public:
			virtual CString ToString(void) const override;
			virtual CEnumeratorPointer GetEnumerator(void) override;
			virtual CEnumeratorConstPointer GetEnumeratorConst(void) const override;
			CString ToString(Size Offset, Size Length) const;
			CString ToString(bool AddPrefix, const CString& Separator, Size Offset=0, Size Length=CPrimitiveType<Size>::Max()) const;
			Size GetLength(void) const noexcept;
			bool IsEmpty(void) const noexcept;
			uint8* GetRawData(void) noexcept;
			const uint8* GetRawData(void) const noexcept;
			uint8* GetRawData(Size Index);
			const uint8* GetRawData(Size Index) const;
			void Add(uint8 Value);
			void Add(uint8 Value, Size Length);
			void Add(const CByteBuffer& Buffer);
			void Add(const uint8* Buffer, Size Length);
			void Insert(uint8 Item, Size Index);
			void Insert(const CByteBuffer& Buffer, Size Index);
			void Insert(const uint8* Items, Size Length, Size Index);
			void Erase(Size Index);
			void Erase(Size Index, Size Length);
			void Clear(void) noexcept;
			CByteBuffer Copy(Size Length) const;
			CByteBuffer Copy(Size Index, Size Length) const;
			void Copy(uint8* Buffer, Size Index, Size Length) const;
			Size FindFirstIndex(uint8 Value, Size Offset=0) const;
			Size FindLastIndex(uint8 Value, Size Offset=END) const;
			void Fill(const CByteBuffer& Buffer);
			void Fill(const uint8* Buffer, Size Length);
			void Resize(Size Length);
			void Resize(Size Length, uint8 FillValue);
			void SetAll(const uint8& Value);
			Size GetCapacity(void) const noexcept;
			void ReserveCapacity(Size Capacity);
			CByteBufferIterator Begin(void);
			CByteBufferIterator End(void);
			CByteBufferIteratorConst Begin(void) const;
			CByteBufferIteratorConst End(void) const;
			CByteBufferIterator begin(void);
			CByteBufferIterator end(void);
			CByteBufferIteratorConst begin(void) const;
			CByteBufferIteratorConst end(void) const;
			CByteBufferReverseIterator ReverseBegin(void);
			CByteBufferReverseIterator ReverseEnd(void);
			CByteBufferReverseIteratorConst ReverseBegin(void) const;
			CByteBufferReverseIteratorConst ReverseEnd(void) const;
			CByteBufferReverseIterator rbegin(void);
			CByteBufferReverseIterator rend(void);
			CByteBufferReverseIteratorConst rbegin(void) const;
			CByteBufferReverseIteratorConst rend(void) const;

		public:
			CByteBuffer(void);
			explicit CByteBuffer(Size BufferSize);
			CByteBuffer(const CByteBuffer& BufferData, Size BufferSize);
			CByteBuffer(const uint8* BufferData, Size BufferSize);
			CByteBuffer(const CByteBuffer& Other);
			CByteBuffer(CByteBuffer&& Other) noexcept;
			CByteBuffer(const CVector<uint8>& Other);
			CByteBuffer(CVector<uint8>&& Other);
			CByteBuffer(IEnumerable<uint8>& Other);
			CByteBuffer(const IEnumerableConst<uint8>& Other);
			CByteBuffer(std::initializer_list<uint8> Other);
			virtual ~CByteBuffer(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPByteBuffer=CSharedPointer<CByteBuffer>;
	using														CCSPByteBuffer=CSharedPointer<const CByteBuffer>;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString ConvertToString(const CByteBuffer& StringBytes);
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------