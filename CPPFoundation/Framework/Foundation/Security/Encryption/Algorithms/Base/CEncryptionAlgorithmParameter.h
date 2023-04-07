//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CEncryptionAlgorithmParameterID.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CEncryptionAlgorithmParameter : public CPPFoundation::Foundation::CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CEncryptionAlgorithmParameterID						MParameterID;

		public:
			const CEncryptionAlgorithmParameterID& GetParameterID(void) const noexcept;

		public:
			CEncryptionAlgorithmParameter(const CEncryptionAlgorithmParameterID& ParameterID);
			virtual ~CEncryptionAlgorithmParameter(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPEncryptionAlgorithmParameter=CPPFoundation::Foundation::CSharedPointer<CEncryptionAlgorithmParameter>;
	using														CCSPEncryptionAlgorithmParameter=CPPFoundation::Foundation::CSharedPointer<const CEncryptionAlgorithmParameter>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------