//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <vector>
#include <memory>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Logger/CLogWriter.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CTest.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CTestManager final : public CPPFoundation::Foundation::CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CPPFoundation::Foundation::CLogWriter&					MLogWriter;
			CPPFoundation::Foundation::CLogCategory				MLogCategoryTest;
			CTestCollection										MTestCollection;

		public:
			CPPFoundation::Foundation::CLogWriter& GetLogWriter(void) noexcept;
			const CPPFoundation::Foundation::CLogCategory& GetLogCategoryTest(void) const noexcept;

		public:
			bool ExecuteTests(void);

		public:
			CTestManager(CPPFoundation::Foundation::CLogWriter& LogWriter, const CPPFoundation::Foundation::CLogCategory& LogCategoryTest, const CTestCollection& TestCollection);
			virtual ~CTestManager(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------