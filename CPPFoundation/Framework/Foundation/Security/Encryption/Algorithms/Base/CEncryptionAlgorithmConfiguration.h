//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CEncryptionAlgorithmConfiguration.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CEncryptionAlgorithmConfiguration : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CString												MAlgorithmName;

		public:
			const CString& GetAlgorithmName(void) const noexcept;

		public:
			CEncryptionAlgorithmConfiguration(const CString& AlgorithmName);
			virtual ~CEncryptionAlgorithmConfiguration(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPEncryptionAlgorithmConfiguration=CSharedPointer<CEncryptionAlgorithmConfiguration>;
	using														CCSPEncryptionAlgorithmConfiguration=CSharedPointer<const CEncryptionAlgorithmConfiguration>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------