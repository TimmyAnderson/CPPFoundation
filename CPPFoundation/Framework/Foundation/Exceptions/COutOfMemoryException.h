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
	class COutOfMemoryException final : public CException
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			COutOfMemoryException& operator=(const COutOfMemoryException& Other);
			COutOfMemoryException& operator=(COutOfMemoryException&& Other) noexcept;

		public:
			COutOfMemoryException(void);
			COutOfMemoryException(const CString& Message);
			COutOfMemoryException(CString&& Message);
			COutOfMemoryException(const std::exception& Exception);
			COutOfMemoryException(const CString& Message, const std::exception& Exception);
			COutOfMemoryException(const CString& Message, const CException& Exception);
			COutOfMemoryException(const COutOfMemoryException& Other);
			COutOfMemoryException(COutOfMemoryException&& Other) noexcept;
			virtual ~COutOfMemoryException(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------