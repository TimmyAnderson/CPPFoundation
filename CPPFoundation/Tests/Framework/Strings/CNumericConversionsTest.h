//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Testing/CTest.h>
#include <Framework/Foundation/Strings/CIntegerFormatter.h>
#include <Framework/Foundation/Strings/CFloatFormatter.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CNumericConversionsTest final : public CTest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CPPFoundation::Foundation::CInt8Formatter				MFormatterInt8Decimal;
			CPPFoundation::Foundation::CInt8Formatter				MFormatterInt8DecimalWithPadding;
			CPPFoundation::Foundation::CInt8Formatter				MFormatterInt8HexaDecimal;
			CPPFoundation::Foundation::CInt8Formatter				MFormatterInt8HexaDecimalWithPrefix1;
			CPPFoundation::Foundation::CInt8Formatter				MFormatterInt8HexaDecimalWithPrefix2;
			CPPFoundation::Foundation::CUInt8Formatter				MUFormatterInt8Decimal;
			CPPFoundation::Foundation::CUInt8Formatter				MUFormatterInt8HexaDecimal;
			CPPFoundation::Foundation::CUInt8Formatter				MUFormatterInt8HexaDecimalWithPrefix;
			CPPFoundation::Foundation::CInt16Formatter				MFormatterInt16Decimal;
			CPPFoundation::Foundation::CInt16Formatter				MFormatterInt16HexaDecimal;
			CPPFoundation::Foundation::CInt16Formatter				MFormatterInt16HexaDecimalWithPrefix;
			CPPFoundation::Foundation::CUInt16Formatter			MUFormatterInt16Decimal;
			CPPFoundation::Foundation::CUInt16Formatter			MUFormatterInt16HexaDecimal;
			CPPFoundation::Foundation::CUInt16Formatter			MUFormatterInt16HexaDecimalWithPrefix;
			CPPFoundation::Foundation::CInt32Formatter				MFormatterInt32Decimal;
			CPPFoundation::Foundation::CInt32Formatter				MFormatterInt32DecimalWithPadding;
			CPPFoundation::Foundation::CInt32Formatter				MFormatterInt32HexaDecimal;
			CPPFoundation::Foundation::CInt32Formatter				MFormatterInt32HexaDecimalWithPrefix1;
			CPPFoundation::Foundation::CInt32Formatter				MFormatterInt32HexaDecimalWithPrefix2;
			CPPFoundation::Foundation::CUInt32Formatter			MUFormatterInt32Decimal;
			CPPFoundation::Foundation::CUInt32Formatter			MUFormatterInt32HexaDecimal;
			CPPFoundation::Foundation::CUInt32Formatter			MUFormatterInt32HexaDecimalWithPrefix;
			CPPFoundation::Foundation::CInt64Formatter				MFormatterInt64Decimal;
			CPPFoundation::Foundation::CInt64Formatter				MFormatterInt64HexaDecimal;
			CPPFoundation::Foundation::CInt64Formatter				MFormatterInt64HexaDecimalWithPrefix;
			CPPFoundation::Foundation::CUInt64Formatter			MUFormatterInt64Decimal;
			CPPFoundation::Foundation::CUInt64Formatter			MUFormatterInt64HexaDecimal;
			CPPFoundation::Foundation::CUInt64Formatter			MUFormatterInt64HexaDecimalWithPrefix;
			CPPFoundation::Foundation::CFloat32Formatter			MFormatterFloat32;
			CPPFoundation::Foundation::CFloat32Formatter			MFormatterFloat32WithPrecision;
			CPPFoundation::Foundation::CFloat64Formatter			MFormatterFloat64;
			CPPFoundation::Foundation::CFloat64Formatter			MFormatterFloat64WithPrecision;
			CPPFoundation::Foundation::CFloat80Formatter			MFormatterFloat80;
			CPPFoundation::Foundation::CFloat80Formatter			MFormatterFloat80WithPrecision;

		private:
			bool TestInt8Decimal(void);
			bool TestInt8DecimalWithPadding(void);
			bool TestInt8HexaDecimal(void);
			bool TestInt8HexaDecimalWithPrefix1(void);
			bool TestInt8HexaDecimalWithPrefix2(void);
			bool TestUInt8Decimal(void);
			bool TestUInt8HexaDecimal(void);
			bool TestUInt8HexaDecimalWithPrefix(void);
			bool TestInt16Decimal(void);
			bool TestInt16HexaDecimal(void);
			bool TestInt16HexaDecimalWithPrefix(void);
			bool TestUInt16Decimal(void);
			bool TestUInt16HexaDecimal(void);
			bool TestUInt16HexaDecimalWithPrefix(void);
			bool TestInt32Decimal(void);
			bool TestInt32DecimalWithPadding(void);
			bool TestInt32HexaDecimal(void);
			bool TestInt32HexaDecimalWithPrefix1(void);
			bool TestInt32HexaDecimalWithPrefix2(void);
			bool TestUInt32Decimal(void);
			bool TestUInt32HexaDecimal(void);
			bool TestUInt32HexaDecimalWithPrefix(void);
			bool TestInt64Decimal(void);
			bool TestInt64HexaDecimal(void);
			bool TestInt64HexaDecimalWithPrefix(void);
			bool TestUInt64Decimal(void);
			bool TestUInt64HexaDecimal(void);
			bool TestUInt64HexaDecimalWithPrefix(void);
			bool TestFloat32(void);
			bool TestFloat32WithPrecision(void);
			bool TestFloat64(void);
			bool TestFloat64WithPrecision(void);
			bool TestFloat80(void);
			bool TestFloat80WithPrecision(void);

		public:
			virtual bool ExecuteTest(void) override;

		public:
			CNumericConversionsTest(CPPFoundation::Foundation::CLogWriter& LogWriter, const CPPFoundation::Foundation::CLogCategory& LogCategoryTest);
			virtual ~CNumericConversionsTest(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------