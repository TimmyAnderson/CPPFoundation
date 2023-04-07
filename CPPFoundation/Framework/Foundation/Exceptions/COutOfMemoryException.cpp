//----------------------------------------------------------------------------------------------------------------------
#include "COutOfMemoryException.h"
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
	COutOfMemoryException::COutOfMemoryException(void)
		: CException("")
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	COutOfMemoryException::COutOfMemoryException(const CString& Message)
		: CException(Message)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	COutOfMemoryException::COutOfMemoryException(CString&& Message)
		: CException(FUNCTION_MOVE(Message))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	COutOfMemoryException::COutOfMemoryException(const exception& Exception)
		: CException(Exception)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	COutOfMemoryException::COutOfMemoryException(const CString& Message, const exception& Exception)
		: CException(Message,Exception)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	COutOfMemoryException::COutOfMemoryException(const CString& Message, const CException& Exception)
		: CException(Message,Exception)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	COutOfMemoryException::COutOfMemoryException(const COutOfMemoryException& Other)
		: CException(Other)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	COutOfMemoryException::COutOfMemoryException(COutOfMemoryException&& Other) noexcept
		: CException(FUNCTION_MOVE(Other))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	COutOfMemoryException::~COutOfMemoryException(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	COutOfMemoryException& COutOfMemoryException::operator=(const COutOfMemoryException& Other)
	{
		CException::operator=(Other);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	COutOfMemoryException& COutOfMemoryException::operator=(COutOfMemoryException&& Other) noexcept
	{
		CException::operator=(FUNCTION_MOVE(Other));

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------