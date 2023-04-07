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
	class CArgumentException final : public CException
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CArgumentException& operator=(const CArgumentException& Other);
			CArgumentException& operator=(CArgumentException&& Other) noexcept;

		public:
			CArgumentException(void);
			CArgumentException(const CString& Message);
			CArgumentException(CString&& Message);
			CArgumentException(const std::exception& Exception);
			CArgumentException(const CString& Message, const std::exception& Exception);
			CArgumentException(const CString& Message, const CException& Exception);
			CArgumentException(const CArgumentException& Other);
			CArgumentException(CArgumentException&& Other) noexcept;
			virtual ~CArgumentException(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------