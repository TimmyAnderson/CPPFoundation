//----------------------------------------------------------------------------------------------------------------------
#include "CEncryptionAlgorithmConfigurationNoEncryption.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	const CString												CEncryptionAlgorithmConfigurationNoEncryption::ALGORITHM_NAME="NO ENCRYPTION";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmConfigurationNoEncryption::CEncryptionAlgorithmConfigurationNoEncryption(void)
		: CEncryptionAlgorithmConfiguration(ALGORITHM_NAME)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmConfigurationNoEncryption::~CEncryptionAlgorithmConfigurationNoEncryption(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------