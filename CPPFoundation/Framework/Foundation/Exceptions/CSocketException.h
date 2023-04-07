//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CCommunicationException.h"
#include "ESocketExceptionCode.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketException final : public CCommunicationException
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			static const int32									NO_SOCKET_ERROR=0;

		private:
			int32												MErrorCode;
			ESocketExceptionCode								MSocketExceptionCode;

		public:
			CSocketException& operator=(const CSocketException& Other);
			CSocketException& operator=(CSocketException&& Other) noexcept;

		private:
			static CString GetSocketMessage(const CString& Message, int32 ErrorCode, ESocketExceptionCode SocketExceptionCode);
			static CString GetSocketMessage(CString&& Message, int32 ErrorCode, ESocketExceptionCode SocketExceptionCode);

		public:
			int32 GetErrorCode(void) const noexcept;
			ESocketExceptionCode GetSocketExceptionCode(void) const noexcept;

		public:
			CSocketException(void);
			CSocketException(const CString& Message, const CSocketException& Exception);
			CSocketException(const CString& Message, const CException& Exception);
			CSocketException(const CString& Message, int32 ErrorCode=NO_SOCKET_ERROR, ESocketExceptionCode SocketExceptionCode=ESocketExceptionCode::E_UNKNOWN);
			CSocketException(CString&& Message, int32 ErrorCode=NO_SOCKET_ERROR, ESocketExceptionCode SocketExceptionCode=ESocketExceptionCode::E_UNKNOWN);
			CSocketException(const std::exception& Exception, int32 ErrorCode=NO_SOCKET_ERROR, ESocketExceptionCode SocketExceptionCode=ESocketExceptionCode::E_UNKNOWN);
			CSocketException(const CString& Message, const std::exception& Exception, int32 ErrorCode=NO_SOCKET_ERROR, ESocketExceptionCode SocketExceptionCode=ESocketExceptionCode::E_UNKNOWN);
			CSocketException(const CSocketException& Other);
			CSocketException(CSocketException&& Other) noexcept;
			virtual ~CSocketException(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------