//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Time/CDateTime.h>
#include "CConsoleMenuItemCommandParams.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CConsoleMenuItemCommandParamsIterator final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CConsoleMenuItemCommandParams						MCommandParams;
			Size												MCommandParamsIndex;

		public:
			const CConsoleMenuItemCommandParams& GetCommandParams(void) const noexcept;
			Size GetCommandParamsIndex(void) const noexcept;
			void CheckNumberOfParams(Size NumberOfParams) const;
			Size GetNumberOfRemainingParams(void) const noexcept;

		public:
			template<typename TEnumType>
			TEnumType GetParamAsEnum(const CString& ParameterName, const CString& DefaultValuePlaceholder="", TEnumType DefaultValue=TEnumType())
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				TEnumType										Value=MCommandParams.GetParamAsEnum<TEnumType>(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue);

				return(Value);
			}

		public:
			int8 GetParamAsInt8(const CString& ParameterName, const CString& DefaultValuePlaceholder="", int8 DefaultValue=0, bool AllowHexValues=false, int8 LowerBound=CInt8::Min(), int8 UpperBound=CInt8::Max());
			uint8 GetParamAsUInt8(const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint8 DefaultValue=0, bool AllowHexValues=false, uint8 LowerBound=CUInt8::Min(), uint8 UpperBound=CUInt8::Max());
			int16 GetParamAsInt16(const CString& ParameterName, const CString& DefaultValuePlaceholder="", int16 DefaultValue=0, bool AllowHexValues=false, int16 LowerBound=CInt16::Min(), int16 UpperBound=CInt16::Max());
			uint16 GetParamAsUInt16(const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint16 DefaultValue=0, bool AllowHexValues=false, uint16 LowerBound=CUInt16::Min(), uint16 UpperBound=CUInt16::Max());
			int32 GetParamAsInt32(const CString& ParameterName, const CString& DefaultValuePlaceholder="", int32 DefaultValue=0, bool AllowHexValues=false, int32 LowerBound=CInt32::Min(), int32 UpperBound=CInt32::Max());
			uint32 GetParamAsUInt32(const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint32 DefaultValue=0, bool AllowHexValues=false, uint32 LowerBound=CUInt32::Min(), uint32 UpperBound=CUInt32::Max());
			int64 GetParamAsInt64(const CString& ParameterName, const CString& DefaultValuePlaceholder="", int64 DefaultValue=0, bool AllowHexValues=false, int64 LowerBound=CInt64::Min(), int64 UpperBound=CInt64::Max());
			uint64 GetParamAsUInt64(const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint64 DefaultValue=0, bool AllowHexValues=false, uint64 LowerBound=CUInt64::Min(), uint64 UpperBound=CUInt64::Max());
			float32 GetParamAsFloat32(const CString& ParameterName, const CString& DefaultValuePlaceholder="", float32 DefaultValue=0, float32 LowerBound=CFloat32::Min(), float32 UpperBound=CFloat32::Max());
			float64 GetParamAsFloat64(const CString& ParameterName, const CString& DefaultValuePlaceholder="", float64 DefaultValue=0, float64 LowerBound=CFloat64::Min(), float64 UpperBound=CFloat64::Max());
			float80 GetParamAsFloat80(const CString& ParameterName, const CString& DefaultValuePlaceholder="", float80 DefaultValue=0, float80 LowerBound=CFloat80::Min(), float80 UpperBound=CFloat80::Max());
			Size GetParamAsSize(const CString& ParameterName, const CString& DefaultValuePlaceholder="", Size DefaultValue=0, bool AllowHexValues=false, Size LowerBound=CSize::Min(), Size UpperBound=CSize::Max());
			CString GetParamAsString(const CString& DefaultValuePlaceholder="", const CString& DefaultValue=CString());
			CDateTime GetParamAsDateTime(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CDateTime& DefaultValue=CDateTime::GetMin(), const CDateTime& LowerBound=CDateTime::GetMin(), const CDateTime& UpperBound=CDateTime::GetMax());
			CSocketIPAddress GetParamAsIPv4Address(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPAddress& DefaultValue=CSocketIPAddress());
			CSocketIPEndpoint GetParamAsIPv4Endpoint(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPEndpoint& DefaultValue=CSocketIPEndpoint());
			CSocketIPAddress GetParamAsIPv6Address(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPAddress& DefaultValue=CSocketIPAddress());
			CSocketIPEndpoint GetParamAsIPv6Endpoint(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPEndpoint& DefaultValue=CSocketIPEndpoint());
			CSocketDNSAddress GetParamAsDNSAddress(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketDNSAddress& DefaultValue=CSocketDNSAddress());
			CSocketDNSEndpoint GetParamAsDNSEndpoint(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketDNSEndpoint& DefaultValue=CSocketDNSEndpoint());
			bool GetParamAsBool(const CString& ParameterName, const CString& DefaultValuePlaceholder="", bool DefaultValue=false);

		public:
			template<typename TEnumType>
			CVector<TEnumType> GetSeparatedParamsAsEnum(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", TEnumType DefaultValue=TEnumType())
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				CVector<TEnumType>								Parameters=MCommandParams.GetSeparatedParamsAsEnum(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue);

				return(Parameters);
			}

		public:
			CVector<int8> GetSeparatedParamsAsInt8(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", int8 DefaultValue=0, bool AllowHexValues=false, int8 LowerBound=CInt8::Min(), int8 UpperBound=CInt8::Max());
			CVector<uint8> GetSeparatedParamsAsUInt8(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", uint8 DefaultValue=0, bool AllowHexValues=false, uint8 LowerBound=CUInt8::Min(), uint8 UpperBound=CUInt8::Max());
			CVector<int16> GetSeparatedParamsAsInt16(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", int16 DefaultValue=0, bool AllowHexValues=false, int16 LowerBound=CInt16::Min(), int16 UpperBound=CInt16::Max());
			CVector<uint16> GetSeparatedParamsAsUInt16(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", uint16 DefaultValue=0, bool AllowHexValues=false, uint16 LowerBound=CUInt16::Min(), uint16 UpperBound=CUInt16::Max());
			CVector<int32> GetSeparatedParamsAsInt32(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", int32 DefaultValue=0, bool AllowHexValues=false, int32 LowerBound=CInt32::Min(), int32 UpperBound=CInt32::Max());
			CVector<uint32> GetSeparatedParamsAsUInt32(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", uint32 DefaultValue=0, bool AllowHexValues=false, uint32 LowerBound=CUInt32::Min(), uint32 UpperBound=CUInt32::Max());
			CVector<int64> GetSeparatedParamsAsInt64(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", int64 DefaultValue=0, bool AllowHexValues=false, int64 LowerBound=CInt64::Min(), int64 UpperBound=CInt64::Max());
			CVector<uint64> GetSeparatedParamsAsUInt64(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", uint64 DefaultValue=0, bool AllowHexValues=false, uint64 LowerBound=CUInt64::Min(), uint64 UpperBound=CUInt64::Max());
			CVector<float32> GetSeparatedParamsAsFloat32(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", float32 DefaultValue=0, float32 LowerBound=CFloat32::Min(), float32 UpperBound=CFloat32::Max());
			CVector<float64> GetSeparatedParamsAsFloat64(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", float64 DefaultValue=0, float64 LowerBound=CFloat64::Min(), float64 UpperBound=CFloat64::Max());
			CVector<float80> GetSeparatedParamsAsFloat80(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", float80 DefaultValue=0, float80 LowerBound=CFloat80::Min(), float80 UpperBound=CFloat80::Max());
			CVector<Size> GetSeparatedParamsAsSize(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", Size DefaultValue=0, bool AllowHexValues=false, Size LowerBound=CSize::Min(), Size UpperBound=CSize::Max());
			CVector<CString> GetSeparatedParamsAsString(const CString& Separator, const CString& DefaultValuePlaceholder="", const CString& DefaultValue=CString());
			CVector<CDateTime> GetSeparatedParamsAsDateTime(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", const CDateTime& DefaultValue=CDateTime::GetMin(), const CDateTime& LowerBound=CDateTime::GetMin(), const CDateTime& UpperBound=CDateTime::GetMax());
			CVector<CSocketIPAddress> GetSeparatedParamsAsIPv4Address(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", const CSocketIPAddress& DefaultValue=CSocketIPAddress());
			CVector<CSocketIPEndpoint> GetSeparatedParamsAsIPv4Endpoint(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", const CSocketIPEndpoint& DefaultValue=CSocketIPEndpoint());
			CVector<CSocketIPAddress> GetSeparatedParamsAsIPv6Address(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", const CSocketIPAddress& DefaultValue=CSocketIPAddress());
			CVector<CSocketIPEndpoint> GetSeparatedParamsAsIPv6Endpoint(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", const CSocketIPEndpoint& DefaultValue=CSocketIPEndpoint());
			CVector<CSocketDNSAddress> GetSeparatedParamsAsDNSAddress(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", const CSocketDNSAddress& DefaultValue=CSocketDNSAddress());
			CVector<CSocketDNSEndpoint> GetSeparatedParamsAsDNSEndpoint(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", const CSocketDNSEndpoint& DefaultValue=CSocketDNSEndpoint());
			CVector<SBool> GetSeparatedParamsAsBool(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", SBool DefaultValue=SBool());
			CByteBuffer GetSeparatedParamsAsByteBuffer(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", uint8 DefaultValue=0, bool AllowHexValues=false, uint8 LowerBound=CUInt8::Min(), uint8 UpperBound=CUInt8::Max());

		public:
			template<typename TEnumType>
			CVector<TEnumType> GetParamsAsEnumArray(const CString& ParameterName, const CString& DefaultValuePlaceholder="", TEnumType DefaultValue=TEnumType())
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				CVector<TEnumType>								Parameters=MCommandParams.GetParamsAsEnumArray<TEnumType>(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue);

				return(Parameters);
			}

		public:
			CVector<int8> GetParamsAsInt8Array(const CString& ParameterName, const CString& DefaultValuePlaceholder="", int8 DefaultValue=0, bool AllowHexValues=false, int8 LowerBound=CInt8::Min(), int8 UpperBound=CInt8::Max());
			CVector<uint8> GetParamsAsUInt8Array(const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint8 DefaultValue=0, bool AllowHexValues=false, uint8 LowerBound=CUInt8::Min(), uint8 UpperBound=CUInt8::Max());
			CVector<int16> GetParamsAsInt16Array(const CString& ParameterName, const CString& DefaultValuePlaceholder="", int16 DefaultValue=0, bool AllowHexValues=false, int16 LowerBound=CInt16::Min(), int16 UpperBound=CInt16::Max());
			CVector<uint16> GetParamsAsUInt16Array(const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint16 DefaultValue=0, bool AllowHexValues=false, uint16 LowerBound=CUInt16::Min(), uint16 UpperBound=CUInt16::Max());
			CVector<int32> GetParamsAsInt32Array(const CString& ParameterName, const CString& DefaultValuePlaceholder="", int32 DefaultValue=0, bool AllowHexValues=false, int32 LowerBound=CInt32::Min(), int32 UpperBound=CInt32::Max());
			CVector<uint32> GetParamsAsUInt32Array(const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint32 DefaultValue=0, bool AllowHexValues=false, uint32 LowerBound=CUInt32::Min(), uint32 UpperBound=CUInt32::Max());
			CVector<int64> GetParamsAsInt64Array(const CString& ParameterName, const CString& DefaultValuePlaceholder="", int64 DefaultValue=0, bool AllowHexValues=false, int64 LowerBound=CInt64::Min(), int64 UpperBound=CInt64::Max());
			CVector<uint64> GetParamsAsUInt64Array(const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint64 DefaultValue=0, bool AllowHexValues=false, uint64 LowerBound=CUInt64::Min(), uint64 UpperBound=CUInt64::Max());
			CVector<float32> GetParamsAsFloat32Array(const CString& ParameterName, const CString& DefaultValuePlaceholder="", float32 DefaultValue=0, float32 LowerBound=CFloat32::Min(), float32 UpperBound=CFloat32::Max());
			CVector<float64> GetParamsAsFloat64Array(const CString& ParameterName, const CString& DefaultValuePlaceholder="", float64 DefaultValue=0, float64 LowerBound=CFloat64::Min(), float64 UpperBound=CFloat64::Max());
			CVector<float80> GetParamsAsFloat80Array(const CString& ParameterName, const CString& DefaultValuePlaceholder="", float80 DefaultValue=0, float80 LowerBound=CFloat80::Min(), float80 UpperBound=CFloat80::Max());
			CVector<Size> GetParamsAsSizeArray(const CString& ParameterName, const CString& DefaultValuePlaceholder="", Size DefaultValue=0, bool AllowHexValues=false, Size LowerBound=CSize::Min(), Size UpperBound=CSize::Max());
			CVector<CString> GetParamsAsStringsArray(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CString& DefaultValue=CString());
			CVector<CDateTime> GetParamsAsDateTimeArray(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CDateTime& DefaultValue=CDateTime::GetMin(), const CDateTime& LowerBound=CDateTime::GetMin(), const CDateTime& UpperBound=CDateTime::GetMax());
			CVector<CSocketIPAddress> GetParamsAsIPv4AddressesArray(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPAddress& DefaultValue=CSocketIPAddress());
			CVector<CSocketIPEndpoint> GetParamsAsIPv4EndpointsArray(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPEndpoint& DefaultValue=CSocketIPEndpoint());
			CVector<CSocketIPAddress> GetParamsAsIPv6AddressesArray(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPAddress& DefaultValue=CSocketIPAddress());
			CVector<CSocketIPEndpoint> GetParamsAsIPv6EndpointsArray(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPEndpoint& DefaultValue=CSocketIPEndpoint());
			CVector<CSocketDNSAddress> GetParamsAsDNSAddressesArray(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketDNSAddress& DefaultValue=CSocketDNSAddress());
			CVector<CSocketDNSEndpoint> GetParamsAsDNSEndpointsArray(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketDNSEndpoint& DefaultValue=CSocketDNSEndpoint());
			CVector<SBool> GetParamsAsBoolsArray(const CString& ParameterName, const CString& DefaultValuePlaceholder="", SBool DefaultValue=SBool());
			CByteBuffer GetParamsAsByteBufferArray(const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint8 DefaultValue=0, bool AllowHexValues=false, uint8 LowerBound=CUInt8::Min(), uint8 UpperBound=CUInt8::Max());

		public:
			template<typename TEnumType>
			CVector<TEnumType> GetRemainingParamsAsEnum(const CString& ParameterName, const CString& DefaultValuePlaceholder="", TEnumType DefaultValue=TEnumType())
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				CVector<TEnumType>								Parameters=MCommandParams.GetRemainingParamsAsEnum(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue);

				return(Parameters);
			}

		public:
			CVector<int8> GetRemainingParamsAsInt8(const CString& ParameterName, const CString& DefaultValuePlaceholder="", int8 DefaultValue=0, bool AllowHexValues=false, int8 LowerBound=CInt8::Min(), int8 UpperBound=CInt8::Max());
			CVector<uint8> GetRemainingParamsAsUInt8(const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint8 DefaultValue=0, bool AllowHexValues=false, uint8 LowerBound=CUInt8::Min(), uint8 UpperBound=CUInt8::Max());
			CVector<int16> GetRemainingParamsAsInt16(const CString& ParameterName, const CString& DefaultValuePlaceholder="", int16 DefaultValue=0, bool AllowHexValues=false, int16 LowerBound=CInt16::Min(), int16 UpperBound=CInt16::Max());
			CVector<uint16> GetRemainingParamsAsUInt16(const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint16 DefaultValue=0, bool AllowHexValues=false, uint16 LowerBound=CUInt16::Min(), uint16 UpperBound=CUInt16::Max());
			CVector<int32> GetRemainingParamsAsInt32(const CString& ParameterName, const CString& DefaultValuePlaceholder="", int32 DefaultValue=0, bool AllowHexValues=false, int32 LowerBound=CInt32::Min(), int32 UpperBound=CInt32::Max());
			CVector<uint32> GetRemainingParamsAsUInt32(const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint32 DefaultValue=0, bool AllowHexValues=false, uint32 LowerBound=CUInt32::Min(), uint32 UpperBound=CUInt32::Max());
			CVector<int64> GetRemainingParamsAsInt64(const CString& ParameterName, const CString& DefaultValuePlaceholder="", int64 DefaultValue=0, bool AllowHexValues=false, int64 LowerBound=CInt64::Min(), int64 UpperBound=CInt64::Max());
			CVector<uint64> GetRemainingParamsAsUInt64(const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint64 DefaultValue=0, bool AllowHexValues=false, uint64 LowerBound=CUInt64::Min(), uint64 UpperBound=CUInt64::Max());
			CVector<float32> GetRemainingParamsAsFloat32(const CString& ParameterName, const CString& DefaultValuePlaceholder="", float32 DefaultValue=0, float32 LowerBound=CFloat32::Min(), float32 UpperBound=CFloat32::Max());
			CVector<float64> GetRemainingParamsAsFloat64(const CString& ParameterName, const CString& DefaultValuePlaceholder="", float64 DefaultValue=0, float64 LowerBound=CFloat64::Min(), float64 UpperBound=CFloat64::Max());
			CVector<float80> GetRemainingParamsAsFloat80(const CString& ParameterName, const CString& DefaultValuePlaceholder="", float80 DefaultValue=0, float80 LowerBound=CFloat80::Min(), float80 UpperBound=CFloat80::Max());
			CVector<Size> GetRemainingParamsAsSize(const CString& ParameterName, const CString& DefaultValuePlaceholder="", Size DefaultValue=0, bool AllowHexValues=false, Size LowerBound=CSize::Min(), Size UpperBound=CSize::Max());
			CVector<CString> GetRemainingParamsAsStrings(const CString& DefaultValuePlaceholder="", const CString& DefaultValue=CString());
			CVector<CDateTime> GetRemainingParamsAsDateTime(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CDateTime& DefaultValue=CDateTime::GetMin(), const CDateTime& LowerBound=CDateTime::GetMin(), const CDateTime& UpperBound=CDateTime::GetMax());
			CVector<CSocketIPAddress> GetRemainingParamsAsIPv4Addresses(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPAddress& DefaultValue=CSocketIPAddress());
			CVector<CSocketIPEndpoint> GetRemainingParamsAsIPv4Endpoints(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPEndpoint& DefaultValue=CSocketIPEndpoint());
			CVector<CSocketIPAddress> GetRemainingParamsAsIPv6Addresses(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPAddress& DefaultValue=CSocketIPAddress());
			CVector<CSocketIPEndpoint> GetRemainingParamsAsIPv6Endpoints(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPEndpoint& DefaultValue=CSocketIPEndpoint());
			CVector<CSocketDNSAddress> GetRemainingParamsAsDNSAddresses(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketDNSAddress& DefaultValue=CSocketDNSAddress());
			CVector<CSocketDNSEndpoint> GetRemainingParamsAsDNSEndpoints(const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketDNSEndpoint& DefaultValue=CSocketDNSEndpoint());
			CVector<SBool> GetRemainingParamsAsBools(const CString& ParameterName, const CString& DefaultValuePlaceholder="", SBool DefaultValue=SBool());
			CByteBuffer GetRemainingParamsAsByteBuffer(const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint8 DefaultValue=0, bool AllowHexValues=false, uint8 LowerBound=CUInt8::Min(), uint8 UpperBound=CUInt8::Max());

		public:
			CConsoleMenuItemCommandParamsIterator(const CConsoleMenuItemCommandParams& CommandParams, Size CommandParamsIndex=0);
			CConsoleMenuItemCommandParamsIterator(CConsoleMenuItemCommandParams&& CommandParams, Size CommandParamsIndex=0);
			virtual ~CConsoleMenuItemCommandParamsIterator(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------