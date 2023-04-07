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
	class CInvalidCastException final : public CException
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CInvalidCastException& operator=(const CInvalidCastException& Other);
			CInvalidCastException& operator=(CInvalidCastException&& Other) noexcept;

		public:
			CInvalidCastException(void);
			CInvalidCastException(const CString& Message);
			CInvalidCastException(CString&& Message);
			CInvalidCastException(const std::exception& Exception);
			CInvalidCastException(const CString& Message, const std::exception& Exception);
			CInvalidCastException(const CString& Message, const CException& Exception);
			CInvalidCastException(const CInvalidCastException& Other);
			CInvalidCastException(CInvalidCastException&& Other) noexcept;
			virtual ~CInvalidCastException(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------