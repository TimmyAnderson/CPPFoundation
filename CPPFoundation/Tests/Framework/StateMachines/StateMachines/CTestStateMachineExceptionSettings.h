//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Time/CTimeout.h>
#include "CTestStateMachineThrowException.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CTestStateMachineExceptionSettings final : public CPPFoundation::Foundation::CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CTestStateMachineThrowException						MThrowExceptionOnInternalGetStateMachineStartState;
			CTestStateMachineThrowException						MThrowExceptionOnInternalExecuteStateMachine;
			CTestStateMachineThrowException						MThrowExceptionOnInternalExecuteStateMachineStateInput1;
			CTestStateMachineThrowException						MThrowExceptionOnInternalExecuteStateMachineStateInput2;
			CTestStateMachineThrowException						MThrowExceptionOnInternalExecuteStateMachineStateInput3;
			CTestStateMachineThrowException						MThrowExceptionOnInternalExecuteStateMachineStateInput4;
			CTestStateMachineThrowException						MThrowExceptionOnInternalTerminateStateMachine;
			CTestStateMachineThrowException						MThrowExceptionOnInternalGetStateMachineTimeout;
			CTestStateMachineThrowException						MThrowExceptionOnStateMachineStartedEvent;
			CTestStateMachineThrowException						MThrowExceptionOnStateMachineFinishedEvent;
			CTestStateMachineThrowException						MThrowExceptionOnStateMachineExpiredEvent;
			CTestStateMachineThrowException						MThrowExceptionOnStateMachineStateChangedEvent;
			CTestStateMachineThrowException						MThrowExceptionOnStateMachineStateOutputFiringEvent;
			CTestStateMachineThrowException						MThrowExceptionOnStateMachineStateOutputFiringEvent1;
			CTestStateMachineThrowException						MThrowExceptionOnStateMachineStateOutputFiringEvent2;
			CTestStateMachineThrowException						MThrowExceptionOnStateMachineStateOutputFiringEvent3;
			CTestStateMachineThrowException						MThrowExceptionOnStateMachineStateOutputFiringEvent4;
			CTestStateMachineThrowException						MThrowExceptionOnChildStateMachineAddedEvent;
			CTestStateMachineThrowException						MThrowExceptionOnChildStateMachineFinishedEvent;
			bool												MProcessStateInput1;
			bool												MProcessStateInput2;
			bool												MProcessStateInput3;
			bool												MProcessStateInput4;
			bool												MProcessStateOutput1;
			bool												MProcessStateOutput2;
			bool												MProcessStateOutput3;
			bool												MProcessStateOutput4;
			CPPFoundation::Foundation::CTimeout					MTimeout;

		public:
			CTestStateMachineThrowException& GetThrowExceptionOnInternalGetStateMachineStartState(void) noexcept;
			void SetThrowExceptionOnInternalGetStateMachineStartState(const CTestStateMachineThrowException& Value) noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnInternalExecuteStateMachine(void) noexcept;
			void SetThrowExceptionOnInternalExecuteStateMachine(const CTestStateMachineThrowException& Value) noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnInternalExecuteStateMachineStateInput1(void) noexcept;
			void SetThrowExceptionOnInternalExecuteStateMachineStateInput1(const CTestStateMachineThrowException& Value) noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnInternalExecuteStateMachineStateInput2(void) noexcept;
			void SetThrowExceptionOnInternalExecuteStateMachineStateInput2(const CTestStateMachineThrowException& Value) noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnInternalExecuteStateMachineStateInput3(void) noexcept;
			void SetThrowExceptionOnInternalExecuteStateMachineStateInput3(const CTestStateMachineThrowException& Value) noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnInternalExecuteStateMachineStateInput4(void) noexcept;
			void SetThrowExceptionOnInternalExecuteStateMachineStateInput4(const CTestStateMachineThrowException& Value) noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnInternalTerminateStateMachine(void) noexcept;
			void SetThrowExceptionOnInternalTerminateStateMachine(const CTestStateMachineThrowException& Value) noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnInternalGetStateMachineTimeout(void) noexcept;
			void SetThrowExceptionOnInternalGetStateMachineTimeout(const CTestStateMachineThrowException& Value) noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnStateMachineStartedEvent(void) noexcept;
			void SetThrowExceptionOnStateMachineStartedEvent(const CTestStateMachineThrowException& Value) noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnStateMachineFinishedEvent(void) noexcept;
			void SetThrowExceptionOnStateMachineFinishedEvent(const CTestStateMachineThrowException& Value) noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnStateMachineExpiredEvent(void) noexcept;
			void SetThrowExceptionOnStateMachineExpiredEvent(const CTestStateMachineThrowException& Value) noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnStateMachineStateChangedEvent(void) noexcept;
			void SetThrowExceptionOnStateMachineStateChangedEvent(const CTestStateMachineThrowException& Value) noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnStateMachineStateOutputFiringEvent(void) noexcept;
			void SetThrowExceptionOnStateMachineStateOutputFiringEvent(const CTestStateMachineThrowException& Value) noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnStateMachineStateOutputFiringEvent1(void) noexcept;
			void SetThrowExceptionOnStateMachineStateOutputFiringEvent1(const CTestStateMachineThrowException& Value) noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnStateMachineStateOutputFiringEvent2(void) noexcept;
			void SetThrowExceptionOnStateMachineStateOutputFiringEvent2(const CTestStateMachineThrowException& Value) noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnStateMachineStateOutputFiringEvent3(void) noexcept;
			void SetThrowExceptionOnStateMachineStateOutputFiringEvent3(const CTestStateMachineThrowException& Value) noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnStateMachineStateOutputFiringEvent4(void) noexcept;
			void SetThrowExceptionOnStateMachineStateOutputFiringEvent4(const CTestStateMachineThrowException& Value) noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnChildStateMachineAddedEvent(void) noexcept;
			void SetThrowExceptionOnChildStateMachineAddedEvent(const CTestStateMachineThrowException& Value) noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnChildStateMachineFinishedEvent(void) noexcept;
			void SetThrowExceptionOnChildStateMachineFinishedEvent(const CTestStateMachineThrowException& Value) noexcept;
			bool GetProcessStateInput1(void) const noexcept;
			void SetProcessStateInput1(bool Value) noexcept;
			bool GetProcessStateInput2(void) const noexcept;
			void SetProcessStateInput2(bool Value) noexcept;
			bool GetProcessStateInput3(void) const noexcept;
			void SetProcessStateInput3(bool Value) noexcept;
			bool GetProcessStateInput4(void) const noexcept;
			void SetProcessStateInput4(bool Value) noexcept;
			bool GetProcessStateOutput1(void) const noexcept;
			void SetProcessStateOutput1(bool Value) noexcept;
			bool GetProcessStateOutput2(void) const noexcept;
			void SetProcessStateOutput2(bool Value) noexcept;
			bool GetProcessStateOutput3(void) const noexcept;
			void SetProcessStateOutput3(bool Value) noexcept;
			bool GetProcessStateOutput4(void) const noexcept;
			void SetProcessStateOutput4(bool Value) noexcept;
			const CPPFoundation::Foundation::CTimeout& GetTimeout(void) const noexcept;
			void SetTimeout(const CPPFoundation::Foundation::CTimeout& Value) noexcept;

		public:
			CTestStateMachineExceptionSettings(const CPPFoundation::Foundation::CTimeout& Timeout);
			CTestStateMachineExceptionSettings(const CTestStateMachineThrowException& ThrowExceptionOnInternalGetStateMachineStartState, const CTestStateMachineThrowException& ThrowExceptionOnInternalExecuteStateMachine, const CTestStateMachineThrowException& ThrowExceptionOnInternalExecuteStateMachineStateInput1, const CTestStateMachineThrowException& ThrowExceptionOnInternalExecuteStateMachineStateInput2, const CTestStateMachineThrowException& ThrowExceptionOnInternalExecuteStateMachineStateInput3, const CTestStateMachineThrowException& ThrowExceptionOnInternalExecuteStateMachineStateInput4, const CTestStateMachineThrowException& ThrowExceptionOnInternalTerminateStateMachine, const CTestStateMachineThrowException& ThrowExceptionOnInternalGetStateMachineTimeout, const CTestStateMachineThrowException& ThrowExceptionOnStateMachineStartedEvent, const CTestStateMachineThrowException& ThrowExceptionOnStateMachineFinishedEvent, const CTestStateMachineThrowException& ThrowExceptionOnStateMachineExpiredEvent, const CTestStateMachineThrowException& ThrowExceptionOnStateMachineStateChangedEvent, const CTestStateMachineThrowException& ThrowExceptionOnStateMachineStateOutputFiringEvent, const CTestStateMachineThrowException& ThrowExceptionOnStateMachineStateOutputFiringEvent1, const CTestStateMachineThrowException& ThrowExceptionOnStateMachineStateOutputFiringEvent2, const CTestStateMachineThrowException& ThrowExceptionOnStateMachineStateOutputFiringEvent3, const CTestStateMachineThrowException& ThrowExceptionOnStateMachineStateOutputFiringEvent4, const CTestStateMachineThrowException& ThrowExceptionOnChildStateMachineAddedEvent, const CTestStateMachineThrowException& ThrowExceptionOnChildStateMachineFinishedEvent, bool ProcessStateInput1, bool ProcessStateInput2, bool ProcessStateInput3, bool ProcessStateInput4, bool ProcessStateOutput1, bool ProcessStateOutput2, bool ProcessStateOutput3, bool ProcessStateOutput4, const CPPFoundation::Foundation::CTimeout& Timeout);
			virtual ~CTestStateMachineExceptionSettings(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------