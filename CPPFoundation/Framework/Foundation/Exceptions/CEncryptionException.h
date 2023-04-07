//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CException.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CEncryptionException final : public CException
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CEncryptionException& operator=(const CEncryptionException& Other);
			CEncryptionException& operator=(CEncryptionException&& Other) noexcept;

		public:
			CEncryptionException(void);
			CEncryptionException(const CString& Message);
			CEncryptionException(CString&& Message);
			CEncryptionException(const std::exception& Exception);
			CEncryptionException(const CString& Message, const std::exception& Exception);
			CEncryptionException(const CString& Message, const CException& Exception);
			CEncryptionException(const CEncryptionException& Other);
			CEncryptionException(CEncryptionException&& Other) noexcept;
			virtual ~CEncryptionException(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------