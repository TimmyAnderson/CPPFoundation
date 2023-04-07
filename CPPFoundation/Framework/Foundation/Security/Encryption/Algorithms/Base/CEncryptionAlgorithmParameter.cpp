//----------------------------------------------------------------------------------------------------------------------
#include "CEncryptionAlgorithmParameter.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmParameter::CEncryptionAlgorithmParameter(const CEncryptionAlgorithmParameterID& ParameterID)
		: MParameterID(ParameterID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmParameter::~CEncryptionAlgorithmParameter(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CEncryptionAlgorithmParameterID& CEncryptionAlgorithmParameter::GetParameterID(void) const noexcept
	{
		return(MParameterID);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------