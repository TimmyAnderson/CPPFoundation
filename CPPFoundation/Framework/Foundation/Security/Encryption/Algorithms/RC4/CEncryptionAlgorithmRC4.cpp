//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Mathematics/CMathematics.h>
#include <Framework/Foundation/Parsing/CParserHelper.h>
#include <Framework/Foundation/Security/Encryption/Algorithms/Base/CEncryptionAlgorithmParameterTime.h>
#include "CEncryptionAlgorithmRC4.h"
#include "CRC4.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmRC4::CEncryptionAlgorithmRC4(CCSPEncryptionAlgorithmConfigurationRC4 Configuration)
		: CEncryptionAlgorithm(Configuration), MPassword(Configuration->GetPassword()), MUseTimestamps(Configuration->GetUseTimestamps()), MValidityTimeout(Configuration->GetValidityTimeout()), MSaltLength(Configuration->GetSaltLength()), MRandomKeyLength(Configuration->GetRandomKeyLength())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmRC4::~CEncryptionAlgorithmRC4(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CEncryptionAlgorithmRC4::EncryptRC4(const CByteBuffer& RawData, const CByteBuffer& Password)
	{
		CRC4													RC4(Password);

		return(RC4.Encrypt(RawData));
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CEncryptionAlgorithmRC4::DecryptRC4(const CByteBuffer& EncryptedData, const CByteBuffer& Password)
	{
		CRC4													RC4(Password);

		return(RC4.Decrypt(EncryptedData));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CEncryptionAlgorithmRC4::EncryptWithTimestamp(const CByteBuffer& RawData, const CDateTime& Time, Size SaltLength, Size RandomKeyLength)
    {
		CByteBuffer												Timestamp(sizeof(CDateTime::DateTimeTicks));

		if (SaltLength<MINIMUM_LENGTH_FOR_TIMEOUT)
		{
			SaltLength=MINIMUM_LENGTH_FOR_TIMEOUT;
		}

		CParserHelper::SerializeInt64(Timestamp,Time.GetTicks(),0,EParserEndianness::E_BIG_ENDIAN);

		CRandom<uint8>											Random;

		for(Size Index=Timestamp.GetLength();Index<SaltLength;Index++)
		{
			Timestamp.Add(Random.GetRandomValue());
		}

		CByteBuffer												Encrypt;

		if (Timestamp.GetLength()<SaltLength)
		{
			throw(CEncryptionException(CString::Format("TIMESTAMPT doesn't contain NUMBER of EXPECTED [",RandomKeyLength,"] BYTES !")));
		}

		if (Timestamp.GetLength()<SaltLength)
		{
			throw(CEncryptionException(CString::Format("TIMESTAMPT doesn't contain NUMBER of EXPECTED [",SaltLength,"] BYTES !")));
		}

		Size													TimestampStartIndex=Timestamp.GetLength()-SaltLength;
		Size													TimestampLength=SaltLength-RandomKeyLength;

		if (Timestamp.GetLength()<(TimestampStartIndex+TimestampLength))
		{
			throw(CEncryptionException(CString::Format("TIMESTAMPT doesn't contain NUMBER of EXPECTED [",(TimestampStartIndex+TimestampLength),"] BYTES !")));
		}

		Encrypt.Add(RawData);
		Encrypt.Add(Timestamp.Copy(TimestampStartIndex,TimestampLength));

		CByteBuffer												Password;

		if (RandomKeyLength>0)
		{
			if (Timestamp.GetLength()<RandomKeyLength)
			{
				throw(CEncryptionException(CString::Format("TIMESTAMP doesn't contain NUMBER of EXPECTED [",RandomKeyLength,"] BYTES !")));
			}

			Password=Timestamp.Copy(Timestamp.GetLength()-RandomKeyLength,RandomKeyLength);

			Encrypt=EncryptRC4(Encrypt,Password);
			Encrypt.Add(Password);
		}

		Encrypt=EncryptRC4(Encrypt,MPassword);

		return(Encrypt);
    }
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CEncryptionAlgorithmRC4::DecryptWithTimestamp(const CByteBuffer& EncryptedData, CDateTime& Time, Size SaltLength, Size RandomKeyLength)
    {
		CByteBuffer												Decrypt(DecryptRC4(EncryptedData,MPassword));
		CByteBuffer												Password;

		if (RandomKeyLength>0)
		{
			if (Decrypt.GetLength()<RandomKeyLength)
			{
				throw(CEncryptionException(CString::Format("DECRYPTED DATA doesn't contain NUMBER of EXPECTED [",RandomKeyLength,"] BYTES !")));
			}

			Size												StartIndex=Decrypt.GetLength()-RandomKeyLength;

			Password=Decrypt.Copy(StartIndex,RandomKeyLength);

			Decrypt.Erase(StartIndex,RandomKeyLength);
			Decrypt=DecryptRC4(Decrypt,Password);
		}

		if (SaltLength<MINIMUM_LENGTH_FOR_TIMEOUT)
		{
			SaltLength=MINIMUM_LENGTH_FOR_TIMEOUT;
		}

		Size													TimestampLength=(SaltLength-RandomKeyLength);
		CByteBuffer												Timestamp;

		if (Decrypt.GetLength()<TimestampLength)
		{
			throw(CEncryptionException(CString::Format("DECRYPTED DATA doesn't contain NUMBER of EXPECTED [",TimestampLength,"] BYTES !")));
		}

		Timestamp=Decrypt.Copy(Decrypt.GetLength()-TimestampLength,TimestampLength);
		Timestamp.Add(Password);

		for(Size Index=Timestamp.GetLength();Index<sizeof(CDateTime::DateTimeTicks);Index++)
		{
			Timestamp.Insert(0,0);
		}
		
		Time=CDateTime(CParserHelper::DeserializeInt64(Timestamp,Timestamp.GetLength()-sizeof(CDateTime::DateTimeTicks),EParserEndianness::E_BIG_ENDIAN));

		Size													TimestampStartIndex=Decrypt.GetLength()-TimestampLength;

		Decrypt.Erase(TimestampStartIndex,TimestampLength);

		return(Decrypt);
    }
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CEncryptionAlgorithmRC4::InternalEncrypt(const CByteBuffer& RawData, CEncryptionAlgorithmParameterCollection& Parameters)
	{
		if (MUseTimestamps==false)
		{
			CRC4												RC4(MPassword);

			return(RC4.Encrypt(RawData));
		}
		else
		{
			CDateTime											ActualTime;
			CCSPEncryptionAlgorithmParameterTime				ParameterTime=Parameters.GetParameterByType<CEncryptionAlgorithmParameterTime>(CEncryptionAlgorithmParameterTime::PARAMETER_ID);

			if (ParameterTime!=nullptr)
			{
				ActualTime=ParameterTime->GetTime();
			}
			else
			{
				ActualTime=CDateTime::GetCurrentUTCTime();
			}

			CByteBuffer											EncryptedData=EncryptWithTimestamp(RawData,ActualTime,MSaltLength,MRandomKeyLength);

			return(EncryptedData);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CEncryptionAlgorithmRC4::InternalDecrypt(const CByteBuffer& EncryptedData, CEncryptionAlgorithmParameterCollection& Parameters)
	{
		if (MUseTimestamps==false)
		{
			CRC4												RC4(MPassword);

			return(RC4.Decrypt(EncryptedData));
		}
		else
		{
			CDateTime											ActualTime;
			CCSPEncryptionAlgorithmParameterTime				ParameterTime=Parameters.GetParameterByType<CEncryptionAlgorithmParameterTime>(CEncryptionAlgorithmParameterTime::PARAMETER_ID);

			if (ParameterTime!=nullptr)
			{
				ActualTime=ParameterTime->GetTime();
			}
			else
			{
				ActualTime=CDateTime::GetCurrentUTCTime();
			}

			CDateTime											DecryptedTime;
			CByteBuffer											DecryptedData=DecryptWithTimestamp(EncryptedData,DecryptedTime,MSaltLength,MRandomKeyLength);
			CDateTime::DateTimeTicks							TimeDifference=CMathematics::AbsoluteValueInteger(ActualTime-DecryptedTime);

			if (MValidityTimeout.IsInfinite()==false)
			{
				if (TimeDifference>MValidityTimeout.GetTimeoutInMS())
				{
					throw(CEncryptionException(CString::Format("DECRYPTED DATA contains INVALID TIMESTAMP [",DecryptedTime,"] !")));
				}
			}

	        return(DecryptedData);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------