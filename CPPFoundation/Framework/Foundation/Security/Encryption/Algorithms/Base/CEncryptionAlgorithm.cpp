//----------------------------------------------------------------------------------------------------------------------
#include "CEncryptionAlgorithm.h"
#include <Framework/Foundation/Security/Encryption/Algorithms/NoEncryption/CEncryptionAlgorithmNoEncryption.h>
#include <Framework/Foundation/Security/Encryption/Algorithms/RC4/CEncryptionAlgorithmRC4.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithm::CEncryptionAlgorithm(CCSPEncryptionAlgorithmConfiguration Configuration)
		: MConfiguration(Configuration)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithm::~CEncryptionAlgorithm(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSPEncryptionAlgorithm CEncryptionAlgorithm::CreateAlgorithm(CCSPEncryptionAlgorithmConfiguration Configuration)
	{
		if (Configuration.IsTypeOfAsConst<CEncryptionAlgorithmConfigurationNoEncryption>()==true)
		{
			return(CSPEncryptionAlgorithm(new CEncryptionAlgorithmNoEncryption(CSPEncryptionAlgorithmConfigurationNoEncryption(new CEncryptionAlgorithmConfigurationNoEncryption()))));
		}
		else if (Configuration.IsTypeOfAsConst<CEncryptionAlgorithmConfigurationRC4>()==true)
		{
			CCSPEncryptionAlgorithmConfigurationRC4				TypedConfiguration=Configuration.DynamicCastAsConst<CEncryptionAlgorithmConfigurationRC4>();

			return(CSPEncryptionAlgorithm(new CEncryptionAlgorithmRC4(TypedConfiguration)));
		}
		else
		{
			throw(CEncryptionException(CString::Format("UNSUPPORTED ENCRYPTION ALGORITHM [",Configuration,"] !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CEncryptionAlgorithm::ToString(void) const
	{
		return(MConfiguration->GetAlgorithmName());
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPEncryptionAlgorithmConfiguration CEncryptionAlgorithm::GetConfiguration(void) const noexcept
	{
		return(MConfiguration);
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CEncryptionAlgorithm::Encrypt(const CByteBuffer& RawData, CEncryptionAlgorithmParameterCollection& Parameters)
	{
		try
		{
			return(InternalEncrypt(RawData,Parameters));
		}
		catch(const CEncryptionException& E)
		{
			throw(CEncryptionException(CString::Format("ENCRYPTION ALGORITHM [",MConfiguration->GetAlgorithmName(),"] FAILED to ENCRYPT DATA [",RawData.ToString(),"] ! EXCEPTION [",E.ToString(),"] !")));
		}
		catch(const CException& E)
		{
			throw(CEncryptionException(CString::Format("ENCRYPTION ALGORITHM [",MConfiguration->GetAlgorithmName(),"] FAILED to ENCRYPT DATA [",RawData.ToString(),"] ! UNEXPECTED EXCEPTION [",E.ToString(),"] !")));
		}
		catch(...)
		{
			throw(CEncryptionException(CString::Format("ENCRYPTION ALGORITHM [",MConfiguration->GetAlgorithmName(),"] FAILED to ENCRYPT DATA [",RawData.ToString(),"] ! UNEXPECTED UNKNOWN EXCEPTION !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CEncryptionAlgorithm::Decrypt(const CByteBuffer& EncryptedData, CEncryptionAlgorithmParameterCollection& Parameters)
	{
		try
		{
			return(InternalDecrypt(EncryptedData,Parameters));
		}
		catch(const CEncryptionException& E)
		{
			throw(CEncryptionException(CString::Format("ENCRYPTION ALGORITHM [",MConfiguration->GetAlgorithmName(),"] FAILED to DECRYPT DATA [",EncryptedData.ToString(),"] ! EXCEPTION [",E.ToString(),"] !")));
		}
		catch(const CException& E)
		{
			throw(CEncryptionException(CString::Format("ENCRYPTION ALGORITHM [",MConfiguration->GetAlgorithmName(),"] FAILED to DECRYPT DATA [",EncryptedData.ToString(),"] ! UNEXPECTED EXCEPTION [",E.ToString(),"] !")));
		}
		catch(...)
		{
			throw(CEncryptionException(CString::Format("ENCRYPTION ALGORITHM [",MConfiguration->GetAlgorithmName(),"] FAILED to DECRYPT DATA [",EncryptedData.ToString(),"] ! UNEXPECTED UNKNOWN EXCEPTION !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------