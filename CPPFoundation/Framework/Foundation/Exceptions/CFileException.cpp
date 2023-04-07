//----------------------------------------------------------------------------------------------------------------------
#include "CFileException.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CFileException::CFileException(void)
		: CException(""), MErrorCode(NO_FILE_ERROR)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CFileException::CFileException(const CString& Message, const CFileException& Exception)
		: CException(Message,Exception), MErrorCode(Exception.GetErrorCode())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CFileException::CFileException(const CString& Message, const CException& Exception)
		: CException(Message,Exception), MErrorCode(NO_FILE_ERROR)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CFileException::CFileException(const CString& Message, int32 ErrorCode)
		: CException(GetFileMessage(Message,ErrorCode)), MErrorCode(ErrorCode)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CFileException::CFileException(CString&& Message, int32 ErrorCode)
		: CException(GetFileMessage(FUNCTION_MOVE(Message),ErrorCode)), MErrorCode(ErrorCode)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CFileException::CFileException(const exception& Exception, int32 ErrorCode)
		: CException(Exception), MErrorCode(ErrorCode)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CFileException::CFileException(const CString& Message, const exception& Exception, int32 ErrorCode)
		: CException(GetFileMessage(Message,ErrorCode),Exception), MErrorCode(ErrorCode)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CFileException::CFileException(const CFileException& Other)
		: CException(Other), MErrorCode(Other.MErrorCode)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CFileException::CFileException(CFileException&& Other) noexcept
		: CException(FUNCTION_MOVE(Other)), MErrorCode(Other.MErrorCode)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CFileException::~CFileException(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CFileException& CFileException::operator=(const CFileException& Other)
	{
		CException::operator=(Other);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CFileException& CFileException::operator=(CFileException&& Other) noexcept
	{
		CException::operator=(FUNCTION_MOVE(Other));

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CFileException::GetFileMessage(const CString& Message, int32 ErrorCode)
	{
		CString													NewMessage=Message;

		if (ErrorCode!=NO_FILE_ERROR)
		{
			if (NewMessage.IsEmpty()==false)
			{
				NewMessage+=" ";
			}

			NewMessage+=CString::Format("ERROR MESSAGE [",CException::GetErrorCodeMessage(ErrorCode),"] ERROR CODE [",ErrorCode,"] !");
		}

		return(NewMessage);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CFileException::GetFileMessage(CString&& Message, int32 ErrorCode)
	{
		CString													NewMessage(FUNCTION_MOVE(Message));

		if (ErrorCode!=NO_FILE_ERROR)
		{
			if (NewMessage.IsEmpty()==false)
			{
				NewMessage+=" ";
			}

			NewMessage+=CString::Format("ERROR MESSAGE [",CException::GetErrorCodeMessage(ErrorCode),"] ERROR CODE [",ErrorCode,"] !");
		}

		return(NewMessage);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int32 CFileException::GetErrorCode(void) const noexcept
	{
		return(MErrorCode);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------