//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CByteBuffer.h>
#include <Framework/Foundation/Exceptions/CEncryptionException.h>
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CEncryptionAlgorithmConfiguration.h"
#include "CEncryptionAlgorithmParameterCollection.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CEncryptionAlgorithm;
//----------------------------------------------------------------------------------------------------------------------
	using														CSPEncryptionAlgorithm=CSharedPointer<CEncryptionAlgorithm>;
	using														CCSPEncryptionAlgorithm=CSharedPointer<const CEncryptionAlgorithm>;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	class CEncryptionAlgorithm : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPEncryptionAlgorithmConfiguration				MConfiguration;

		public:
			static CSPEncryptionAlgorithm CreateAlgorithm(CCSPEncryptionAlgorithmConfiguration Configuration);

		protected:
			virtual CByteBuffer InternalEncrypt(const CByteBuffer& RawData, CEncryptionAlgorithmParameterCollection& Parameters)=0;
			virtual CByteBuffer InternalDecrypt(const CByteBuffer& EncryptedData, CEncryptionAlgorithmParameterCollection& Parameters)=0;

		public:
			virtual CString ToString(void) const override;
			CCSPEncryptionAlgorithmConfiguration GetConfiguration(void) const noexcept;
			CByteBuffer Encrypt(const CByteBuffer& RawData, CEncryptionAlgorithmParameterCollection& Parameters);
			CByteBuffer Decrypt(const CByteBuffer& EncryptedData, CEncryptionAlgorithmParameterCollection& Parameters);

		public:
			CEncryptionAlgorithm(CCSPEncryptionAlgorithmConfiguration Configuration);
			virtual ~CEncryptionAlgorithm(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------