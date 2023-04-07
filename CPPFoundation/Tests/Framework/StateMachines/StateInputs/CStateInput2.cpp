//----------------------------------------------------------------------------------------------------------------------
#include "CStateInput2.h"
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
	CStateInput2::CStateInput2(const CString& Data)
		: MData(Data)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInput2::CStateInput2(const CStateMachineID& StateMachineID, const CString& Data)
		: CStateInput(StateMachineID), MData(Data)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInput2::CStateInput2(CStateMachineID&& StateMachineID, const CString& Data)
		: CStateInput(FUNCTION_MOVE(StateMachineID)), MData(Data)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInput2::CStateInput2(const CStateInput2& Other)
		: CStateInput(Other), MData(Other.MData)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInput2::CStateInput2(CStateInput2&& Other) noexcept
		: CStateInput(FUNCTION_MOVE(Other)), MData(FUNCTION_MOVE(Other.MData))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInput2::~CStateInput2(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CStateInput2& CStateInput2::operator=(const CStateInput2& Other)
	{
		CStateInput::operator=(Other);

		MData=Other.MData;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInput2& CStateInput2::operator=(CStateInput2&& Other) noexcept
	{
		CStateInput::operator=(FUNCTION_MOVE(Other));

		MData=FUNCTION_MOVE(Other.MData);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CString& CStateInput2::GetData(void) const noexcept
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------