//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Security/Encryption/Algorithms/Base/CEncryptionAlgorithm.h>
#include "CEncryptionAlgorithmConfigurationNoEncryption.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CEncryptionAlgorithmNoEncryption final : public CEncryptionAlgorithm
	{
//----------------------------------------------------------------------------------------------------------------------
		protected:
			virtual CByteBuffer InternalEncrypt(const CByteBuffer& RawData, CEncryptionAlgorithmParameterCollection& Parameters) override;
			virtual CByteBuffer InternalDecrypt(const CByteBuffer& EncryptedData, CEncryptionAlgorithmParameterCollection& Parameters) override;

		public:
			CEncryptionAlgorithmNoEncryption(CCSPEncryptionAlgorithmConfigurationNoEncryption Configuration);
			virtual ~CEncryptionAlgorithmNoEncryption(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPEncryptionAlgorithmNoEncryption=CSharedPointer<CEncryptionAlgorithmNoEncryption>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------