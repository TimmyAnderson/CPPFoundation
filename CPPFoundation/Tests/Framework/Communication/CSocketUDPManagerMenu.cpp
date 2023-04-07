//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPManagerMenu.h"
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/Console/CConsoleHelper.h>
#include <Framework/Foundation/Console/CConsoleMenuItemCommandParamsIterator.h>
#include <Framework/Foundation/Communication/Networking/Sockets/CSocket.h>
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketLibrary.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Manager/CSocketUDPManagerMessageRequestSocketAdd.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Manager/CSocketUDPManagerMessageRequestSocketRemove.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Manager/CSocketUDPManagerMessageRequestSocketWrite.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Manager/CSocketUDPManagerMessageResponseSocketAdd.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Manager/CSocketUDPManagerMessageResponseSocketClose.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Manager/CSocketUDPManagerMessageResponseSocketError.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Manager/CSocketUDPManagerMessageResponseSocketRead.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Manager/CSocketUDPManagerMessageResponseSocketRemove.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Manager/CSocketUDPManagerMessageResponseSocketWrite.h>
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
	CSocketUDPManagerMenu::CSocketUDPManagerMenu(CConsoleLogWriter& LogWriter)
		: CConsoleMenu(LogWriter,"SOCKET MANAGER UDP"), MIsLibraryInitialized(false), MSocketCollection(), MSocketManager(), MRandom(), MNumberOfPacketsSends(0), MNumberOfPacketsSendSuccesses(0), MNumberOfPacketsSendFailures(0), MNumberOfPacketsReceives(0), MNumberOfSocketsAdds(0), MNumberOfSocketsAddSuccesses(0), MNumberOfSocketsAddFailures(0), MNumberOfSocketsRemoves(0), MNumberOfSocketsRemoveSuccesses(0), MNumberOfSocketsRemoveFailures(0), MNumberOfSocketsCloses(0), MNumberOfSocketsErrors(0), MNumberOfBytesSent(0), MNumberOfBytesReceived(0), MSumOfBytesSent(0), MSumOfBytesReceived(0)
	{
		AddMenuItem(CConsoleMenuItem("X","Exit","",EConsoleMenuItemType::E_ITEM_EXIT,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemExit)));
		AddMenuItem(CConsoleMenuItem("Q","Initialize","[BufferSize]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemInitialize)));
		AddMenuItem(CConsoleMenuItem("A","Uninitialize","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemUninitialize)));
		AddMenuItem(CConsoleMenuItem("W","Start Socket Manager","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemStartSocketManager)));
		AddMenuItem(CConsoleMenuItem("S","Stop Socket Manager","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemStopSocketManager)));
		AddMenuItem(CConsoleMenuItem("R","Register Event","[EventID]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemRegisterEvent)));
		AddMenuItem(CConsoleMenuItem("U","Unregister Event","[EventID]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemUnregisterEvent)));
		AddMenuItem(CConsoleMenuItem("E","Create Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemCreateSocket)));
		AddMenuItem(CConsoleMenuItem("D","Destroy Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemDestroySocket)));
		AddMenuItem(CConsoleMenuItem("B","Bind Socket","[SocketName] [IPEndpoint]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemBindSocket)));
		AddMenuItem(CConsoleMenuItem("AS","Add Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemAddSocket)));
		AddMenuItem(CConsoleMenuItem("RS","Remove Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemRemoveSocket)));
		AddMenuItem(CConsoleMenuItem("N","Send Data to Socket","[SocketName] [RemoteIPEndpoint] [WriteExpirationTime] [Byte1] ... [ByteN]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemSendToSocket)));
		AddMenuItem(CConsoleMenuItem("MN","Multi Send Data to Socket","[SocketName] [NumberOfPackets] [RemoteIPEndpoint] [WriteExpirationTime] [Byte1] ... [ByteN]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemMultiSendToSocket)));
		AddMenuItem(CConsoleMenuItem("LN","Send Long Packet to Socket","[SocketName] [RemoteIPEndpoint] [WriteExpirationTime] [PacketSize]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemSendLongPacketToSocket)));
		AddMenuItem(CConsoleMenuItem("LMN","Multi Send Long Packet to Socket","[SocketName] [NumberOfPackets] [RemoteIPEndpoint] [WriteExpirationTime] [PacketSize]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemMultiSendLongPacketToSocket)));
		AddMenuItem(CConsoleMenuItem("F","Get Send Buffer Size","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemGetSendBufferSize)));
		AddMenuItem(CConsoleMenuItem("G","Set Send Buffer Size","[SocketName] [SendBufferSize]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemSetSendBufferSize)));
		AddMenuItem(CConsoleMenuItem("H","Get Receive Buffer Size","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemGetReceiveBufferSize)));
		AddMenuItem(CConsoleMenuItem("J","Set Receive Buffer Size","[SocketName] [ReceiveBufferSize]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemSetReceiveBufferSize)));
		AddMenuItem(CConsoleMenuItem("C","Execute Command","[CommandNumber]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemExecuteCommand)));
		AddMenuItem(CConsoleMenuItem("P","Statistics","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemStatistics)));
		AddMenuItem(CConsoleMenuItem("PP","Data Statistics","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPManagerMenu>(this,&CSocketUDPManagerMenu::MenuItemDataStatistics)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMenu::~CSocketUDPManagerMenu(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerMenu::ProcessMessageResponse(CCSPSocketUDPManagerMessageResponse MessageResponse)
	{
		if (MessageResponse.IsTypeOfAsConst<CSocketUDPManagerMessageResponseSocketAdd>()==true)
		{
			CCSPSocketUDPManagerMessageResponseSocketAdd		TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketUDPManagerMessageResponseSocketAdd>();

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
		else if (MessageResponse.IsTypeOfAsConst<CSocketUDPManagerMessageResponseSocketRemove>()==true)
		{
			CCSPSocketUDPManagerMessageResponseSocketRemove		TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketUDPManagerMessageResponseSocketRemove>();

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
		else if (MessageResponse.IsTypeOfAsConst<CSocketUDPManagerMessageResponseSocketRead>()==true)
		{
			CCSPSocketUDPManagerMessageResponseSocketRead		TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketUDPManagerMessageResponseSocketRead>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			Size												Sum=0;

			for(Size Index=0;Index<TypedMessageResponse->GetData()->GetLength();Index++)
			{
				Sum+=(*TypedMessageResponse->GetData())[Index];
			}

			MNumberOfBytesReceived.Increment(TypedMessageResponse->GetData()->GetLength());
			MSumOfBytesReceived.Increment(Sum);

			MNumberOfPacketsReceives.Increment();
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketUDPManagerMessageResponseSocketWrite>()==true)
		{
			CCSPSocketUDPManagerMessageResponseSocketWrite		TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketUDPManagerMessageResponseSocketWrite>();

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
		else if (MessageResponse.IsTypeOfAsConst<CSocketUDPManagerMessageResponseSocketClose>()==true)
		{
			CCSPSocketUDPManagerMessageResponseSocketClose		TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketUDPManagerMessageResponseSocketClose>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			MNumberOfSocketsCloses.Increment();
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketUDPManagerMessageResponseSocketError>()==true)
		{
			CCSPSocketUDPManagerMessageResponseSocketError		TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketUDPManagerMessageResponseSocketError>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			MNumberOfSocketsErrors.Increment();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerMenu::MenuItemExit(const CConsoleMenuItemCommandParams&)
	{
		// EMPTY.
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerMenu::MenuItemInitialize(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			Size												BufferSize=CommandParamsIterator.GetParamAsSize("BufferSize");

			CSocketLibrary::Initialize();

			MSocketManager=CSPSocketUDPManager(new CSocketUDPManager(GetLogWriter(),BufferSize));

			MIsLibraryInitialized=true;

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET LIBRARY is INITIALIZED !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("INITIALIZATION FAILED !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerMenu::MenuItemUninitialize(const CConsoleMenuItemCommandParams&)
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
	void CSocketUDPManagerMenu::MenuItemStartSocketManager(const CConsoleMenuItemCommandParams&)
	{
		try
		{
			MSocketManager->StartThread();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET MANAGER is STARTED !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't START SOCKET MANAGER !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerMenu::MenuItemStopSocketManager(const CConsoleMenuItemCommandParams&)
	{
		try
		{
			MSocketManager->StopThread();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET MANAGER is STOPPED !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't STOP SOCKET MANAGER !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerMenu::MenuItemRegisterEvent(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CEventID											EventID=CommandParamsIterator.GetParamAsString();

			MSocketManager->AddEvent(EventID,*this);

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("EVENT [",EventID,"] is REGISTERED !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't REGISTER EVENT !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerMenu::MenuItemUnregisterEvent(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CEventID											EventID=CommandParamsIterator.GetParamAsString();

			MSocketManager->RemoveEvent(EventID);

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("EVENT [",EventID,"] is UNREGISTERED !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't UNREGISTER EVENT !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerMenu::MenuItemCreateSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MSocketCollection.Contains(SocketName)==false)
			{
				CSPSocketUDP									Socket(new CSocketUDP(GetLogWriter(),SocketName));

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
	void CSocketUDPManagerMenu::MenuItemDestroySocket(const CConsoleMenuItemCommandParams& CommandParams)
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
	void CSocketUDPManagerMenu::MenuItemBindSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			CSocketUDPAddress									IPEndpoint=CommandParamsIterator.GetParamAsIPv4Endpoint("IPEndpoint");

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketUDP									Socket=MSocketCollection[SocketName];

				Socket->BindToAddress(IPEndpoint);
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
	void CSocketUDPManagerMenu::MenuItemAddSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketUDP									Socket=MSocketCollection[SocketName];
				CSPSocketUDPManagerMessageRequestSocketAdd		Message(new CSocketUDPManagerMessageRequestSocketAdd(CCSPSocketUDPManagerMessageContext(new CSocketUDPManagerMessageContext(CSocketUDPManagerMessageID())),Socket));

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
	void CSocketUDPManagerMenu::MenuItemRemoveSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketUDP									Socket=MSocketCollection[SocketName];
				CSPSocketUDPManagerMessageRequestSocketRemove	Message(new CSocketUDPManagerMessageRequestSocketRemove(CSocketID(SocketName),CCSPSocketUDPManagerMessageContext(new CSocketUDPManagerMessageContext(CSocketUDPManagerMessageID()))));

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
	void CSocketUDPManagerMenu::MenuItemSendToSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(3);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			CSocketUDPAddress									RemoteIPEndpoint=CommandParamsIterator.GetParamAsIPv4Endpoint("RemoteIPEndpoint");
			CExpirationTime										WriteExpirationTime=CExpirationTime(CommandParamsIterator.GetParamAsInt64("WriteExpirationTime"));
			CSPByteBuffer										Data=CSPByteBuffer(new CByteBuffer(CommandParamsIterator.GetRemainingParamsAsByteBuffer("Data","",0,true)));
			Size												Sum=0;

			for(Size Index=0;Index<Data->GetLength();Index++)
			{
				Sum+=(*Data)[Index];
			}

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketUDPManagerMessageRequestSocketWrite	Message(new CSocketUDPManagerMessageRequestSocketWrite(CSocketID(SocketName),CCSPSocketUDPManagerMessageContext(new CSocketUDPManagerMessageContext(CSocketUDPManagerMessageID())),RemoteIPEndpoint,Data,WriteExpirationTime));

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
	void CSocketUDPManagerMenu::MenuItemMultiSendToSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(4);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			Size												NumberOfPackets=CommandParamsIterator.GetParamAsSize("NumberOfPackets");
			CSocketUDPAddress									RemoteIPEndpoint=CommandParamsIterator.GetParamAsIPv4Endpoint("RemoteIPEndpoint");
			CExpirationTime										WriteExpirationTime=CExpirationTime(CommandParamsIterator.GetParamAsInt64("WriteExpirationTime"));
			CSPByteBuffer										Data=CSPByteBuffer(new CByteBuffer(CommandParamsIterator.GetRemainingParamsAsByteBuffer("Data","",0,true)));
			Size												Sum=0;

			for(Size Index=0;Index<Data->GetLength();Index++)
			{
				Sum+=(*Data)[Index];
			}

			if (MSocketCollection.Contains(SocketName)==true)
			{
				for(Size Index=0;Index<NumberOfPackets;Index++)
				{
					CSPSocketUDPManagerMessageRequestSocketWrite	Message(new CSocketUDPManagerMessageRequestSocketWrite(CSocketID(SocketName),CCSPSocketUDPManagerMessageContext(new CSocketUDPManagerMessageContext(CSocketUDPManagerMessageID())),RemoteIPEndpoint,Data,WriteExpirationTime));

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
	void CSocketUDPManagerMenu::MenuItemSendLongPacketToSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(4);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			CSocketUDPAddress									RemoteIPEndpoint=CommandParamsIterator.GetParamAsIPv4Endpoint("RemoteIPEndpoint");
			CExpirationTime										WriteExpirationTime=CExpirationTime(CommandParamsIterator.GetParamAsInt64("WriteExpirationTime"));
			Size												PacketSize=CommandParamsIterator.GetParamAsSize("PacketSize");
			CSPByteBuffer										Data=CSPByteBuffer(new CByteBuffer(PacketSize));
			Size												Sum=0;

			for(Size Index=0;Index<PacketSize;Index++)
			{
				Sum+=(*Data)[Index]=uint8(Index % (static_cast<Size>(CUInt8::Max())+1));
			}

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketUDPManagerMessageRequestSocketWrite	Message(new CSocketUDPManagerMessageRequestSocketWrite(CSocketID(SocketName),CCSPSocketUDPManagerMessageContext(new CSocketUDPManagerMessageContext(CSocketUDPManagerMessageID())),RemoteIPEndpoint,Data,WriteExpirationTime));

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("MESSAGE [",Message,"] is SENT to SOCKET MANAGER !")));

				MSocketManager->SendRequest(Message);

				MNumberOfBytesSent.Increment(PacketSize);
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
	void CSocketUDPManagerMenu::MenuItemMultiSendLongPacketToSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(5);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			Size												NumberOfPackets=CommandParamsIterator.GetParamAsSize("NumberOfPackets");
			CSocketUDPAddress									RemoteIPEndpoint=CommandParamsIterator.GetParamAsIPv4Endpoint("RemoteIPEndpoint");
			CExpirationTime										WriteExpirationTime=CExpirationTime(CommandParamsIterator.GetParamAsInt64("WriteExpirationTime"));
			Size												PacketSize=CommandParamsIterator.GetParamAsSize("PacketSize");
			CSPByteBuffer										Data=CSPByteBuffer(new CByteBuffer(PacketSize));
			Size												Sum=0;

			for(Size Index=0;Index<PacketSize;Index++)
			{
				Sum+=(*Data)[Index]=uint8(Index % (static_cast<Size>(CUInt8::Max())+1));
			}

			if (MSocketCollection.Contains(SocketName)==true)
			{
				for(Size Index=0;Index<NumberOfPackets;Index++)
				{
					CSPSocketUDPManagerMessageRequestSocketWrite	Message(new CSocketUDPManagerMessageRequestSocketWrite(CSocketID(SocketName),CCSPSocketUDPManagerMessageContext(new CSocketUDPManagerMessageContext(CSocketUDPManagerMessageID())),RemoteIPEndpoint,Data,WriteExpirationTime));

					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("MESSAGE [",Message,"] is SENT to SOCKET MANAGER !")));

					MSocketManager->SendRequest(Message);

					MNumberOfBytesSent.Increment(PacketSize);
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
	void CSocketUDPManagerMenu::MenuItemGetSendBufferSize(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			
			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketUDP									Socket=MSocketCollection[SocketName].DynamicCast<CSocketUDP>();
				int32											SendBufferSize=Socket->GetSendBufferSize();

				CConsoleHelper::WriteLine(CString::Format("SOCKET [",SocketName,"] SEND BUFFER SIZE [",SendBufferSize,"] !"));
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't GET SEND BUFFER SIZE !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerMenu::MenuItemSetSendBufferSize(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			int32												SendBufferSize(CommandParamsIterator.GetParamAsInt32("SendBufferSize"));
			
			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketUDP									Socket=MSocketCollection[SocketName].DynamicCast<CSocketUDP>();
				
				Socket->SetSendBufferSize(SendBufferSize);

				CConsoleHelper::WriteLine(CString::Format("SOCKET [",SocketName,"] SET SEND BUFFER SIZE !"));
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't SET SEND BUFFER SIZE !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerMenu::MenuItemGetReceiveBufferSize(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			
			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketUDP									Socket=MSocketCollection[SocketName].DynamicCast<CSocketUDP>();
				int32											ReceiveBufferSize=Socket->GetReceiveBufferSize();

				CConsoleHelper::WriteLine(CString::Format("SOCKET [",SocketName,"] RECEIVE BUFFER SIZE [",ReceiveBufferSize,"] !"));
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't GET RECEIVE BUFFER SIZE !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerMenu::MenuItemSetReceiveBufferSize(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			int32												ReceiveBufferSize(CommandParamsIterator.GetParamAsInt32("ReceiveBufferSize"));
			
			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketUDP									Socket=MSocketCollection[SocketName].DynamicCast<CSocketUDP>();
				
				Socket->SetReceiveBufferSize(ReceiveBufferSize);

				CConsoleHelper::WriteLine(CString::Format("SOCKET [",SocketName,"] SET RECEIVE BUFFER SIZE !"));
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't SET RECEIVE BUFFER SIZE !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerMenu::MenuItemExecuteCommand(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			Size												CommandNumber=CommandParamsIterator.GetParamAsSize("CommandNumber");

			if (CommandNumber==1)
			{
				ExecuteCommand("b aaa 0.0.0.0:10000");
			}
			else if (CommandNumber==2)
			{
				ExecuteCommand("n aaa 127.0.0.1:10000 1000 1 2 3 4 5");
			}
			else if (CommandNumber==3)
			{
				ExecuteCommand("mn aaa 1000 127.0.0.1:20000 1000000 1 2 3 4 5");
			}
			else if (CommandNumber==4)
			{
				ExecuteCommand("q 2000");
				ExecuteCommand("w");
				ExecuteCommand("r EVENT");
				ExecuteCommand("e aaa");
				ExecuteCommand("e bbb");
				ExecuteCommand("b aaa 0.0.0.0:10000");
				ExecuteCommand("b bbb 0.0.0.0:20000");

				CThread::Sleep(100);

				ExecuteCommand("as aaa");
				ExecuteCommand("as bbb");
			}
			else if (CommandNumber==5)
			{
				CommandParamsIterator.CheckNumberOfParams(1);

				Size											BufferSize(CommandParamsIterator.GetParamAsSize("BufferSize"));

				ExecuteCommand(CString::Format("q ",BufferSize));
				ExecuteCommand("w");
				ExecuteCommand("r EVENT");
				ExecuteCommand("e aaa");
				ExecuteCommand("e bbb");
				ExecuteCommand("b aaa 0.0.0.0:10000");
				ExecuteCommand("b bbb 0.0.0.0:20000");

				CThread::Sleep(100);

				ExecuteCommand("as aaa");
				ExecuteCommand("as bbb");
			}
			else if (CommandNumber==6)
			{
				ExecuteCommand("q 2000");
				ExecuteCommand("w");
				ExecuteCommand("r EVENT");
				ExecuteCommand("e aaa");
				ExecuteCommand("e bbb");
				ExecuteCommand("e ccc");
				ExecuteCommand("e ddd");
				ExecuteCommand("b aaa 0.0.0.0:10000");
				ExecuteCommand("b bbb 0.0.0.0:20000");
				ExecuteCommand("b ccc 0.0.0.0:30000");
				ExecuteCommand("b ddd 0.0.0.0:40000");

				CThread::Sleep(100);

				ExecuteCommand("as aaa");
				ExecuteCommand("as bbb");
				ExecuteCommand("as ccc");
				ExecuteCommand("as ddd");
			}
			else if (CommandNumber==7)
			{
				CommandParamsIterator.CheckNumberOfParams(1);

				Size											NumberOfIterations(CommandParamsIterator.GetParamAsSize("NumberOfIterations"));

				for(Size Index=0;Index<NumberOfIterations;Index++)
				{
					ExecuteCommand("n aaa 127.0.0.1:20000 1000000000 1 2 3 4 5");
					ExecuteCommand("n aaa 127.0.0.1:30000 1000000000 2 3 4 5 6 7");
					ExecuteCommand("n aaa 127.0.0.1:40000 1000000000 8 9 10");

					ExecuteCommand("n bbb 127.0.0.1:10000 1000000000 11 12 13 14");
					ExecuteCommand("n bbb 127.0.0.1:30000 1000000000 15 16 17 18");
					ExecuteCommand("n bbb 127.0.0.1:40000 1000000000 19 20");

					ExecuteCommand("n ccc 127.0.0.1:10000 1000000000 21 22");
					ExecuteCommand("n ccc 127.0.0.1:20000 1000000000 23 24");
					ExecuteCommand("n ccc 127.0.0.1:40000 1000000000 25 26 27 28 29 30");

					ExecuteCommand("n ddd 127.0.0.1:10000 1000000000 1 2 3 4 5");
					ExecuteCommand("n ddd 127.0.0.1:20000 1000000000 1 2 3 4 5");
					ExecuteCommand("n ddd 127.0.0.1:30000 1000000000 1 2 3 4 5");
				}
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
	void CSocketUDPManagerMenu::MenuItemStatistics(const CConsoleMenuItemCommandParams&)
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
	void CSocketUDPManagerMenu::MenuItemDataStatistics(const CConsoleMenuItemCommandParams&)
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
	CString CSocketUDPManagerMenu::GetStatus(void) const
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

		return(Status);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------