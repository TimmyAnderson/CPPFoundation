//----------------------------------------------------------------------------------------------------------------------
#include "CStateMachine.h"
#include <Framework/Foundation/Exceptions/CUnknownException.h>
#include <Framework/Foundation/StateMachines/StateMachinesProcessor/CStateMachinesProcessor.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CStateMachine::CStateMachine(CLogWriter& LogWriter, const CString& StateMachineName, IStateMachineCallback& StateMachineCallback, CCSPStateMachineSettings StateMachineSettings, CStateMachine* StateMachineParent)
		: MLogWriter(LogWriter), MLogCategoryStateMachine(CString::Format("STATE MACHINE [",StateMachineName,"]")), MStateMachineName(StateMachineName), MStateMachineCallback(StateMachineCallback), MStateMachineSettings(StateMachineSettings), MStateMachineInternalCurrentState(EStateMachineInternalState::E_CREATED), MStateMachineCurrentState(), MStateMachineExpirationTime(), MStateMachineExecuteImmediately(false), MStateMachineParent(StateMachineParent), MStateMachineChildCollection(), MStateMachineChildCollectionTree()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachine::~CStateMachine(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachine::CallInternalExecuteStateMachine(CCSPStateInput StateInput)
	{
		if (MStateMachineCurrentState.IsValidState()==true && MStateMachineCurrentState.IsFinalState()==false)
		{
			bool												StateInputProcessed=InternalExecuteStateMachine(StateInput);

			return(StateInputProcessed);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachine::ChildStateMachineAdded(CSPStateMachine StateMachine)
	{
		MStateMachineChildCollectionTree.Add(StateMachine->GetStateMachineID(),StateMachine);

		try
		{
			ChildStateMachineAddedEvent();
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while EXECUTING CHILD STATE MACHINE ADDED EVENT !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while EXECUTING CHILD STATE MACHINE ADDED EVENT !"),CUnknownException()));
		}

		if (MStateMachineParent!=nullptr)
		{
			MStateMachineParent->ChildStateMachineAdded(StateMachine);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachine::ChildStateMachineFinished(void) noexcept
	{
		try
		{
			ChildStateMachineFinishedEvent();
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while EXECUTING CHILD STATE MACHINE FINISHED EVENT !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while EXECUTING CHILD STATE MACHINE FINISHED EVENT !"),CUnknownException()));
		}

		if (MStateMachineParent!=nullptr)
		{
			MStateMachineParent->ChildStateMachineFinished();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachine::StateMachineFinished(void) noexcept
	{
		if (HaveAllChildStateMachinesFinished()==false)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] DETECTED that NOT ALL CHILD STATE MACHINES have FINISHED !")));

			TerminateChildStateMachines();
		}

		try
		{
			StateMachineFinishedEvent();
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while EXECUTING STATE MACHINE FINISHED EVENT !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while EXECUTING STATE MACHINE FINISHED EVENT !"),CUnknownException()));
		}

		if (MStateMachineCurrentState.IsValidState()==true)
		{
			MStateMachineCurrentState.ResetState();
		}

		MStateMachineInternalCurrentState=EStateMachineInternalState::E_FINISHED;

		// After STATE MACHINE STATE is CHANGED to FINAL PARENT STATE MACHINES are NOTIFIED.
		if (MStateMachineParent!=nullptr)
		{
			MStateMachineParent->ChildStateMachineFinished();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachine::StateMachineExpired(void) noexcept
	{
		try
		{
			StateMachineExpiredEvent();
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while EXECUTING STATE MACHINE EXPIRED EVENT !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while EXECUTING STATE MACHINE EXPIRED EVENT !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachine::CheckStateMachineFinished(void) noexcept
	{
		if (MStateMachineCurrentState.IsValidState()==true && MStateMachineCurrentState.IsFinalState()==true)
		{
			if (HaveAllChildStateMachinesFinished()==true)
			{
				StateMachineFinished();

				return(true);
			}
			else
			{
				return(false);
			}
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachine::ExecuteChildStateMachine(CStateMachine* StateMachine, CCSPStateInput StateInput) noexcept
	{
		if (StateMachine->HasStarted()==true && StateMachine->HasFinished()==false)
		{
			if (StateMachine->ExecuteStateMachine(StateInput)==true)
			{
				return(true);
			}
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachine::ExecuteChildStateMachine(CSPStateMachine StateMachine, CCSPStateInput StateInput) noexcept
	{
		if (StateMachine->HasStarted()==true && StateMachine->HasFinished()==false)
		{
			if (StateMachine->ExecuteStateMachine(StateInput)==true)
			{
				return(true);
			}
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachine::ExecuteChildStateMachines(CCSPStateInput StateInput)
	{
		bool													ChildStateMachineProcessedStateInput=false;

		for(CSPStateMachine ChildStateMachine : CreateMapValueIterator(MStateMachineChildCollection))
		{
			if (ExecuteChildStateMachine(ChildStateMachine,StateInput)==true)
			{
				ChildStateMachineProcessedStateInput=true;
			}
		}

		return(ChildStateMachineProcessedStateInput);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachine::TerminateChildStateMachines(void) noexcept
	{
		try
		{
			for(CSPStateMachine ChildStateMachine : CreateMapValueIterator(MStateMachineChildCollection))
			{
				if (ChildStateMachine->HasFinished()==false)
				{
					ChildStateMachine->TerminateStateMachine();
				}
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while TERMINATING CHILD STATE MACHINES !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while TERMINATING CHILD STATE MACHINES !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CStateMachine::GetChildStateMachinesTimeout(CSteadyClock::Milliseconds TimeInMS) const
	{
		CTimeout												Timeout=CTimeout::GetInfinite();

		for(CSPStateMachine ChildStateMachine : CreateMapValueIterator(MStateMachineChildCollection))
		{
			if (ChildStateMachine->HasStarted()==true && ChildStateMachine->HasFinished()==false)
			{
				CTimeout										ChildStateMachineTimeout=ChildStateMachine->GetStateMachineTimeout(TimeInMS);

				Timeout=CTimeout::Min(Timeout,ChildStateMachineTimeout);
			}
		}

		return(Timeout);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachine::IsStateMachineIDUnique(const CStateMachineID& StateMachineID) const
	{
		if (MStateMachineSettings->GetStateMachineID()!=StateMachineID)
		{
			if (MStateMachineChildCollectionTree.Contains(StateMachineID)==false)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachine::InitializeState(const CState& NewState)
	{
		MStateMachineCurrentState=NewState;

		MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] has been INITIALIZED to STATE [",NewState,"] !")));

		StateMachineStateChangedEvent(NewState,"");
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachine::StateMachineStartedEvent(void)
	{
		// EMPTY.
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachine::StateMachineFinishedEvent(void)
	{
		// EMPTY.
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachine::StateMachineExpiredEvent(void)
	{
		// EMPTY.
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachine::StateMachineStateChangedEvent(const CState&, const CString&)
	{
		// EMPTY.
	}
//----------------------------------------------------------------------------------------------------------------------
	// Asks STATE MACHINE if it wants to FORWARD STATE OUTPUT to PARENT STATE MACHINE.
	bool CStateMachine::StateMachineStateOutputFiringEvent(CCSPStateOutput)
	{
		bool													FireStateOutputToParentStateMachine=true;

		return(FireStateOutputToParentStateMachine);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachine::ChildStateMachineAddedEvent(void)
	{
		// EMPTY.
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachine::ChildStateMachineFinishedEvent(void)
	{
		// EMPTY.
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CLogWriter& CStateMachine::GetLogWriter(void) const noexcept
	{
		return(MLogWriter);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CLogCategory& CStateMachine::GetLogCategoryStateMachine(void) const noexcept
	{
		return(MLogCategoryStateMachine);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CString& CStateMachine::GetStateMachineName(void) const noexcept
	{
		return(MStateMachineName);
	}
//----------------------------------------------------------------------------------------------------------------------
	IStateMachineCallback& CStateMachine::GetStateMachineCallback(void) const noexcept
	{
		return(MStateMachineCallback);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CState& CStateMachine::GetState(void) const noexcept
	{
		return(MStateMachineCurrentState);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CStateMachine* CStateMachine::GetStateMachineRoot(void) const
	{
		if (MStateMachineParent!=nullptr)
		{
			return(MStateMachineParent->GetStateMachineRoot());
		}
		else
		{
			return(this);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachine* CStateMachine::GetStateMachineParent(void) const noexcept
	{
		return(MStateMachineParent);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachine::AddChildStateMachine(CSPStateMachine StateMachine)
	{
		if (StateMachine->HasStarted()==true)
		{
			ThrowStateMachineException(CString::Format("STATE MACHINE [",ToString(),"] FAILED to ADD CHILD STATE MACHINE [",StateMachine,"] because CHILD STATE MACHINE was already STARTED !"));
		}

		if (StateMachine->GetStateMachineParent()!=this)
		{
			ThrowStateMachineException(CString::Format("STATE MACHINE [",ToString(),"] FAILED to ADD CHILD STATE MACHINE [",StateMachine,"] because PARENT STATE MACHINE ID is NOT SET to CURRENT STATE MACHINE !"));
		}

		if (IsStateMachineIDUnique(StateMachine->GetStateMachineID())==false)
		{
			ThrowStateMachineException(CString::Format("STATE MACHINE [",ToString(),"] FAILED to ADD CHILD STATE MACHINE [",StateMachine,"] because STATE MACHINE ID is NOT UNIQUE !"));
		}
		else
		{
			MStateMachineChildCollection.Add(StateMachine->GetStateMachineID(),StateMachine);

			ChildStateMachineAdded(StateMachine);

			StateMachine->StartStateMachine();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachine::HasChildStateMachineByID(const CStateMachineID& StateMachineID) const
	{
		if (MStateMachineChildCollection.Contains(StateMachineID)==true)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	const CStateMachine::CStateMachineChildCollection& CStateMachine::GetChildStateMachines(void) const noexcept
	{
		return(MStateMachineChildCollection);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CStateMachine::CStateMachineChildCollection& CStateMachine::GetChildStateMachineTree(void) const noexcept
	{
		return(MStateMachineChildCollectionTree);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPStateMachine CStateMachine::GetChildStateMachineByID(const CStateMachineID& StateMachineID) const
	{
		return(GetChildStateMachineByID<CStateMachine>(StateMachineID));
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachine::HaveAllChildStateMachinesFinished(void) const noexcept
	{
		try
		{
			for(CSPStateMachine ChildStateMachine : CreateMapValueIterator(MStateMachineChildCollection))
			{
				if (ChildStateMachine->HasFinished()==false)
				{
					return(false);
				}
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while GETTING CHILD STATE MACHINES STATE !"),E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while GETTING CHILD STATE MACHINES STATE !"),CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachine::ExecuteStateMachine(CCSPStateInput StateInput, bool ExecuteInternalExecuteStateMachine) noexcept
	{
		try
		{
			if (MStateMachineInternalCurrentState==EStateMachineInternalState::E_RUNNING)
			{
				if (StateMachineTimeoutHasExpired()==false)
				{
					if (StateInput!=nullptr)
					{
						if (StateInput->HasStateMachineID()==true)
						{
							if (MStateMachineSettings->GetStateMachineID()==StateInput->GetStateMachineID())
							{
								bool							StateMachineProcessedStateInput=CallInternalExecuteStateMachine(StateInput);
			
								CheckStateMachineFinished();

								if (StateMachineProcessedStateInput==true)
								{
									return(true);
								}
								else
								{
									return(false);
								}
							}
							else if (MStateMachineChildCollectionTree.Contains(StateInput->GetStateMachineID())==true)
							{
								CStateMachine*					ChildStateMachine=MStateMachineChildCollectionTree[StateInput->GetStateMachineID()].GetPointer();

								while(ChildStateMachine->GetStateMachineParent()->GetStateMachineID()!=MStateMachineSettings->GetStateMachineID())
								{
									ChildStateMachine=ChildStateMachine->GetStateMachineParent();
								}

								bool							ChildStateMachineProcessedStateInput=ExecuteChildStateMachine(ChildStateMachine,StateInput);
	
								if (ExecuteInternalExecuteStateMachine==true)
								{
									CallInternalExecuteStateMachine(nullptr);
								}
			
								CheckStateMachineFinished();

								if (ChildStateMachineProcessedStateInput==true)
								{
									return(true);
								}
								else
								{
									return(false);
								}
							}
							else
							{
								MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED to FIND STATE MACHINE for STATE INPUT [",StateInput,"] !")));

								return(false);
							}
						}
						else
						{
							bool								StateInputProcessed=false;

							if (ExecuteChildStateMachines(StateInput)==true)
							{
								StateInputProcessed=true;
							}

							if (CallInternalExecuteStateMachine(StateInput)==true)
							{
								StateInputProcessed=true;
							}
			
							CheckStateMachineFinished();

							return(StateInputProcessed);
						}
					}
					else
					{
						ExecuteChildStateMachines(nullptr);

						CallInternalExecuteStateMachine(nullptr);

						CheckStateMachineFinished();

						return(false);
					}
				}
				else
				{
					StateMachineExpired();

					TerminateStateMachine();

					return(false);
				}
			}
			else
			{
				throw(CStateMachineException(CString::Format("STATE MACHINE [",ToString(),"] has thrown EXCEPTION [STATE MACHINE is in UNEXPECTED STATE [",MStateMachineInternalCurrentState,"] while EXECUTING STATE MACHINE !] !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while EXECUTING STATE MACHINE !"),E));

			TerminateStateMachine();

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while EXECUTING STATE MACHINE !"),CUnknownException()));

			TerminateStateMachine();

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachine::ChangeState(const CState& NewState, bool ExecuteImmediately)
	{
		ChangeState(NewState,"",ExecuteImmediately);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachine::ChangeState(const CState& NewState, const CString& Reason, bool ExecuteImmediately)
	{
		if (MStateMachineCurrentState.IsEqual(NewState)==false)
		{
			MStateMachineCurrentState=NewState;

			if (Reason.IsEmpty()==true)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] has changed STATE to [",NewState,"] !")));
			}
			else
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] has changed STATE to [",NewState,"] REASON [",Reason,"] !")));
			}

			StateMachineStateChangedEvent(NewState,Reason);
		}
		else
		{
			if (Reason.IsEmpty()==true)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] was RESET to IDENTICAL STATE [",NewState,"] !")));
			}
			else
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] was RESET to IDENTICAL STATE [",NewState,"] REASON [",Reason,"] !")));
			}
		}

		if (ExecuteImmediately==true)
		{
			MStateMachineExecuteImmediately=true;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachine::StateMachineTimeoutHasExpired(void) const
	{
		return(StateMachineTimeoutHasExpired(CSteadyClock::GetCurrentTimeInMilliseconds()));
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachine::StateMachineTimeoutHasExpired(CSteadyClock::Milliseconds TimeInMS) const
	{
		if (MStateMachineExpirationTime.HasExpired(TimeInMS)==true)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	[[noreturn]] void CStateMachine::ThrowStateMachineException(const CString& Message)
	{
		throw(CStateMachineException(CString::Format("STATE MACHINE [",ToString(),"] has thrown EXCEPTION [",Message,"] !")));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachine::FireStateOutput(CCSPStateOutput StateOutput)
	{
		if (StateOutput!=nullptr)
		{
			try
			{
				// Asks CURRENT STATE MACHINE if it wants to FORWARD STATE OUTPUT to PARENT STATE MACHINE.
				if (StateMachineStateOutputFiringEvent(StateOutput)==true)
				{
					if (MStateMachineParent!=nullptr)
					{
						MStateMachineParent->FireStateOutput(StateOutput);
					}
					else
					{
						MStateMachineCallback.ProcessStateOutput(StateOutput);
					}
				}
			}
			catch(const CException& E)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED to send STATE OUTPUT [",StateOutput,"] !"),E));
			}
			catch(...)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED to send STATE OUTPUT [",StateOutput,"] !"),CUnknownException()));
			}
		}
		else
		{
			ThrowStateMachineException(CString::Format("STATE MACHINE [",ToString(),"] is TRYING to send NULL STATE OUTPUT !"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CStateMachine::ToString(void) const
	{
		return(CString::Format(MStateMachineName," ID [",MStateMachineSettings->GetStateMachineID(),"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	const CStateMachineID& CStateMachine::GetStateMachineID(void) const noexcept
	{
		return(MStateMachineSettings->GetStateMachineID());
	}
//----------------------------------------------------------------------------------------------------------------------
	const CPriority& CStateMachine::GetStateMachinePriority(void) const noexcept
	{
		return(MStateMachineSettings->GetStateMachinePriority());
	}
//----------------------------------------------------------------------------------------------------------------------
	const CTimeout& CStateMachine::GetStateMachineExpirationTimeout(void) const noexcept
	{
		return(MStateMachineSettings->GetStateMachineExpirationTimeout());
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPStateMachineSettings CStateMachine::GetStateMachineSettings(void) const noexcept
	{
		return(MStateMachineSettings);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachine::HasStarted(void) const noexcept
	{
		if (MStateMachineInternalCurrentState==EStateMachineInternalState::E_CREATED)
		{
			return(false);
		}
		else
		{
			return(true);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachine::HasFinished(void) const noexcept
	{
		if (MStateMachineInternalCurrentState==EStateMachineInternalState::E_FINISHED)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachine::HasChildStateMachineInChildMachineTree(const CStateMachineID& StateMachineID) const
	{
		if (MStateMachineChildCollectionTree.Contains(StateMachineID)==true)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachine::StartStateMachine(void) noexcept
	{
		try
		{
			if (MStateMachineInternalCurrentState==EStateMachineInternalState::E_CREATED)
			{
				MStateMachineInternalCurrentState=EStateMachineInternalState::E_RUNNING;

				MStateMachineExpirationTime.Reset(MStateMachineSettings->GetStateMachineExpirationTimeout());

				InitializeState(InternalGetStateMachineStartState());

				StateMachineStartedEvent();

				CallInternalExecuteStateMachine(nullptr);
			
				CheckStateMachineFinished();
			}
			else
			{
				ThrowStateMachineException(CString::Format("STATE MACHINE [",ToString(),"] has thrown EXCEPTION [STATE MACHINE is in UNEXPECTED STATE [",MStateMachineInternalCurrentState,"] while STARTING STATE MACHINE !] !"));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while STARTING STATE MACHINE !"),E));

			TerminateStateMachine();
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while STARTING STATE MACHINE !"),CUnknownException()));

			TerminateStateMachine();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachine::ExecuteStateMachine(CCSPStateInput StateInput) noexcept
	{
		bool													StateInputProcessed=ExecuteStateMachine(StateInput,true);

		return(StateInputProcessed);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! ALWAYS brings STATE MACHINE to FINAL STATE.
	void CStateMachine::TerminateStateMachine(void) noexcept
	{
		try
		{
			if (MStateMachineInternalCurrentState==EStateMachineInternalState::E_CREATED || MStateMachineInternalCurrentState==EStateMachineInternalState::E_RUNNING)
			{
				// Terminates ALL CHILD STATE MACHINES.
				TerminateChildStateMachines();

				try
				{
					InternalTerminateStateMachine();

					if (MStateMachineCurrentState.IsValidState()==false || MStateMachineCurrentState.IsFinalState()==false)
					{
						MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED to CHANGE STATE to FINAL STATE by EXECUTING INTERNAL TERMINATE STATE MACHINE METHOD !")));
					}
				}
				catch(const CException& E)
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while EXECUTING INTERNAL TERMINATE STATE MACHINE METHOD !"),E));
				}
				catch(...)
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while EXECUTING INTERNAL TERMINATE STATE MACHINE METHOD !"),CUnknownException()));
				}

				StateMachineFinished();
			}
			else if (MStateMachineInternalCurrentState==EStateMachineInternalState::E_FINISHED)
			{
				// Do NOTHING.
			}
			else
			{
				ThrowStateMachineException(CString::Format("STATE MACHINE [",ToString(),"] is in UNEXPECTED STATE [",MStateMachineInternalCurrentState,"] while TERMINATING STATE MACHINE !"));
			}
		}
		catch(const CException& E)
		{
			StateMachineFinished();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while TERMINATING STATE MACHINE !"),E));
		}
		catch(...)
		{
			StateMachineFinished();
			
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while TERMINATING STATE MACHINE !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CStateMachine::GetStateMachineTimeout(CSteadyClock::Milliseconds TimeInMS) noexcept
	{
		try
		{
			if (MStateMachineInternalCurrentState==EStateMachineInternalState::E_RUNNING)
			{
				CTimeout										Timeout;

				if (MStateMachineExecuteImmediately==false)
				{
					CTimeout									StateMachineTimeout=MStateMachineExpirationTime.CalculateTimeout(TimeInMS);
					CTimeout									ChildStateMachinesTimeout=GetChildStateMachinesTimeout(TimeInMS);
					CTimeout									ExecutionTimeout=InternalGetStateMachineTimeout(TimeInMS);

					Timeout=CTimeout::Min({StateMachineTimeout,ChildStateMachinesTimeout,ExecutionTimeout});
				}
				else
				{
					MStateMachineExecuteImmediately=false;

					Timeout=CTimeout::GetZero();
				}

				return(Timeout);
			}
			else
			{
				throw(CStateMachineException(CString::Format("STATE MACHINE [",ToString(),"] has thrown EXCEPTION [STATE MACHINE is in UNEXPECTED STATE [",MStateMachineInternalCurrentState,"] while GETTING STATE MACHINE EXECUTION TIME !] !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while GETTING STATE MACHINE EXECUTION TIME !"),E));

			TerminateStateMachine();

			return(CTimeout::GetZero());
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryStateMachine(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("STATE MACHINE [",ToString(),"] FAILED while GETTING STATE MACHINE EXECUTION TIME !"),CUnknownException()));

			TerminateStateMachine();

			return(CTimeout::GetZero());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------