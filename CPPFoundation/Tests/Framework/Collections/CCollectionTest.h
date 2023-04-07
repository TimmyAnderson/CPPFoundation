//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Testing/CTest.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CCollectionTest final : public CTest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			bool TestSet1(void);
			bool TestSet2(void);

		private:
			bool TestMultiSet1(void);
			bool TestMultiSet2(void);

		private:
			bool TestMap1(void);
			bool TestMap2(void);
			bool TestMap3(void);
			bool TestMap4(void);
			bool TestMap5(void);

		private:
			bool TestMultiMap1(void);
			bool TestMultiMap2(void);
			bool TestMultiMap3(void);
			bool TestMultiMap4(void);
			bool TestMultiMap5(void);

		private:
			bool TestTuple1(void);
			bool TestTuple2(void);

		public:
			virtual bool ExecuteTest(void) override;

		public:
			CCollectionTest(CPPFoundation::Foundation::CLogWriter& LogWriter, const CPPFoundation::Foundation::CLogCategory& LogCategoryTest);
			virtual ~CCollectionTest(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------