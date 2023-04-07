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
	class CSystemException final : public CException
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CSystemException& operator=(const CSystemException& Other);
			CSystemException& operator=(CSystemException&& Other) noexcept;

		public:
			CSystemException(void);
			CSystemException(const CString& Message);
			CSystemException(CString&& Message);
			CSystemException(const std::exception& Exception);
			CSystemException(const CString& Message, const std::exception& Exception);
			CSystemException(const CString& Message, const CException& Exception);
			CSystemException(const CSystemException& Other);
			CSystemException(CSystemException&& Other) noexcept;
			virtual ~CSystemException(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------