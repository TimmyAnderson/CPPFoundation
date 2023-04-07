//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/Exceptions/CStateMachineException.h>
#include "CTestStateMachineThrowException.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException::CTestStateMachineThrowException(void)
		: MExceptionType(ETestStateMachineThrowExceptionType::E_NO_EXCEPTION), MExceptionCounter(0), MResetExceptionCounter(false), MExceptionCounterCurrentValue(0)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException::CTestStateMachineThrowException(ETestStateMachineThrowExceptionType ExceptionType, Size ExceptionCounter, bool ResetExceptionCounter)
		: MExceptionType(ExceptionType), MExceptionCounter(ExceptionCounter), MResetExceptionCounter(ResetExceptionCounter), MExceptionCounterCurrentValue(ExceptionCounter)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException::~CTestStateMachineThrowException(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	ETestStateMachineThrowExceptionType CTestStateMachineThrowException::GetExceptionType(void) const noexcept
	{
		return(MExceptionType);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineThrowException::GetExceptionCounter(void) const noexcept
	{
		return(MExceptionCounter);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineThrowException::GetResetExceptionCounter(void) const noexcept
	{
		return(MResetExceptionCounter);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineThrowException::GetExceptionCounterCurrentValue(void) const noexcept
	{
		return(MExceptionCounterCurrentValue);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineThrowException::DecrementExceptionCounterCurrentValueAndThrowException(void)
	{
		if (MExceptionCounterCurrentValue>0)
		{
			if (--MExceptionCounterCurrentValue==0)
			{
				if (MResetExceptionCounter==true)
				{
					MExceptionCounterCurrentValue=MExceptionCounter;
				}

				if (MExceptionType==ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE)
				{
					throw(CInvalidOperationException("INVALID OPERATION EXCEPTION !"));
				}
				else if (MExceptionType==ETestStateMachineThrowExceptionType::E_EXCEPTION_INVALID_OPERATION)
				{
					throw(CStateMachineException("STATE MACHINE EXCEPTION !"));
				}
				else if (MExceptionType==ETestStateMachineThrowExceptionType::E_EXCEPTION_CSTRING)
				{
					throw(CString("STATE MACHINE EXCEPTION !"));
				}
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------