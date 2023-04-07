//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include "ETestStateMachineThrowExceptionType.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CTestStateMachineThrowException final : public CPPFoundation::Foundation::CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			ETestStateMachineThrowExceptionType					MExceptionType;
			Size												MExceptionCounter;
			bool												MResetExceptionCounter;
			Size												MExceptionCounterCurrentValue;

		public:
			ETestStateMachineThrowExceptionType GetExceptionType(void) const noexcept;
			Size GetExceptionCounter(void) const noexcept;
			bool GetResetExceptionCounter(void) const noexcept;
			Size GetExceptionCounterCurrentValue(void) const noexcept;
			void DecrementExceptionCounterCurrentValueAndThrowException(void);

		public:
			CTestStateMachineThrowException(void);
			CTestStateMachineThrowException(ETestStateMachineThrowExceptionType ExceptionType, Size ExceptionCounter, bool ResetExceptionCounter);
			virtual ~CTestStateMachineThrowException(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------