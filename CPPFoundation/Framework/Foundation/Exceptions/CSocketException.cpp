//----------------------------------------------------------------------------------------------------------------------
#include "CSocketException.h"
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
	CSocketException::CSocketException(void)
		: CCommunicationException(""), MErrorCode(NO_SOCKET_ERROR), MSocketExceptionCode(ESocketExceptionCode::E_UNKNOWN)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketException::CSocketException(const CString& Message, const CSocketException& Exception)
		: CCommunicationException(Message,Exception), MErrorCode(Exception.GetErrorCode()), MSocketExceptionCode(Exception.GetSocketExceptionCode())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketException::CSocketException(const CString& Message, const CException& Exception)
		: CCommunicationException(Message,Exception), MErrorCode(NO_SOCKET_ERROR), MSocketExceptionCode(ESocketExceptionCode::E_UNKNOWN)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketException::CSocketException(const CString& Message, int32 ErrorCode, ESocketExceptionCode SocketExceptionCode)
		: CCommunicationException(GetSocketMessage(Message,ErrorCode,SocketExceptionCode)), MErrorCode(ErrorCode), MSocketExceptionCode(SocketExceptionCode)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketException::CSocketException(CString&& Message, int32 ErrorCode, ESocketExceptionCode SocketExceptionCode)
		: CCommunicationException(GetSocketMessage(FUNCTION_MOVE(Message),ErrorCode,SocketExceptionCode)), MErrorCode(ErrorCode), MSocketExceptionCode(SocketExceptionCode)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketException::CSocketException(const exception& Exception, int32 ErrorCode, ESocketExceptionCode SocketExceptionCode)
		: CCommunicationException(Exception), MErrorCode(ErrorCode), MSocketExceptionCode(SocketExceptionCode)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketException::CSocketException(const CString& Message, const exception& Exception, int32 ErrorCode, ESocketExceptionCode SocketExceptionCode)
		: CCommunicationException(GetSocketMessage(Message,ErrorCode,SocketExceptionCode),Exception), MErrorCode(ErrorCode), MSocketExceptionCode(SocketExceptionCode)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketException::CSocketException(const CSocketException& Other)
		: CCommunicationException(Other), MErrorCode(Other.MErrorCode), MSocketExceptionCode(Other.MSocketExceptionCode)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketException::CSocketException(CSocketException&& Other) noexcept
		: CCommunicationException(FUNCTION_MOVE(Other)), MErrorCode(Other.MErrorCode), MSocketExceptionCode(Other.MSocketExceptionCode)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketException::~CSocketException(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketException& CSocketException::operator=(const CSocketException& Other)
	{
		CCommunicationException::operator=(Other);

		MErrorCode=Other.MErrorCode;
		MSocketExceptionCode=Other.MSocketExceptionCode;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketException& CSocketException::operator=(CSocketException&& Other) noexcept
	{
		CCommunicationException::operator=(FUNCTION_MOVE(Other));

		MErrorCode=Other.MErrorCode;
		MSocketExceptionCode=Other.MSocketExceptionCode;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketException::GetSocketMessage(const CString& Message, int32 ErrorCode, ESocketExceptionCode SocketExceptionCode)
	{
		CString													NewMessage=Message;

		if (ErrorCode!=NO_SOCKET_ERROR)
		{
			if (NewMessage.IsEmpty()==false)
			{
				NewMessage+=" ";
			}

			NewMessage+=CString::Format("ERROR MESSAGE [",CException::GetErrorCodeMessage(ErrorCode),"] ERROR CODE [",ErrorCode,"] SOCKET EXCEPTION CODE [",SocketExceptionCode,"] !");
		}

		return(NewMessage);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketException::GetSocketMessage(CString&& Message, int32 ErrorCode, ESocketExceptionCode SocketExceptionCode)
	{
		CString													NewMessage(FUNCTION_MOVE(Message));

		if (ErrorCode!=NO_SOCKET_ERROR)
		{
			if (NewMessage.IsEmpty()==false)
			{
				NewMessage+=" ";
			}

			NewMessage+=CString::Format("ERROR MESSAGE [",CException::GetErrorCodeMessage(ErrorCode),"] ERROR CODE [",ErrorCode,"] SOCKET EXCEPTION CODE [",SocketExceptionCode,"] !");
		}

		return(NewMessage);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int32 CSocketException::GetErrorCode(void) const noexcept
	{
		return(MErrorCode);
	}
//----------------------------------------------------------------------------------------------------------------------
	ESocketExceptionCode CSocketException::GetSocketExceptionCode(void) const noexcept
	{
		return(MSocketExceptionCode);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------