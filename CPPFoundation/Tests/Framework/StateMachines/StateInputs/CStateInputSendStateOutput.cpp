//----------------------------------------------------------------------------------------------------------------------
#include "CStateInputSendStateOutput.h"
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
	CStateInputSendStateOutput::CStateInputSendStateOutput(const CStateMachineID& StateMachineID, const CStateMachineID& SendingStateMachineID, CSPStateOutput StateOutputToSend)
		: CStateInput(StateMachineID), MSendingStateMachineID(SendingStateMachineID), MStateOutputToSend(StateOutputToSend)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInputSendStateOutput::CStateInputSendStateOutput(CStateMachineID&& StateMachineID, CStateMachineID&& SendingStateMachineID, CSPStateOutput StateOutputToSend)
		: CStateInput(FUNCTION_MOVE(StateMachineID)), MSendingStateMachineID(SendingStateMachineID), MStateOutputToSend(FUNCTION_MOVE(StateOutputToSend))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInputSendStateOutput::CStateInputSendStateOutput(const CStateInputSendStateOutput& Other)
		: CStateInput(Other), MSendingStateMachineID(Other.MSendingStateMachineID), MStateOutputToSend(Other.MStateOutputToSend)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInputSendStateOutput::CStateInputSendStateOutput(CStateInputSendStateOutput&& Other) noexcept
		: CStateInput(FUNCTION_MOVE(Other)), MSendingStateMachineID(FUNCTION_MOVE(Other.MSendingStateMachineID)), MStateOutputToSend(FUNCTION_MOVE(Other.MStateOutputToSend))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInputSendStateOutput::~CStateInputSendStateOutput(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CStateInputSendStateOutput& CStateInputSendStateOutput::operator=(const CStateInputSendStateOutput& Other)
	{
		CStateInput::operator=(Other);

		MSendingStateMachineID=Other.MSendingStateMachineID;
		MStateOutputToSend=Other.MStateOutputToSend;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInputSendStateOutput& CStateInputSendStateOutput::operator=(CStateInputSendStateOutput&& Other) noexcept
	{
		CStateInput::operator=(FUNCTION_MOVE(Other));

		MSendingStateMachineID=FUNCTION_MOVE(Other.MSendingStateMachineID);
		MStateOutputToSend=FUNCTION_MOVE(Other.MStateOutputToSend);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CStateMachineID& CStateInputSendStateOutput::GetSendingStateMachineID(void) const noexcept
	{
		return(MSendingStateMachineID);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPStateOutput CStateInputSendStateOutput::GetStateOutputToSend(void) const noexcept
	{
		return(MStateOutputToSend);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------