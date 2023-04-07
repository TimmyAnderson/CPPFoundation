//----------------------------------------------------------------------------------------------------------------------
#include "CFunctionTestDerived1.h"
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
	CFunctionTestDerived1::CFunctionTestDerived1(int32 BaseValue, int32 DerivedValue1)
		: CFunctionTestBase(BaseValue), MDerivedValue1(DerivedValue1)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CFunctionTestDerived1::~CFunctionTestDerived1(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CFunctionTestDerived1::GetText(void) const
	{
		return(CString::Format("BASE [",MBaseValue,"] DERIVED VALUE 1 [",MDerivedValue1,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CFunctionTestDerived1::GetSum(void) const
	{
		return(MBaseValue+MDerivedValue1);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------