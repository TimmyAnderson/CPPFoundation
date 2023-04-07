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
	class CParserException final : public CException
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CParserException& operator=(const CParserException& Other);
			CParserException& operator=(CParserException&& Other) noexcept;

		public:
			CParserException(void);
			CParserException(const CString& Message);
			CParserException(CString&& Message);
			CParserException(const std::exception& Exception);
			CParserException(const CString& Message, const std::exception& Exception);
			CParserException(const CString& Message, const CException& Exception);
			CParserException(const CParserException& Other);
			CParserException(CParserException&& Other) noexcept;
			virtual ~CParserException(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------