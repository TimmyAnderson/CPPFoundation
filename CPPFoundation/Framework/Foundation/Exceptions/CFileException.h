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
	class CFileException final : public CException
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			static const int32 									NO_FILE_ERROR=0;

		private:
			int32												MErrorCode;

		public:
			CFileException& operator=(const CFileException& Other);
			CFileException& operator=(CFileException&& Other) noexcept;

		private:
			static CString GetFileMessage(const CString& Message, int32 ErrorCode);
			static CString GetFileMessage(CString&& Message, int32 ErrorCode);

		public:
			int32 GetErrorCode(void) const noexcept;

		public:
			CFileException(void);
			CFileException(const CString& Message, const CFileException& Exception);
			CFileException(const CString& Message, const CException& Exception);
			CFileException(const CString& Message, int32 ErrorCode=NO_FILE_ERROR);
			CFileException(CString&& Message, int32 ErrorCode=NO_FILE_ERROR);
			CFileException(const std::exception& Exception, int32 ErrorCode=NO_FILE_ERROR);
			CFileException(const CString& Message, const std::exception& Exception, int32 ErrorCode=NO_FILE_ERROR);
			CFileException(const CFileException& Other);
			CFileException(CFileException&& Other) noexcept;
			virtual ~CFileException(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------