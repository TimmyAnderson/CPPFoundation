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
	class CCommunicationException : public CException
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CCommunicationException& operator=(const CCommunicationException& Other);
			CCommunicationException& operator=(CCommunicationException&& Other) noexcept;

		public:
			CCommunicationException(void);
			CCommunicationException(const CString& Message);
			CCommunicationException(CString&& Message);
			CCommunicationException(const std::exception& Exception);
			CCommunicationException(const CString& Message, const std::exception& Exception);
			CCommunicationException(const CString& Message, const CException& Exception);
			CCommunicationException(const CCommunicationException& Other);
			CCommunicationException(CCommunicationException&& Other) noexcept;
			virtual ~CCommunicationException(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------