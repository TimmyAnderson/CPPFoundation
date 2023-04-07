//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPResponseItem.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPResponseItem::CSocketUDPResponseItem(const CTimeout& Timeout, const CSocketID& SocketID, const CSocketUDPAddress& DestinationAddress, const CSocketUDPResponseItemDataCollection& ResponseItemDataCollection)
		: MTimeout(Timeout), MSocketID(SocketID), MDestinationAddress(DestinationAddress), MResponseItemDataCollection(ResponseItemDataCollection)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPResponseItem::~CSocketUDPResponseItem(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CSocketUDPResponseItem::GetTimeout(void) const noexcept
	{
		return(MTimeout);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPSocketUDPManagerMessageRequestSocketWrite CSocketUDPResponseItem::CreateWriteRequest(CCSPByteBuffer RequestData) const
	{
		CByteBuffer												RawResponseData;

		for(const CSocketUDPResponseItemData& ResponseItemData : MResponseItemDataCollection)
		{
			ESocketUDPResponseItemDataMode						ResponseItemDataMode=ResponseItemData.GetResponseItemDataMode();

			if (ResponseItemDataMode==ESocketUDPResponseItemDataMode::E_DATA)
			{
				RawResponseData.Add(ResponseItemData.GetValueCollection());
			}
			else if (ResponseItemDataMode==ESocketUDPResponseItemDataMode::E_USE_REQUEST_DATA)
			{
				for(Size Index : ResponseItemData.GetIndexCollection())
				{
					uint8										Value=(*RequestData)[Index];

					RawResponseData.Add(Value);
				}
			}
			else if (ResponseItemDataMode==ESocketUDPResponseItemDataMode::E_USE_VALUE_GENERATOR)
			{
				const CByteBuffer&								Values=ResponseItemData.GetValueGenerator()(*RequestData);

				RawResponseData.Add(Values);
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("INVALID RESPONSE DATA MODE [",ResponseItemDataMode,"] !")));
			}
		}

		CCSPByteBuffer											ResponseData(new CByteBuffer(RawResponseData));

		return(CSPSocketUDPManagerMessageRequestSocketWrite(new CSocketUDPManagerMessageRequestSocketWrite(MSocketID,CCSPSocketUDPManagerMessageContext(new CSocketUDPManagerMessageContext(CSocketUDPManagerMessageID())),MDestinationAddress,ResponseData,CExpirationTime(1000))));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSPSocketUDPResponseItem CSocketUDPResponseItem::CreateCopyWithModifiedAddress(const CSocketUDPAddress& DestinationAddress) const
	{
		return(CSPSocketUDPResponseItem(new CSocketUDPResponseItem(MTimeout,MSocketID,DestinationAddress,MResponseItemDataCollection)));
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------