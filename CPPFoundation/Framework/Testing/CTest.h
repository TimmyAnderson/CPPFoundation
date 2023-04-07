//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Logger/CLogWriter.h>
#include <Framework/Foundation/Types/CMethod.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CTest : public virtual CPPFoundation::Foundation::CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		protected:
			template<typename TTestClass>
			using												CTestMethod=CPPFoundation::Foundation::CMethod<TTestClass,bool(void)>;

		private:
			CPPFoundation::Foundation::CLogWriter&					MLogWriter;
			CPPFoundation::Foundation::CLogCategory				MLogCategoryTest;
			CPPFoundation::Foundation::CString						MName;

		protected:
			CPPFoundation::Foundation::CString GetSeparator(bool AddNewLine) const;

		public:
			virtual bool ExecuteTest(void)=0;

		public:
			CPPFoundation::Foundation::CLogWriter& GetLogWriter(void) noexcept;
			const CPPFoundation::Foundation::CLogCategory& GetLogCategoryTest(void) const noexcept;
			const CPPFoundation::Foundation::CString& GetName(void) const noexcept;

		public:
			CTest(CPPFoundation::Foundation::CLogWriter& LogWriter, const CPPFoundation::Foundation::CLogCategory& LogCategoryTest, const CPPFoundation::Foundation::CString& Name);
			virtual ~CTest(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPTest=CPPFoundation::Foundation::CSharedPointer<CTest>;
	using														CCSPTest=CPPFoundation::Foundation::CSharedPointer<const CTest>;
	using														CTestCollection=CPPFoundation::Foundation::CVector<CSPTest>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------