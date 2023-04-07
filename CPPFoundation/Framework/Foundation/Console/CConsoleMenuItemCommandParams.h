//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Collections/CByteBuffer.h>
#include <Framework/Foundation/Communication/Networking/Protocols/DNS/Resolver/CSocketDNSEndpoint.h>
#include <Framework/Foundation/Communication/Networking/Protocols/IP/CSocketIPEndpoint.h>
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Time/CDateTime.h>
#include <Framework/Foundation/Types/ICallableObject.h>
#include <Framework/Foundation/Types/CFunction.h>
#include <Framework/Foundation/Types/CMethod.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include <Framework/Foundation/Types/CPrimitiveType.h>
#include <Framework/Foundation/Types/SBool.h>
#include <Framework/Foundation/Types/TypeTraits.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CConsoleMenuItemCommandParams final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			static const CString								HEXADECIMAL_PREFIX;

		private:
			CString												MCommand;
			CVector<CString>									MCommandParams;

		private:
			void CheckParamIndex(Size Index) const;

		private:
			template<typename TEnumType>
			static TEnumType GetValueAsEnum(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, TEnumType DefaultValue)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				if (DefaultValuePlaceholder==RawValue)
				{
					return(DefaultValue);
				}
				else
				{
					TEnumType									Value;

					if (ParseValue(RawValue,Value)==true)
					{
						return(Value);
					}
					else
					{
						throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE !")));
					}
				}
			}

		private:
			static int8 GetValueAsInt8(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, int8 DefaultValue, bool AllowHexValues, int8 LowerBound, int8 UpperBound);
			static uint8 GetValueAsUInt8(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint8 DefaultValue, bool AllowHexValues, uint8 LowerBound, uint8 UpperBound);
			static int16 GetValueAsInt16(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, int16 DefaultValue, bool AllowHexValues, int16 LowerBound, int16 UpperBound);
			static uint16 GetValueAsUInt16(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint16 DefaultValue, bool AllowHexValues, uint16 LowerBound, uint16 UpperBound);
			static int32 GetValueAsInt32(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, int32 DefaultValue, bool AllowHexValues, int32 LowerBound, int32 UpperBound);
			static uint32 GetValueAsUInt32(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint32 DefaultValue, bool AllowHexValues, uint32 LowerBound, uint32 UpperBound);
			static int64 GetValueAsInt64(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, int64 DefaultValue, bool AllowHexValues, int64 LowerBound, int64 UpperBound);
			static uint64 GetValueAsUInt64(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint64 DefaultValue, bool AllowHexValues, uint64 LowerBound, uint64 UpperBound);
			static float32 GetValueAsFloat32(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, float32 DefaultValue, float32 LowerBound, float32 UpperBound);
			static float64 GetValueAsFloat64(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, float64 DefaultValue, float64 LowerBound, float64 UpperBound);
			static float80 GetValueAsFloat80(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, float80 DefaultValue, float80 LowerBound, float80 UpperBound);
			static Size GetValueAsSize(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, Size DefaultValue, bool AllowHexValues, Size LowerBound, Size UpperBound);
			static CString GetValueAsString(const CString& RawValue, const CString& DefaultValuePlaceholder, const CString& DefaultValue);
			static CDateTime GetValueAsDateTime(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CDateTime& DefaultValue, const CDateTime& LowerBound, const CDateTime& UpperBound);
			static CSocketIPAddress GetValueAsIPv4Address(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPAddress& DefaultValue);
			static CSocketIPEndpoint GetValueAsIPv4Endpoint(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPEndpoint& DefaultValue);
			static CSocketIPAddress GetValueAsIPv6Address(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPAddress& DefaultValue);
			static CSocketIPEndpoint GetValueAsIPv6Endpoint(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPEndpoint& DefaultValue);
			static CSocketDNSAddress GetValueAsDNSAddress(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketDNSAddress& DefaultValue);
			static CSocketDNSEndpoint GetValueAsDNSEndpoint(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketDNSEndpoint& DefaultValue);
			static bool GetValueAsBool(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, bool DefaultValue);

		public:
			const CString& GetCommand(void) const noexcept;
			const CVector<CString>& GetCommandParams(void) const noexcept;
			Size GetNumberOfParams(void) const noexcept;
			void CheckNumberOfParams(Size NumberOfParams) const;

		public:
			template<typename TEnumType>
			TEnumType GetParamAsEnum(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", TEnumType DefaultValue=TEnumType()) const
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				CheckParamIndex(Index);

				TEnumType										Value=GetValueAsEnum<TEnumType>(MCommandParams[Index],ParameterName,DefaultValuePlaceholder,DefaultValue);

				return(Value);
			}

		public:
			int8 GetParamAsInt8(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", int8 DefaultValue=0, bool AllowHexValues=false, int8 LowerBound=CInt8::Min(), int8 UpperBound=CInt8::Max()) const;
			uint8 GetParamAsUInt8(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint8 DefaultValue=0, bool AllowHexValues=false, uint8 LowerBound=CUInt8::Min(), uint8 UpperBound=CUInt8::Max()) const;
			int16 GetParamAsInt16(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", int16 DefaultValue=0, bool AllowHexValues=false, int16 LowerBound=CInt16::Min(), int16 UpperBound=CInt16::Max()) const;
			uint16 GetParamAsUInt16(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint16 DefaultValue=0, bool AllowHexValues=false, uint16 LowerBound=CUInt16::Min(), uint16 UpperBound=CUInt16::Max()) const;
			int32 GetParamAsInt32(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", int32 DefaultValue=0, bool AllowHexValues=false, int32 LowerBound=CInt32::Min(), int32 UpperBound=CInt32::Max()) const;
			uint32 GetParamAsUInt32(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint32 DefaultValue=0, bool AllowHexValues=false, uint32 LowerBound=CUInt32::Min(), uint32 UpperBound=CUInt32::Max()) const;
			int64 GetParamAsInt64(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", int64 DefaultValue=0, bool AllowHexValues=false, int64 LowerBound=CInt64::Min(), int64 UpperBound=CInt64::Max()) const;
			uint64 GetParamAsUInt64(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint64 DefaultValue=0, bool AllowHexValues=false, uint64 LowerBound=CUInt64::Min(), uint64 UpperBound=CUInt64::Max()) const;
			float32 GetParamAsFloat32(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", float32 DefaultValue=0, float32 LowerBound=CFloat32::Min(), float32 UpperBound=CFloat32::Max()) const;
			float64 GetParamAsFloat64(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", float64 DefaultValue=0, float64 LowerBound=CFloat64::Min(), float64 UpperBound=CFloat64::Max()) const;
			float80 GetParamAsFloat80(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", float80 DefaultValue=0, float80 LowerBound=CFloat80::Min(), float80 UpperBound=CFloat80::Max()) const;
			Size GetParamAsSize(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", Size DefaultValue=0, bool AllowHexValues=false, Size LowerBound=CSize::Min(), Size UpperBound=CSize::Max()) const;
			CString GetParamAsString(Size Index, const CString& DefaultValuePlaceholder="", const CString& DefaultValue=CString()) const;
			CDateTime GetParamAsDateTime(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CDateTime& DefaultValue=CDateTime::GetMin(), const CDateTime& LowerBound=CDateTime::GetMin(), const CDateTime& UpperBound=CDateTime::GetMax()) const;
			CSocketIPAddress GetParamAsIPv4Address(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPAddress& DefaultValue=CSocketIPAddress()) const;
			CSocketIPEndpoint GetParamAsIPv4Endpoint(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPEndpoint& DefaultValue=CSocketIPEndpoint()) const;
			CSocketIPAddress GetParamAsIPv6Address(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPAddress& DefaultValue=CSocketIPAddress()) const;
			CSocketIPEndpoint GetParamAsIPv6Endpoint(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPEndpoint& DefaultValue=CSocketIPEndpoint()) const;
			CSocketDNSAddress GetParamAsDNSAddress(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketDNSAddress& DefaultValue=CSocketDNSAddress()) const;
			CSocketDNSEndpoint GetParamAsDNSEndpoint(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketDNSEndpoint& DefaultValue=CSocketDNSEndpoint()) const;
			bool GetParamAsBool(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", bool DefaultValue=false) const;

		public:
			template<typename TEnumType>
			CVector<TEnumType> GetSeparatedParamsAsEnum(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", TEnumType DefaultValue=TEnumType()) const
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				CheckParamIndex(Index);

				CString											RawParamValue=CString::ToUpperString(MCommandParams[Index]);
				CVector<CString>								ParamValues=RawParamValue.Split(Separator);
				CVector<TEnumType>								Values;

				Values.ReserveCapacity(ParamValues.GetLength());

				for(const CString& ParamValue : ParamValues)
				{
					TEnumType									Value=GetValueAsEnum<TEnumType>(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue);

					Values.Add(Value);
				}

				return(Values);
			}

		public:
			CVector<int8> GetSeparatedParamsAsInt8(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", int8 DefaultValue=0, bool AllowHexValues=false, int8 LowerBound=CInt8::Min(), int8 UpperBound=CInt8::Max()) const;
			CVector<uint8> GetSeparatedParamsAsUInt8(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", uint8 DefaultValue=0, bool AllowHexValues=false, uint8 LowerBound=CUInt8::Min(), uint8 UpperBound=CUInt8::Max()) const;
			CVector<int16> GetSeparatedParamsAsInt16(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", int16 DefaultValue=0, bool AllowHexValues=false, int16 LowerBound=CInt16::Min(), int16 UpperBound=CInt16::Max()) const;
			CVector<uint16> GetSeparatedParamsAsUInt16(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", uint16 DefaultValue=0, bool AllowHexValues=false, uint16 LowerBound=CUInt16::Min(), uint16 UpperBound=CUInt16::Max()) const;
			CVector<int32> GetSeparatedParamsAsInt32(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", int32 DefaultValue=0, bool AllowHexValues=false, int32 LowerBound=CInt32::Min(), int32 UpperBound=CInt32::Max()) const;
			CVector<uint32> GetSeparatedParamsAsUInt32(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", uint32 DefaultValue=0, bool AllowHexValues=false, uint32 LowerBound=CUInt32::Min(), uint32 UpperBound=CUInt32::Max()) const;
			CVector<int64> GetSeparatedParamsAsInt64(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", int64 DefaultValue=0, bool AllowHexValues=false, int64 LowerBound=CInt64::Min(), int64 UpperBound=CInt64::Max()) const;
			CVector<uint64> GetSeparatedParamsAsUInt64(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", uint64 DefaultValue=0, bool AllowHexValues=false, uint64 LowerBound=CUInt64::Min(), uint64 UpperBound=CUInt64::Max()) const;
			CVector<float32> GetSeparatedParamsAsFloat32(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", float32 DefaultValue=0, float32 LowerBound=CFloat32::Min(), float32 UpperBound=CFloat32::Max()) const;
			CVector<float64> GetSeparatedParamsAsFloat64(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", float64 DefaultValue=0, float64 LowerBound=CFloat64::Min(), float64 UpperBound=CFloat64::Max()) const;
			CVector<float80> GetSeparatedParamsAsFloat80(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", float80 DefaultValue=0, float80 LowerBound=CFloat80::Min(), float80 UpperBound=CFloat80::Max()) const;
			CVector<Size> GetSeparatedParamsAsSize(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", Size DefaultValue=0, bool AllowHexValues=false, Size LowerBound=CSize::Min(), Size UpperBound=CSize::Max()) const;
			CVector<CString> GetSeparatedParamsAsString(Size Index, const CString& Separator, const CString& DefaultValuePlaceholder="", const CString& DefaultValue=CString()) const;
			CVector<CDateTime> GetSeparatedParamsAsDateTime(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", const CDateTime& DefaultValue=CDateTime::GetMin(), const CDateTime& LowerBound=CDateTime::GetMin(), const CDateTime& UpperBound=CDateTime::GetMax()) const;
			CVector<CSocketIPAddress> GetSeparatedParamsAsIPv4Address(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", const CSocketIPAddress& DefaultValue=CSocketIPAddress()) const;
			CVector<CSocketIPEndpoint> GetSeparatedParamsAsIPv4Endpoint(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", const CSocketIPEndpoint& DefaultValue=CSocketIPEndpoint()) const;
			CVector<CSocketIPAddress> GetSeparatedParamsAsIPv6Address(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", const CSocketIPAddress& DefaultValue=CSocketIPAddress()) const;
			CVector<CSocketIPEndpoint> GetSeparatedParamsAsIPv6Endpoint(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", const CSocketIPEndpoint& DefaultValue=CSocketIPEndpoint()) const;
			CVector<CSocketDNSAddress> GetSeparatedParamsAsDNSAddress(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", const CSocketDNSAddress& DefaultValue=CSocketDNSAddress()) const;
			CVector<CSocketDNSEndpoint> GetSeparatedParamsAsDNSEndpoint(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", const CSocketDNSEndpoint& DefaultValue=CSocketDNSEndpoint()) const;
			CVector<SBool> GetSeparatedParamsAsBool(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", SBool DefaultValue=SBool()) const;
			CByteBuffer GetSeparatedParamsAsByteBuffer(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder="", uint8 DefaultValue=0, bool AllowHexValues=false, uint8 LowerBound=CUInt8::Min(), uint8 UpperBound=CUInt8::Max()) const;

		public:
			template<typename TEnumType>
			CVector<TEnumType> GetParamsAsEnumArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", TEnumType DefaultValue=TEnumType()) const
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				CVector<TEnumType>								Parameters;

				CheckParamIndex(Index);

				Size											NumberOfParameters=GetParamAsSize(Index,ParameterName);

				CheckParamIndex(Index+NumberOfParameters);

				Index++;

				for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
				{
					TEnumType									Value=GetParamAsEnum<TEnumType>(Index,ParameterName,DefaultValuePlaceholder,DefaultValue);

					Parameters.Add(Value);
				}

				return(Parameters);
			}

		public:
			CVector<int8> GetParamsAsInt8Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", int8 DefaultValue=0, bool AllowHexValues=false, int8 LowerBound=CInt8::Min(), int8 UpperBound=CInt8::Max()) const;
			CVector<uint8> GetParamsAsUInt8Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint8 DefaultValue=0, bool AllowHexValues=false, uint8 LowerBound=CUInt8::Min(), uint8 UpperBound=CUInt8::Max()) const;
			CVector<int16> GetParamsAsInt16Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", int16 DefaultValue=0, bool AllowHexValues=false, int16 LowerBound=CInt16::Min(), int16 UpperBound=CInt16::Max()) const;
			CVector<uint16> GetParamsAsUInt16Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint16 DefaultValue=0, bool AllowHexValues=false, uint16 LowerBound=CUInt16::Min(), uint16 UpperBound=CUInt16::Max()) const;
			CVector<int32> GetParamsAsInt32Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", int32 DefaultValue=0, bool AllowHexValues=false, int32 LowerBound=CInt32::Min(), int32 UpperBound=CInt32::Max()) const;
			CVector<uint32> GetParamsAsUInt32Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint32 DefaultValue=0, bool AllowHexValues=false, uint32 LowerBound=CUInt32::Min(), uint32 UpperBound=CUInt32::Max()) const;
			CVector<int64> GetParamsAsInt64Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", int64 DefaultValue=0, bool AllowHexValues=false, int64 LowerBound=CInt64::Min(), int64 UpperBound=CInt64::Max()) const;
			CVector<uint64> GetParamsAsUInt64Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint64 DefaultValue=0, bool AllowHexValues=false, uint64 LowerBound=CUInt64::Min(), uint64 UpperBound=CUInt64::Max()) const;
			CVector<float32> GetParamsAsFloat32Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", float32 DefaultValue=0, float32 LowerBound=CFloat32::Min(), float32 UpperBound=CFloat32::Max()) const;
			CVector<float64> GetParamsAsFloat64Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", float64 DefaultValue=0, float64 LowerBound=CFloat64::Min(), float64 UpperBound=CFloat64::Max()) const;
			CVector<float80> GetParamsAsFloat80Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", float80 DefaultValue=0, float80 LowerBound=CFloat80::Min(), float80 UpperBound=CFloat80::Max()) const;
			CVector<Size> GetParamsAsSizeArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", Size DefaultValue=0, bool AllowHexValues=false, Size LowerBound=CSize::Min(), Size UpperBound=CSize::Max()) const;
			CVector<CString> GetParamsAsStringsArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CString& DefaultValue=CString()) const;
			CVector<CDateTime> GetParamsAsDateTimeArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CDateTime& DefaultValue=CDateTime::GetMin(), const CDateTime& LowerBound=CDateTime::GetMin(), const CDateTime& UpperBound=CDateTime::GetMax()) const;
			CVector<CSocketIPAddress> GetParamsAsIPv4AddressesArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPAddress& DefaultValue=CSocketIPAddress()) const;
			CVector<CSocketIPEndpoint> GetParamsAsIPv4EndpointsArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPEndpoint& DefaultValue=CSocketIPEndpoint()) const;
			CVector<CSocketIPAddress> GetParamsAsIPv6AddressesArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPAddress& DefaultValue=CSocketIPAddress()) const;
			CVector<CSocketIPEndpoint> GetParamsAsIPv6EndpointsArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPEndpoint& DefaultValue=CSocketIPEndpoint()) const;
			CVector<CSocketDNSAddress> GetParamsAsDNSAddressesArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketDNSAddress& DefaultValue=CSocketDNSAddress()) const;
			CVector<CSocketDNSEndpoint> GetParamsAsDNSEndpointsArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketDNSEndpoint& DefaultValue=CSocketDNSEndpoint()) const;
			CVector<SBool> GetParamsAsBoolsArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", SBool DefaultValue=SBool()) const;
			CByteBuffer GetParamsAsByteBufferArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint8 DefaultValue=0, bool AllowHexValues=false, uint8 LowerBound=CUInt8::Min(), uint8 UpperBound=CUInt8::Max()) const;

		public:
			template<typename TEnumType>
			CVector<TEnumType> GetRemainingParamsAsEnum(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", TEnumType DefaultValue=TEnumType()) const
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				CVector<TEnumType>								Parameters;
				Size											NumberOfParameters=GetNumberOfParams();

				for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
				{
					TEnumType									Value=GetParamAsEnum<TEnumType>(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue);

					Parameters.Add(Value);
				}

				return(Parameters);
			}

		public:
			CVector<int8> GetRemainingParamsAsInt8(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", int8 DefaultValue=0, bool AllowHexValues=false, int8 LowerBound=CInt8::Min(), int8 UpperBound=CInt8::Max()) const;
			CVector<uint8> GetRemainingParamsAsUInt8(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint8 DefaultValue=0, bool AllowHexValues=false, uint8 LowerBound=CUInt8::Min(), uint8 UpperBound=CUInt8::Max()) const;
			CVector<int16> GetRemainingParamsAsInt16(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", int16 DefaultValue=0, bool AllowHexValues=false, int16 LowerBound=CInt16::Min(), int16 UpperBound=CInt16::Max()) const;
			CVector<uint16> GetRemainingParamsAsUInt16(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint16 DefaultValue=0, bool AllowHexValues=false, uint16 LowerBound=CUInt16::Min(), uint16 UpperBound=CUInt16::Max()) const;
			CVector<int32> GetRemainingParamsAsInt32(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", int32 DefaultValue=0, bool AllowHexValues=false, int32 LowerBound=CInt32::Min(), int32 UpperBound=CInt32::Max()) const;
			CVector<uint32> GetRemainingParamsAsUInt32(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint32 DefaultValue=0, bool AllowHexValues=false, uint32 LowerBound=CUInt32::Min(), uint32 UpperBound=CUInt32::Max()) const;
			CVector<int64> GetRemainingParamsAsInt64(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", int64 DefaultValue=0, bool AllowHexValues=false, int64 LowerBound=CInt64::Min(), int64 UpperBound=CInt64::Max()) const;
			CVector<uint64> GetRemainingParamsAsUInt64(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint64 DefaultValue=0, bool AllowHexValues=false, uint64 LowerBound=CUInt64::Min(), uint64 UpperBound=CUInt64::Max()) const;
			CVector<float32> GetRemainingParamsAsFloat32(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", float32 DefaultValue=0, float32 LowerBound=CFloat32::Min(), float32 UpperBound=CFloat32::Max()) const;
			CVector<float64> GetRemainingParamsAsFloat64(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", float64 DefaultValue=0, float64 LowerBound=CFloat64::Min(), float64 UpperBound=CFloat64::Max()) const;
			CVector<float80> GetRemainingParamsAsFloat80(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", float80 DefaultValue=0, float80 LowerBound=CFloat80::Min(), float80 UpperBound=CFloat80::Max()) const;
			CVector<Size> GetRemainingParamsAsSize(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", Size DefaultValue=0, bool AllowHexValues=false, Size LowerBound=CSize::Min(), Size UpperBound=CSize::Max()) const;
			CVector<CString> GetRemainingParamsAsStrings(Size& Index, const CString& DefaultValuePlaceholder="", const CString& DefaultValue=CString()) const;
			CVector<CDateTime> GetRemainingParamsAsDateTime(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CDateTime& DefaultValue=CDateTime::GetMin(), const CDateTime& LowerBound=CDateTime::GetMin(), const CDateTime& UpperBound=CDateTime::GetMax()) const;
			CVector<CSocketIPAddress> GetRemainingParamsAsIPv4Addresses(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPAddress& DefaultValue=CSocketIPAddress()) const;
			CVector<CSocketIPEndpoint> GetRemainingParamsAsIPv4Endpoints(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPEndpoint& DefaultValue=CSocketIPEndpoint()) const;
			CVector<CSocketIPAddress> GetRemainingParamsAsIPv6Addresses(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPAddress& DefaultValue=CSocketIPAddress()) const;
			CVector<CSocketIPEndpoint> GetRemainingParamsAsIPv6Endpoints(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketIPEndpoint& DefaultValue=CSocketIPEndpoint()) const;
			CVector<CSocketDNSAddress> GetRemainingParamsAsDNSAddresses(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketDNSAddress& DefaultValue=CSocketDNSAddress()) const;
			CVector<CSocketDNSEndpoint> GetRemainingParamsAsDNSEndpoints(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", const CSocketDNSEndpoint& DefaultValue=CSocketDNSEndpoint()) const;
			CVector<SBool> GetRemainingParamsAsBools(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", SBool DefaultValue=SBool()) const;
			CByteBuffer GetRemainingParamsAsByteBuffer(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder="", uint8 DefaultValue=0, bool AllowHexValues=false, uint8 LowerBound=CUInt8::Min(), uint8 UpperBound=CUInt8::Max()) const;

		public:
			CConsoleMenuItemCommandParams(const CString& CommandText);
			CConsoleMenuItemCommandParams(const CConsoleMenuItemCommandParams& Other);
			CConsoleMenuItemCommandParams(CConsoleMenuItemCommandParams&& Other) noexcept;
			virtual ~CConsoleMenuItemCommandParams(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPConsoleMenuItemCallback=CSharedPointer<ICallableObject<void(const CConsoleMenuItemCommandParams& CommandParams)>>;
	using														CCSPConsoleMenuItemCallback=CSharedPointer<const ICallableObject<void(const CConsoleMenuItemCommandParams& CommandParams)>>;
	using														CConsoleMenuItemCallbackFunction=CFunction<void(const CConsoleMenuItemCommandParams& CommandParams)>;
	template<typename TClassType>
	using														CConsoleMenuItemCallbackMethod=CMethod<TClassType,void(const CConsoleMenuItemCommandParams& CommandParams)>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------