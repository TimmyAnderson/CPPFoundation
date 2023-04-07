//----------------------------------------------------------------------------------------------------------------------
#include "CInvalidOperationException.h"
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
	CInvalidOperationException::CInvalidOperationException(void)
		: CException("")
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CInvalidOperationException::CInvalidOperationException(const CString& Message)
		: CException(Message)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CInvalidOperationException::CInvalidOperationException(CString&& Message)
		: CException(FUNCTION_MOVE(Message))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CInvalidOperationException::CInvalidOperationException(const exception& Exception)
		: CException(Exception)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CInvalidOperationException::CInvalidOperationException(const CString& Message, const exception& Exception)
		: CException(Message,Exception)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CInvalidOperationException::CInvalidOperationException(const CString& Message, const CException& Exception)
		: CException(Message,Exception)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CInvalidOperationException::CInvalidOperationException(const CInvalidOperationException& Other)
		: CException(Other)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CInvalidOperationException::CInvalidOperationException(CInvalidOperationException&& Other) noexcept
		: CException(FUNCTION_MOVE(Other))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CInvalidOperationException::~CInvalidOperationException(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CInvalidOperationException& CInvalidOperationException::operator=(const CInvalidOperationException& Other)
	{
		CException::operator=(Other);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CInvalidOperationException& CInvalidOperationException::operator=(CInvalidOperationException&& Other) noexcept
	{
		CException::operator=(FUNCTION_MOVE(Other));

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------