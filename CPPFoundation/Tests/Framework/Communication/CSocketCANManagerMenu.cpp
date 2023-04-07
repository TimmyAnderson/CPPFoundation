//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANManagerMenu.h"
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/Console/CConsoleHelper.h>
#include <Framework/Foundation/Console/CConsoleMenuItemCommandParamsIterator.h>
#include <Framework/Foundation/Communication/Networking/Sockets/CSocket.h>
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketLibrary.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANFrame.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Manager/CSocketCANManagerMessageRequestSocketAdd.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Manager/CSocketCANManagerMessageRequestSocketRemove.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Manager/CSocketCANManagerMessageRequestSocketWrite.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Manager/CSocketCANManagerMessageResponseSocketAdd.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Manager/CSocketCANManagerMessageResponseSocketClose.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Manager/CSocketCANManagerMessageResponseSocketError.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Manager/CSocketCANManagerMessageResponseSocketRead.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Manager/CSocketCANManagerMessageResponseSocketRemove.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Manager/CSocketCANManagerMessageResponseSocketWrite.h>
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
	CSocketCANManagerMenu::CSocketCANManagerMenu(CConsoleLogWriter& LogWriter)
		: CConsoleMenu(LogWriter,"SOCKET MANAGER CAN"), MIsLibraryInitialized(false), MSocketCollection(), MSocketManager(), MRandom(), MNumberOfPacketsSends(0), MNumberOfPacketsSendSuccesses(0), MNumberOfPacketsSendFailures(0), MNumberOfPacketsReceives(0), MNumberOfSocketsAdds(0), MNumberOfSocketsAddSuccesses(0), MNumberOfSocketsAddFailures(0), MNumberOfSocketsRemoves(0), MNumberOfSocketsRemoveSuccesses(0), MNumberOfSocketsRemoveFailures(0), MNumberOfSocketsCloses(0), MNumberOfSocketsErrors(0), MNumberOfBytesSent(0), MNumberOfBytesReceived(0), MSumOfBytesSent(0), MSumOfBytesReceived(0)
	{
		AddMenuItem(CConsoleMenuItem("X","Exit","",EConsoleMenuItemType::E_ITEM_EXIT,CConsoleMenuItemCallbackMethod<CSocketCANManagerMenu>(this,&CSocketCANManagerMenu::MenuItemExit)));
		AddMenuItem(CConsoleMenuItem("Q","Initialize","[BufferSize]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANManagerMenu>(this,&CSocketCANManagerMenu::MenuItemInitialize)));
		AddMenuItem(CConsoleMenuItem("A","Uninitialize","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANManagerMenu>(this,&CSocketCANManagerMenu::MenuItemUninitialize)));
		AddMenuItem(CConsoleMenuItem("W","Start Socket Manager","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANManagerMenu>(this,&CSocketCANManagerMenu::MenuItemStartSocketManager)));
		AddMenuItem(CConsoleMenuItem("S","Stop Socket Manager","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANManagerMenu>(this,&CSocketCANManagerMenu::MenuItemStopSocketManager)));
		AddMenuItem(CConsoleMenuItem("E","Create Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANManagerMenu>(this,&CSocketCANManagerMenu::MenuItemCreateSocket)));
		AddMenuItem(CConsoleMenuItem("D","Destroy Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANManagerMenu>(this,&CSocketCANManagerMenu::MenuItemDestroySocket)));
		AddMenuItem(CConsoleMenuItem("B","Bind Socket","[SocketName] [NetworkInterfaceIndex]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANManagerMenu>(this,&CSocketCANManagerMenu::MenuItemBindSocket)));
		AddMenuItem(CConsoleMenuItem("AS","Add Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANManagerMenu>(this,&CSocketCANManagerMenu::MenuItemAddSocket)));
		AddMenuItem(CConsoleMenuItem("RS","Remove Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANManagerMenu>(this,&CSocketCANManagerMenu::MenuItemRemoveSocket)));
		AddMenuItem(CConsoleMenuItem("N","Send Data to Socket","[SocketName] [NetworkInterfaceIndex] [IsExtendedFrame] [IsRemoteFrame] [IsErrorFrame] [WriteExpirationTime] [CANID] [Byte1] ... [ByteN]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANManagerMenu>(this,&CSocketCANManagerMenu::MenuItemSendToSocket)));
		AddMenuItem(CConsoleMenuItem("MN","Send Data to Socket","[SocketName] [NumberOfPackets] [NetworkInterfaceIndex] [IsExtendedFrame] [IsRemoteFrame] [IsErrorFrame] [WriteExpirationTime] [CANID] [Byte1] ... [ByteN]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANManagerMenu>(this,&CSocketCANManagerMenu::MenuItemMultiSendToSocket)));
		AddMenuItem(CConsoleMenuItem("GN","Get Network Interface Name","[SocketName] [NetworkInterfaceIndex]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANManagerMenu>(this,&CSocketCANManagerMenu::MenuItemGetNetworkInterfaceNameForDevice)));
		AddMenuItem(CConsoleMenuItem("GI","Get Network Interface Index","[SocketName] [DeviceName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANManagerMenu>(this,&CSocketCANManagerMenu::MenuItemGetNetworkInterfaceIndexForDevice)));
		AddMenuItem(CConsoleMenuItem("C","Execute Command","[CommandNumber]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANManagerMenu>(this,&CSocketCANManagerMenu::MenuItemExecuteCommand)));
		AddMenuItem(CConsoleMenuItem("P","Statistics","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANManagerMenu>(this,&CSocketCANManagerMenu::MenuItemStatistics)));
		AddMenuItem(CConsoleMenuItem("PP","Data Statistics","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANManagerMenu>(this,&CSocketCANManagerMenu::MenuItemDataStatistics)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMenu::~CSocketCANManagerMenu(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerMenu::ProcessMessageResponse(CCSPSocketCANManagerMessageResponse MessageResponse)
	{
		if (MessageResponse.IsTypeOfAsConst<CSocketCANManagerMessageResponseSocketAdd>()==true)
		{
			CCSPSocketCANManagerMessageResponseSocketAdd		TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketCANManagerMessageResponseSocketAdd>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			if (TypedMessageResponse->GetOperationSucceeded()==true)
			{
				MNumberOfSocketsAddSuccesses.Increment();
			}
			else
			{
				MNumberOfSocketsAddFailures.Increment();
			}
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketCANManagerMessageResponseSocketRemove>()==true)
		{
			CCSPSocketCANManagerMessageResponseSocketRemove		TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketCANManagerMessageResponseSocketRemove>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			if (TypedMessageResponse->GetOperationSucceeded()==true)
			{
				MNumberOfSocketsRemoveSuccesses.Increment();
			}
			else
			{
				MNumberOfSocketsRemoveFailures.Increment();
			}
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketCANManagerMessageResponseSocketRead>()==true)
		{
			CCSPSocketCANManagerMessageResponseSocketRead		TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketCANManagerMessageResponseSocketRead>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			CSocketCANFrame										Frame;

			Frame.Deserialize(*TypedMessageResponse->GetData());

			Size												Sum=0;
			
			for(Size Index=0;Index<Frame.GetCANData().GetLength();Index++)
			{
				Sum+=Frame.GetCANData()[Index];
			}

			MNumberOfBytesReceived.Increment(TypedMessageResponse->GetData()->GetLength());
			MSumOfBytesReceived.Increment(Sum);

			MNumberOfPacketsReceives.Increment();
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketCANManagerMessageResponseSocketWrite>()==true)
		{
			CCSPSocketCANManagerMessageResponseSocketWrite		TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketCANManagerMessageResponseSocketWrite>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			if (TypedMessageResponse->GetOperationSucceeded()==true)
			{
				MNumberOfPacketsSendSuccesses.Increment();
			}
			else
			{
				MNumberOfPacketsSendFailures.Increment();
			}
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketCANManagerMessageResponseSocketClose>()==true)
		{
			CCSPSocketCANManagerMessageResponseSocketClose		TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketCANManagerMessageResponseSocketClose>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			MNumberOfSocketsCloses.Increment();
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketCANManagerMessageResponseSocketError>()==true)
		{
			CCSPSocketCANManagerMessageResponseSocketError		TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketCANManagerMessageResponseSocketError>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			MNumberOfSocketsErrors.Increment();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerMenu::MenuItemExit(const CConsoleMenuItemCommandParams&)
	{
		// EMPTY.
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerMenu::MenuItemInitialize(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			Size												BufferSize=CommandParamsIterator.GetParamAsSize("BufferSize");

			CSocketLibrary::Initialize();

			MSocketManager=CSPSocketCANManager(new CSocketCANManager(GetLogWriter(),BufferSize));

			MIsLibraryInitialized=true;

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET LIBRARY is INITIALIZED !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("INITIALIZATION FAILED !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerMenu::MenuItemUninitialize(const CConsoleMenuItemCommandParams&)
	{
		try
		{
			MSocketManager=nullptr;

			CSocketLibrary::Uninitialize();

			MIsLibraryInitialized=false;

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET LIBRARY is UNINITIALIZED !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't UNINITIALIZE LIBRARY !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerMenu::MenuItemStartSocketManager(const CConsoleMenuItemCommandParams&)
	{
		try
		{
			MSocketManager->AddEvent(CEventID("EVENT"),*this);

			MSocketManager->StartThread();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET MANAGER is STARTED !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't START SOCKET MANAGER !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerMenu::MenuItemStopSocketManager(const CConsoleMenuItemCommandParams&)
	{
		try
		{
			MSocketManager->StopThread();

			MSocketManager->RemoveEvent(CEventID("EVENT"));

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET MANAGER is STOPPED !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't STOP SOCKET MANAGER !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerMenu::MenuItemCreateSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MSocketCollection.Contains(SocketName)==false)
			{
				CSPSocketCAN									Socket(new CSocketCAN(GetLogWriter(),SocketName));

				MSocketCollection.Add(SocketName,Socket);

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",SocketName,"] is CREATED !")));
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] is ALREADY CREATED !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't CREATE SOCKET !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerMenu::MenuItemDestroySocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MSocketCollection.Contains(SocketName)==true)
			{
				MSocketCollection.Erase(SocketName);

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",SocketName,"] is DESTROYED !")));
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't DESTROY SOCKET !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerMenu::MenuItemBindSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			CSocketCANAddress									Address=CSocketCANAddress(CommandParamsIterator.GetParamAsInt32("NetworkInterfaceIndex"));

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketCAN									Socket=MSocketCollection[SocketName];

				Socket->BindToAddress(Address);
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't BIND SOCKET !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerMenu::MenuItemAddSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketCAN									Socket=MSocketCollection[SocketName];
				CSPSocketCANManagerMessageRequestSocketAdd		Message(new CSocketCANManagerMessageRequestSocketAdd(CCSPSocketCANManagerMessageContext(new CSocketCANManagerMessageContext(CSocketCANManagerMessageID())),Socket));

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("MESSAGE [",Message,"] is SENT to SOCKET MANAGER !")));

				MSocketManager->SendRequest(Message);

				MNumberOfSocketsAdds.Increment();
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't ADD SOCKET to SOCKET MANAGER !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerMenu::MenuItemRemoveSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketCAN									Socket=MSocketCollection[SocketName];
				CSPSocketCANManagerMessageRequestSocketRemove	Message(new CSocketCANManagerMessageRequestSocketRemove(CSocketID(SocketName),CCSPSocketCANManagerMessageContext(new CSocketCANManagerMessageContext(CSocketCANManagerMessageID()))));

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("MESSAGE [",Message,"] is SENT to SOCKET MANAGER !")));

				MSocketManager->SendRequest(Message);

				MNumberOfSocketsRemoves.Increment();
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't REMOVE SOCKET from SOCKET MANAGER !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerMenu::MenuItemSendToSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(7);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			CSocketCANAddress									RemoteAddress(CommandParamsIterator.GetParamAsInt32("NetworkInterfaceIndex"));
			bool												IsExtendedFrame=CommandParamsIterator.GetParamAsBool("IsExtendedFrame");
			bool												IsRemoteFrame=CommandParamsIterator.GetParamAsBool("IsRemoteFrame");
			bool												IsErrorFrame=CommandParamsIterator.GetParamAsBool("IsErrorFrame");
			CExpirationTime										WriteExpirationTime=CExpirationTime(CommandParamsIterator.GetParamAsInt64("WriteExpirationTime"));
			uint32												ID=CommandParamsIterator.GetParamAsUInt32("ID","",0,true);
			CSocketCANID										CANID(IsExtendedFrame,IsRemoteFrame,IsErrorFrame,ID);
			CByteBuffer											RawData(CommandParamsIterator.GetRemainingParamsAsByteBuffer("Data","",0,true));
			Size												Sum=0;

			for(Size Index=0;Index<RawData.GetLength();Index++)
			{
				Sum+=RawData[Index];
			}

			CSocketCANFrame										Frame(CANID,RawData);
			CSPByteBuffer										Data(new CByteBuffer(Frame.Serialize()));

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketCANManagerMessageRequestSocketWrite	Message(new CSocketCANManagerMessageRequestSocketWrite(CSocketID(SocketName),CCSPSocketCANManagerMessageContext(new CSocketCANManagerMessageContext(CSocketCANManagerMessageID())),RemoteAddress,Data,WriteExpirationTime));

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("MESSAGE [",Message,"] is SENT to SOCKET MANAGER !")));

				MSocketManager->SendRequest(Message);

				MNumberOfBytesSent.Increment(Data->GetLength());
				MSumOfBytesSent.Increment(Sum);

				MNumberOfPacketsSends.Increment();
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't SEND DATA to SOCKET !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerMenu::MenuItemMultiSendToSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(8);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			Size												NumberOfPackets=CommandParamsIterator.GetParamAsSize("NumberOfPackets");
			CSocketCANAddress									RemoteAddress(CommandParamsIterator.GetParamAsInt32("NetworkInterfaceIndex"));
			bool												IsExtendedFrame=CommandParamsIterator.GetParamAsBool("IsExtendedFrame");
			bool												IsRemoteFrame=CommandParamsIterator.GetParamAsBool("IsRemoteFrame");
			bool												IsErrorFrame=CommandParamsIterator.GetParamAsBool("IsErrorFrame");
			CExpirationTime										WriteExpirationTime=CExpirationTime(CommandParamsIterator.GetParamAsInt64("WriteExpirationTime"));
			uint32												ID=CommandParamsIterator.GetParamAsUInt32("ID","",0,true);
			CSocketCANID										CANID(IsExtendedFrame,IsRemoteFrame,IsErrorFrame,ID);
			CByteBuffer											RawData(CommandParamsIterator.GetRemainingParamsAsByteBuffer("Data","",0,true));
			Size												Sum=0;

			for(Size Index=0;Index<RawData.GetLength();Index++)
			{
				Sum+=RawData[Index];
			}

			CSocketCANFrame										Frame(CANID,RawData);
			CSPByteBuffer										Data(new CByteBuffer(Frame.Serialize()));

			if (MSocketCollection.Contains(SocketName)==true)
			{
				for(Size Index=0;Index<NumberOfPackets;Index++)
				{
					CSPSocketCANManagerMessageRequestSocketWrite	Message(new CSocketCANManagerMessageRequestSocketWrite(CSocketID(SocketName),CCSPSocketCANManagerMessageContext(new CSocketCANManagerMessageContext(CSocketCANManagerMessageID())),RemoteAddress,Data,WriteExpirationTime));

					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("MESSAGE [",Message,"] is SENT to SOCKET MANAGER !")));

					MSocketManager->SendRequest(Message);

					MNumberOfBytesSent.Increment(Data->GetLength());
					MSumOfBytesSent.Increment(Sum);

					MNumberOfPacketsSends.Increment();
				}
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't SEND DATA to SOCKET !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerMenu::MenuItemGetNetworkInterfaceNameForDevice(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			int32												NetworkInterfaceIndex=CommandParamsIterator.GetParamAsInt32("NetworkInterfaceIndex");

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketCAN									Socket=MSocketCollection[SocketName];
				CString											NetworkInterfaceName=Socket->GetNetworkInterfaceName(NetworkInterfaceIndex);

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("NETWORK INTERFACE NAME [",NetworkInterfaceName,"] !")));
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't GET NETWORK INTERFACE NAME !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerMenu::MenuItemGetNetworkInterfaceIndexForDevice(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			CString												DeviceName=CommandParamsIterator.GetParamAsString();

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketCAN									Socket=MSocketCollection[SocketName];
				int32											NetworkInterfaceIndex=Socket->GetNetworkInterfaceIndex(DeviceName);

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("NETWORK INTERFACE INDEX [",NetworkInterfaceIndex,"] !")));
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't GET NETWORK INTERFACE INDEX !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerMenu::MenuItemExecuteCommand(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			Size												CommandNumber=CommandParamsIterator.GetParamAsSize("CommandNumber");

			// BIND to CAN with NETWORK ID 3.
			if (CommandNumber==1)
			{
				ExecuteCommand("b aaa 3");
			}
			// DATA FRAME RUN ALARM 0x01 to CAN with NETWORK ID 3.
			else if (CommandNumber==2)
			{
				ExecuteCommand("n aaa 3 1 0 0 1000 0x2000000 01");
			}
			// DATA FRAME STOP to CAN with NETWORK ID 3.
			else if (CommandNumber==3)
			{
				ExecuteCommand("n aaa 3 1 0 0 1000 0x2000000 00");
			}
			// REMOTE FRAME RUN ALARM to CAN with NETWORK ID 3.
			else if (CommandNumber==4)
			{
				ExecuteCommand("n aaa 3 1 1 0 1000 0x2000000");
			}
			// REMOTE FRAME STATUS to CAN with NETWORK ID 3.
			else if (CommandNumber==5)
			{
				ExecuteCommand("n aaa 3 1 1 0 1000 0x2800000");
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("COMMAND is NOT SUPPORTED !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't EXECUTE COMMAND !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerMenu::MenuItemStatistics(const CConsoleMenuItemCommandParams&)
	{
		CConsoleHelper::WriteLine("STATISTICS:");
		CConsoleHelper::WriteLine(CString::Format("\tSENDS [",MNumberOfPacketsSends.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tSEND SUCCESSES [",MNumberOfPacketsSendSuccesses.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tSEND FAILURES [",MNumberOfPacketsSendFailures.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tRECEIVES [",MNumberOfPacketsReceives.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tADDS [",MNumberOfSocketsAdds.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tADD SUCCESSES [",MNumberOfSocketsAddSuccesses.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tADD FAILURES [",MNumberOfSocketsAddFailures.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tREMOVES [",MNumberOfSocketsRemoves.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tREMOVE SUCCESSES [",MNumberOfSocketsRemoveSuccesses.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tREMOVE FAILURES [",MNumberOfSocketsRemoveFailures.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tCLOSES [",MNumberOfSocketsCloses.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tERRORS [",MNumberOfSocketsErrors.GetValue(),"] !"));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerMenu::MenuItemDataStatistics(const CConsoleMenuItemCommandParams&)
	{
		CConsoleHelper::WriteLine("DATA STATISTICS:");
		CConsoleHelper::WriteLine(CString::Format("\tSENT BYTES [",MNumberOfBytesSent.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tRECEIVED BYTES [",MNumberOfBytesReceived.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tSUM SENT [",MSumOfBytesSent.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tSUM RECEIVED [",MSumOfBytesReceived.GetValue(),"] !"));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketCANManagerMenu::GetStatus(void) const
	{
		CString													Status;

		Status="INITIALIZED: ";

		if (MIsLibraryInitialized==true)
		{
			Status+=CConsoleHelper::AddEscapeSequences("YES",EConsoleColor::E_LIGHT_GREEN,EConsoleColor::E_DEFAULT,false);
		}
		else
		{
			Status+=CConsoleHelper::AddEscapeSequences("NO",EConsoleColor::E_LIGHT_RED,EConsoleColor::E_DEFAULT,false);
		}

		Status+=", SOCKETS: ";
		Status+=CString(MSocketCollection.GetLength());
		Status+=", BATCHES: ";
		Status+=CString(GetNumberOfRunningBatches());

		return(Status);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------