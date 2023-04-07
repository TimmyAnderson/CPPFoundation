//----------------------------------------------------------------------------------------------------------------------
#include "CStateMachineCollection.h"
#include <Framework/Foundation/StateMachines/StateMachines/CStateMachine.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineCollection::CStateMachineCollection(void)
		: MCollection()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineCollection::~CStateMachineCollection(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	Size CStateMachineCollection::GetLength(void) const
	{
		return(MCollection.GetLength());
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineCollection::IsEmpty(void) const
	{
		if (MCollection.GetLength()==0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachineCollection::AddStateMachine(CSPStateMachine StateMachine)
	{
		MCollection.Add(StateMachine->GetStateMachineID(),StateMachine);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineCollection::RemoveStateMachine(const CStateMachineID& StateMachineID)
	{
		return(MCollection.Erase(StateMachineID));
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineCollection::HasStateMachineByID(const CStateMachineID& StateMachineID) const
	{
		if (MCollection.Contains(StateMachineID)==true)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPStateMachine CStateMachineCollection::GetStateMachineByID(const CStateMachineID& StateMachineID) const
	{
		if (MCollection.Contains(StateMachineID)==true)
		{
			return(MCollection[StateMachineID]);
		}
		else
		{
			return(CSPStateMachine());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPStateMachine CStateMachineCollection::GetRootStateMachineForStateMachineID(const CStateMachineID& StateMachineID) const
	{
		if (HasStateMachineByID(StateMachineID)==true)
		{
			return(MCollection[StateMachineID]);
		}
		else
		{
			for(CSPStateMachine StateMachine : CreateMapValueIterator(MCollection))
			{
				if (StateMachine->HasChildStateMachineInChildMachineTree(StateMachineID)==true)
				{
					return(StateMachine);
				}
			}

			return(CSPStateMachine());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineCollection::CStateMachineMapIterator CStateMachineCollection::Begin(void)
	{
		return(MCollection.Begin());
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineCollection::CStateMachineMapIterator CStateMachineCollection::End(void)
	{
		return(MCollection.End());
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineCollection::CStateMachineMapIteratorConst CStateMachineCollection::Begin(void) const
	{
		return(MCollection.Begin());
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineCollection::CStateMachineMapIteratorConst CStateMachineCollection::End(void) const
	{
		return(MCollection.End());
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineCollection::CStateMachineMapValueIterator CStateMachineCollection::BeginValue(void)
	{
		return(MCollection.BeginValue());
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineCollection::CStateMachineMapValueIterator CStateMachineCollection::EndValue(void)
	{
		return(MCollection.EndValue());
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineCollection::CStateMachineMapValueIteratorConst CStateMachineCollection::BeginValue(void) const
	{
		return(MCollection.BeginValue());
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineCollection::CStateMachineMapValueIteratorConst CStateMachineCollection::EndValue(void) const
	{
		return(MCollection.EndValue());
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineCollection::CStateMachineMapIterator CStateMachineCollection::begin(void)
	{
		return(MCollection.begin());
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineCollection::CStateMachineMapIterator CStateMachineCollection::end(void)
	{
		return(MCollection.end());
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineCollection::CStateMachineMapIteratorConst CStateMachineCollection::begin(void) const
	{
		return(MCollection.begin());
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineCollection::CStateMachineMapIteratorConst CStateMachineCollection::end(void) const
	{
		return(MCollection.end());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------