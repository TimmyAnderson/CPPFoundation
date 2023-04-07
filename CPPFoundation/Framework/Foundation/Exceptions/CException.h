//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Strings/CString.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CException : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CString												MMessage;

		public:
			CException& operator=(const CString& Message);
			CException& operator=(CString&& Message);
			CException& operator=(const std::exception& Exception);
			CException& operator=(const CException& Other);
			CException& operator=(CException&& Other) noexcept;

		private:
			static CString GetExceptionMessage(const std::exception& Exception);
			static CString GetExceptionMessage(const CException& Exception);

		public:
			static CString GetErrorCodeMessage(int32 ErrorCode);

		public:
			const CString& GetMessage(void) const;
			virtual CString ToString(void) const override;

		public:
			CException(void);
			CException(const CString& Message);
			CException(CString&& Message);
			CException(const std::exception& Exception);
			CException(const CString& Message, const std::exception& Exception);
			CException(const CString& Message, const CException& Exception);
			CException(const CException& Other);
			CException(CException&& Other) noexcept;
			virtual ~CException(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	std::ostream& operator<<(std::ostream& Stream, const CException& Value);
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------