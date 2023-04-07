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
	class CNullPointerException final : public CException
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CNullPointerException& operator=(const CNullPointerException& Other);
			CNullPointerException& operator=(CNullPointerException&& Other) noexcept;

		public:
			CNullPointerException(void);
			CNullPointerException(const CString& Message);
			CNullPointerException(CString&& Message);
			CNullPointerException(const std::exception& Exception);
			CNullPointerException(const CString& Message, const std::exception& Exception);
			CNullPointerException(const CString& Message, const CException& Exception);
			CNullPointerException(const CNullPointerException& Other);
			CNullPointerException(CNullPointerException&& Other) noexcept;
			virtual ~CNullPointerException(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------