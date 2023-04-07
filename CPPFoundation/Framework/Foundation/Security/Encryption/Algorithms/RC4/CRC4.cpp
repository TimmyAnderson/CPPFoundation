//----------------------------------------------------------------------------------------------------------------------
#include "CRC4.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CRC4::CRC4(const CByteBuffer& Password)
		: MKey(Password)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CRC4::~CRC4(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	uint8 CRC4::EncryptDecryptLoop(CArray<uint8,256>& Permutation, uint8& Pointer1, uint8& Pointer2, uint8 Input)
	{
		static const uint8										MASK=0xFF;

		uint8													Value1=0;
		uint8													Value2=0;

		Pointer1=(static_cast<uint8>(Pointer1+1) & MASK);

		Value1=Permutation[Pointer1];

		Pointer2=(static_cast<uint8>(Value1+Pointer2) & MASK);

		Value2=Permutation[Pointer2];

		Permutation[Pointer1]=Value2;

		Permutation[Pointer2]=Value1;

		uint8													Result=static_cast<uint8>(Permutation[(Value1+Value2) & MASK] ^ Input);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CRC4::EncryptDecrypt(const CByteBuffer& InputData)
	{
		static const Size										STEP=8;
		static const Size										SHIFT=3;
		static const Size										MASK=0x07;

		CByteBuffer												OutputData;
		CArray<uint8,256>&										Permutation=MKey.GetPermutation();
		uint8													Pointer1=MKey.GetPointer1();
		uint8													Pointer2=MKey.GetPointer2();
		Size													DataIndex=0;
		Size													Index=0;

		OutputData.Resize(InputData.GetLength());

		Index=(InputData.GetLength() >> SHIFT);

		if (Index!=0)
		{
			for(;;)
			{
				OutputData[DataIndex+0]=EncryptDecryptLoop(Permutation,Pointer1,Pointer2,InputData[DataIndex+0]);
				OutputData[DataIndex+1]=EncryptDecryptLoop(Permutation,Pointer1,Pointer2,InputData[DataIndex+1]);
				OutputData[DataIndex+2]=EncryptDecryptLoop(Permutation,Pointer1,Pointer2,InputData[DataIndex+2]);
				OutputData[DataIndex+3]=EncryptDecryptLoop(Permutation,Pointer1,Pointer2,InputData[DataIndex+3]);
				OutputData[DataIndex+4]=EncryptDecryptLoop(Permutation,Pointer1,Pointer2,InputData[DataIndex+4]);
				OutputData[DataIndex+5]=EncryptDecryptLoop(Permutation,Pointer1,Pointer2,InputData[DataIndex+5]);
				OutputData[DataIndex+6]=EncryptDecryptLoop(Permutation,Pointer1,Pointer2,InputData[DataIndex+6]);
				OutputData[DataIndex+7]=EncryptDecryptLoop(Permutation,Pointer1,Pointer2,InputData[DataIndex+7]);

				DataIndex+=STEP;

				if (--Index==0)
				{
					break;
				}
			}
		}

		Index=(InputData.GetLength() & MASK);

		if (Index!=0)
		{
			for(;;)
			{
				OutputData[DataIndex+0]=EncryptDecryptLoop(Permutation,Pointer1,Pointer2,InputData[DataIndex+0]);

				if (--Index==0)
				{
					break;
				}

				OutputData[DataIndex+1]=EncryptDecryptLoop(Permutation,Pointer1,Pointer2,InputData[DataIndex+1]);

				if (--Index==0)
				{
					break;
				}

				OutputData[DataIndex+2]=EncryptDecryptLoop(Permutation,Pointer1,Pointer2,InputData[DataIndex+2]);

				if (--Index==0)
				{
					break;
				}

				OutputData[DataIndex+3]=EncryptDecryptLoop(Permutation,Pointer1,Pointer2,InputData[DataIndex+3]);

				if (--Index==0)
				{
					break;
				}

				OutputData[DataIndex+4]=EncryptDecryptLoop(Permutation,Pointer1,Pointer2,InputData[DataIndex+4]);

				if (--Index==0)
				{
					break;
				}

				OutputData[DataIndex+5]=EncryptDecryptLoop(Permutation,Pointer1,Pointer2,InputData[DataIndex+5]);

				if (--Index==0)
				{
					break;
				}

				OutputData[DataIndex+6]=EncryptDecryptLoop(Permutation,Pointer1,Pointer2,InputData[DataIndex+6]);

				if (--Index==0)
				{
					break;
				}
			}
		}

		MKey.SetPointer1(Pointer1);
		MKey.SetPointer2(Pointer2);

		return(OutputData);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CRC4::Encrypt(const CByteBuffer& RawData)
	{
		return(EncryptDecrypt(RawData));
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CRC4::Decrypt(const CByteBuffer& EncryptedData)
	{
		return(EncryptDecrypt(EncryptedData));
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------