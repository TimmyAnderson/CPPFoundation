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
	class CInvalidValueException final : public CException
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CInvalidValueException& operator=(const CInvalidValueException& Other);
			CInvalidValueException& operator=(CInvalidValueException&& Other) noexcept;

		public:
			CInvalidValueException(void);
			CInvalidValueException(const CString& Message);
			CInvalidValueException(CString&& Message);
			CInvalidValueException(const std::exception& Exception);
			CInvalidValueException(const CString& Message, const std::exception& Exception);
			CInvalidValueException(const CString& Message, const CException& Exception);
			CInvalidValueException(const CInvalidValueException& Other);
			CInvalidValueException(CInvalidValueException&& Other) noexcept;
			virtual ~CInvalidValueException(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------