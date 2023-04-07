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
	class CValueOutOfRangeException final : public CException
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CValueOutOfRangeException& operator=(const CValueOutOfRangeException& Other);
			CValueOutOfRangeException& operator=(CValueOutOfRangeException&& Other) noexcept;

		public:
			CValueOutOfRangeException(void);
			CValueOutOfRangeException(const CString& Message);
			CValueOutOfRangeException(CString&& Message);
			CValueOutOfRangeException(const std::exception& Exception);
			CValueOutOfRangeException(const CString& Message, const std::exception& Exception);
			CValueOutOfRangeException(const CString& Message, const CException& Exception);
			CValueOutOfRangeException(const CValueOutOfRangeException& Other);
			CValueOutOfRangeException(CValueOutOfRangeException&& Other) noexcept;
			virtual ~CValueOutOfRangeException(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------