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
	class CUnknownException final : public CException
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CUnknownException& operator=(const CUnknownException& Other);
			CUnknownException& operator=(CUnknownException&& Other) noexcept;

		public:
			CUnknownException(void);
			CUnknownException(const CString& Message);
			CUnknownException(CString&& Message);
			CUnknownException(const std::exception& Exception);
			CUnknownException(const CString& Message, const std::exception& Exception);
			CUnknownException(const CString& Message, const CException& Exception);
			CUnknownException(const CUnknownException& Other);
			CUnknownException(CUnknownException&& Other) noexcept;
			virtual ~CUnknownException(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------