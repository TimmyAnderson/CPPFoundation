//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CArray.h>
#include <Framework/Foundation/Collections/CByteBuffer.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CRC4Key final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CArray<uint8,256>									MPermutation;
			uint8												MPointer1;
			uint8												MPointer2;

		private:
			void InitializeKeyLoop(const CByteBuffer& Password, Size Index, Size& Index1, Size& Index2);
			void InitializeKey(const CByteBuffer& Password);

		public:
			CArray<uint8,256>& GetPermutation(void) noexcept;
			uint8 GetPointer1(void) const noexcept;
			void SetPointer1(uint8 Value) noexcept;
			uint8 GetPointer2(void) const noexcept;
			void SetPointer2(uint8 Value) noexcept;

		public:
			CRC4Key(const CByteBuffer& Password);
			virtual ~CRC4Key(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------