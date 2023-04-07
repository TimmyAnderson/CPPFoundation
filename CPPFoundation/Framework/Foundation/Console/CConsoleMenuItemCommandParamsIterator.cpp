//----------------------------------------------------------------------------------------------------------------------
#include "CConsoleMenuItemCommandParamsIterator.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CConsoleMenuItemCommandParamsIterator::CConsoleMenuItemCommandParamsIterator(const CConsoleMenuItemCommandParams& CommandParams, Size CommandParamsIndex)
		: MCommandParams(CommandParams), MCommandParamsIndex(CommandParamsIndex)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CConsoleMenuItemCommandParamsIterator::CConsoleMenuItemCommandParamsIterator(CConsoleMenuItemCommandParams&& CommandParams, Size CommandParamsIndex)
		: MCommandParams(FUNCTION_MOVE(CommandParams)), MCommandParamsIndex(CommandParamsIndex)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CConsoleMenuItemCommandParamsIterator::~CConsoleMenuItemCommandParamsIterator(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CConsoleMenuItemCommandParams& CConsoleMenuItemCommandParamsIterator::GetCommandParams(void) const noexcept
	{
		return(MCommandParams);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CConsoleMenuItemCommandParamsIterator::GetCommandParamsIndex(void) const noexcept
	{
		return(MCommandParamsIndex);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleMenuItemCommandParamsIterator::CheckNumberOfParams(Size NumberOfParams) const
	{
		MCommandParams.CheckNumberOfParams(MCommandParamsIndex+NumberOfParams);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CConsoleMenuItemCommandParamsIterator::GetNumberOfRemainingParams(void) const noexcept
	{
		if (MCommandParamsIndex<MCommandParams.GetNumberOfParams())
		{
			return(MCommandParams.GetNumberOfParams()-MCommandParamsIndex);
		}
		else
		{
			return(0);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int8 CConsoleMenuItemCommandParamsIterator::GetParamAsInt8(const CString& ParameterName, const CString& DefaultValuePlaceholder, int8 DefaultValue, bool AllowHexValues, int8 LowerBound, int8 UpperBound)
	{
		return(MCommandParams.GetParamAsInt8(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8 CConsoleMenuItemCommandParamsIterator::GetParamAsUInt8(const CString& ParameterName, const CString& DefaultValuePlaceholder, uint8 DefaultValue, bool AllowHexValues, uint8 LowerBound, uint8 UpperBound)
	{
		return(MCommandParams.GetParamAsUInt8(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	int16 CConsoleMenuItemCommandParamsIterator::GetParamAsInt16(const CString& ParameterName, const CString& DefaultValuePlaceholder, int16 DefaultValue, bool AllowHexValues, int16 LowerBound, int16 UpperBound)
	{
		return(MCommandParams.GetParamAsInt16(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint16 CConsoleMenuItemCommandParamsIterator::GetParamAsUInt16(const CString& ParameterName, const CString& DefaultValuePlaceholder, uint16 DefaultValue, bool AllowHexValues, uint16 LowerBound, uint16 UpperBound)
	{
		return(MCommandParams.GetParamAsUInt16(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CConsoleMenuItemCommandParamsIterator::GetParamAsInt32(const CString& ParameterName, const CString& DefaultValuePlaceholder, int32 DefaultValue, bool AllowHexValues, int32 LowerBound, int32 UpperBound)
	{
		return(MCommandParams.GetParamAsInt32(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint32 CConsoleMenuItemCommandParamsIterator::GetParamAsUInt32(const CString& ParameterName, const CString& DefaultValuePlaceholder, uint32 DefaultValue, bool AllowHexValues, uint32 LowerBound, uint32 UpperBound)
	{
		return(MCommandParams.GetParamAsUInt32(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CConsoleMenuItemCommandParamsIterator::GetParamAsInt64(const CString& ParameterName, const CString& DefaultValuePlaceholder, int64 DefaultValue, bool AllowHexValues, int64 LowerBound, int64 UpperBound)
	{
		return(MCommandParams.GetParamAsInt64(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint64 CConsoleMenuItemCommandParamsIterator::GetParamAsUInt64(const CString& ParameterName, const CString& DefaultValuePlaceholder, uint64 DefaultValue, bool AllowHexValues, uint64 LowerBound, uint64 UpperBound)
	{
		return(MCommandParams.GetParamAsUInt64(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	float32 CConsoleMenuItemCommandParamsIterator::GetParamAsFloat32(const CString& ParameterName, const CString& DefaultValuePlaceholder, float32 DefaultValue, float32 LowerBound, float32 UpperBound)
	{
		return(MCommandParams.GetParamAsFloat32(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	float64 CConsoleMenuItemCommandParamsIterator::GetParamAsFloat64(const CString& ParameterName, const CString& DefaultValuePlaceholder, float64 DefaultValue, float64 LowerBound, float64 UpperBound)
	{
		return(MCommandParams.GetParamAsFloat64(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	float80 CConsoleMenuItemCommandParamsIterator::GetParamAsFloat80(const CString& ParameterName, const CString& DefaultValuePlaceholder, float80 DefaultValue, float80 LowerBound, float80 UpperBound)
	{
		return(MCommandParams.GetParamAsFloat80(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CConsoleMenuItemCommandParamsIterator::GetParamAsSize(const CString& ParameterName, const CString& DefaultValuePlaceholder, Size DefaultValue, bool AllowHexValues, Size LowerBound, Size UpperBound)
	{
		return(MCommandParams.GetParamAsSize(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CConsoleMenuItemCommandParamsIterator::GetParamAsString(const CString& DefaultValuePlaceholder, const CString& DefaultValue)
	{
		return(MCommandParams.GetParamAsString(MCommandParamsIndex++,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime CConsoleMenuItemCommandParamsIterator::GetParamAsDateTime(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CDateTime& DefaultValue, const CDateTime& LowerBound, const CDateTime& UpperBound)
	{
		return(MCommandParams.GetParamAsDateTime(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPAddress CConsoleMenuItemCommandParamsIterator::GetParamAsIPv4Address(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPAddress& DefaultValue)
	{
		return(MCommandParams.GetParamAsIPv4Address(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPEndpoint CConsoleMenuItemCommandParamsIterator::GetParamAsIPv4Endpoint(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPEndpoint& DefaultValue)
	{
		return(MCommandParams.GetParamAsIPv4Endpoint(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPAddress CConsoleMenuItemCommandParamsIterator::GetParamAsIPv6Address(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPAddress& DefaultValue)
	{
		return(MCommandParams.GetParamAsIPv6Address(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPEndpoint CConsoleMenuItemCommandParamsIterator::GetParamAsIPv6Endpoint(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPEndpoint& DefaultValue)
	{
		return(MCommandParams.GetParamAsIPv6Endpoint(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSAddress CConsoleMenuItemCommandParamsIterator::GetParamAsDNSAddress(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketDNSAddress& DefaultValue)
	{
		return(MCommandParams.GetParamAsDNSAddress(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSEndpoint CConsoleMenuItemCommandParamsIterator::GetParamAsDNSEndpoint(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketDNSEndpoint& DefaultValue)
	{
		return(MCommandParams.GetParamAsDNSEndpoint(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CConsoleMenuItemCommandParamsIterator::GetParamAsBool(const CString& ParameterName, const CString& DefaultValuePlaceholder, bool DefaultValue)
	{
		return(MCommandParams.GetParamAsBool(MCommandParamsIndex++,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CVector<int8> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsInt8(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, int8 DefaultValue, bool AllowHexValues, int8 LowerBound, int8 UpperBound)
	{
		return(MCommandParams.GetSeparatedParamsAsInt8(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint8> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsUInt8(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, uint8 DefaultValue, bool AllowHexValues, uint8 LowerBound, uint8 UpperBound)
	{
		return(MCommandParams.GetSeparatedParamsAsUInt8(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<int16> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsInt16(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, int16 DefaultValue, bool AllowHexValues, int16 LowerBound, int16 UpperBound)
	{
		return(MCommandParams.GetSeparatedParamsAsInt16(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint16> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsUInt16(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, uint16 DefaultValue, bool AllowHexValues, uint16 LowerBound, uint16 UpperBound)
	{
		return(MCommandParams.GetSeparatedParamsAsUInt16(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<int32> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsInt32(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, int32 DefaultValue, bool AllowHexValues, int32 LowerBound, int32 UpperBound)
	{
		return(MCommandParams.GetSeparatedParamsAsInt32(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint32> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsUInt32(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, uint32 DefaultValue, bool AllowHexValues, uint32 LowerBound, uint32 UpperBound)
	{
		return(MCommandParams.GetSeparatedParamsAsUInt32(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<int64> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsInt64(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, int64 DefaultValue, bool AllowHexValues, int64 LowerBound, int64 UpperBound)
	{
		return(MCommandParams.GetSeparatedParamsAsInt64(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint64> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsUInt64(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, uint64 DefaultValue, bool AllowHexValues, uint64 LowerBound, uint64 UpperBound)
	{
		return(MCommandParams.GetSeparatedParamsAsUInt64(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<float32> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsFloat32(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, float32 DefaultValue, float32 LowerBound, float32 UpperBound)
	{
		return(MCommandParams.GetSeparatedParamsAsFloat32(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<float64> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsFloat64(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, float64 DefaultValue, float64 LowerBound, float64 UpperBound)
	{
		return(MCommandParams.GetSeparatedParamsAsFloat64(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<float80> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsFloat80(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, float80 DefaultValue, float80 LowerBound, float80 UpperBound)
	{
		return(MCommandParams.GetSeparatedParamsAsFloat80(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<Size> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsSize(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, Size DefaultValue, bool AllowHexValues, Size LowerBound, Size UpperBound)
	{
		return(MCommandParams.GetSeparatedParamsAsSize(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CString> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsString(const CString& Separator, const CString& DefaultValuePlaceholder, const CString& DefaultValue)
	{
		return(MCommandParams.GetSeparatedParamsAsString(MCommandParamsIndex++,Separator,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CDateTime> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsDateTime(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, const CDateTime& DefaultValue, const CDateTime& LowerBound, const CDateTime& UpperBound)
	{
		return(MCommandParams.GetSeparatedParamsAsDateTime(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPAddress> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsIPv4Address(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, const CSocketIPAddress& DefaultValue)
	{
		return(MCommandParams.GetSeparatedParamsAsIPv4Address(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPEndpoint> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsIPv4Endpoint(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, const CSocketIPEndpoint& DefaultValue)
	{
		return(MCommandParams.GetSeparatedParamsAsIPv4Endpoint(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPAddress> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsIPv6Address(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, const CSocketIPAddress& DefaultValue)
	{
		return(MCommandParams.GetSeparatedParamsAsIPv6Address(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPEndpoint> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsIPv6Endpoint(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, const CSocketIPEndpoint& DefaultValue)
	{
		return(MCommandParams.GetSeparatedParamsAsIPv6Endpoint(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketDNSAddress> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsDNSAddress(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, const CSocketDNSAddress& DefaultValue)
	{
		return(MCommandParams.GetSeparatedParamsAsDNSAddress(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketDNSEndpoint> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsDNSEndpoint(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, const CSocketDNSEndpoint& DefaultValue)
	{
		return(MCommandParams.GetSeparatedParamsAsDNSEndpoint(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<SBool> CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsBool(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, SBool DefaultValue)
	{
		return(MCommandParams.GetSeparatedParamsAsBool(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CConsoleMenuItemCommandParamsIterator::GetSeparatedParamsAsByteBuffer(const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, uint8 DefaultValue, bool AllowHexValues, uint8 LowerBound, uint8 UpperBound)
	{
		return(MCommandParams.GetSeparatedParamsAsByteBuffer(MCommandParamsIndex++,ParameterName,Separator,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CVector<int8> CConsoleMenuItemCommandParamsIterator::GetParamsAsInt8Array(const CString& ParameterName, const CString& DefaultValuePlaceholder, int8 DefaultValue, bool AllowHexValues, int8 LowerBound, int8 UpperBound)
	{
		return(MCommandParams.GetParamsAsInt8Array(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint8> CConsoleMenuItemCommandParamsIterator::GetParamsAsUInt8Array(const CString& ParameterName, const CString& DefaultValuePlaceholder, uint8 DefaultValue, bool AllowHexValues, uint8 LowerBound, uint8 UpperBound)
	{
		return(MCommandParams.GetParamsAsUInt8Array(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<int16> CConsoleMenuItemCommandParamsIterator::GetParamsAsInt16Array(const CString& ParameterName, const CString& DefaultValuePlaceholder, int16 DefaultValue, bool AllowHexValues, int16 LowerBound, int16 UpperBound)
	{
		return(MCommandParams.GetParamsAsInt16Array(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint16> CConsoleMenuItemCommandParamsIterator::GetParamsAsUInt16Array(const CString& ParameterName, const CString& DefaultValuePlaceholder, uint16 DefaultValue, bool AllowHexValues, uint16 LowerBound, uint16 UpperBound)
	{
		return(MCommandParams.GetParamsAsUInt16Array(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<int32> CConsoleMenuItemCommandParamsIterator::GetParamsAsInt32Array(const CString& ParameterName, const CString& DefaultValuePlaceholder, int32 DefaultValue, bool AllowHexValues, int32 LowerBound, int32 UpperBound)
	{
		return(MCommandParams.GetParamsAsInt32Array(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint32> CConsoleMenuItemCommandParamsIterator::GetParamsAsUInt32Array(const CString& ParameterName, const CString& DefaultValuePlaceholder, uint32 DefaultValue, bool AllowHexValues, uint32 LowerBound, uint32 UpperBound)
	{
		return(MCommandParams.GetParamsAsUInt32Array(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<int64> CConsoleMenuItemCommandParamsIterator::GetParamsAsInt64Array(const CString& ParameterName, const CString& DefaultValuePlaceholder, int64 DefaultValue, bool AllowHexValues, int64 LowerBound, int64 UpperBound)
	{
		return(MCommandParams.GetParamsAsInt64Array(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint64> CConsoleMenuItemCommandParamsIterator::GetParamsAsUInt64Array(const CString& ParameterName, const CString& DefaultValuePlaceholder, uint64 DefaultValue, bool AllowHexValues, uint64 LowerBound, uint64 UpperBound)
	{
		return(MCommandParams.GetParamsAsUInt64Array(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<float32> CConsoleMenuItemCommandParamsIterator::GetParamsAsFloat32Array(const CString& ParameterName, const CString& DefaultValuePlaceholder, float32 DefaultValue, float32 LowerBound, float32 UpperBound)
	{
		return(MCommandParams.GetParamsAsFloat32Array(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<float64> CConsoleMenuItemCommandParamsIterator::GetParamsAsFloat64Array(const CString& ParameterName, const CString& DefaultValuePlaceholder, float64 DefaultValue, float64 LowerBound, float64 UpperBound)
	{
		return(MCommandParams.GetParamsAsFloat64Array(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<float80> CConsoleMenuItemCommandParamsIterator::GetParamsAsFloat80Array(const CString& ParameterName, const CString& DefaultValuePlaceholder, float80 DefaultValue, float80 LowerBound, float80 UpperBound)
	{
		return(MCommandParams.GetParamsAsFloat80Array(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<Size> CConsoleMenuItemCommandParamsIterator::GetParamsAsSizeArray(const CString& ParameterName, const CString& DefaultValuePlaceholder, Size DefaultValue, bool AllowHexValues, Size LowerBound, Size UpperBound)
	{
		return(MCommandParams.GetParamsAsSizeArray(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CString> CConsoleMenuItemCommandParamsIterator::GetParamsAsStringsArray(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CString& DefaultValue)
	{
		return(MCommandParams.GetParamsAsStringsArray(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CDateTime> CConsoleMenuItemCommandParamsIterator::GetParamsAsDateTimeArray(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CDateTime& DefaultValue, const CDateTime& LowerBound, const CDateTime& UpperBound)
	{
		return(MCommandParams.GetParamsAsDateTimeArray(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPAddress> CConsoleMenuItemCommandParamsIterator::GetParamsAsIPv4AddressesArray(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPAddress& DefaultValue)
	{
		return(MCommandParams.GetParamsAsIPv4AddressesArray(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPEndpoint> CConsoleMenuItemCommandParamsIterator::GetParamsAsIPv4EndpointsArray(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPEndpoint& DefaultValue)
	{
		return(MCommandParams.GetParamsAsIPv4EndpointsArray(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPAddress> CConsoleMenuItemCommandParamsIterator::GetParamsAsIPv6AddressesArray(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPAddress& DefaultValue)
	{
		return(MCommandParams.GetParamsAsIPv6AddressesArray(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPEndpoint> CConsoleMenuItemCommandParamsIterator::GetParamsAsIPv6EndpointsArray(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPEndpoint& DefaultValue)
	{
		return(MCommandParams.GetParamsAsIPv6EndpointsArray(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketDNSAddress> CConsoleMenuItemCommandParamsIterator::GetParamsAsDNSAddressesArray(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketDNSAddress& DefaultValue)
	{
		return(MCommandParams.GetParamsAsDNSAddressesArray(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketDNSEndpoint> CConsoleMenuItemCommandParamsIterator::GetParamsAsDNSEndpointsArray(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketDNSEndpoint& DefaultValue)
	{
		return(MCommandParams.GetParamsAsDNSEndpointsArray(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<SBool> CConsoleMenuItemCommandParamsIterator::GetParamsAsBoolsArray(const CString& ParameterName, const CString& DefaultValuePlaceholder, SBool DefaultValue)
	{
		return(MCommandParams.GetParamsAsBoolsArray(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CConsoleMenuItemCommandParamsIterator::GetParamsAsByteBufferArray(const CString& ParameterName, const CString& DefaultValuePlaceholder, uint8 DefaultValue, bool AllowHexValues, uint8 LowerBound, uint8 UpperBound)
	{
		return(MCommandParams.GetParamsAsByteBufferArray(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CVector<int8> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsInt8(const CString& ParameterName, const CString& DefaultValuePlaceholder, int8 DefaultValue, bool AllowHexValues, int8 LowerBound, int8 UpperBound)
	{
		return(MCommandParams.GetRemainingParamsAsInt8(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint8> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsUInt8(const CString& ParameterName, const CString& DefaultValuePlaceholder, uint8 DefaultValue, bool AllowHexValues, uint8 LowerBound, uint8 UpperBound)
	{
		return(MCommandParams.GetRemainingParamsAsUInt8(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<int16> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsInt16(const CString& ParameterName, const CString& DefaultValuePlaceholder, int16 DefaultValue, bool AllowHexValues, int16 LowerBound, int16 UpperBound)
	{
		return(MCommandParams.GetRemainingParamsAsInt16(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint16> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsUInt16(const CString& ParameterName, const CString& DefaultValuePlaceholder, uint16 DefaultValue, bool AllowHexValues, uint16 LowerBound, uint16 UpperBound)
	{
		return(MCommandParams.GetRemainingParamsAsUInt16(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<int32> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsInt32(const CString& ParameterName, const CString& DefaultValuePlaceholder, int32 DefaultValue, bool AllowHexValues, int32 LowerBound, int32 UpperBound)
	{
		return(MCommandParams.GetRemainingParamsAsInt32(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint32> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsUInt32(const CString& ParameterName, const CString& DefaultValuePlaceholder, uint32 DefaultValue, bool AllowHexValues, uint32 LowerBound, uint32 UpperBound)
	{
		return(MCommandParams.GetRemainingParamsAsUInt32(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<int64> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsInt64(const CString& ParameterName, const CString& DefaultValuePlaceholder, int64 DefaultValue, bool AllowHexValues, int64 LowerBound, int64 UpperBound)
	{
		return(MCommandParams.GetRemainingParamsAsInt64(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint64> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsUInt64(const CString& ParameterName, const CString& DefaultValuePlaceholder, uint64 DefaultValue, bool AllowHexValues, uint64 LowerBound, uint64 UpperBound)
	{
		return(MCommandParams.GetRemainingParamsAsUInt64(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<float32> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsFloat32(const CString& ParameterName, const CString& DefaultValuePlaceholder, float32 DefaultValue, float32 LowerBound, float32 UpperBound)
	{
		return(MCommandParams.GetRemainingParamsAsFloat32(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<float64> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsFloat64(const CString& ParameterName, const CString& DefaultValuePlaceholder, float64 DefaultValue, float64 LowerBound, float64 UpperBound)
	{
		return(MCommandParams.GetRemainingParamsAsFloat64(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<float80> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsFloat80(const CString& ParameterName, const CString& DefaultValuePlaceholder, float80 DefaultValue, float80 LowerBound, float80 UpperBound)
	{
		return(MCommandParams.GetRemainingParamsAsFloat80(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<Size> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsSize(const CString& ParameterName, const CString& DefaultValuePlaceholder, Size DefaultValue, bool AllowHexValues, Size LowerBound, Size UpperBound)
	{
		return(MCommandParams.GetRemainingParamsAsSize(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CString> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsStrings(const CString& DefaultValuePlaceholder, const CString& DefaultValue)
	{
		return(MCommandParams.GetRemainingParamsAsStrings(MCommandParamsIndex,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CDateTime> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsDateTime(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CDateTime& DefaultValue, const CDateTime& LowerBound, const CDateTime& UpperBound)
	{
		return(MCommandParams.GetRemainingParamsAsDateTime(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPAddress> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsIPv4Addresses(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPAddress& DefaultValue)
	{
		return(MCommandParams.GetRemainingParamsAsIPv4Addresses(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPEndpoint> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsIPv4Endpoints(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPEndpoint& DefaultValue)
	{
		return(MCommandParams.GetRemainingParamsAsIPv4Endpoints(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPAddress> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsIPv6Addresses(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPAddress& DefaultValue)
	{
		return(MCommandParams.GetRemainingParamsAsIPv6Addresses(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPEndpoint> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsIPv6Endpoints(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPEndpoint& DefaultValue)
	{
		return(MCommandParams.GetRemainingParamsAsIPv6Endpoints(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketDNSAddress> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsDNSAddresses(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketDNSAddress& DefaultValue)
	{
		return(MCommandParams.GetRemainingParamsAsDNSAddresses(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketDNSEndpoint> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsDNSEndpoints(const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketDNSEndpoint& DefaultValue)
	{
		return(MCommandParams.GetRemainingParamsAsDNSEndpoints(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<SBool> CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsBools(const CString& ParameterName, const CString& DefaultValuePlaceholder, SBool DefaultValue)
	{
		return(MCommandParams.GetRemainingParamsAsBools(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CConsoleMenuItemCommandParamsIterator::GetRemainingParamsAsByteBuffer(const CString& ParameterName, const CString& DefaultValuePlaceholder, uint8 DefaultValue, bool AllowHexValues, uint8 LowerBound, uint8 UpperBound)
	{
		return(MCommandParams.GetRemainingParamsAsByteBuffer(MCommandParamsIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------