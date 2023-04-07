//----------------------------------------------------------------------------------------------------------------------
#include "CEncryptionAlgorithmParameterID.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmParameterID::CEncryptionAlgorithmParameterID(void)
		: CID(CID::CreateID())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmParameterID::CEncryptionAlgorithmParameterID(const CString& ID)
		: CID(ID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmParameterID::CEncryptionAlgorithmParameterID(CString&& ID)
		: CID(FUNCTION_MOVE(ID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmParameterID::CEncryptionAlgorithmParameterID(CCSPString ID)
		: CID(ID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmParameterID::CEncryptionAlgorithmParameterID(const CEncryptionAlgorithmParameterID& Other)
		: CID(Other)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmParameterID::CEncryptionAlgorithmParameterID(CEncryptionAlgorithmParameterID&& Other) noexcept
		: CID(FUNCTION_MOVE(Other))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmParameterID::~CEncryptionAlgorithmParameterID(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmParameterID& CEncryptionAlgorithmParameterID::operator=(const CEncryptionAlgorithmParameterID& Other)
	{
		CID::operator=(Other);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmParameterID& CEncryptionAlgorithmParameterID::operator=(CEncryptionAlgorithmParameterID&& Other) noexcept
	{
		CID::operator=(FUNCTION_MOVE(Other));

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------