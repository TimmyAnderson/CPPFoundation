//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Security/Encryption/Algorithms/Base/CEncryptionAlgorithm.h>
#include <Framework/Foundation/Time/CDateTime.h>
#include "CEncryptionAlgorithmConfigurationRC4.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CEncryptionAlgorithmRC4 final : public CEncryptionAlgorithm
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			static const Size									MINIMUM_LENGTH_FOR_TIMEOUT=6;

		private:
			CByteBuffer											MPassword;
			bool												MUseTimestamps;
			CTimeout											MValidityTimeout;
			Size												MSaltLength;
			Size												MRandomKeyLength;

		private:
			CByteBuffer EncryptRC4(const CByteBuffer& RawData, const CByteBuffer& Password);
			CByteBuffer DecryptRC4(const CByteBuffer& EncryptedData, const CByteBuffer& Password);

		private:
			CByteBuffer EncryptWithTimestamp(const CByteBuffer& RawData, const CDateTime& Time, Size SaltLength, Size RandomKeyLength);
			CByteBuffer DecryptWithTimestamp(const CByteBuffer& EncryptedData, CDateTime& Time, Size SaltLength, Size RandomKeyLength);

		protected:
			virtual CByteBuffer InternalEncrypt(const CByteBuffer& RawData, CEncryptionAlgorithmParameterCollection& Parameters) override;
			virtual CByteBuffer InternalDecrypt(const CByteBuffer& EncryptedData, CEncryptionAlgorithmParameterCollection& Parameters) override;

		public:
			CEncryptionAlgorithmRC4(CCSPEncryptionAlgorithmConfigurationRC4 Configuration);
			virtual ~CEncryptionAlgorithmRC4(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPEncryptionAlgorithmRC4=CSharedPointer<CEncryptionAlgorithmRC4>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------