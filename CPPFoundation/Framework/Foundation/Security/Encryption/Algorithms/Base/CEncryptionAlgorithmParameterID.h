//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Miscellaneous/CID.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CEncryptionAlgorithmParameterID final : public CID
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CEncryptionAlgorithmParameterID& operator=(const CEncryptionAlgorithmParameterID& Other);
			CEncryptionAlgorithmParameterID& operator=(CEncryptionAlgorithmParameterID&& Other) noexcept;

		public:
			CEncryptionAlgorithmParameterID(void);
			CEncryptionAlgorithmParameterID(const CString& ID);
			CEncryptionAlgorithmParameterID(CString&& ID);
			CEncryptionAlgorithmParameterID(CCSPString ID);
			CEncryptionAlgorithmParameterID(const CEncryptionAlgorithmParameterID& Other);
			CEncryptionAlgorithmParameterID(CEncryptionAlgorithmParameterID&& Other) noexcept;
			virtual ~CEncryptionAlgorithmParameterID(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------