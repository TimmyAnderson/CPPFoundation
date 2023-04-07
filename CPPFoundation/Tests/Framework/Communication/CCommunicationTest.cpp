//----------------------------------------------------------------------------------------------------------------------
#include "CCommunicationTest.h"
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
	CCommunicationTest::CCommunicationTest(CLogWriter& LogWriter, const CLogCategory& LogCategoryTest)
		: CTest(LogWriter,LogCategoryTest,"COMMUNICATION TEST")
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CCommunicationTest::~CCommunicationTest(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCommunicationTest::TestIPAddressParsing(void)
	{
		Size													TestNumber=0;
		CVector<SIPAddressParsingTestData>						IPAddressParsingTestDataCollection;

		IPAddressParsingTestDataCollection.Add(SIPAddressParsingTestData(ESocketIPAddressType::E_IP_V4,"10.20.30.40",true,CSocketIPAddress(10,20,30,40)));
		IPAddressParsingTestDataCollection.Add(SIPAddressParsingTestData(ESocketIPAddressType::E_IP_V4,"10.20.30.",false,CSocketIPAddress()));
		IPAddressParsingTestDataCollection.Add(SIPAddressParsingTestData(ESocketIPAddressType::E_IP_V4,"10.20..40",false,CSocketIPAddress()));
		IPAddressParsingTestDataCollection.Add(SIPAddressParsingTestData(ESocketIPAddressType::E_IP_V4,"10.20.30.40.50",false,CSocketIPAddress()));
		IPAddressParsingTestDataCollection.Add(SIPAddressParsingTestData(ESocketIPAddressType::E_IP_V4,"",false,CSocketIPAddress()));

		IPAddressParsingTestDataCollection.Add(SIPAddressParsingTestData(ESocketIPAddressType::E_IP_V6,"2001:0db8:0000:0000:0000:ff00:0042:8329",true,CSocketIPAddress({0x20,0x01,0x0d,0xb8,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x42,0x83,0x29})));
		IPAddressParsingTestDataCollection.Add(SIPAddressParsingTestData(ESocketIPAddressType::E_IP_V6,"2001:db8:0:0:0:ff00:42:8329",true,CSocketIPAddress({0x20,0x01,0x0d,0xb8,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x42,0x83,0x29})));
		IPAddressParsingTestDataCollection.Add(SIPAddressParsingTestData(ESocketIPAddressType::E_IP_V6,"2001:db8::ff00:42:8329",true,CSocketIPAddress({0x20,0x01,0x0d,0xb8,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x42,0x83,0x29})));
		IPAddressParsingTestDataCollection.Add(SIPAddressParsingTestData(ESocketIPAddressType::E_IP_V6,"::1",true,CSocketIPAddress({0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01})));
		IPAddressParsingTestDataCollection.Add(SIPAddressParsingTestData(ESocketIPAddressType::E_IP_V6,"1::",true,CSocketIPAddress({0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00})));
		IPAddressParsingTestDataCollection.Add(SIPAddressParsingTestData(ESocketIPAddressType::E_IP_V6,"2001:db8::0000::ff00:42:8329",false,CSocketIPAddress()));
		IPAddressParsingTestDataCollection.Add(SIPAddressParsingTestData(ESocketIPAddressType::E_IP_V6,"2001:db8::ff00:42:8329:",false,CSocketIPAddress()));
		IPAddressParsingTestDataCollection.Add(SIPAddressParsingTestData(ESocketIPAddressType::E_IP_V6,":2001:db8::ff00:42:8329",false,CSocketIPAddress()));
		IPAddressParsingTestDataCollection.Add(SIPAddressParsingTestData(ESocketIPAddressType::E_IP_V6,"2w01:db8::ff00:42:8329",false,CSocketIPAddress()));
		IPAddressParsingTestDataCollection.Add(SIPAddressParsingTestData(ESocketIPAddressType::E_IP_V6,"2001:0db8:0000:0000:0000:0000:0000:0000:ff00:0042:8329",false,CSocketIPAddress()));
		IPAddressParsingTestDataCollection.Add(SIPAddressParsingTestData(ESocketIPAddressType::E_IP_V6,"2001:0db8:0000:0000::0000:ff00:0042:8329",false,CSocketIPAddress()));
		IPAddressParsingTestDataCollection.Add(SIPAddressParsingTestData(ESocketIPAddressType::E_IP_V6,"2001:10db8:0000:0000:0000:ff00:0042:8329",false,CSocketIPAddress()));
		IPAddressParsingTestDataCollection.Add(SIPAddressParsingTestData(ESocketIPAddressType::E_IP_V6,"",false,CSocketIPAddress()));
		IPAddressParsingTestDataCollection.Add(SIPAddressParsingTestData(ESocketIPAddressType::E_IP_V6,"::",true,CSocketIPAddress({0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00})));

		for(const SIPAddressParsingTestData& IPAddressParsingTestData : IPAddressParsingTestDataCollection)
		{
			TestNumber++;

			CSocketIPAddress									Address;

			if (IPAddressParsingTestData.GetAddressType()==ESocketIPAddressType::E_IP_V4)
			{
				if (IPAddressParsingTestData.GetIsValidAddress()==true)
				{
					if (CSocketIPAddress::ParseIPv4Address(IPAddressParsingTestData.GetAddressAsString(),Address)==false || Address!=IPAddressParsingTestData.GetAddressToCheck())
					{
						CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to PARSE IPv4 ADDRESS !\n"));
						return(false);
					}
				}
				else
				{
					if (CSocketIPAddress::ParseIPv4Address(IPAddressParsingTestData.GetAddressAsString(),Address)==true)
					{
						CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," INCORRECTLY PARSED INVALID IPv4 ADDRESS !\n"));
						return(false);
					}
				}
			}
			else if (IPAddressParsingTestData.GetAddressType()==ESocketIPAddressType::E_IP_V6)
			{
				if (IPAddressParsingTestData.GetIsValidAddress()==true)
				{
					if (CSocketIPAddress::ParseIPv6Address(IPAddressParsingTestData.GetAddressAsString(),Address)==false || Address!=IPAddressParsingTestData.GetAddressToCheck())
					{
						CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to PARSE IPv6 ADDRESS !\n"));
						return(false);
					}
				}
				else
				{
					if (CSocketIPAddress::ParseIPv6Address(IPAddressParsingTestData.GetAddressAsString(),Address)==true)
					{
						CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," INCORRECTLY PARSED INVALID IPv6 ADDRESS !\n"));
						return(false);
					}
				}
			}
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCommunicationTest::TestIPEndpointParsing(void)
	{
		Size													TestNumber=0;
		CVector<SIPEndpointParsingTestData>						IPEndpointParsingTestDataCollection;

		IPEndpointParsingTestDataCollection.Add(SIPEndpointParsingTestData(ESocketIPAddressType::E_IP_V4,"10.20.30.40:1000",true,CSocketIPEndpoint(CSocketIPAddress(10,20,30,40),1000)));
		IPEndpointParsingTestDataCollection.Add(SIPEndpointParsingTestData(ESocketIPAddressType::E_IP_V4,"155.255.255.255:40000",true,CSocketIPEndpoint(CSocketIPAddress(155,255,255,255),40000)));
		IPEndpointParsingTestDataCollection.Add(SIPEndpointParsingTestData(ESocketIPAddressType::E_IP_V4,"10.20.30.40:",false,CSocketIPEndpoint()));
		IPEndpointParsingTestDataCollection.Add(SIPEndpointParsingTestData(ESocketIPAddressType::E_IP_V4,"10.20.30.40",false,CSocketIPEndpoint()));
		IPEndpointParsingTestDataCollection.Add(SIPEndpointParsingTestData(ESocketIPAddressType::E_IP_V4,"10.20.30.:1000",false,CSocketIPEndpoint()));
		IPEndpointParsingTestDataCollection.Add(SIPEndpointParsingTestData(ESocketIPAddressType::E_IP_V4,"10.20..40:1000",false,CSocketIPEndpoint()));
		IPEndpointParsingTestDataCollection.Add(SIPEndpointParsingTestData(ESocketIPAddressType::E_IP_V4,"10.20.30.40.50:1000",false,CSocketIPEndpoint()));
		IPEndpointParsingTestDataCollection.Add(SIPEndpointParsingTestData(ESocketIPAddressType::E_IP_V4,"",false,CSocketIPEndpoint()));

		IPEndpointParsingTestDataCollection.Add(SIPEndpointParsingTestData(ESocketIPAddressType::E_IP_V6,"[2001:0db8:0000:0000:0000:ff00:0042:8329]:40000",true,CSocketIPEndpoint(CSocketIPAddress({0x20,0x01,0x0d,0xb8,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x42,0x83,0x29}),40000)));
		IPEndpointParsingTestDataCollection.Add(SIPEndpointParsingTestData(ESocketIPAddressType::E_IP_V6," [2001:0db8:0000:0000:0000:ff00:0042:8329]:40000",false,CSocketIPEndpoint()));
		IPEndpointParsingTestDataCollection.Add(SIPEndpointParsingTestData(ESocketIPAddressType::E_IP_V6,"2001:0db8:0000:0000:0000:ff00:0042:8329]:40000",false,CSocketIPEndpoint()));
		IPEndpointParsingTestDataCollection.Add(SIPEndpointParsingTestData(ESocketIPAddressType::E_IP_V6,"[[2001:0db8:0000:0000:0000:ff00:0042:8329]:40000",false,CSocketIPEndpoint()));
		IPEndpointParsingTestDataCollection.Add(SIPEndpointParsingTestData(ESocketIPAddressType::E_IP_V6,"[2001:0db8:0000:0000:0000:ff00:0042:8329]]:40000",false,CSocketIPEndpoint()));
		IPEndpointParsingTestDataCollection.Add(SIPEndpointParsingTestData(ESocketIPAddressType::E_IP_V6,"[2001:0db8:0000:0000:0000:ff00:0042:8329:40000",false,CSocketIPEndpoint()));
		IPEndpointParsingTestDataCollection.Add(SIPEndpointParsingTestData(ESocketIPAddressType::E_IP_V6,"[2001:0db8:0000:0000:0000:ff00:0042:8329]::40000",false,CSocketIPEndpoint()));
		IPEndpointParsingTestDataCollection.Add(SIPEndpointParsingTestData(ESocketIPAddressType::E_IP_V6,"[2001:0db8:0000:0000:0000:ff00:0042:8329]:40000aa",false,CSocketIPEndpoint()));
		IPEndpointParsingTestDataCollection.Add(SIPEndpointParsingTestData(ESocketIPAddressType::E_IP_V6,"[2001:0db8:0000:0000:0000:ff00:0042:8329]:",false,CSocketIPEndpoint()));
		IPEndpointParsingTestDataCollection.Add(SIPEndpointParsingTestData(ESocketIPAddressType::E_IP_V6,"[]:10000",false,CSocketIPEndpoint()));
		IPEndpointParsingTestDataCollection.Add(SIPEndpointParsingTestData(ESocketIPAddressType::E_IP_V6,"",false,CSocketIPEndpoint()));

		for(const SIPEndpointParsingTestData& IPEndpointParsingTestData : IPEndpointParsingTestDataCollection)
		{
			TestNumber++;

			CSocketIPEndpoint							Endpoint;

			if (IPEndpointParsingTestData.GetEndpointType()==ESocketIPAddressType::E_IP_V4)
			{
				if (IPEndpointParsingTestData.GetIsValidEndpoint()==true)
				{
					if (CSocketIPEndpoint::ParseIPv4Endpoint(IPEndpointParsingTestData.GetEndpointAsString(),Endpoint)==false || Endpoint!=IPEndpointParsingTestData.GetEndpointToCheck())
					{
						CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to PARSE IPv4 ENDPOINT !\n"));
						return(false);
					}
				}
				else
				{
					if (CSocketIPEndpoint::ParseIPv4Endpoint(IPEndpointParsingTestData.GetEndpointAsString(),Endpoint)==true)
					{
						CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," INCORRECTLY PARSED INVALID IPv4 ENDPOINT !\n"));
						return(false);
					}
				}
			}
			else if (IPEndpointParsingTestData.GetEndpointType()==ESocketIPAddressType::E_IP_V6)
			{
				if (IPEndpointParsingTestData.GetIsValidEndpoint()==true)
				{
					if (CSocketIPEndpoint::ParseIPv6Endpoint(IPEndpointParsingTestData.GetEndpointAsString(),Endpoint)==false || Endpoint!=IPEndpointParsingTestData.GetEndpointToCheck())
					{
						CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," FAILED to PARSE IPv6 ENDPOINT !\n"));
						return(false);
					}
				}
				else
				{
					if (CSocketIPEndpoint::ParseIPv6Endpoint(IPEndpointParsingTestData.GetEndpointAsString(),Endpoint)==true)
					{
						CConsoleHelper::WriteLine(CString::Format("\tTEST ",++TestNumber," INCORRECTLY PARSED INVALID IPv6 ENDPOINT !\n"));
						return(false);
					}
				}
			}
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCommunicationTest::ExecuteTest(void)
	{
		CVector<CTestMethod<CCommunicationTest>>				Tests;

		Tests.Add(CTestMethod<CCommunicationTest>(this,&CCommunicationTest::TestIPAddressParsing));
		Tests.Add(CTestMethod<CCommunicationTest>(this,&CCommunicationTest::TestIPEndpointParsing));

		bool													AllTestPassed=true;
		Size													TestNumber=0;

		for(CTestMethod<CCommunicationTest>& Method : Tests)
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