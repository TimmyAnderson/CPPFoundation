//----------------------------------------------------------------------------------------------------------------------
#include "CNullPointerException.h"
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
	CNullPointerException::CNullPointerException(void)
		: CException("")
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CNullPointerException::CNullPointerException(const CString& Message)
		: CException(Message)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CNullPointerException::CNullPointerException(CString&& Message)
		: CException(FUNCTION_MOVE(Message))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CNullPointerException::CNullPointerException(const exception& Exception)
		: CException(Exception)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CNullPointerException::CNullPointerException(const CString& Message, const exception& Exception)
		: CException(Message,Exception)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CNullPointerException::CNullPointerException(const CString& Message, const CException& Exception)
		: CException(Message,Exception)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CNullPointerException::CNullPointerException(const CNullPointerException& Other)
		: CException(Other)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CNullPointerException::CNullPointerException(CNullPointerException&& Other) noexcept
		: CException(FUNCTION_MOVE(Other))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CNullPointerException::~CNullPointerException(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CNullPointerException& CNullPointerException::operator=(const CNullPointerException& Other)
	{
		CException::operator=(Other);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CNullPointerException& CNullPointerException::operator=(CNullPointerException&& Other) noexcept
	{
		CException::operator=(FUNCTION_MOVE(Other));

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------