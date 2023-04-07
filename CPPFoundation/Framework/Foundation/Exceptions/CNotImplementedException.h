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
	class CNotImplementedException final : public CException
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CNotImplementedException& operator=(const CNotImplementedException& Other);
			CNotImplementedException& operator=(CNotImplementedException&& Other) noexcept;

		public:
			CNotImplementedException(void);
			CNotImplementedException(const CString& Message);
			CNotImplementedException(CString&& Message);
			CNotImplementedException(const std::exception& Exception);
			CNotImplementedException(const CString& Message, const std::exception& Exception);
			CNotImplementedException(const CString& Message, const CException& Exception);
			CNotImplementedException(const CNotImplementedException& Other);
			CNotImplementedException(CNotImplementedException&& Other) noexcept;
			virtual ~CNotImplementedException(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------