//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CByteBuffer.h>
#include "CRC4Key.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CRC4 final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CRC4Key												MKey;

		private:
			uint8 EncryptDecryptLoop(CArray<uint8,256>& Permutation, uint8& Pointer1, uint8& Pointer2, uint8 Input);
			CByteBuffer EncryptDecrypt(const CByteBuffer& InputData);

		public:
			CByteBuffer Encrypt(const CByteBuffer& RawData);
			CByteBuffer Decrypt(const CByteBuffer& EncryptedData);

		public:
			CRC4(const CByteBuffer& Password);
			virtual ~CRC4(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------