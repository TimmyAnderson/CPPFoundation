//----------------------------------------------------------------------------------------------------------------------
#include "CTestStateMachineExceptionSettings.h"
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
	CTestStateMachineExceptionSettings::CTestStateMachineExceptionSettings(const CTimeout& Timeout)
		: MThrowExceptionOnInternalGetStateMachineStartState(), MThrowExceptionOnInternalExecuteStateMachine(), MThrowExceptionOnInternalExecuteStateMachineStateInput1(), MThrowExceptionOnInternalExecuteStateMachineStateInput2(), MThrowExceptionOnInternalExecuteStateMachineStateInput3(), MThrowExceptionOnInternalExecuteStateMachineStateInput4(), MThrowExceptionOnInternalTerminateStateMachine(), MThrowExceptionOnInternalGetStateMachineTimeout(), MThrowExceptionOnStateMachineStartedEvent(), MThrowExceptionOnStateMachineFinishedEvent(), MThrowExceptionOnStateMachineExpiredEvent(), MThrowExceptionOnStateMachineStateChangedEvent(), MThrowExceptionOnStateMachineStateOutputFiringEvent(), MThrowExceptionOnStateMachineStateOutputFiringEvent1(), MThrowExceptionOnStateMachineStateOutputFiringEvent2(), MThrowExceptionOnStateMachineStateOutputFiringEvent3(), MThrowExceptionOnStateMachineStateOutputFiringEvent4(), MThrowExceptionOnChildStateMachineAddedEvent(), MThrowExceptionOnChildStateMachineFinishedEvent(), MProcessStateInput1(false), MProcessStateInput2(false), MProcessStateInput3(false), MProcessStateInput4(false), MProcessStateOutput1(false), MProcessStateOutput2(false), MProcessStateOutput3(false), MProcessStateOutput4(false), MTimeout(Timeout)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineExceptionSettings::CTestStateMachineExceptionSettings(const CTestStateMachineThrowException& ThrowExceptionOnInternalGetStateMachineStartState, const CTestStateMachineThrowException& ThrowExceptionOnInternalExecuteStateMachine, const CTestStateMachineThrowException& ThrowExceptionOnInternalExecuteStateMachineStateInput1, const CTestStateMachineThrowException& ThrowExceptionOnInternalExecuteStateMachineStateInput2, const CTestStateMachineThrowException& ThrowExceptionOnInternalExecuteStateMachineStateInput3, const CTestStateMachineThrowException& ThrowExceptionOnInternalExecuteStateMachineStateInput4, const CTestStateMachineThrowException& ThrowExceptionOnInternalTerminateStateMachine, const CTestStateMachineThrowException& ThrowExceptionOnInternalGetStateMachineTimeout, const CTestStateMachineThrowException& ThrowExceptionOnStateMachineStartedEvent, const CTestStateMachineThrowException& ThrowExceptionOnStateMachineFinishedEvent, const CTestStateMachineThrowException& ThrowExceptionOnStateMachineExpiredEvent, const CTestStateMachineThrowException& ThrowExceptionOnStateMachineStateChangedEvent, const CTestStateMachineThrowException& ThrowExceptionOnStateMachineStateOutputFiringEvent, const CTestStateMachineThrowException& ThrowExceptionOnStateMachineStateOutputFiringEvent1, const CTestStateMachineThrowException& ThrowExceptionOnStateMachineStateOutputFiringEvent2, const CTestStateMachineThrowException& ThrowExceptionOnStateMachineStateOutputFiringEvent3, const CTestStateMachineThrowException& ThrowExceptionOnStateMachineStateOutputFiringEvent4, const CTestStateMachineThrowException& ThrowExceptionOnChildStateMachineAddedEvent, const CTestStateMachineThrowException& ThrowExceptionOnChildStateMachineFinishedEvent, bool ProcessStateInput1, bool ProcessStateInput2, bool ProcessStateInput3, bool ProcessStateInput4, bool ProcessStateOutput1, bool ProcessStateOutput2, bool ProcessStateOutput3, bool ProcessStateOutput4, const CTimeout& Timeout)
		: MThrowExceptionOnInternalGetStateMachineStartState(ThrowExceptionOnInternalGetStateMachineStartState), MThrowExceptionOnInternalExecuteStateMachine(ThrowExceptionOnInternalExecuteStateMachine), MThrowExceptionOnInternalExecuteStateMachineStateInput1(ThrowExceptionOnInternalExecuteStateMachineStateInput1), MThrowExceptionOnInternalExecuteStateMachineStateInput2(ThrowExceptionOnInternalExecuteStateMachineStateInput2), MThrowExceptionOnInternalExecuteStateMachineStateInput3(ThrowExceptionOnInternalExecuteStateMachineStateInput3), MThrowExceptionOnInternalExecuteStateMachineStateInput4(ThrowExceptionOnInternalExecuteStateMachineStateInput4), MThrowExceptionOnInternalTerminateStateMachine(ThrowExceptionOnInternalTerminateStateMachine), MThrowExceptionOnInternalGetStateMachineTimeout(ThrowExceptionOnInternalGetStateMachineTimeout), MThrowExceptionOnStateMachineStartedEvent(ThrowExceptionOnStateMachineStartedEvent), MThrowExceptionOnStateMachineFinishedEvent(ThrowExceptionOnStateMachineFinishedEvent), MThrowExceptionOnStateMachineExpiredEvent(ThrowExceptionOnStateMachineExpiredEvent), MThrowExceptionOnStateMachineStateChangedEvent(ThrowExceptionOnStateMachineStateChangedEvent), MThrowExceptionOnStateMachineStateOutputFiringEvent(ThrowExceptionOnStateMachineStateOutputFiringEvent), MThrowExceptionOnStateMachineStateOutputFiringEvent1(ThrowExceptionOnStateMachineStateOutputFiringEvent1), MThrowExceptionOnStateMachineStateOutputFiringEvent2(ThrowExceptionOnStateMachineStateOutputFiringEvent2), MThrowExceptionOnStateMachineStateOutputFiringEvent3(ThrowExceptionOnStateMachineStateOutputFiringEvent3), MThrowExceptionOnStateMachineStateOutputFiringEvent4(ThrowExceptionOnStateMachineStateOutputFiringEvent4), MThrowExceptionOnChildStateMachineAddedEvent(ThrowExceptionOnChildStateMachineAddedEvent), MThrowExceptionOnChildStateMachineFinishedEvent(ThrowExceptionOnChildStateMachineFinishedEvent), MProcessStateInput1(ProcessStateInput1), MProcessStateInput2(ProcessStateInput2), MProcessStateInput3(ProcessStateInput3), MProcessStateInput4(ProcessStateInput4), MProcessStateOutput1(ProcessStateOutput1), MProcessStateOutput2(ProcessStateOutput2), MProcessStateOutput3(ProcessStateOutput3), MProcessStateOutput4(ProcessStateOutput4), MTimeout(Timeout)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineExceptionSettings::~CTestStateMachineExceptionSettings(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachineExceptionSettings::GetThrowExceptionOnInternalGetStateMachineStartState(void) noexcept
	{
		return(MThrowExceptionOnInternalGetStateMachineStartState);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetThrowExceptionOnInternalGetStateMachineStartState(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnInternalGetStateMachineStartState=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachineExceptionSettings::GetThrowExceptionOnInternalExecuteStateMachine(void) noexcept
	{
		return(MThrowExceptionOnInternalExecuteStateMachine);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetThrowExceptionOnInternalExecuteStateMachine(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnInternalExecuteStateMachine=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachineExceptionSettings::GetThrowExceptionOnInternalExecuteStateMachineStateInput1(void) noexcept
	{
		return(MThrowExceptionOnInternalExecuteStateMachineStateInput1);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetThrowExceptionOnInternalExecuteStateMachineStateInput1(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnInternalExecuteStateMachineStateInput1=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachineExceptionSettings::GetThrowExceptionOnInternalExecuteStateMachineStateInput2(void) noexcept
	{
		return(MThrowExceptionOnInternalExecuteStateMachineStateInput2);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetThrowExceptionOnInternalExecuteStateMachineStateInput2(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnInternalExecuteStateMachineStateInput2=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachineExceptionSettings::GetThrowExceptionOnInternalExecuteStateMachineStateInput3(void) noexcept
	{
		return(MThrowExceptionOnInternalExecuteStateMachineStateInput3);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetThrowExceptionOnInternalExecuteStateMachineStateInput3(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnInternalExecuteStateMachineStateInput3=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachineExceptionSettings::GetThrowExceptionOnInternalExecuteStateMachineStateInput4(void) noexcept
	{
		return(MThrowExceptionOnInternalExecuteStateMachineStateInput4);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetThrowExceptionOnInternalExecuteStateMachineStateInput4(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnInternalExecuteStateMachineStateInput4=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachineExceptionSettings::GetThrowExceptionOnInternalTerminateStateMachine(void) noexcept
	{
		return(MThrowExceptionOnInternalTerminateStateMachine);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetThrowExceptionOnInternalTerminateStateMachine(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnInternalTerminateStateMachine=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachineExceptionSettings::GetThrowExceptionOnInternalGetStateMachineTimeout(void) noexcept
	{
		return(MThrowExceptionOnInternalGetStateMachineTimeout);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetThrowExceptionOnInternalGetStateMachineTimeout(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnInternalGetStateMachineTimeout=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachineExceptionSettings::GetThrowExceptionOnStateMachineStartedEvent(void) noexcept
	{
		return(MThrowExceptionOnStateMachineStartedEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetThrowExceptionOnStateMachineStartedEvent(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnStateMachineStartedEvent=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachineExceptionSettings::GetThrowExceptionOnStateMachineFinishedEvent(void) noexcept
	{
		return(MThrowExceptionOnStateMachineFinishedEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetThrowExceptionOnStateMachineFinishedEvent(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnStateMachineFinishedEvent=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachineExceptionSettings::GetThrowExceptionOnStateMachineExpiredEvent(void) noexcept
	{
		return(MThrowExceptionOnStateMachineExpiredEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetThrowExceptionOnStateMachineExpiredEvent(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnStateMachineExpiredEvent=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachineExceptionSettings::GetThrowExceptionOnStateMachineStateChangedEvent(void) noexcept
	{
		return(MThrowExceptionOnStateMachineStateChangedEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetThrowExceptionOnStateMachineStateChangedEvent(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnStateMachineStateChangedEvent=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachineExceptionSettings::GetThrowExceptionOnStateMachineStateOutputFiringEvent(void) noexcept
	{
		return(MThrowExceptionOnStateMachineStateOutputFiringEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetThrowExceptionOnStateMachineStateOutputFiringEvent(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnStateMachineStateOutputFiringEvent=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachineExceptionSettings::GetThrowExceptionOnStateMachineStateOutputFiringEvent1(void) noexcept
	{
		return(MThrowExceptionOnStateMachineStateOutputFiringEvent1);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetThrowExceptionOnStateMachineStateOutputFiringEvent1(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnStateMachineStateOutputFiringEvent1=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachineExceptionSettings::GetThrowExceptionOnStateMachineStateOutputFiringEvent2(void) noexcept
	{
		return(MThrowExceptionOnStateMachineStateOutputFiringEvent2);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetThrowExceptionOnStateMachineStateOutputFiringEvent2(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnStateMachineStateOutputFiringEvent2=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachineExceptionSettings::GetThrowExceptionOnStateMachineStateOutputFiringEvent3(void) noexcept
	{
		return(MThrowExceptionOnStateMachineStateOutputFiringEvent3);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetThrowExceptionOnStateMachineStateOutputFiringEvent3(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnStateMachineStateOutputFiringEvent3=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachineExceptionSettings::GetThrowExceptionOnStateMachineStateOutputFiringEvent4(void) noexcept
	{
		return(MThrowExceptionOnStateMachineStateOutputFiringEvent4);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetThrowExceptionOnStateMachineStateOutputFiringEvent4(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnStateMachineStateOutputFiringEvent4=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachineExceptionSettings::GetThrowExceptionOnChildStateMachineAddedEvent(void) noexcept
	{
		return(MThrowExceptionOnChildStateMachineAddedEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetThrowExceptionOnChildStateMachineAddedEvent(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnChildStateMachineAddedEvent=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachineExceptionSettings::GetThrowExceptionOnChildStateMachineFinishedEvent(void) noexcept
	{
		return(MThrowExceptionOnChildStateMachineFinishedEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetThrowExceptionOnChildStateMachineFinishedEvent(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnChildStateMachineFinishedEvent=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineExceptionSettings::GetProcessStateInput1(void) const noexcept
	{
		return(MProcessStateInput1);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetProcessStateInput1(bool Value) noexcept
	{
		MProcessStateInput1=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineExceptionSettings::GetProcessStateInput2(void) const noexcept
	{
		return(MProcessStateInput2);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetProcessStateInput2(bool Value) noexcept
	{
		MProcessStateInput2=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineExceptionSettings::GetProcessStateInput3(void) const noexcept
	{
		return(MProcessStateInput3);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetProcessStateInput3(bool Value) noexcept
	{
		MProcessStateInput3=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineExceptionSettings::GetProcessStateInput4(void) const noexcept
	{
		return(MProcessStateInput3);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetProcessStateInput4(bool Value) noexcept
	{
		MProcessStateInput3=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineExceptionSettings::GetProcessStateOutput1(void) const noexcept
	{
		return(MProcessStateOutput1);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetProcessStateOutput1(bool Value) noexcept
	{
		MProcessStateOutput1=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineExceptionSettings::GetProcessStateOutput2(void) const noexcept
	{
		return(MProcessStateOutput2);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetProcessStateOutput2(bool Value) noexcept
	{
		MProcessStateOutput2=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineExceptionSettings::GetProcessStateOutput3(void) const noexcept
	{
		return(MProcessStateOutput3);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetProcessStateOutput3(bool Value) noexcept
	{
		MProcessStateOutput3=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineExceptionSettings::GetProcessStateOutput4(void) const noexcept
	{
		return(MProcessStateOutput4);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetProcessStateOutput4(bool Value) noexcept
	{
		MProcessStateOutput4=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	const CTimeout& CTestStateMachineExceptionSettings::GetTimeout(void) const noexcept
	{
		return(MTimeout);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineExceptionSettings::SetTimeout(const CTimeout& Value) noexcept
	{
		MTimeout=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------