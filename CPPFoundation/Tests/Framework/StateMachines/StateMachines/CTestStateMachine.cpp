//----------------------------------------------------------------------------------------------------------------------
#include "CTestStateMachine.h"
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
	CTestStateMachine::CTestStateMachine(CLogWriter& LogWriter, const CString& StateMachineName, IStateMachineCallback& StateMachineCallback, CCSPStateMachineSettings StateMachineSettings, CStateMachine* StateMachineParent)
		: CStateMachine(LogWriter,StateMachineName,StateMachineCallback,StateMachineSettings,StateMachineParent)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachine::~CTestStateMachine(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachine::ChildStateMachineAddedEvent(void)
	{
		CStateMachine::ChildStateMachineAddedEvent();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachine::ChildStateMachineFinishedEvent(void)
	{
		CStateMachine::ChildStateMachineFinishedEvent();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachine::TestHasChildStateMachineByID(const CStateMachineID& StateMachineID) const
	{
		return(HasChildStateMachineByID(StateMachineID));
	}
//----------------------------------------------------------------------------------------------------------------------
	const CTestStateMachine::CTestStateMachineChildCollection& CTestStateMachine::TestGetChildStateMachines(void) const noexcept
	{
		return(GetChildStateMachines());
	}
//----------------------------------------------------------------------------------------------------------------------
	const CTestStateMachine::CTestStateMachineChildCollection& CTestStateMachine::TestGetChildStateMachineTree(void) const
	{
		return(GetChildStateMachineTree());
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPStateMachine CTestStateMachine::TestGetChildStateMachineByID(const CStateMachineID& StateMachineID) const
	{
		return(GetChildStateMachineByID(StateMachineID));
	}
//----------------------------------------------------------------------------------------------------------------------
	const CStateMachine* CTestStateMachine::TestGetStateMachineRoot(void) const
	{
		return(GetStateMachineRoot());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------