//----------------------------------------------------------------------------------------------------------------------
#include "CNumericConversionsTest.h"
#include <limits>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Console/CConsoleHelper.h>
#include <Framework/Foundation/Types/CMethod.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace std;
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CNumericConversionsTest::CNumericConversionsTest(CLogWriter& LogWriter, const CLogCategory& LogCategoryTest)
		: CTest(LogWriter,LogCategoryTest,"CONVERSION TEST"), MFormatterInt8Decimal(), MFormatterInt8DecimalWithPadding(EIntegerFormat::E_NONE,25,true), MFormatterInt8HexaDecimal(EIntegerFormat::E_HEXADECIMAL), MFormatterInt8HexaDecimalWithPrefix1(EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX,5,true), MFormatterInt8HexaDecimalWithPrefix2(EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX,25,true), MUFormatterInt8Decimal(), MUFormatterInt8HexaDecimal(EIntegerFormat::E_HEXADECIMAL), MUFormatterInt8HexaDecimalWithPrefix(EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX,5,true), MFormatterInt16Decimal(), MFormatterInt16HexaDecimal(EIntegerFormat::E_HEXADECIMAL), MFormatterInt16HexaDecimalWithPrefix(EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX,5,true), MUFormatterInt16Decimal(), MUFormatterInt16HexaDecimal(EIntegerFormat::E_HEXADECIMAL), MUFormatterInt16HexaDecimalWithPrefix(EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX,5,true), MFormatterInt32Decimal(), MFormatterInt32DecimalWithPadding(EIntegerFormat::E_NONE,25,true), MFormatterInt32HexaDecimal(EIntegerFormat::E_HEXADECIMAL), MFormatterInt32HexaDecimalWithPrefix1(EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX,5,true), MFormatterInt32HexaDecimalWithPrefix2(EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX,25,true), MUFormatterInt32Decimal(), MUFormatterInt32HexaDecimal(EIntegerFormat::E_HEXADECIMAL), MUFormatterInt32HexaDecimalWithPrefix(EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX,5,true), MFormatterInt64Decimal(), MFormatterInt64HexaDecimal(EIntegerFormat::E_HEXADECIMAL), MFormatterInt64HexaDecimalWithPrefix(EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX,5,true), MUFormatterInt64Decimal(), MUFormatterInt64HexaDecimal(EIntegerFormat::E_HEXADECIMAL), MUFormatterInt64HexaDecimalWithPrefix(EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX,5,true), MFormatterFloat32(), MFormatterFloat32WithPrecision(5,12,'0',EPaddingDirection::E_INTERNAL), MFormatterFloat64(), MFormatterFloat64WithPrecision(5,12,'0',EPaddingDirection::E_INTERNAL), MFormatterFloat80(), MFormatterFloat80WithPrecision(5,12,'0',EPaddingDirection::E_INTERNAL)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CNumericConversionsTest::~CNumericConversionsTest(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestInt8Decimal(void)
	{
		int8													Input1=100;
		int8													Output1=0;
		CString													TextInput1=MFormatterInt8Decimal.ConvertToString(Input1);
		bool													Parsed1=MFormatterInt8Decimal.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 DECIMAL - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		int8													Input2=0;
		int8													Output2=0;
		CString													TextInput2=MFormatterInt8Decimal.ConvertToString(Input2);
		bool													Parsed2=MFormatterInt8Decimal.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 DECIMAL - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		int8													Input3=-100;
		int8													Output3=0;
		CString													TextInput3=MFormatterInt8Decimal.ConvertToString(Input3);
		bool													Parsed3=MFormatterInt8Decimal.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 DECIMAL - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		int8													Input4=numeric_limits<int8>::max();
		int8													Output4=0;
		CString													TextInput4=MFormatterInt8Decimal.ConvertToString(Input4);
		bool													Parsed4=MFormatterInt8Decimal.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 DECIMAL - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		int8													Input5=numeric_limits<int8>::lowest();
		int8													Output5=0;
		CString													TextInput5=MFormatterInt8Decimal.ConvertToString(Input5);
		bool													Parsed5=MFormatterInt8Decimal.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 DECIMAL - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		int8													Output6=0;
		bool													Parsed6=MFormatterInt8Decimal.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 DECIMAL - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		int8													Output7=0;
		CString													TextInput7("-150");
		bool													Parsed7=MFormatterInt8Decimal.Parse(TextInput7,Output7);

		if (Parsed7==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 DECIMAL - 7 FAILED [",TextInput7,",",Output7,"] !\n"));

			return(false);
		}

		int8													Output8=0;
		CString													TextInput8("150");
		bool													Parsed8=MFormatterInt8Decimal.Parse(TextInput8,Output8);

		if (Parsed8==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 DECIMAL - 8 FAILED [",TextInput8,",",Output8,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestInt8DecimalWithPadding(void)
	{
		int8													Input1=100;
		int8													Output1=0;
		CString													TextInput1=MFormatterInt8DecimalWithPadding.ConvertToString(Input1);
		bool													Parsed1=MFormatterInt8DecimalWithPadding.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 DECIMAL with PADDING - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		int8													Input2=0;
		int8													Output2=0;
		CString													TextInput2=MFormatterInt8DecimalWithPadding.ConvertToString(Input2);
		bool													Parsed2=MFormatterInt8DecimalWithPadding.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 DECIMAL with PADDING - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		int8													Input3=-100;
		int8													Output3=0;
		CString													TextInput3=MFormatterInt8DecimalWithPadding.ConvertToString(Input3);
		bool													Parsed3=MFormatterInt8DecimalWithPadding.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 DECIMAL with PADDING - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		int8													Input4=numeric_limits<int8>::max();
		int8													Output4=0;
		CString													TextInput4=MFormatterInt8DecimalWithPadding.ConvertToString(Input4);
		bool													Parsed4=MFormatterInt8DecimalWithPadding.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 DECIMAL with PADDING - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		int8													Input5=numeric_limits<int8>::lowest();
		int8													Output5=0;
		CString													TextInput5=MFormatterInt8DecimalWithPadding.ConvertToString(Input5);
		bool													Parsed5=MFormatterInt8DecimalWithPadding.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 DECIMAL with PADDING - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		int8													Output6=0;
		bool													Parsed6=MFormatterInt8DecimalWithPadding.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 DECIMAL with PADDING - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestInt8HexaDecimal(void)
	{
		int8													Input1=100;
		int8													Output1=0;
		CString													TextInput1=MFormatterInt8HexaDecimal.ConvertToString(Input1);
		bool													Parsed1=MFormatterInt8HexaDecimal.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 HEXADECIMAL - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		int8													Input2=0;
		int8													Output2=0;
		CString													TextInput2=MFormatterInt8HexaDecimal.ConvertToString(Input2);
		bool													Parsed2=MFormatterInt8HexaDecimal.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 HEXADECIMAL - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		int8													Input3=-100;
		int8													Output3=0;
		CString													TextInput3=MFormatterInt8HexaDecimal.ConvertToString(Input3);
		bool													Parsed3=MFormatterInt8HexaDecimal.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 HEXADECIMAL - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		int8													Input4=numeric_limits<int8>::max();
		int8													Output4=0;
		CString													TextInput4=MFormatterInt8HexaDecimal.ConvertToString(Input4);
		bool													Parsed4=MFormatterInt8HexaDecimal.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 HEXADECIMAL - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		int8													Input5=numeric_limits<int8>::lowest();
		int8													Output5=0;
		CString													TextInput5=MFormatterInt8HexaDecimal.ConvertToString(Input5);
		bool													Parsed5=MFormatterInt8HexaDecimal.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 HEXADECIMAL - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		int8													Output6=0;
		bool													Parsed6=MFormatterInt8HexaDecimal.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 HEXADECIMAL - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		int8													Output7=0;
		CString													TextInput7("-150");
		bool													Parsed7=MFormatterInt8HexaDecimal.Parse(TextInput7,Output7);

		if (Parsed7==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 HEXADECIMAL - 7 FAILED [",TextInput7,",",Output7,"] !\n"));

			return(false);
		}

		int8													Output8=0;
		CString													TextInput8("150");
		bool													Parsed8=MFormatterInt8HexaDecimal.Parse(TextInput8,Output8);

		if (Parsed8==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 HEXADECIMAL - 8 FAILED [",TextInput8,",",Output8,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestInt8HexaDecimalWithPrefix1(void)
	{
		int8													Input1=100;
		int8													Output1=0;
		CString													TextInput1=MFormatterInt8HexaDecimalWithPrefix1.ConvertToString(Input1);
		bool													Parsed1=MFormatterInt8HexaDecimalWithPrefix1.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 HEXADECIMAL with PREFIX 1 - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		int8													Input2=0;
		int8													Output2=0;
		CString													TextInput2=MFormatterInt8HexaDecimalWithPrefix1.ConvertToString(Input2);
		bool													Parsed2=MFormatterInt8HexaDecimalWithPrefix1.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 HEXADECIMAL with PREFIX 1 - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		int8													Input3=-100;
		int8													Output3=0;
		CString													TextInput3=MFormatterInt8HexaDecimalWithPrefix1.ConvertToString(Input3);
		bool													Parsed3=MFormatterInt8HexaDecimalWithPrefix1.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 HEXADECIMAL with PREFIX 1 - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		int8													Input4=numeric_limits<int8>::max();
		int8													Output4=0;
		CString													TextInput4=MFormatterInt8HexaDecimalWithPrefix1.ConvertToString(Input4);
		bool													Parsed4=MFormatterInt8HexaDecimalWithPrefix1.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 HEXADECIMAL with PREFIX 1 - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		int8													Input5=numeric_limits<int8>::lowest();
		int8													Output5=0;
		CString													TextInput5=MFormatterInt8HexaDecimalWithPrefix1.ConvertToString(Input5);
		bool													Parsed5=MFormatterInt8HexaDecimalWithPrefix1.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 HEXADECIMAL with PREFIX 1 - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		int8													Output6=0;
		bool													Parsed6=MFormatterInt8HexaDecimalWithPrefix1.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 HEXADECIMAL with PREFIX 1 - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestInt8HexaDecimalWithPrefix2(void)
	{
		int8													Input1=100;
		int8													Output1=0;
		CString													TextInput1=MFormatterInt8HexaDecimalWithPrefix2.ConvertToString(Input1);
		bool													Parsed1=MFormatterInt8HexaDecimalWithPrefix2.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 HEXADECIMAL with PREFIX 2 - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		int8													Input2=0;
		int8													Output2=0;
		CString													TextInput2=MFormatterInt8HexaDecimalWithPrefix2.ConvertToString(Input2);
		bool													Parsed2=MFormatterInt8HexaDecimalWithPrefix2.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 HEXADECIMAL with PREFIX 2 - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		int8													Input3=-100;
		int8													Output3=0;
		CString													TextInput3=MFormatterInt8HexaDecimalWithPrefix2.ConvertToString(Input3);
		bool													Parsed3=MFormatterInt8HexaDecimalWithPrefix2.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 HEXADECIMAL with PREFIX 2 - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		int8													Input4=numeric_limits<int8>::max();
		int8													Output4=0;
		CString													TextInput4=MFormatterInt8HexaDecimalWithPrefix2.ConvertToString(Input4);
		bool													Parsed4=MFormatterInt8HexaDecimalWithPrefix2.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 HEXADECIMAL with PREFIX 2 - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		int8													Input5=numeric_limits<int8>::lowest();
		int8													Output5=0;
		CString													TextInput5=MFormatterInt8HexaDecimalWithPrefix2.ConvertToString(Input5);
		bool													Parsed5=MFormatterInt8HexaDecimalWithPrefix2.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 HEXADECIMAL with PREFIX 2 - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		int8													Output6=0;
		bool													Parsed6=MFormatterInt8HexaDecimalWithPrefix2.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int8 HEXADECIMAL with PREFIX 2 - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestUInt8Decimal(void)
	{
		uint8													Input1=100;
		uint8													Output1=0;
		CString													TextInput1=MUFormatterInt8Decimal.ConvertToString(Input1);
		bool													Parsed1=MUFormatterInt8Decimal.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 DECIMAL - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		uint8													Input2=0;
		uint8													Output2=0;
		CString													TextInput2=MUFormatterInt8Decimal.ConvertToString(Input2);
		bool													Parsed2=MUFormatterInt8Decimal.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 DECIMAL - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		uint8													Input3=uint8(-100);
		uint8													Output3=0;
		CString													TextInput3=MUFormatterInt8Decimal.ConvertToString(Input3);
		bool													Parsed3=MUFormatterInt8Decimal.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 DECIMAL - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		uint8													Input4=numeric_limits<uint8>::max();
		uint8													Output4=0;
		CString													TextInput4=MUFormatterInt8Decimal.ConvertToString(Input4);
		bool													Parsed4=MUFormatterInt8Decimal.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 DECIMAL - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		uint8													Input5=numeric_limits<uint8>::lowest();
		uint8													Output5=0;
		CString													TextInput5=MUFormatterInt8Decimal.ConvertToString(Input5);
		bool													Parsed5=MUFormatterInt8Decimal.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 DECIMAL - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		uint8													Output6=0;
		bool													Parsed6=MUFormatterInt8Decimal.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 DECIMAL - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		uint8													Output7=0;
		CString													TextInput7("-350");
		bool													Parsed7=MUFormatterInt8Decimal.Parse(TextInput7,Output7);

		if (Parsed7==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 DECIMAL - 7 FAILED [",TextInput7,",",Output7,"] !\n"));

			return(false);
		}

		uint8													Output8=0;
		CString													TextInput8("350");
		bool													Parsed8=MUFormatterInt8Decimal.Parse(TextInput8,Output8);

		if (Parsed8==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 DECIMAL - 8 FAILED [",TextInput8,",",Output8,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestUInt8HexaDecimal(void)
	{
		uint8													Input1=100;
		uint8													Output1=0;
		CString													TextInput1=MUFormatterInt8HexaDecimal.ConvertToString(Input1);
		bool													Parsed1=MUFormatterInt8HexaDecimal.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 HEXADECIMAL - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		uint8													Input2=0;
		uint8													Output2=0;
		CString													TextInput2=MUFormatterInt8HexaDecimal.ConvertToString(Input2);
		bool													Parsed2=MUFormatterInt8HexaDecimal.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 HEXADECIMAL - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		uint8													Input3=uint8(-100);
		uint8													Output3=0;
		CString													TextInput3=MUFormatterInt8HexaDecimal.ConvertToString(Input3);
		bool													Parsed3=MUFormatterInt8HexaDecimal.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 HEXADECIMAL - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		uint8													Input4=numeric_limits<uint8>::max();
		uint8													Output4=0;
		CString													TextInput4=MUFormatterInt8HexaDecimal.ConvertToString(Input4);
		bool													Parsed4=MUFormatterInt8HexaDecimal.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 HEXADECIMAL - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		uint8													Input5=numeric_limits<uint8>::lowest();
		uint8													Output5=0;
		CString													TextInput5=MUFormatterInt8HexaDecimal.ConvertToString(Input5);
		bool													Parsed5=MUFormatterInt8HexaDecimal.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 HEXADECIMAL - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		uint8													Output6=0;
		bool													Parsed6=MUFormatterInt8HexaDecimal.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 HEXADECIMAL - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		uint8													Output7=0;
		CString													TextInput7("-350");
		bool													Parsed7=MUFormatterInt8HexaDecimal.Parse(TextInput7,Output7);

		if (Parsed7==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 HEXADECIMAL - 7 FAILED [",TextInput7,",",Output7,"] !\n"));

			return(false);
		}

		uint8													Output8=0;
		CString													TextInput8("350");
		bool													Parsed8=MUFormatterInt8HexaDecimal.Parse(TextInput8,Output8);

		if (Parsed8==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 HEXADECIMAL - 8 FAILED [",TextInput8,",",Output8,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestUInt8HexaDecimalWithPrefix(void)
	{
		uint8													Input1=100;
		uint8													Output1=0;
		CString													TextInput1=MUFormatterInt8HexaDecimalWithPrefix.ConvertToString(Input1);
		bool													Parsed1=MUFormatterInt8HexaDecimalWithPrefix.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 HEXADECIMAL with PREFIX - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		uint8													Input2=0;
		uint8													Output2=0;
		CString													TextInput2=MUFormatterInt8HexaDecimalWithPrefix.ConvertToString(Input2);
		bool													Parsed2=MUFormatterInt8HexaDecimalWithPrefix.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 HEXADECIMAL with PREFIX - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		uint8													Input3=uint8(-100);
		uint8													Output3=0;
		CString													TextInput3=MUFormatterInt8HexaDecimalWithPrefix.ConvertToString(Input3);
		bool													Parsed3=MUFormatterInt8HexaDecimalWithPrefix.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 HEXADECIMAL with PREFIX - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		uint8													Input4=numeric_limits<uint8>::max();
		uint8													Output4=0;
		CString													TextInput4=MUFormatterInt8HexaDecimalWithPrefix.ConvertToString(Input4);
		bool													Parsed4=MUFormatterInt8HexaDecimalWithPrefix.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 HEXADECIMAL with PREFIX - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		uint8													Input5=numeric_limits<uint8>::lowest();
		uint8													Output5=0;
		CString													TextInput5=MUFormatterInt8HexaDecimalWithPrefix.ConvertToString(Input5);
		bool													Parsed5=MUFormatterInt8HexaDecimalWithPrefix.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 HEXADECIMAL with PREFIX - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		uint8													Output6=0;
		bool													Parsed6=MUFormatterInt8HexaDecimalWithPrefix.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint8 HEXADECIMAL with PREFIX - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestInt16Decimal(void)
	{
		int16													Input1=100;
		int16													Output1=0;
		CString													TextInput1=MFormatterInt16Decimal.ConvertToString(Input1);
		bool													Parsed1=MFormatterInt16Decimal.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int16 DECIMAL - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		int16													Input2=0;
		int16													Output2=0;
		CString													TextInput2=MFormatterInt16Decimal.ConvertToString(Input2);
		bool													Parsed2=MFormatterInt16Decimal.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int16 DECIMAL - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		int16													Input3=-100;
		int16													Output3=0;
		CString													TextInput3=MFormatterInt16Decimal.ConvertToString(Input3);
		bool													Parsed3=MFormatterInt16Decimal.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int16 DECIMAL - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		int16													Input4=numeric_limits<int16>::max();
		int16													Output4=0;
		CString													TextInput4=MFormatterInt16Decimal.ConvertToString(Input4);
		bool													Parsed4=MFormatterInt16Decimal.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int16 DECIMAL - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		int16													Input5=numeric_limits<int16>::lowest();
		int16													Output5=0;
		CString													TextInput5=MFormatterInt16Decimal.ConvertToString(Input5);
		bool													Parsed5=MFormatterInt16Decimal.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int16 DECIMAL - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		int16													Output6=0;
		bool													Parsed6=MFormatterInt16Decimal.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int16 DECIMAL - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestInt16HexaDecimal(void)
	{
		int16													Input1=100;
		int16													Output1=0;
		CString													TextInput1=MFormatterInt16HexaDecimal.ConvertToString(Input1);
		bool													Parsed1=MFormatterInt16HexaDecimal.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int16 HEXADECIMAL - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		int16													Input2=0;
		int16													Output2=0;
		CString													TextInput2=MFormatterInt16HexaDecimal.ConvertToString(Input2);
		bool													Parsed2=MFormatterInt16HexaDecimal.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int16 HEXADECIMAL - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		int16													Input3=-100;
		int16													Output3=0;
		CString													TextInput3=MFormatterInt16HexaDecimal.ConvertToString(Input3);
		bool													Parsed3=MFormatterInt16HexaDecimal.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int16 HEXADECIMAL - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		int16													Input4=numeric_limits<int16>::max();
		int16													Output4=0;
		CString													TextInput4=MFormatterInt16HexaDecimal.ConvertToString(Input4);
		bool													Parsed4=MFormatterInt16HexaDecimal.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int16 HEXADECIMAL - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		int16													Input5=numeric_limits<int16>::lowest();
		int16													Output5=0;
		CString													TextInput5=MFormatterInt16HexaDecimal.ConvertToString(Input5);
		bool													Parsed5=MFormatterInt16HexaDecimal.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int16 HEXADECIMAL - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		int16													Output6=0;
		bool													Parsed6=MFormatterInt16HexaDecimal.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int16 HEXADECIMAL - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestInt16HexaDecimalWithPrefix(void)
	{
		int16													Input1=100;
		int16													Output1=0;
		CString													TextInput1=MFormatterInt16HexaDecimalWithPrefix.ConvertToString(Input1);
		bool													Parsed1=MFormatterInt16HexaDecimalWithPrefix.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int16 HEXADECIMAL with PREFIX - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		int16													Input2=0;
		int16													Output2=0;
		CString													TextInput2=MFormatterInt16HexaDecimalWithPrefix.ConvertToString(Input2);
		bool													Parsed2=MFormatterInt16HexaDecimalWithPrefix.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int16 HEXADECIMAL with PREFIX - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		int16													Input3=-100;
		int16													Output3=0;
		CString													TextInput3=MFormatterInt16HexaDecimalWithPrefix.ConvertToString(Input3);
		bool													Parsed3=MFormatterInt16HexaDecimalWithPrefix.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int16 HEXADECIMAL with PREFIX - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		int16													Input4=numeric_limits<int16>::max();
		int16													Output4=0;
		CString													TextInput4=MFormatterInt16HexaDecimalWithPrefix.ConvertToString(Input4);
		bool													Parsed4=MFormatterInt16HexaDecimalWithPrefix.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int16 HEXADECIMAL with PREFIX - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		int16													Input5=numeric_limits<int16>::lowest();
		int16													Output5=0;
		CString													TextInput5=MFormatterInt16HexaDecimalWithPrefix.ConvertToString(Input5);
		bool													Parsed5=MFormatterInt16HexaDecimalWithPrefix.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int16 HEXADECIMAL with PREFIX - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		int16													Output6=0;
		bool													Parsed6=MFormatterInt16HexaDecimalWithPrefix.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int16 HEXADECIMAL with PREFIX - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestUInt16Decimal(void)
	{
		uint16													Input1=100;
		uint16													Output1=0;
		CString													TextInput1=MUFormatterInt16Decimal.ConvertToString(Input1);
		bool													Parsed1=MUFormatterInt16Decimal.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint16 DECIMAL - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		uint16													Input2=0;
		uint16													Output2=0;
		CString													TextInput2=MUFormatterInt16Decimal.ConvertToString(Input2);
		bool													Parsed2=MUFormatterInt16Decimal.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint16 DECIMAL - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		uint16													Input3=uint16(-100);
		uint16													Output3=0;
		CString													TextInput3=MUFormatterInt16Decimal.ConvertToString(Input3);
		bool													Parsed3=MUFormatterInt16Decimal.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint16 DECIMAL - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		uint16													Input4=numeric_limits<uint16>::max();
		uint16													Output4=0;
		CString													TextInput4=MUFormatterInt16Decimal.ConvertToString(Input4);
		bool													Parsed4=MUFormatterInt16Decimal.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint16 DECIMAL - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		uint16													Input5=numeric_limits<uint16>::lowest();
		uint16													Output5=0;
		CString													TextInput5=MUFormatterInt16Decimal.ConvertToString(Input5);
		bool													Parsed5=MUFormatterInt16Decimal.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint16 DECIMAL - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		uint16													Output6=0;
		bool													Parsed6=MUFormatterInt16Decimal.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint16 DECIMAL - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestUInt16HexaDecimal(void)
	{
		uint16													Input1=100;
		uint16													Output1=0;
		CString													TextInput1=MUFormatterInt16HexaDecimal.ConvertToString(Input1);
		bool													Parsed1=MUFormatterInt16HexaDecimal.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint16 HEXADECIMAL - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		uint16													Input2=0;
		uint16													Output2=0;
		CString													TextInput2=MUFormatterInt16HexaDecimal.ConvertToString(Input2);
		bool													Parsed2=MUFormatterInt16HexaDecimal.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint16 HEXADECIMAL - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		uint16													Input3=uint16(-100);
		uint16													Output3=0;
		CString													TextInput3=MUFormatterInt16HexaDecimal.ConvertToString(Input3);
		bool													Parsed3=MUFormatterInt16HexaDecimal.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint16 HEXADECIMAL - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		uint16													Input4=numeric_limits<uint16>::max();
		uint16													Output4=0;
		CString													TextInput4=MUFormatterInt16HexaDecimal.ConvertToString(Input4);
		bool													Parsed4=MUFormatterInt16HexaDecimal.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint16 HEXADECIMAL - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		uint16													Input5=numeric_limits<uint16>::lowest();
		uint16													Output5=0;
		CString													TextInput5=MUFormatterInt16HexaDecimal.ConvertToString(Input5);
		bool													Parsed5=MUFormatterInt16HexaDecimal.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint16 HEXADECIMAL - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		uint16													Output6=0;
		bool													Parsed6=MUFormatterInt16HexaDecimal.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint16 HEXADECIMAL - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestUInt16HexaDecimalWithPrefix(void)
	{
		uint16													Input1=100;
		uint16													Output1=0;
		CString													TextInput1=MUFormatterInt16HexaDecimalWithPrefix.ConvertToString(Input1);
		bool													Parsed1=MUFormatterInt16HexaDecimalWithPrefix.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint16 HEXADECIMAL with PREFIX - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		uint16													Input2=0;
		uint16													Output2=0;
		CString													TextInput2=MUFormatterInt16HexaDecimalWithPrefix.ConvertToString(Input2);
		bool													Parsed2=MUFormatterInt16HexaDecimalWithPrefix.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint16 HEXADECIMAL with PREFIX - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		uint16													Input3=uint16(-100);
		uint16													Output3=0;
		CString													TextInput3=MUFormatterInt16HexaDecimalWithPrefix.ConvertToString(Input3);
		bool													Parsed3=MUFormatterInt16HexaDecimalWithPrefix.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint16 HEXADECIMAL with PREFIX - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		uint16													Input4=numeric_limits<uint16>::max();
		uint16													Output4=0;
		CString													TextInput4=MUFormatterInt16HexaDecimalWithPrefix.ConvertToString(Input4);
		bool													Parsed4=MUFormatterInt16HexaDecimalWithPrefix.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint16 HEXADECIMAL with PREFIX - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		uint16													Input5=numeric_limits<uint16>::lowest();
		uint16													Output5=0;
		CString													TextInput5=MUFormatterInt16HexaDecimalWithPrefix.ConvertToString(Input5);
		bool													Parsed5=MUFormatterInt16HexaDecimalWithPrefix.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint16 HEXADECIMAL with PREFIX - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		uint16													Output6=0;
		bool													Parsed6=MUFormatterInt16HexaDecimalWithPrefix.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint16 HEXADECIMAL with PREFIX - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestInt32Decimal(void)
	{
		int32													Input1=100;
		int32													Output1=0;
		CString													TextInput1=MFormatterInt32Decimal.ConvertToString(Input1);
		bool													Parsed1=MFormatterInt32Decimal.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 DECIMAL - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		int32													Input2=0;
		int32													Output2=0;
		CString													TextInput2=MFormatterInt32Decimal.ConvertToString(Input2);
		bool													Parsed2=MFormatterInt32Decimal.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 DECIMAL - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		int32													Input3=-100;
		int32													Output3=0;
		CString													TextInput3=MFormatterInt32Decimal.ConvertToString(Input3);
		bool													Parsed3=MFormatterInt32Decimal.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 DECIMAL - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		int32													Input4=numeric_limits<int32>::max();
		int32													Output4=0;
		CString													TextInput4=MFormatterInt32Decimal.ConvertToString(Input4);
		bool													Parsed4=MFormatterInt32Decimal.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 DECIMAL - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		int32													Input5=numeric_limits<int32>::lowest();
		int32													Output5=0;
		CString													TextInput5=MFormatterInt32Decimal.ConvertToString(Input5);
		bool													Parsed5=MFormatterInt32Decimal.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 DECIMAL - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		int32													Output6=0;
		bool													Parsed6=MFormatterInt32Decimal.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 DECIMAL - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestInt32DecimalWithPadding(void)
	{
		int32													Input1=100;
		int32													Output1=0;
		CString													TextInput1=MFormatterInt32DecimalWithPadding.ConvertToString(Input1);
		bool													Parsed1=MFormatterInt32DecimalWithPadding.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 DECIMAL - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		int32													Input2=0;
		int32													Output2=0;
		CString													TextInput2=MFormatterInt32DecimalWithPadding.ConvertToString(Input2);
		bool													Parsed2=MFormatterInt32DecimalWithPadding.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 DECIMAL - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		int32													Input3=-100;
		int32													Output3=0;
		CString													TextInput3=MFormatterInt32DecimalWithPadding.ConvertToString(Input3);
		bool													Parsed3=MFormatterInt32DecimalWithPadding.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 DECIMAL - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		int32													Input4=numeric_limits<int32>::max();
		int32													Output4=0;
		CString													TextInput4=MFormatterInt32DecimalWithPadding.ConvertToString(Input4);
		bool													Parsed4=MFormatterInt32DecimalWithPadding.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 DECIMAL - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		int32													Input5=numeric_limits<int32>::lowest();
		int32													Output5=0;
		CString													TextInput5=MFormatterInt32DecimalWithPadding.ConvertToString(Input5);
		bool													Parsed5=MFormatterInt32DecimalWithPadding.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 DECIMAL - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		int32													Output6=0;
		bool													Parsed6=MFormatterInt32DecimalWithPadding.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 DECIMAL - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestInt32HexaDecimal(void)
	{
		int32													Input1=100;
		int32													Output1=0;
		CString													TextInput1=MFormatterInt32HexaDecimal.ConvertToString(Input1);
		bool													Parsed1=MFormatterInt32HexaDecimal.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 HEXADECIMAL - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		int32													Input2=0;
		int32													Output2=0;
		CString													TextInput2=MFormatterInt32HexaDecimal.ConvertToString(Input2);
		bool													Parsed2=MFormatterInt32HexaDecimal.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 HEXADECIMAL - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		int32													Input3=-100;
		int32													Output3=0;
		CString													TextInput3=MFormatterInt32HexaDecimal.ConvertToString(Input3);
		bool													Parsed3=MFormatterInt32HexaDecimal.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 HEXADECIMAL - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		int32													Input4=numeric_limits<int32>::max();
		int32													Output4=0;
		CString													TextInput4=MFormatterInt32HexaDecimal.ConvertToString(Input4);
		bool													Parsed4=MFormatterInt32HexaDecimal.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 HEXADECIMAL - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		int32													Input5=numeric_limits<int32>::lowest();
		int32													Output5=0;
		CString													TextInput5=MFormatterInt32HexaDecimal.ConvertToString(Input5);
		bool													Parsed5=MFormatterInt32HexaDecimal.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 HEXADECIMAL - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		int32													Output6=0;
		bool													Parsed6=MFormatterInt32HexaDecimal.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 HEXADECIMAL - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestInt32HexaDecimalWithPrefix1(void)
	{
		int32													Input1=100;
		int32													Output1=0;
		CString													TextInput1=MFormatterInt32HexaDecimalWithPrefix1.ConvertToString(Input1);
		bool													Parsed1=MFormatterInt32HexaDecimalWithPrefix1.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 HEXADECIMAL with PREFIX 1 - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		int32													Input2=0;
		int32													Output2=0;
		CString													TextInput2=MFormatterInt32HexaDecimalWithPrefix1.ConvertToString(Input2);
		bool													Parsed2=MFormatterInt32HexaDecimalWithPrefix1.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 HEXADECIMAL with PREFIX 1 - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		int32													Input3=-100;
		int32													Output3=0;
		CString													TextInput3=MFormatterInt32HexaDecimalWithPrefix1.ConvertToString(Input3);
		bool													Parsed3=MFormatterInt32HexaDecimalWithPrefix1.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 HEXADECIMAL with PREFIX 1 - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		int32													Input4=numeric_limits<int32>::max();
		int32													Output4=0;
		CString													TextInput4=MFormatterInt32HexaDecimalWithPrefix1.ConvertToString(Input4);
		bool													Parsed4=MFormatterInt32HexaDecimalWithPrefix1.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 HEXADECIMAL with PREFIX 1 - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		int32													Input5=numeric_limits<int32>::lowest();
		int32													Output5=0;
		CString													TextInput5=MFormatterInt32HexaDecimalWithPrefix1.ConvertToString(Input5);
		bool													Parsed5=MFormatterInt32HexaDecimalWithPrefix1.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 HEXADECIMAL with PREFIX 1 - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		int32													Output6=0;
		bool													Parsed6=MFormatterInt32HexaDecimalWithPrefix1.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 HEXADECIMAL with PREFIX 1 - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestInt32HexaDecimalWithPrefix2(void)
	{
		int32													Input1=100;
		int32													Output1=0;
		CString													TextInput1=MFormatterInt32HexaDecimalWithPrefix2.ConvertToString(Input1);
		bool													Parsed1=MFormatterInt32HexaDecimalWithPrefix2.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 HEXADECIMAL with PREFIX 2 - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		int32													Input2=0;
		int32													Output2=0;
		CString													TextInput2=MFormatterInt32HexaDecimalWithPrefix2.ConvertToString(Input2);
		bool													Parsed2=MFormatterInt32HexaDecimalWithPrefix2.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 HEXADECIMAL with PREFIX 2 - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		int32													Input3=-100;
		int32													Output3=0;
		CString													TextInput3=MFormatterInt32HexaDecimalWithPrefix2.ConvertToString(Input3);
		bool													Parsed3=MFormatterInt32HexaDecimalWithPrefix2.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 HEXADECIMAL with PREFIX 2 - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		int32													Input4=numeric_limits<int32>::max();
		int32													Output4=0;
		CString													TextInput4=MFormatterInt32HexaDecimalWithPrefix2.ConvertToString(Input4);
		bool													Parsed4=MFormatterInt32HexaDecimalWithPrefix2.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 HEXADECIMAL with PREFIX 2 - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		int32													Input5=numeric_limits<int32>::lowest();
		int32													Output5=0;
		CString													TextInput5=MFormatterInt32HexaDecimalWithPrefix2.ConvertToString(Input5);
		bool													Parsed5=MFormatterInt32HexaDecimalWithPrefix2.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 HEXADECIMAL with PREFIX 2 - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		int32													Output6=0;
		bool													Parsed6=MFormatterInt32HexaDecimalWithPrefix2.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int32 HEXADECIMAL with PREFIX 2 - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestUInt32Decimal(void)
	{
		uint32													Input1=100;
		uint32													Output1=0;
		CString													TextInput1=MUFormatterInt32Decimal.ConvertToString(Input1);
		bool													Parsed1=MUFormatterInt32Decimal.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint32 DECIMAL - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		uint32													Input2=0;
		uint32													Output2=0;
		CString													TextInput2=MUFormatterInt32Decimal.ConvertToString(Input2);
		bool													Parsed2=MUFormatterInt32Decimal.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint32 DECIMAL - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		uint32													Input3=uint32(-100);
		uint32													Output3=0;
		CString													TextInput3=MUFormatterInt32Decimal.ConvertToString(Input3);
		bool													Parsed3=MUFormatterInt32Decimal.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint32 DECIMAL - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		uint32													Input4=numeric_limits<uint32>::max();
		uint32													Output4=0;
		CString													TextInput4=MUFormatterInt32Decimal.ConvertToString(Input4);
		bool													Parsed4=MUFormatterInt32Decimal.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint32 DECIMAL - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		uint32													Input5=numeric_limits<uint32>::lowest();
		uint32													Output5=0;
		CString													TextInput5=MUFormatterInt32Decimal.ConvertToString(Input5);
		bool													Parsed5=MUFormatterInt32Decimal.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint32 DECIMAL - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		uint32													Output6=0;
		bool													Parsed6=MUFormatterInt32Decimal.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint32 DECIMAL - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestUInt32HexaDecimal(void)
	{
		uint32													Input1=100;
		uint32													Output1=0;
		CString													TextInput1=MUFormatterInt32HexaDecimal.ConvertToString(Input1);
		bool													Parsed1=MUFormatterInt32HexaDecimal.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint32 HEXADECIMAL - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		uint32													Input2=0;
		uint32													Output2=0;
		CString													TextInput2=MUFormatterInt32HexaDecimal.ConvertToString(Input2);
		bool													Parsed2=MUFormatterInt32HexaDecimal.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint32 HEXADECIMAL - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		uint32													Input3=uint32(-100);
		uint32													Output3=0;
		CString													TextInput3=MUFormatterInt32HexaDecimal.ConvertToString(Input3);
		bool													Parsed3=MUFormatterInt32HexaDecimal.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint32 HEXADECIMAL - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		uint32													Input4=numeric_limits<uint32>::max();
		uint32													Output4=0;
		CString													TextInput4=MUFormatterInt32HexaDecimal.ConvertToString(Input4);
		bool													Parsed4=MUFormatterInt32HexaDecimal.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint32 HEXADECIMAL - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		uint32													Input5=numeric_limits<uint32>::lowest();
		uint32													Output5=0;
		CString													TextInput5=MUFormatterInt32HexaDecimal.ConvertToString(Input5);
		bool													Parsed5=MUFormatterInt32HexaDecimal.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint32 HEXADECIMAL - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		uint32													Output6=0;
		bool													Parsed6=MUFormatterInt32HexaDecimal.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint32 HEXADECIMAL - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestUInt32HexaDecimalWithPrefix(void)
	{
		uint32													Input1=100;
		uint32													Output1=0;
		CString													TextInput1=MUFormatterInt32HexaDecimalWithPrefix.ConvertToString(Input1);
		bool													Parsed1=MUFormatterInt32HexaDecimalWithPrefix.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint32 HEXADECIMAL with PREFIX - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		uint32													Input2=0;
		uint32													Output2=0;
		CString													TextInput2=MUFormatterInt32HexaDecimalWithPrefix.ConvertToString(Input2);
		bool													Parsed2=MUFormatterInt32HexaDecimalWithPrefix.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint32 HEXADECIMAL with PREFIX - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		uint32													Input3=uint32(-100);
		uint32													Output3=0;
		CString													TextInput3=MUFormatterInt32HexaDecimalWithPrefix.ConvertToString(Input3);
		bool													Parsed3=MUFormatterInt32HexaDecimalWithPrefix.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint32 HEXADECIMAL with PREFIX - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		uint32													Input4=numeric_limits<uint32>::max();
		uint32													Output4=0;
		CString													TextInput4=MUFormatterInt32HexaDecimalWithPrefix.ConvertToString(Input4);
		bool													Parsed4=MUFormatterInt32HexaDecimalWithPrefix.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint32 HEXADECIMAL with PREFIX - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		uint32													Input5=numeric_limits<uint32>::lowest();
		uint32													Output5=0;
		CString													TextInput5=MUFormatterInt32HexaDecimalWithPrefix.ConvertToString(Input5);
		bool													Parsed5=MUFormatterInt32HexaDecimalWithPrefix.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint32 HEXADECIMAL with PREFIX - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		uint32													Output6=0;
		bool													Parsed6=MUFormatterInt32HexaDecimalWithPrefix.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint32 HEXADECIMAL with PREFIX - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestInt64Decimal(void)
	{
		int64													Input1=100;
		int64													Output1=0;
		CString													TextInput1=MFormatterInt64Decimal.ConvertToString(Input1);
		bool													Parsed1=MFormatterInt64Decimal.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int64 DECIMAL - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		int64													Input2=0;
		int64													Output2=0;
		CString													TextInput2=MFormatterInt64Decimal.ConvertToString(Input2);
		bool													Parsed2=MFormatterInt64Decimal.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int64 DECIMAL - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		int64													Input3=-100;
		int64													Output3=0;
		CString													TextInput3=MFormatterInt64Decimal.ConvertToString(Input3);
		bool													Parsed3=MFormatterInt64Decimal.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int64 DECIMAL - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		int64													Input4=numeric_limits<int64>::max();
		int64													Output4=0;
		CString													TextInput4=MFormatterInt64Decimal.ConvertToString(Input4);
		bool													Parsed4=MFormatterInt64Decimal.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int64 DECIMAL - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		int64													Input5=numeric_limits<int64>::lowest();
		int64													Output5=0;
		CString													TextInput5=MFormatterInt64Decimal.ConvertToString(Input5);
		bool													Parsed5=MFormatterInt64Decimal.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int64 DECIMAL - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		int64													Output6=0;
		bool													Parsed6=MFormatterInt64Decimal.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int64 DECIMAL - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestInt64HexaDecimal(void)
	{
		int64													Input1=100;
		int64													Output1=0;
		CString													TextInput1=MFormatterInt64HexaDecimal.ConvertToString(Input1);
		bool													Parsed1=MFormatterInt64HexaDecimal.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int64 HEXADECIMAL - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		int64													Input2=0;
		int64													Output2=0;
		CString													TextInput2=MFormatterInt64HexaDecimal.ConvertToString(Input2);
		bool													Parsed2=MFormatterInt64HexaDecimal.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int64 HEXADECIMAL - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		int64													Input3=-100;
		int64													Output3=0;
		CString													TextInput3=MFormatterInt64HexaDecimal.ConvertToString(Input3);
		bool													Parsed3=MFormatterInt64HexaDecimal.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int64 HEXADECIMAL - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		int64													Input4=numeric_limits<int64>::max();
		int64													Output4=0;
		CString													TextInput4=MFormatterInt64HexaDecimal.ConvertToString(Input4);
		bool													Parsed4=MFormatterInt64HexaDecimal.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int64 HEXADECIMAL - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		int64													Input5=numeric_limits<int64>::lowest();
		int64													Output5=0;
		CString													TextInput5=MFormatterInt64HexaDecimal.ConvertToString(Input5);
		bool													Parsed5=MFormatterInt64HexaDecimal.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int64 HEXADECIMAL - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		int64													Output6=0;
		bool													Parsed6=MFormatterInt64HexaDecimal.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int64 HEXADECIMAL - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestInt64HexaDecimalWithPrefix(void)
	{
		int64													Input1=100;
		int64													Output1=0;
		CString													TextInput1=MFormatterInt64HexaDecimalWithPrefix.ConvertToString(Input1);
		bool													Parsed1=MFormatterInt64HexaDecimalWithPrefix.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int64 HEXADECIMAL with PREFIX - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		int64													Input2=0;
		int64													Output2=0;
		CString													TextInput2=MFormatterInt64HexaDecimalWithPrefix.ConvertToString(Input2);
		bool													Parsed2=MFormatterInt64HexaDecimalWithPrefix.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int64 HEXADECIMAL with PREFIX - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		int64													Input3=-100;
		int64													Output3=0;
		CString													TextInput3=MFormatterInt64HexaDecimalWithPrefix.ConvertToString(Input3);
		bool													Parsed3=MFormatterInt64HexaDecimalWithPrefix.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int64 HEXADECIMAL with PREFIX - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		int64													Input4=numeric_limits<int64>::max();
		int64													Output4=0;
		CString													TextInput4=MFormatterInt64HexaDecimalWithPrefix.ConvertToString(Input4);
		bool													Parsed4=MFormatterInt64HexaDecimalWithPrefix.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int64 HEXADECIMAL with PREFIX - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		int64													Input5=numeric_limits<int64>::lowest();
		int64													Output5=0;
		CString													TextInput5=MFormatterInt64HexaDecimalWithPrefix.ConvertToString(Input5);
		bool													Parsed5=MFormatterInt64HexaDecimalWithPrefix.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int64 HEXADECIMAL with PREFIX - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		int64													Output6=0;
		bool													Parsed6=MFormatterInt64HexaDecimalWithPrefix.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST int64 HEXADECIMAL with PREFIX - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestUInt64Decimal(void)
	{
		uint64													Input1=100;
		uint64													Output1=0;
		CString													TextInput1=MUFormatterInt64Decimal.ConvertToString(Input1);
		bool													Parsed1=MUFormatterInt64Decimal.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint64 DECIMAL - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		uint64													Input2=0;
		uint64													Output2=0;
		CString													TextInput2=MUFormatterInt64Decimal.ConvertToString(Input2);
		bool													Parsed2=MUFormatterInt64Decimal.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint64 DECIMAL - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		uint64													Input3=uint64(-100);
		uint64													Output3=0;
		CString													TextInput3=MUFormatterInt64Decimal.ConvertToString(Input3);
		bool													Parsed3=MUFormatterInt64Decimal.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint64 DECIMAL - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		uint64													Input4=numeric_limits<uint64>::max();
		uint64													Output4=0;
		CString													TextInput4=MUFormatterInt64Decimal.ConvertToString(Input4);
		bool													Parsed4=MUFormatterInt64Decimal.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint64 DECIMAL - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		uint64													Input5=numeric_limits<uint64>::lowest();
		uint64													Output5=0;
		CString													TextInput5=MUFormatterInt64Decimal.ConvertToString(Input5);
		bool													Parsed5=MUFormatterInt64Decimal.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint64 DECIMAL - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		uint64													Output6=0;
		bool													Parsed6=MUFormatterInt64Decimal.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint64 DECIMAL - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestUInt64HexaDecimal(void)
	{
		uint64													Input1=100;
		uint64													Output1=0;
		CString													TextInput1=MUFormatterInt64HexaDecimal.ConvertToString(Input1);
		bool													Parsed1=MUFormatterInt64HexaDecimal.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint64 HEXADECIMAL - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		uint64													Input2=0;
		uint64													Output2=0;
		CString													TextInput2=MUFormatterInt64HexaDecimal.ConvertToString(Input2);
		bool													Parsed2=MUFormatterInt64HexaDecimal.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint64 HEXADECIMAL - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		uint64													Input3=uint64(-100);
		uint64													Output3=0;
		CString													TextInput3=MUFormatterInt64HexaDecimal.ConvertToString(Input3);
		bool													Parsed3=MUFormatterInt64HexaDecimal.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint64 HEXADECIMAL - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		uint64													Input4=numeric_limits<uint64>::max();
		uint64													Output4=0;
		CString													TextInput4=MUFormatterInt64HexaDecimal.ConvertToString(Input4);
		bool													Parsed4=MUFormatterInt64HexaDecimal.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint64 HEXADECIMAL - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		uint64													Input5=numeric_limits<uint64>::lowest();
		uint64													Output5=0;
		CString													TextInput5=MUFormatterInt64HexaDecimal.ConvertToString(Input5);
		bool													Parsed5=MUFormatterInt64HexaDecimal.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint64 HEXADECIMAL - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		uint64													Output6=0;
		bool													Parsed6=MUFormatterInt64HexaDecimal.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint64 HEXADECIMAL - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestUInt64HexaDecimalWithPrefix(void)
	{
		uint64													Input1=100;
		uint64													Output1=0;
		CString													TextInput1=MUFormatterInt64HexaDecimalWithPrefix.ConvertToString(Input1);
		bool													Parsed1=MUFormatterInt64HexaDecimalWithPrefix.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint64 HEXADECIMAL with PREFIX - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		uint64													Input2=0;
		uint64													Output2=0;
		CString													TextInput2=MUFormatterInt64HexaDecimalWithPrefix.ConvertToString(Input2);
		bool													Parsed2=MUFormatterInt64HexaDecimalWithPrefix.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint64 HEXADECIMAL with PREFIX - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		uint64													Input3=uint64(-100);
		uint64													Output3=0;
		CString													TextInput3=MUFormatterInt64HexaDecimalWithPrefix.ConvertToString(Input3);
		bool													Parsed3=MUFormatterInt64HexaDecimalWithPrefix.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint64 HEXADECIMAL with PREFIX - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		uint64													Input4=numeric_limits<uint64>::max();
		uint64													Output4=0;
		CString													TextInput4=MUFormatterInt64HexaDecimalWithPrefix.ConvertToString(Input4);
		bool													Parsed4=MUFormatterInt64HexaDecimalWithPrefix.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint64 HEXADECIMAL with PREFIX - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		uint64													Input5=numeric_limits<uint64>::lowest();
		uint64													Output5=0;
		CString													TextInput5=MUFormatterInt64HexaDecimalWithPrefix.ConvertToString(Input5);
		bool													Parsed5=MUFormatterInt64HexaDecimalWithPrefix.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint64 HEXADECIMAL with PREFIX - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		uint64													Output6=0;
		bool													Parsed6=MUFormatterInt64HexaDecimalWithPrefix.Parse("9999999999999999999999999999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST uint64 HEXADECIMAL with PREFIX - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestFloat32(void)
	{
		float32													Dummy;

		float32													Input1=100;
		float32													Output1=0;
		CString													TextInput1=MFormatterFloat32.ConvertToString(Input1);
		bool													Parsed1=MFormatterFloat32.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		float32													Input2=123.1234f;
		float32													Output2=0;
		CString													TextInput2=MFormatterFloat32.ConvertToString(Input2);
		bool													Parsed2=MFormatterFloat32.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		float32													Input3=0;
		float32													Output3=0;
		CString													TextInput3=MFormatterFloat32.ConvertToString(Input3);
		bool													Parsed3=MFormatterFloat32.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}
		
		float32													Input4=-100;
		float32													Output4=0;
		CString													TextInput4=MFormatterFloat32.ConvertToString(Input4);
		bool													Parsed4=MFormatterFloat32.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		float32													Input5=-123.1234f;
		float32													Output5=0;
		CString													TextInput5=MFormatterFloat32.ConvertToString(Input5);
		bool													Parsed5=MFormatterFloat32.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		float32													Input6=numeric_limits<float32>::max();
		float32													Output6=0;
		CString													TextInput6=MFormatterFloat32.ConvertToString(Input6);
		bool													Parsed6=MFormatterFloat32.Parse(TextInput6,Output6);

		if (Parsed6==false || Input6!=Output6)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 6 FAILED [",TextInput6,",",Input6,",",Output6,"] !\n"));

			return(false);
		}

		float32													Input7=numeric_limits<float32>::lowest();
		float32													Output7=0;
		CString													TextInput7=MFormatterFloat32.ConvertToString(Input7);
		bool													Parsed7=MFormatterFloat32.Parse(TextInput7,Output7);

		if (Parsed7==false || Input7!=Output7)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 7 FAILED [",TextInput7,",",Input7,",",Output7,"] !\n"));

			return(false);
		}

		float32													Output8=0;
		bool													Parsed8=MFormatterFloat32.Parse("9999999999999999999999999999999999999999999999999999999999999999999.9999999999999999999999",Output8);

		if (Parsed8==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 8 FAILED [",Output8,"] !\n"));

			return(false);
		}

		bool													Parsed9=MFormatterFloat32.Parse("",Dummy);

		if (Parsed9==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 9 FAILED !\n"));

			return(false);
		}

		bool													Parsed10=MFormatterFloat32.Parse(".",Dummy);

		if (Parsed10==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 10 FAILED !\n"));

			return(false);
		}

		bool													Parsed11=MFormatterFloat32.Parse("e1",Dummy);

		if (Parsed11==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 11 FAILED !\n"));

			return(false);
		}

		bool													Parsed12=MFormatterFloat32.Parse(".e1",Dummy);

		if (Parsed12==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 12 FAILED !\n"));

			return(false);
		}

		bool													Parsed13=MFormatterFloat32.Parse("3.123e-",Dummy);

		if (Parsed13==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 13 FAILED !\n"));

			return(false);
		}

		bool													Parsed14=MFormatterFloat32.Parse("3.123ee-2",Dummy);

		if (Parsed14==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 14 FAILED !\n"));

			return(false);
		}

		bool													Parsed15=MFormatterFloat32.Parse("-",Dummy);

		if (Parsed15==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 15 FAILED !\n"));

			return(false);
		}

		bool													Parsed16=MFormatterFloat32.Parse("1e-1",Dummy);

		if (Parsed16==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 16 FAILED !\n"));

			return(false);
		}

		bool													Parsed17=MFormatterFloat32.Parse("1e+1",Dummy);

		if (Parsed17==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 17 FAILED !\n"));

			return(false);
		}

		bool													Parsed18=MFormatterFloat32.Parse("1.0e-1",Dummy);

		if (Parsed18==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 18 FAILED !\n"));

			return(false);
		}

		bool													Parsed19=MFormatterFloat32.Parse("1.0e+1",Dummy);

		if (Parsed19==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 19 FAILED !\n"));

			return(false);
		}

		bool													Parsed20=MFormatterFloat32.Parse("1.e-1",Dummy);

		if (Parsed20==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 20 FAILED !\n"));

			return(false);
		}

		bool													Parsed21=MFormatterFloat32.Parse("1.e+1",Dummy);

		if (Parsed21==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 21 FAILED !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestFloat32WithPrecision(void)
	{
		float32													Input1=100;
		float32													Output1=0;
		CString													TextInput1=MFormatterFloat32WithPrecision.ConvertToString(Input1);
		bool													Parsed1=MFormatterFloat32WithPrecision.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		float32													Input2=123.12f;
		float32													Output2=0;
		CString													TextInput2=MFormatterFloat32WithPrecision.ConvertToString(Input2);
		bool													Parsed2=MFormatterFloat32WithPrecision.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		float32													Input3=0;
		float32													Output3=0;
		CString													TextInput3=MFormatterFloat32WithPrecision.ConvertToString(Input3);
		bool													Parsed3=MFormatterFloat32WithPrecision.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		float32													Input4=-100;
		float32													Output4=0;
		CString													TextInput4=MFormatterFloat32WithPrecision.ConvertToString(Input4);
		bool													Parsed4=MFormatterFloat32WithPrecision.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		float32													Input5=-123.12f;
		float32													Output5=0;
		CString													TextInput5=MFormatterFloat32WithPrecision.ConvertToString(Input5);
		bool													Parsed5=MFormatterFloat32WithPrecision.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		float32													Output6=0;
		bool													Parsed6=MFormatterFloat32WithPrecision.Parse("9999999999999999999999999999999999999999999999999999999999999999999.9999999999999999999999",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float32 - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestFloat64(void)
	{
		float64													Dummy;

		float64													Input1=100;
		float64													Output1=0;
		CString													TextInput1=MFormatterFloat64.ConvertToString(Input1);
		bool													Parsed1=MFormatterFloat64.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		float64													Input2=123.1234;
		float64													Output2=0;
		CString													TextInput2=MFormatterFloat64.ConvertToString(Input2);
		bool													Parsed2=MFormatterFloat64.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		float64													Input3=0;
		float64													Output3=0;
		CString													TextInput3=MFormatterFloat64.ConvertToString(Input3);
		bool													Parsed3=MFormatterFloat64.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}
		
		float64													Input4=-100;
		float64													Output4=0;
		CString													TextInput4=MFormatterFloat64.ConvertToString(Input4);
		bool													Parsed4=MFormatterFloat64.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		float64													Input5=-123.1234;
		float64													Output5=0;
		CString													TextInput5=MFormatterFloat64.ConvertToString(Input5);
		bool													Parsed5=MFormatterFloat64.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		float64													Input6=numeric_limits<float64>::max();
		float64													Output6=0;
		CString													TextInput6=MFormatterFloat64.ConvertToString(Input6);
		bool													Parsed6=MFormatterFloat64.Parse(TextInput6,Output6);

		if (Parsed6==false || Input6!=Output6)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 6 FAILED [",TextInput6,",",Input6,",",Output6,"] !\n"));

			return(false);
		}

		float64													Input7=numeric_limits<float64>::lowest();
		float64													Output7=0;
		CString													TextInput7=MFormatterFloat64.ConvertToString(Input7);
		bool													Parsed7=MFormatterFloat64.Parse(TextInput7,Output7);

		if (Parsed7==false || Input7!=Output7)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 7 FAILED [",TextInput7,",",Input7,",",Output7,"] !\n"));

			return(false);
		}

		float64													Output8=0;
		bool													Parsed8=MFormatterFloat64.Parse("1.7976931348623157e+22308",Output8);

		if (Parsed8==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 8 FAILED [",Output8,"] !\n"));

			return(false);
		}

		bool													Parsed9=MFormatterFloat64.Parse("",Dummy);

		if (Parsed9==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 9 FAILED !\n"));

			return(false);
		}

		bool													Parsed10=MFormatterFloat64.Parse(".",Dummy);

		if (Parsed10==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 10 FAILED !\n"));

			return(false);
		}

		bool													Parsed11=MFormatterFloat64.Parse("e1",Dummy);

		if (Parsed11==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 11 FAILED !\n"));

			return(false);
		}

		bool													Parsed12=MFormatterFloat64.Parse(".e1",Dummy);

		if (Parsed12==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 12 FAILED !\n"));

			return(false);
		}

		bool													Parsed13=MFormatterFloat64.Parse("3.123e-",Dummy);

		if (Parsed13==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 13 FAILED !\n"));

			return(false);
		}

		bool													Parsed14=MFormatterFloat64.Parse("3.123ee-2",Dummy);

		if (Parsed14==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 14 FAILED !\n"));

			return(false);
		}

		bool													Parsed15=MFormatterFloat64.Parse("-",Dummy);

		if (Parsed15==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 15 FAILED !\n"));

			return(false);
		}

		bool													Parsed16=MFormatterFloat64.Parse("1e-1",Dummy);

		if (Parsed16==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 16 FAILED !\n"));

			return(false);
		}

		bool													Parsed17=MFormatterFloat64.Parse("1e+1",Dummy);

		if (Parsed17==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 17 FAILED !\n"));

			return(false);
		}

		bool													Parsed18=MFormatterFloat64.Parse("1.0e-1",Dummy);

		if (Parsed18==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 18 FAILED !\n"));

			return(false);
		}

		bool													Parsed19=MFormatterFloat64.Parse("1.0e+1",Dummy);

		if (Parsed19==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 19 FAILED !\n"));

			return(false);
		}

		bool													Parsed20=MFormatterFloat64.Parse("1.e-1",Dummy);

		if (Parsed20==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 20 FAILED !\n"));

			return(false);
		}

		bool													Parsed21=MFormatterFloat64.Parse("1.e+1",Dummy);

		if (Parsed21==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 21 FAILED !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestFloat64WithPrecision(void)
	{
		float64													Input1=100;
		float64													Output1=0;
		CString													TextInput1=MFormatterFloat64WithPrecision.ConvertToString(Input1);
		bool													Parsed1=MFormatterFloat64WithPrecision.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		float64													Input2=123.12;
		float64													Output2=0;
		CString													TextInput2=MFormatterFloat64WithPrecision.ConvertToString(Input2);
		bool													Parsed2=MFormatterFloat64WithPrecision.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		float64													Input3=0;
		float64													Output3=0;
		CString													TextInput3=MFormatterFloat64WithPrecision.ConvertToString(Input3);
		bool													Parsed3=MFormatterFloat64WithPrecision.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		float64													Input4=-100;
		float64													Output4=0;
		CString													TextInput4=MFormatterFloat64WithPrecision.ConvertToString(Input4);
		bool													Parsed4=MFormatterFloat64WithPrecision.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		float64													Input5=-123.12;
		float64													Output5=0;
		CString													TextInput5=MFormatterFloat64WithPrecision.ConvertToString(Input5);
		bool													Parsed5=MFormatterFloat64WithPrecision.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		float64													Output6=0;
		bool													Parsed6=MFormatterFloat64WithPrecision.Parse("1.7976931348623157e+22308",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float64 - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestFloat80(void)
	{
		float80													Dummy=0;

		float80													Input1=100;
		float80													Output1=0;
		CString													TextInput1=MFormatterFloat80.ConvertToString(Input1);
		bool													Parsed1=MFormatterFloat80.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		float80													Input2=123.1234l;
		float80													Output2=0;
		CString													TextInput2=MFormatterFloat80.ConvertToString(Input2);
		bool													Parsed2=MFormatterFloat80.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		float80													Input3=0;
		float80													Output3=0;
		CString													TextInput3=MFormatterFloat80.ConvertToString(Input3);
		bool													Parsed3=MFormatterFloat80.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}
		
		float80													Input4=-100;
		float80													Output4=0;
		CString													TextInput4=MFormatterFloat80.ConvertToString(Input4);
		bool													Parsed4=MFormatterFloat80.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		float80													Input5=-123.1234l;
		float80													Output5=0;
		CString													TextInput5=MFormatterFloat80.ConvertToString(Input5);
		bool													Parsed5=MFormatterFloat80.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		float80													Input6=numeric_limits<float80>::max();
		float80													Output6=0;
		CString													TextInput6=MFormatterFloat80.ConvertToString(Input6);
		bool													Parsed6=MFormatterFloat80.Parse(TextInput6,Output6);

		if (Parsed6==false || Input6!=Output6)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 6 FAILED [",TextInput6,",",Input6,",",Output6,"] !\n"));

			return(false);
		}

		float80													Input7=numeric_limits<float80>::lowest();
		float80													Output7=0;
		CString													TextInput7=MFormatterFloat80.ConvertToString(Input7);
		bool													Parsed7=MFormatterFloat80.Parse(TextInput7,Output7);

		if (Parsed7==false || Input7!=Output7)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 7 FAILED [",TextInput7,",",Input7,",",Output7,"] !\n"));

			return(false);
		}

		float80													Output8=0;
		bool													Parsed8=MFormatterFloat80.Parse("1.7976931348623157e+22308",Output8);

		if (Parsed8==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 8 FAILED [",Output8,"] !\n"));

			return(false);
		}

		bool													Parsed9=MFormatterFloat80.Parse("",Dummy);

		if (Parsed9==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 9 FAILED !\n"));

			return(false);
		}

		bool													Parsed10=MFormatterFloat80.Parse(".",Dummy);

		if (Parsed10==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 10 FAILED !\n"));

			return(false);
		}

		bool													Parsed11=MFormatterFloat80.Parse("e1",Dummy);

		if (Parsed11==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 11 FAILED !\n"));

			return(false);
		}

		bool													Parsed12=MFormatterFloat80.Parse(".e1",Dummy);

		if (Parsed12==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 12 FAILED !\n"));

			return(false);
		}

		bool													Parsed13=MFormatterFloat80.Parse("3.123e-",Dummy);

		if (Parsed13==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 13 FAILED !\n"));

			return(false);
		}

		bool													Parsed14=MFormatterFloat80.Parse("3.123ee-2",Dummy);

		if (Parsed14==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 14 FAILED !\n"));

			return(false);
		}

		bool													Parsed15=MFormatterFloat80.Parse("-",Dummy);

		if (Parsed15==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 15 FAILED !\n"));

			return(false);
		}

		bool													Parsed16=MFormatterFloat80.Parse("1e-1",Dummy);

		if (Parsed16==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 16 FAILED !\n"));

			return(false);
		}

		bool													Parsed17=MFormatterFloat80.Parse("1e+1",Dummy);

		if (Parsed17==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 17 FAILED !\n"));

			return(false);
		}

		bool													Parsed18=MFormatterFloat80.Parse("1.0e-1",Dummy);

		if (Parsed18==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 18 FAILED !\n"));

			return(false);
		}

		bool													Parsed19=MFormatterFloat80.Parse("1.0e+1",Dummy);

		if (Parsed19==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 19 FAILED !\n"));

			return(false);
		}

		bool													Parsed20=MFormatterFloat80.Parse("1.e-1",Dummy);

		if (Parsed20==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 20 FAILED !\n"));

			return(false);
		}

		bool													Parsed21=MFormatterFloat80.Parse("1.e+1",Dummy);

		if (Parsed21==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 21 FAILED !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::TestFloat80WithPrecision(void)
	{
		float80													Input1=100;
		float80													Output1=0;
		CString													TextInput1=MFormatterFloat80WithPrecision.ConvertToString(Input1);
		bool													Parsed1=MFormatterFloat80WithPrecision.Parse(TextInput1,Output1);

		if (Parsed1==false || Input1!=Output1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 1 FAILED [",TextInput1,",",Input1,",",Output1,"] !\n"));

			return(false);
		}

		float80													Input2=123.12l;
		float80													Output2=0;
		CString													TextInput2=MFormatterFloat80WithPrecision.ConvertToString(Input2);
		bool													Parsed2=MFormatterFloat80WithPrecision.Parse(TextInput2,Output2);

		if (Parsed2==false || Input2!=Output2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 2 FAILED [",TextInput2,",",Input2,",",Output2,"] !\n"));

			return(false);
		}

		float80													Input3=0;
		float80													Output3=0;
		CString													TextInput3=MFormatterFloat80WithPrecision.ConvertToString(Input3);
		bool													Parsed3=MFormatterFloat80WithPrecision.Parse(TextInput3,Output3);

		if (Parsed3==false || Input3!=Output3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 3 FAILED [",TextInput3,",",Input3,",",Output3,"] !\n"));

			return(false);
		}

		float80													Input4=-100;
		float80													Output4=0;
		CString													TextInput4=MFormatterFloat80WithPrecision.ConvertToString(Input4);
		bool													Parsed4=MFormatterFloat80WithPrecision.Parse(TextInput4,Output4);

		if (Parsed4==false || Input4!=Output4)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 4 FAILED [",TextInput4,",",Input4,",",Output4,"] !\n"));

			return(false);
		}

		float80													Input5=-123.12l;
		float80													Output5=0;
		CString													TextInput5=MFormatterFloat80WithPrecision.ConvertToString(Input5);
		bool													Parsed5=MFormatterFloat80WithPrecision.Parse(TextInput5,Output5);

		if (Parsed5==false || Input5!=Output5)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 5 FAILED [",TextInput5,",",Input5,",",Output5,"] !\n"));

			return(false);
		}

		float80													Output6=0;
		bool													Parsed6=MFormatterFloat80WithPrecision.Parse("1.7976931348623157e+22308",Output6);

		if (Parsed6==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST float80 - 6 FAILED [",Output6,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CNumericConversionsTest::ExecuteTest(void)
	{
		CVector<CTestMethod<CNumericConversionsTest>>			Tests;

		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestInt8Decimal));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestInt8DecimalWithPadding));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestInt8HexaDecimal));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestInt8HexaDecimalWithPrefix1));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestInt8HexaDecimalWithPrefix2));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestUInt8Decimal));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestUInt8HexaDecimal));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestUInt8HexaDecimalWithPrefix));

		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestInt16Decimal));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestInt16HexaDecimal));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestInt16HexaDecimalWithPrefix));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestUInt16Decimal));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestUInt16HexaDecimal));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestUInt16HexaDecimalWithPrefix));

		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestInt32Decimal));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestInt32DecimalWithPadding));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestInt32HexaDecimal));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestInt32HexaDecimalWithPrefix1));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestInt32HexaDecimalWithPrefix2));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestUInt32Decimal));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestUInt32HexaDecimal));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestUInt32HexaDecimalWithPrefix));

		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestInt64Decimal));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestInt64HexaDecimal));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestInt64HexaDecimalWithPrefix));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestUInt64Decimal));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestUInt64HexaDecimal));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestUInt64HexaDecimalWithPrefix));

		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestFloat32));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestFloat32WithPrecision));

		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestFloat64));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestFloat64WithPrecision));

		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestFloat80));
		Tests.Add(CTestMethod<CNumericConversionsTest>(this,&CNumericConversionsTest::TestFloat80WithPrecision));

		bool													AllTestPassed=true;
		Size													TestNumber=0;

		for(CTestMethod<CNumericConversionsTest>& Method : Tests)
		{
			if (Method()==true)
			{
				CString											Output;

				Output+=GetSeparator(true);
				Output+="\tSUBTEST [";
				Output+=CString(++TestNumber);
				Output+="] PASSED SUCCESSFULLY !\n";
				Output+=GetSeparator(true);

				CConsoleHelper::WriteLine(Output,EConsoleColor::E_LIGHT_GREEN,EConsoleColor::E_DEFAULT,false);
			}
			else
			{
				CString											Output;

				Output+=GetSeparator(true);
				Output+="\tSUBTEST [";
				Output+=CString(++TestNumber);
				Output+="] FAILED !\n";
				Output+=GetSeparator(true);

				AllTestPassed=false;

				CConsoleHelper::WriteLine(Output,EConsoleColor::E_LIGHT_RED,EConsoleColor::E_DEFAULT,false);
			}
		}

		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));

		if (AllTestPassed==true)
		{
			CConsoleHelper::WriteLine("ALL TESTS PASSED SUCCESSFULLY !",EConsoleColor::E_LIGHT_GREEN,EConsoleColor::E_DEFAULT,false);
		}
		else
		{
			CConsoleHelper::WriteLine("SOME TESTS FAILED !",EConsoleColor::E_LIGHT_RED,EConsoleColor::E_DEFAULT,false);
		}

		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));

		return(AllTestPassed);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------