//----------------------------------------------------------------------------------------------------------------------
#include "CEncryptionAlgorithmConfigurationRC4.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	const CString												CEncryptionAlgorithmConfigurationRC4::ALGORITHM_NAME="RC4";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmConfigurationRC4::CEncryptionAlgorithmConfigurationRC4(const CByteBuffer& Password, bool UseTimestamps, const CTimeout& ValidityTimeout, Size SaltLength, Size RandomKeyLength)
		: CEncryptionAlgorithmConfiguration(ALGORITHM_NAME), MPassword(Password), MUseTimestamps(UseTimestamps), MValidityTimeout(ValidityTimeout), MSaltLength(SaltLength), MRandomKeyLength(RandomKeyLength)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmConfigurationRC4::~CEncryptionAlgorithmConfigurationRC4(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CByteBuffer& CEncryptionAlgorithmConfigurationRC4::GetPassword(void) const noexcept
	{
		return(MPassword);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CEncryptionAlgorithmConfigurationRC4::GetUseTimestamps(void) const noexcept
	{
		return(MUseTimestamps);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CTimeout& CEncryptionAlgorithmConfigurationRC4::GetValidityTimeout(void) const noexcept
	{
		return(MValidityTimeout);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CEncryptionAlgorithmConfigurationRC4::GetSaltLength(void) const noexcept
	{
		return(MSaltLength);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CEncryptionAlgorithmConfigurationRC4::GetRandomKeyLength(void) const noexcept
	{
		return(MRandomKeyLength);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------