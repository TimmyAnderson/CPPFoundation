//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Testing/CTest.h>
#include <Framework/Foundation/Communication/Networking/Protocols/IP/CSocketIPAddress.h>
#include <Framework/Foundation/Communication/Networking/Protocols/IP/CSocketIPEndpoint.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CCommunicationTest final : public CTest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			struct SIPAddressParsingTestData final
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					CPPFoundation::Foundation::ESocketIPAddressType	MAddressType;
					CPPFoundation::Foundation::CString				MAddressAsString;
					bool										MIsValidAddress;
					CPPFoundation::Foundation::CSocketIPAddress	MAddressToCheck;

				public:
					CPPFoundation::Foundation::ESocketIPAddressType GetAddressType(void) const noexcept
					{
						return(MAddressType);
					}

					const CPPFoundation::Foundation::CString& GetAddressAsString(void) const noexcept
					{
						return(MAddressAsString);
					}

					bool GetIsValidAddress(void) const noexcept
					{
						return(MIsValidAddress);
					}

					const CPPFoundation::Foundation::CSocketIPAddress& GetAddressToCheck(void) const noexcept
					{
						return(MAddressToCheck);
					}

				public:
					SIPAddressParsingTestData(CPPFoundation::Foundation::ESocketIPAddressType AddressType, const CPPFoundation::Foundation::CString& AddressAsString, bool IsValidAddress, const CPPFoundation::Foundation::CSocketIPAddress& AddressToCheck)
						: MAddressType(AddressType), MAddressAsString(AddressAsString), MIsValidAddress(IsValidAddress), MAddressToCheck(AddressToCheck)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private:
			struct SIPEndpointParsingTestData final
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					CPPFoundation::Foundation::ESocketIPAddressType	MEndpointType;
					CPPFoundation::Foundation::CString				MEndpointAsString;
					bool										MIsValidEndpoint;
					CPPFoundation::Foundation::CSocketIPEndpoint	MEndpointToCheck;

				public:
					CPPFoundation::Foundation::ESocketIPAddressType GetEndpointType(void) const noexcept
					{
						return(MEndpointType);
					}

					const CPPFoundation::Foundation::CString& GetEndpointAsString(void) const noexcept
					{
						return(MEndpointAsString);
					}

					bool GetIsValidEndpoint(void) const noexcept
					{
						return(MIsValidEndpoint);
					}

					const CPPFoundation::Foundation::CSocketIPEndpoint& GetEndpointToCheck(void) const noexcept
					{
						return(MEndpointToCheck);
					}

				public:
					SIPEndpointParsingTestData(CPPFoundation::Foundation::ESocketIPAddressType EndpointType, const CPPFoundation::Foundation::CString& EndpointAsString, bool IsValidEndpoint, const CPPFoundation::Foundation::CSocketIPEndpoint EndpointToCheck)
						: MEndpointType(EndpointType), MEndpointAsString(EndpointAsString), MIsValidEndpoint(IsValidEndpoint), MEndpointToCheck(EndpointToCheck)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private:
			bool TestIPAddressParsing(void);
			bool TestIPEndpointParsing(void);

		public:
			virtual bool ExecuteTest(void) override;

		public:
			CCommunicationTest(CPPFoundation::Foundation::CLogWriter& LogWriter, const CPPFoundation::Foundation::CLogCategory& LogCategoryTest);
			virtual ~CCommunicationTest(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------