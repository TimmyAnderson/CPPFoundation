//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CByteBuffer.h>
#include <Framework/Foundation/Security/Encryption/Algorithms/Base/CEncryptionAlgorithmConfiguration.h>
#include <Framework/Foundation/Time/CTimeout.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CEncryptionAlgorithmConfigurationRC4 final : public CEncryptionAlgorithmConfiguration
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			static const CString								ALGORITHM_NAME;
			static const Size									DEFAULT_SALT_LENGTH=6;
			static const Size									DEFAULT_RANDOM_KEY_LENGTH=2;

		private:
			CByteBuffer											MPassword;
			bool												MUseTimestamps;
			CTimeout											MValidityTimeout;
			Size												MSaltLength;
			Size												MRandomKeyLength;

		public:
			const CByteBuffer& GetPassword(void) const noexcept;
			bool GetUseTimestamps(void) const noexcept;
			const CTimeout& GetValidityTimeout(void) const noexcept;
			Size GetSaltLength(void) const noexcept;
			Size GetRandomKeyLength(void) const noexcept;

		public:
			CEncryptionAlgorithmConfigurationRC4(const CByteBuffer& Password, bool UseTimestamps, const CTimeout& ValidityTimeout, Size SaltLength=DEFAULT_SALT_LENGTH, Size RandomKeyLength=DEFAULT_RANDOM_KEY_LENGTH);
			virtual ~CEncryptionAlgorithmConfigurationRC4(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPEncryptionAlgorithmConfigurationRC4=CSharedPointer<CEncryptionAlgorithmConfigurationRC4>;
	using														CCSPEncryptionAlgorithmConfigurationRC4=CSharedPointer<const CEncryptionAlgorithmConfigurationRC4>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------