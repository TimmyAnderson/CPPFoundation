//----------------------------------------------------------------------------------------------------------------------
#include "CStateMachinesProcessor.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CStateMachinesProcessor::CStateMachinesProcessor(CLogWriter& LogWriter, const CString& StateMachinesProcessorName, CCSPStateMachinesProcessorSettings StateMachinesProcessorSettings)
		: MLogWriter(LogWriter), MLogCategoryStateMachinesProcessor(CString::Format("STATE MACHINES PROCESSOR [",StateMachinesProcessorName,"]")), MStateMachinesProcessorName(StateMachinesProcessorName), MStateMachinesProcessorSettings(StateMachinesProcessorSettings), MStateMachines(), MStateInputs(), MExecuteImmediately(false)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachinesProcessor::~CStateMachinesProcessor(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachinesProcessor::RemoveFinishedStateMachines(void)
	{
		CVector<CSPStateMachine>								StateMachinesToRemove;

		for(CSPStateMachine StateMachine : CreateMapValueIterator(MStateMachines))
		{
			if (StateMachine->HasFinished()==true)
			{
				StateMachinesToRemove.Add(StateMachine);
			}
		}

		for(CSPStateMachine StateMachineToRemove : StateMachinesToRemove)
		{
			MStateMachines.RemoveStateMachine(StateMachineToRemove->GetStateMachineID());

			try
			{
				StateMachineFinished(StateMachineToRemove);
			}
			catch(const CException& E)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachinesProcessor(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINES PROCESSOR [",ToString(),"] FAILED to CALL STATE MACHNINE FINISHED EVENT for STATE MACHINE [",StateMachineToRemove->ToString(),"] !"),E));
			}
			catch(...)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachinesProcessor(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINES PROCESSOR [",ToString(),"] FAILED to CALL STATE MACHNINE FINISHED EVENT for STATE MACHINE [",StateMachineToRemove->ToString(),"] !"),CUnknownException()));
			}
		}

		if (StateMachinesToRemove.GetLength()>0)
		{
			// If STATE MACHINE has FINISHED STATE MACHINES PROCESSOR MUST NOTIFY all STATE MACHINES about its FINISH to allow STATE MACHINES to EXECUTE IMMEDIATELY.
			MExecuteImmediately=true;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachinesProcessor::ProcessAllInputs(void)
	{
		CCSPStateInput											StateInput;

		while(MStateInputs.PopFront(StateInput)==true)
		{
			bool												InputWasConsumed=false;

			// If STATE INPUT is able to identify ASSOCIATED STATE MACHINE, STATE INPUT is processed by ASSOCIATED STATE MACHINES.
			if (StateInput->HasStateMachineID()==true)
			{
				CSPStateMachine									StateMachine=MStateMachines.GetRootStateMachineForStateMachineID(StateInput->GetStateMachineID());

				if (StateMachine!=nullptr)
				{
					if (StateMachine->HasStarted()==true && StateMachine->HasFinished()==false)
					{
						if (StateMachine->ExecuteStateMachine(StateInput)==true)
						{
							InputWasConsumed=true;
						}
					}
				}
				else
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachinesProcessor(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINES PROCESSOR [",ToString(),"] can't process STATE INPUT [",StateInput->ToString(),"] because NO STATE MACHINE for STATE MACHINE ID [",StateInput->GetStateMachineID(),"] FOUND !")));
				}
			}
			// If STATE INPUT is NOT able to identify ASSOCIATED STATE MACHINE, STATE INPUT is processed by ALL STATE MACHINES.
			else
			{
				for(CSPStateMachine StateMachine : CreateMapValueIterator(MStateMachines))
				{
					if (StateMachine->HasStarted()==true && StateMachine->HasFinished()==false)
					{
						if (StateMachine->ExecuteStateMachine(StateInput)==true)
						{
							InputWasConsumed=true;
						}
					}
				}
			}

			if (InputWasConsumed==false)
			{
				try
				{
					StateInputNotProcessed(StateInput);
				}
				catch(const CException& E)
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachinesProcessor(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINES PROCESSOR [",ToString(),"] FAILED to CALL STATE INPUT NOT PROCESSED EVENT for STATE MACHINE [",StateInput->ToString(),"] !"),E));
				}
				catch(...)
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachinesProcessor(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINES PROCESSOR [",ToString(),"] FAILED to CALL STATE INPUT NOT PROCESSED EVENT for STATE MACHINE [",StateInput->ToString(),"] !"),CUnknownException()));
				}
			}

			RemoveFinishedStateMachines();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachinesProcessor::ProcessTimeout(void)
	{
		for(CSPStateMachine StateMachine : CreateMapValueIterator(MStateMachines))
		{
			if (StateMachine->HasStarted()==true && StateMachine->HasFinished()==false)
			{
				StateMachine->ExecuteStateMachine(nullptr);
			}
		}

		RemoveFinishedStateMachines();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachinesProcessor::StateInputNotProcessed(CCSPStateInput StateInput)
	{
		MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachinesProcessor(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINES PROCESSOR [",ToString(),"] didn't PROCESS STATE INPUT [",StateInput->ToString(),"] !")));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachinesProcessor::StateMachineAdded(CSPStateMachine StateMachine)
	{
		MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachinesProcessor(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINES PROCESSOR [",ToString(),"] detected ADDITION of STATE MACHINE [",StateMachine->ToString(),"] ! NUMBER of STATE MACHINES [",MStateMachines.GetLength(),"] !")));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachinesProcessor::StateMachineFinished(CSPStateMachine StateMachine)
	{
		MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachinesProcessor(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINES PROCESSOR [",ToString(),"] detected FINISH of STATE MACHINE [",StateMachine->ToString(),"] ! NUMBER of STATE MACHINES [",MStateMachines.GetLength(),"] !")));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CLogWriter& CStateMachinesProcessor::GetLogWriter(void) const noexcept
	{
		return(MLogWriter);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CLogCategory& CStateMachinesProcessor::GetLogCategoryStateMachinesProcessor(void) const noexcept
	{
		return(MLogCategoryStateMachinesProcessor);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CString& CStateMachinesProcessor::GetStateMachinesProcessorName(void) const noexcept
	{
		return(MStateMachinesProcessorName);
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPStateMachinesProcessorSettings CStateMachinesProcessor::GetStateMachinesProcessorSettings(void) const noexcept
	{
		return(MStateMachinesProcessorSettings);
	}
//----------------------------------------------------------------------------------------------------------------------
	[[noreturn]] void CStateMachinesProcessor::ThrowStateMachineException(const CString& Message)
	{
		throw(CStateMachineException(CString::Format("STATE MACHINES PROCESSOR [",ToString(),"] has thrown EXCEPTION [",Message,"] !")));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachinesProcessor::StartStateMachine(CSPStateMachine StateMachine)
	{
		if (StateMachine==nullptr)
		{
			ThrowStateMachineException("Can't STATE STATE MACHINE ! STATE MACHINE is set to NULL !");
		}

		StateMachine->StartStateMachine();

		RemoveFinishedStateMachines();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CStateMachinesProcessor::ToString(void) const
	{
		return(MStateMachinesProcessorName);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachinesProcessor::AddStateMachine(CSPStateMachine StateMachine)
	{
		if (MStateMachines.HasStateMachineByID(StateMachine->GetStateMachineID())==true)
		{
			ThrowStateMachineException(CString::Format("STATE MACHINE PROCESSOR can't ADD STATE MACHINE [",StateMachine,"] with DUPLICATE ID !"));
		}

		MStateMachines.AddStateMachine(StateMachine);

		try
		{
			StateMachineAdded(StateMachine);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachinesProcessor(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINES PROCESSOR [",ToString(),"] FAILED to CALL STATE MACHINE ADDED EVENT for STATE MACHINE [",StateMachine->ToString(),"] !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachinesProcessor(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINES PROCESSOR [",ToString(),"] FAILED to CALL STATE MACHINE ADDED EVENT for STATE MACHINE [",StateMachine->ToString(),"] !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachinesProcessor::AddStateInput(CCSPStateInput Input)
	{
		MStateInputs.PushBack(Input);

		MExecuteImmediately=true;
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachinesProcessor::HasStateMachine(const CStateMachineID& StateMachineID) const
	{
		if (MStateMachines.HasStateMachineByID(StateMachineID)==true)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachinesProcessor::ExecuteStateMachines(void)
	{
		// STATE MACHINE that had FINISHED and notified all STATE MACHINES by IMMEDIATE EXECUTION so now other RUNNING STATE MACHINES can continue in their REGULAR OPERATIONS.
		// !!!!! This LINE MUST be BEFORE actual CALLING of METHODS ProcessAllInputs() and ProcessTimeout().
		MExecuteImmediately=false;

		ProcessAllInputs();
		ProcessTimeout();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachinesProcessor::TerminateStateMachines(void)
	{
		for(CSPStateMachine StateMachine : CreateMapValueIterator(MStateMachines))
		{
			StateMachine->TerminateStateMachine();
		}

		RemoveFinishedStateMachines();
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CStateMachinesProcessor::GetStateMachinesTimeout(CSteadyClock::Milliseconds TimeInMS)
	{
		if (MExecuteImmediately==false)
		{
			CTimeout											MinTimeout=CTimeout::GetInfinite();

			for(CSPStateMachine StateMachine : CreateMapValueIterator(MStateMachines))
			{
				if (StateMachine->HasStarted()==true && StateMachine->HasFinished()==false)
				{
					CTimeout									StateMachineTimeout=StateMachine->GetStateMachineTimeout(TimeInMS);

					MinTimeout=CTimeout::Min(MinTimeout,StateMachineTimeout);
				}
			}

			RemoveFinishedStateMachines();

			return(MinTimeout);
		}
		else
		{
			// If STATE MACHINES has just FINISHED it MUST EXECUTE ALL STATE MACHINE to notify them that it is FINISHED.
			return(CTimeout::GetZero());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	const CStateMachineCollection& CStateMachinesProcessor::GetStateMachines(void) const noexcept
	{
		return(MStateMachines);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------