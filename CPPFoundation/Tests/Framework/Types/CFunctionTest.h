//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Testing/CTest.h>
#include <Framework/Foundation/Types/CFunction.h>
#include <Framework/Foundation/Types/CMethod.h>
#include "CFunctionTestClass.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CFunctionTest final : public CTest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			static int32 FunctionTest1(int32 Value);
			static int32 FunctionTest2(int32 Value);
			static int32 FunctionTest3(int32 Value, const CFunctionTestBase& Class);
			static int32 TestFunctionTransfer1(const CPPFoundation::Foundation::CFunction<int32(int32,CFunctionTestBase&)>& Function);
			static int32 TestFunctionTransfer2(CPPFoundation::Foundation::CFunction<int32(int32,CFunctionTestBase&)> Function);

		private:
			int32 TestMethodTransfer1(const CPPFoundation::Foundation::CMethod<CFunctionTestClass,int32(int32,CFunctionTestBase&)>& Method);
			int32 TestMethodTransfer2(CPPFoundation::Foundation::CMethod<CFunctionTestClass,int32(int32,CFunctionTestBase&)> Method);

		private:
			bool TestFunction(void);
			bool TestMethod(void);

		public:
			virtual bool ExecuteTest(void) override;

		public:
			CFunctionTest(CPPFoundation::Foundation::CLogWriter& LogWriter, const CPPFoundation::Foundation::CLogCategory& LogCategoryTest);
			virtual ~CFunctionTest(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------