//----------------------------------------------------------------------------------------------------------------------
#include "CValueOutOfRangeException.h"
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
	CValueOutOfRangeException::CValueOutOfRangeException(void)
		: CException("")
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CValueOutOfRangeException::CValueOutOfRangeException(const CString& Message)
		: CException(Message)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CValueOutOfRangeException::CValueOutOfRangeException(CString&& Message)
		: CException(FUNCTION_MOVE(Message))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CValueOutOfRangeException::CValueOutOfRangeException(const exception& Exception)
		: CException(Exception)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CValueOutOfRangeException::CValueOutOfRangeException(const CString& Message, const exception& Exception)
		: CException(Message,Exception)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CValueOutOfRangeException::CValueOutOfRangeException(const CString& Message, const CException& Exception)
		: CException(Message,Exception)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CValueOutOfRangeException::CValueOutOfRangeException(const CValueOutOfRangeException& Other)
		: CException(Other)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CValueOutOfRangeException::CValueOutOfRangeException(CValueOutOfRangeException&& Other) noexcept
		: CException(FUNCTION_MOVE(Other))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CValueOutOfRangeException::~CValueOutOfRangeException(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CValueOutOfRangeException& CValueOutOfRangeException::operator=(const CValueOutOfRangeException& Other)
	{
		CException::operator=(Other);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CValueOutOfRangeException& CValueOutOfRangeException::operator=(CValueOutOfRangeException&& Other) noexcept
	{
		CException::operator=(FUNCTION_MOVE(Other));

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------