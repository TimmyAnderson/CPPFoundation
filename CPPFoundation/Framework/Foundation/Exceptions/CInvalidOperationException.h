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
	class CInvalidOperationException final : public CException
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CInvalidOperationException& operator=(const CInvalidOperationException& Other);
			CInvalidOperationException& operator=(CInvalidOperationException&& Other) noexcept;

		public:
			CInvalidOperationException(void);
			CInvalidOperationException(const CString& Message);
			CInvalidOperationException(CString&& Message);
			CInvalidOperationException(const std::exception& Exception);
			CInvalidOperationException(const CString& Message, const std::exception& Exception);
			CInvalidOperationException(const CString& Message, const CException& Exception);
			CInvalidOperationException(const CInvalidOperationException& Other);
			CInvalidOperationException(CInvalidOperationException&& Other) noexcept;
			virtual ~CInvalidOperationException(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------