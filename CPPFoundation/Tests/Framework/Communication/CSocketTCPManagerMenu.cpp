//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPManagerMenu.h"
//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
#include <Winsock2.h>
#elif defined(PLATFORM_LINUX)
#include <unistd.h>
#else
#error UNSUPPORTED PLATFORM !
#endif
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/Console/CConsoleHelper.h>
#include <Framework/Foundation/Console/CConsoleMenuItemCommandParamsIterator.h>
#include <Framework/Foundation/Communication/Networking/Sockets/CSocket.h>
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketLibrary.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPServerManagerMessageRequestSocketAdd.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPServerManagerMessageRequestSocketRemove.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPServerManagerMessageResponseSocketAccept.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPServerManagerMessageResponseSocketAdd.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPServerManagerMessageResponseSocketClose.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPServerManagerMessageResponseSocketError.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPServerManagerMessageResponseSocketRemove.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPClientManagerMessageRequestSocketAdd.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPClientManagerMessageRequestSocketConnect.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPClientManagerMessageRequestSocketRemove.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPClientManagerMessageRequestSocketShutdown.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPClientManagerMessageRequestSocketWrite.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPClientManagerMessageResponseSocketAdd.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPClientManagerMessageResponseSocketClosing.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPClientManagerMessageResponseSocketClosed.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPClientManagerMessageResponseSocketConnect.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPClientManagerMessageResponseSocketError.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPClientManagerMessageResponseSocketRead.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPClientManagerMessageResponseSocketRemove.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPClientManagerMessageResponseSocketShutdown.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPClientManagerMessageResponseSocketWrite.h>
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
	CSocketTCPManagerMenu::CSocketTCPManagerMenu(CConsoleLogWriter& LogWriter)
		: CConsoleMenu(LogWriter,"SOCKET MANAGER TCP"), MIsServerManagerInitialized(false), MIsClientManagerInitialized(false), MServerSocketCollection(), MClientSocketCollection(), MServerSocketManager(), MClientSocketManager(), MRandom(), MAcceptSocketCounter(0), MNumberOfPacketsSends(0), MNumberOfPacketsSendSuccesses(0), MNumberOfPacketsSendFailures(0), MNumberOfPacketsReceives(0), MNumberOfSocketsAccepts(0), MNumberOfSocketsConnects(0), MNumberOfSocketsConnectSuccesses(0), MNumberOfSocketsConnectFailures(0), MNumberOfSocketsShutdowns(0), MNumberOfSocketsShutdownSuccesses(0), MNumberOfSocketsShutdownFailures(0), MNumberOfSocketsServerAdds(0), MNumberOfSocketsServerAddSuccesses(0), MNumberOfSocketsServerAddFailures(0), MNumberOfSocketsServerRemoves(0), MNumberOfSocketsServerRemoveSuccesses(0), MNumberOfSocketsServerRemoveFailures(0), MNumberOfSocketsClientAdds(0), MNumberOfSocketsClientAddSuccesses(0), MNumberOfSocketsClientAddFailures(0), MNumberOfSocketsClientRemoves(0), MNumberOfSocketsClientRemoveSuccesses(0), MNumberOfSocketsClientRemoveFailures(0), MNumberOfSocketsServerCloses(0), MNumberOfSocketsServerErrors(0), MNumberOfSocketsClientClosings(0), MNumberOfSocketsClientCloses(0), MNumberOfSocketsClientErrors(0), MSocketStatistics()
	{
		AddMenuItem(CConsoleMenuItem("X","Exit","",EConsoleMenuItemType::E_ITEM_EXIT,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemExit)));
		AddMenuItem(CConsoleMenuItem("SQ","Server Initialize","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemInitializeServer)));
		AddMenuItem(CConsoleMenuItem("SA","Server Uninitialize","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemUninitializeServer)));
		AddMenuItem(CConsoleMenuItem("CQ","Client Initialize","[BufferSize]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemInitializeClient)));
		AddMenuItem(CConsoleMenuItem("CA","Client Uninitialize","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemUninitializeClient)));
		AddMenuItem(CConsoleMenuItem("SW","Start Server Socket Manager","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemStartSocketManagerServer)));
		AddMenuItem(CConsoleMenuItem("SS","Stop Server Socket Manager","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemStopSocketManagerServer)));
		AddMenuItem(CConsoleMenuItem("CW","Start Client Socket Manager","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemStartSocketManagerClient)));
		AddMenuItem(CConsoleMenuItem("CS","Stop Client Socket Manager","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemStopSocketManagerClient)));
		AddMenuItem(CConsoleMenuItem("E","Create Socket","[SocketName] [ServerSide]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemCreateSocket)));
		AddMenuItem(CConsoleMenuItem("D","Destroy Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemDestroySocket)));
		AddMenuItem(CConsoleMenuItem("B","Bind Socket","[SocketName] [IPEndpoint]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemBindSocket)));
		AddMenuItem(CConsoleMenuItem("T","Listen Socket","[SocketName] [MaximumNumberOfPendingConnections]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemListenSocket)));
		AddMenuItem(CConsoleMenuItem("AS","Add Server Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemAddSocket)));
		AddMenuItem(CConsoleMenuItem("RS","Remove Server Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemRemoveSocket)));
		AddMenuItem(CConsoleMenuItem("COM","Connect Socket Manually","[SocketName] [IPEndpoint]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemConnectSocketManually)));
		AddMenuItem(CConsoleMenuItem("CL","Close Socket Manually","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemCloseSocketManually)));
		AddMenuItem(CConsoleMenuItem("CO","Connect Socket","[SocketName] [IPEndpoint]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemConnectSocket)));
		AddMenuItem(CConsoleMenuItem("SH","Shutdown Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemShutdownSocket)));
		AddMenuItem(CConsoleMenuItem("N","Send Data to Socket","[SocketName] [WriteExpirationTime] [Byte1] ... [ByteN]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemSendToSocket)));
		AddMenuItem(CConsoleMenuItem("MN","Multi Send Data to Socket","[SocketName] [NumberOfPackets] [WriteExpirationTime] [Byte1] ... [ByteN]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemMultiSendToSocket)));
		AddMenuItem(CConsoleMenuItem("LN","Send Long Packet to Socket","[SocketName] [WriteExpirationTime] [PacketSize]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemSendLongPacketToSocket)));
		AddMenuItem(CConsoleMenuItem("LMN","Multi Send Long Packet to Socket","[SocketName] [NumberOfPackets] [WriteExpirationTime] [PacketSize]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemMultiSendLongPacketToSocket)));
		AddMenuItem(CConsoleMenuItem("F","Get Send Buffer Size","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemGetSendBufferSize)));
		AddMenuItem(CConsoleMenuItem("G","Set Send Buffer Size","[SocketName] [SendBufferSize]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemSetSendBufferSize)));
		AddMenuItem(CConsoleMenuItem("H","Get Receive Buffer Size","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemGetReceiveBufferSize)));
		AddMenuItem(CConsoleMenuItem("J","Set Receive Buffer Size","[SocketName] [ReceiveBufferSize]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemSetReceiveBufferSize)));
		AddMenuItem(CConsoleMenuItem("C","Execute Command","[CommandNumber]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemExecuteCommand)));
		AddMenuItem(CConsoleMenuItem("P","Statistics","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemStatistics)));
		AddMenuItem(CConsoleMenuItem("PP","Data Statistics","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPManagerMenu>(this,&CSocketTCPManagerMenu::MenuItemDataStatistics)));

		CSocketLibrary::Initialize();
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPManagerMenu::~CSocketTCPManagerMenu(void)
	{
		CSocketLibrary::Uninitialize();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPManagerMenu::ProcessMessageResponse(CCSPSocketTCPServerManagerMessageResponse MessageResponse)
	{
		if (MessageResponse.IsTypeOfAsConst<CSocketTCPServerManagerMessageResponseSocketAdd>()==true)
		{
			CCSPSocketTCPServerManagerMessageResponseSocketAdd	TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketTCPServerManagerMessageResponseSocketAdd>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			if (TypedMessageResponse->GetOperationSucceeded()==true)
			{
				MNumberOfSocketsServerAddSuccesses.Increment();
			}
			else
			{
				MNumberOfSocketsServerAddFailures.Increment();
			}
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketTCPServerManagerMessageResponseSocketRemove>()==true)
		{
			CCSPSocketTCPServerManagerMessageResponseSocketRemove	TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketTCPServerManagerMessageResponseSocketRemove>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			if (TypedMessageResponse->GetOperationSucceeded()==true)
			{
				MNumberOfSocketsServerRemoveSuccesses.Increment();
			}
			else
			{
				MNumberOfSocketsServerRemoveFailures.Increment();
			}
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketTCPServerManagerMessageResponseSocketAccept>()==true)
		{
			CCSPSocketTCPServerManagerMessageResponseSocketAccept	TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketTCPServerManagerMessageResponseSocketAccept>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			MNumberOfSocketsAccepts.Increment();

			CString												SocketID=CString::Format("C",MAcceptSocketCounter.Increment());
			CSPSocketTCPClient									Socket(new CSocketTCPClient(GetLogWriter(),SocketID,TypedMessageResponse->GetSocketTCPWrapper()));

			MClientSocketCollection.Add(Socket->GetSocketID().ToString(),Socket);
			MSocketStatistics.AddSocket(Socket->GetSocketID());

			CSPSocketTCPClientManagerMessageRequestSocketAdd	Message(new CSocketTCPClientManagerMessageRequestSocketAdd(CCSPSocketTCPClientManagerMessageContext(new CSocketTCPClientManagerMessageContext(CSocketTCPClientManagerMessageID())),Socket));

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("MESSAGE [",Message,"] is SENT to SOCKET MANAGER !")));

			MClientSocketManager->SendRequest(Message);

			MNumberOfSocketsClientAdds.Increment();
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketTCPServerManagerMessageResponseSocketClose>()==true)
		{
			CCSPSocketTCPServerManagerMessageResponseSocketClose	TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketTCPServerManagerMessageResponseSocketClose>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			MNumberOfSocketsServerCloses.Increment();
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketTCPServerManagerMessageResponseSocketError>()==true)
		{
			CCSPSocketTCPServerManagerMessageResponseSocketError	TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketTCPServerManagerMessageResponseSocketError>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			MNumberOfSocketsServerErrors.Increment();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPManagerMenu::ProcessMessageResponse(CCSPSocketTCPClientManagerMessageResponse MessageResponse)
	{
		if (MessageResponse.IsTypeOfAsConst<CSocketTCPClientManagerMessageResponseSocketAdd>()==true)
		{
			CCSPSocketTCPClientManagerMessageResponseSocketAdd	TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketTCPClientManagerMessageResponseSocketAdd>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			if (TypedMessageResponse->GetOperationSucceeded()==true)
			{
				MNumberOfSocketsClientAddSuccesses.Increment();
			}
			else
			{
				MNumberOfSocketsClientAddFailures.Increment();
			}
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketTCPClientManagerMessageResponseSocketRemove>()==true)
		{
			CCSPSocketTCPClientManagerMessageResponseSocketRemove	TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketTCPClientManagerMessageResponseSocketRemove>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			if (TypedMessageResponse->GetOperationSucceeded()==true)
			{
				MNumberOfSocketsClientRemoveSuccesses.Increment();
			}
			else
			{
				MNumberOfSocketsClientRemoveFailures.Increment();
			}
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketTCPClientManagerMessageResponseSocketConnect>()==true)
		{
			CCSPSocketTCPClientManagerMessageResponseSocketConnect	TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketTCPClientManagerMessageResponseSocketConnect>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			if (TypedMessageResponse->GetOperationSucceeded()==true)
			{
				MNumberOfSocketsConnectSuccesses.Increment();
			}
			else
			{
				MNumberOfSocketsConnectFailures.Increment();
			}
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketTCPClientManagerMessageResponseSocketShutdown>()==true)
		{
			CCSPSocketTCPClientManagerMessageResponseSocketShutdown	TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketTCPClientManagerMessageResponseSocketShutdown>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			if (TypedMessageResponse->GetOperationSucceeded()==true)
			{
				MNumberOfSocketsShutdownSuccesses.Increment();
			}
			else
			{
				MNumberOfSocketsShutdownFailures.Increment();
			}
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketTCPClientManagerMessageResponseSocketRead>()==true)
		{
			CCSPSocketTCPClientManagerMessageResponseSocketRead	TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketTCPClientManagerMessageResponseSocketRead>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			Size												Sum=0;

			for(Size Index=0;Index<TypedMessageResponse->GetData()->GetLength();Index++)
			{
				Sum+=(*TypedMessageResponse->GetData())[Index];
			}

			MSocketStatistics.AddSocketReceivedBytes(TypedMessageResponse->GetSocketID(),TypedMessageResponse->GetData()->GetLength(),Sum);
			MSocketStatistics.AddTotalReceivedBytes(TypedMessageResponse->GetData()->GetLength(),Sum);

			MNumberOfPacketsReceives.Increment();
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketTCPClientManagerMessageResponseSocketWrite>()==true)
		{
			CCSPSocketTCPClientManagerMessageResponseSocketWrite	TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketTCPClientManagerMessageResponseSocketWrite>();

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
		else if (MessageResponse.IsTypeOfAsConst<CSocketTCPClientManagerMessageResponseSocketClosing>()==true)
		{
			CCSPSocketTCPClientManagerMessageResponseSocketClosing	TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketTCPClientManagerMessageResponseSocketClosing>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			MNumberOfSocketsClientClosings.Increment();
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketTCPClientManagerMessageResponseSocketClosed>()==true)
		{
			CCSPSocketTCPClientManagerMessageResponseSocketClosed	TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketTCPClientManagerMessageResponseSocketClosed>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			MNumberOfSocketsClientCloses.Increment();
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketTCPClientManagerMessageResponseSocketError>()==true)
		{
			CCSPSocketTCPClientManagerMessageResponseSocketError	TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketTCPClientManagerMessageResponseSocketError>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			MNumberOfSocketsClientErrors.Increment();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPManagerMenu::MenuItemExit(const CConsoleMenuItemCommandParams&)
	{
		// EMPTY.
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPManagerMenu::MenuItemInitializeServer(const CConsoleMenuItemCommandParams&)
	{
		try
		{
			MServerSocketManager=CSPSocketTCPServerManager(new CSocketTCPServerManager(GetLogWriter()));

			MIsServerManagerInitialized=true;

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SERVER SOCKET MANAGER is INITIALIZED !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("INITIALIZATION FAILED !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPManagerMenu::MenuItemUninitializeServer(const CConsoleMenuItemCommandParams&)
	{
		try
		{
			MServerSocketManager=nullptr;

			MIsServerManagerInitialized=false;

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SERVER SOCKET MANAGER is UNINITIALIZED !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't UNINITIALIZE SERVER MANAGER !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPManagerMenu::MenuItemInitializeClient(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			Size												BufferSize=CommandParamsIterator.GetParamAsSize("BufferSize");

			MClientSocketManager=CSPSocketTCPClientManager(new CSocketTCPClientManager(GetLogWriter(),BufferSize));

			MIsClientManagerInitialized=true;

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CLIENT SOCKET MANAGER is INITIALIZED !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("INITIALIZATION FAILED !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPManagerMenu::MenuItemUninitializeClient(const CConsoleMenuItemCommandParams&)
	{
		try
		{
			MClientSocketManager=nullptr;

			MIsClientManagerInitialized=false;

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CLIENT SOCKET MANAGER is UNINITIALIZED !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't UNINITIALIZE CLIENT MANAGER !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPManagerMenu::MenuItemStartSocketManagerServer(const CConsoleMenuItemCommandParams&)
	{
		try
		{
			MServerSocketManager->AddEvent(CEventID("EVENT"),*this);

			MServerSocketManager->StartThread();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SERVER SOCKET MANAGER is STARTED !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't START SERVER SOCKET MANAGER !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPManagerMenu::MenuItemStopSocketManagerServer(const CConsoleMenuItemCommandParams&)
	{
		try
		{
			MServerSocketManager->StopThread();

			MServerSocketManager->RemoveEvent(CEventID("EVENT"));

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SERVER SOCKET MANAGER is STOPPED !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't STOP SERVER SOCKET MANAGER !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPManagerMenu::MenuItemStartSocketManagerClient(const CConsoleMenuItemCommandParams&)
	{
		try
		{
			MClientSocketManager->AddEvent(CEventID("EVENT"),*this);

			MClientSocketManager->StartThread();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CLIENT SOCKET MANAGER is STARTED !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't START CLIENT SOCKET MANAGER !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPManagerMenu::MenuItemStopSocketManagerClient(const CConsoleMenuItemCommandParams&)
	{
		try
		{
			MClientSocketManager->StopThread();

			MClientSocketManager->RemoveEvent(CEventID("EVENT"));

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CLIENT SOCKET MANAGER is STOPPED !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't STOP CLIENT SOCKET MANAGER !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPManagerMenu::MenuItemCreateSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			bool												ServerSide=CommandParamsIterator.GetParamAsBool("ServerSide");

			if (MServerSocketCollection.Contains(SocketName)==false && MClientSocketCollection.Contains(SocketName)==false)
			{
				if (ServerSide==true)
				{
					CSPSocketTCPServer							Socket(new CSocketTCPServer(GetLogWriter(),SocketName));

					MServerSocketCollection.Add(SocketName,Socket);

					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",SocketName,"] is CREATED !")));
				}
				else
				{
					CSPSocketTCPClient							Socket(new CSocketTCPClient(GetLogWriter(),SocketName));

					MClientSocketCollection.Add(SocketName,Socket);
					MSocketStatistics.AddSocket(SocketName);

					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",SocketName,"] is CREATED !")));
				}
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
	void CSocketTCPManagerMenu::MenuItemDestroySocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MServerSocketCollection.Contains(SocketName)==true)
			{
				MServerSocketCollection.Erase(SocketName);

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET [",SocketName,"] is DESTROYED !")));
			}
			else if (MClientSocketCollection.Contains(SocketName)==true)
			{
				MClientSocketCollection.Erase(SocketName);
				MSocketStatistics.RemoveSocket(SocketName);

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
	void CSocketTCPManagerMenu::MenuItemBindSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			CSocketTCPAddress									IPEndpoint=CSocketTCPAddress(CommandParamsIterator.GetParamAsIPv4Endpoint("IPEndpoint"));
			
			if (MServerSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPServer								Socket=MServerSocketCollection[SocketName].DynamicCast<CSocketTCPServer>();

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
	void CSocketTCPManagerMenu::MenuItemListenSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			Size												MaximumNumberOfPendingConnections=CommandParamsIterator.GetParamAsSize("MaximumNumberOfPendingConnections");
			
			if (MServerSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPServer								Socket=MServerSocketCollection[SocketName].DynamicCast<CSocketTCPServer>();

				Socket->Listen(MaximumNumberOfPendingConnections);
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't LISTEN for SOCKET !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPManagerMenu::MenuItemAddSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MServerSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPServer								Socket=MServerSocketCollection[SocketName];
				CSPSocketTCPServerManagerMessageRequestSocketAdd	Message(new CSocketTCPServerManagerMessageRequestSocketAdd(CCSPSocketTCPServerManagerMessageContext(new CSocketTCPServerManagerMessageContext(CSocketTCPServerManagerMessageID())),Socket));

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("MESSAGE [",Message,"] is SENT to SOCKET MANAGER !")));

				MServerSocketManager->SendRequest(Message);

				MNumberOfSocketsServerAdds.Increment();
			}
			else if (MClientSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClient								Socket=MClientSocketCollection[SocketName];
				CSPSocketTCPClientManagerMessageRequestSocketAdd	Message(new CSocketTCPClientManagerMessageRequestSocketAdd(CCSPSocketTCPClientManagerMessageContext(new CSocketTCPClientManagerMessageContext(CSocketTCPClientManagerMessageID())),Socket));

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("MESSAGE [",Message,"] is SENT to SOCKET MANAGER !")));

				MClientSocketManager->SendRequest(Message);

				MNumberOfSocketsClientAdds.Increment();
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't ADD SOCKET to SERVER SOCKET MANAGER !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPManagerMenu::MenuItemRemoveSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MServerSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPServer								Socket=MServerSocketCollection[SocketName];
				CSPSocketTCPServerManagerMessageRequestSocketRemove	Message(new CSocketTCPServerManagerMessageRequestSocketRemove(CSocketID(SocketName),CCSPSocketTCPServerManagerMessageContext(new CSocketTCPServerManagerMessageContext(CSocketTCPServerManagerMessageID()))));

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("MESSAGE [",Message,"] is SENT to SOCKET MANAGER !")));

				MServerSocketManager->SendRequest(Message);

				MNumberOfSocketsServerRemoves.Increment();
			}
			else if (MClientSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClient								Socket=MClientSocketCollection[SocketName];
				CSPSocketTCPClientManagerMessageRequestSocketRemove	Message(new CSocketTCPClientManagerMessageRequestSocketRemove(CSocketID(SocketName),CCSPSocketTCPClientManagerMessageContext(new CSocketTCPClientManagerMessageContext(CSocketTCPClientManagerMessageID()))));

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("MESSAGE [",Message,"] is SENT to SOCKET MANAGER !")));

				MClientSocketManager->SendRequest(Message);

				MNumberOfSocketsClientRemoves.Increment();
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't REMOVE SOCKET from SERVER SOCKET MANAGER !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPManagerMenu::MenuItemConnectSocketManually(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			CSocketTCPAddress									IPEndpoint=CommandParamsIterator.GetParamAsIPv4Endpoint("IPEndpoint");

			if (MClientSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClient								Socket=MClientSocketCollection[SocketName];

				MNumberOfSocketsConnects.Increment();

				if (Socket->ConnectToAddress(IPEndpoint)==true)
				{
					MNumberOfSocketsConnectSuccesses.Increment();
				}
				else
				{
					MNumberOfSocketsConnectFailures.Increment();
				}
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't CONNECT SOCKET !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPManagerMenu::MenuItemCloseSocketManually(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MClientSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClient								Socket=MClientSocketCollection[SocketName];
				int32											SocketHandler=Socket->GetSocketHandler();

				// For TESTING PURPOSES METHOD DELIBERATELY CLOSES SOCKET in NON-STANDARD WAY by closing its DESCRIPTOR.
#if defined(PLATFORM_WINDOWS)
				closesocket(SOCKET(SocketHandler));
#elif defined(PLATFORM_LINUX)
				close(int(SocketHandler));
#else
#error UNSUPPORTED PLATFORM !
#endif
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't CONNECT SOCKET !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPManagerMenu::MenuItemConnectSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			CSocketTCPAddress									IPEndpoint=CommandParamsIterator.GetParamAsIPv4Endpoint("IPEndpoint");
			
			if (MClientSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClient								Socket=MClientSocketCollection[SocketName];
				CSPSocketTCPClientManagerMessageRequestSocketConnect	Message(new CSocketTCPClientManagerMessageRequestSocketConnect(CCSPSocketTCPClientManagerMessageContext(new CSocketTCPClientManagerMessageContext(CSocketTCPClientManagerMessageID())),Socket,IPEndpoint));

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("MESSAGE [",Message,"] is SENT to SOCKET MANAGER !")));

				MClientSocketManager->SendRequest(Message);

				MNumberOfSocketsConnects.Increment();
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't CONNECT SOCKET !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPManagerMenu::MenuItemShutdownSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MClientSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClientManagerMessageRequestSocketShutdown	Message(new CSocketTCPClientManagerMessageRequestSocketShutdown(CSocketID(SocketName),CCSPSocketTCPClientManagerMessageContext(new CSocketTCPClientManagerMessageContext(CSocketTCPClientManagerMessageID()))));

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("MESSAGE [",Message,"] is SENT to SOCKET MANAGER !")));

				MClientSocketManager->SendRequest(Message);

				MNumberOfSocketsShutdowns.Increment();
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't SHUTDOWN SOCKET !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPManagerMenu::MenuItemSendToSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			CExpirationTime										WriteExpirationTime=CExpirationTime(CommandParamsIterator.GetParamAsInt64("WriteExpirationTime"));
			CSPByteBuffer										Data=CSPByteBuffer(new CByteBuffer(CommandParamsIterator.GetRemainingParamsAsByteBuffer("Data","",0,true)));
			Size												Sum=0;

			for(Size Index=0;Index<Data->GetLength();Index++)
			{
				Sum+=(*Data)[Index];
			}

			if (MClientSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClientManagerMessageRequestSocketWrite	Message(new CSocketTCPClientManagerMessageRequestSocketWrite(CSocketID(SocketName),CCSPSocketTCPClientManagerMessageContext(new CSocketTCPClientManagerMessageContext(CSocketTCPClientManagerMessageID())),Data,WriteExpirationTime));

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("MESSAGE [",Message,"] is SENT to SOCKET MANAGER !")));

				MClientSocketManager->SendRequest(Message);

				MNumberOfPacketsSends.Increment();

				MSocketStatistics.AddSocketSentBytes(SocketName,Data->GetLength(),Sum);
				MSocketStatistics.AddTotalSentBytes(Data->GetLength(),Sum);
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
	void CSocketTCPManagerMenu::MenuItemMultiSendToSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(3);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			Size												NumberOfPackets=CommandParamsIterator.GetParamAsSize("NumberOfPackets");
			CExpirationTime										WriteExpirationTime=CExpirationTime(CommandParamsIterator.GetParamAsInt64("WriteExpirationTime"));
			CSPByteBuffer										Data=CSPByteBuffer(new CByteBuffer(CommandParamsIterator.GetRemainingParamsAsByteBuffer("Data","",0,true)));
			Size												Sum=0;

			for(Size Index=0;Index<Data->GetLength();Index++)
			{
				Sum+=(*Data)[Index];
			}

			if (MClientSocketCollection.Contains(SocketName)==true)
			{
				for(Size Index=0;Index<NumberOfPackets;Index++)
				{
					CSPSocketTCPClientManagerMessageRequestSocketWrite	Message(new CSocketTCPClientManagerMessageRequestSocketWrite(CSocketID(SocketName),CCSPSocketTCPClientManagerMessageContext(new CSocketTCPClientManagerMessageContext(CSocketTCPClientManagerMessageID())),Data,WriteExpirationTime));

					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("MESSAGE [",Message,"] is SENT to SOCKET MANAGER !")));

					MClientSocketManager->SendRequest(Message);

					MNumberOfPacketsSends.Increment();

					MSocketStatistics.AddSocketSentBytes(SocketName,Data->GetLength(),Sum);
					MSocketStatistics.AddTotalSentBytes(Data->GetLength(),Sum);
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
	void CSocketTCPManagerMenu::MenuItemSendLongPacketToSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(3);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			CExpirationTime										WriteExpirationTime=CExpirationTime(CommandParamsIterator.GetParamAsInt64("WriteExpirationTime"));
			Size												PacketSize=CommandParamsIterator.GetParamAsSize("PacketSize");
			CSPByteBuffer										Data=CSPByteBuffer(new CByteBuffer(PacketSize));
			Size												Sum=0;

			for(Size Index=0;Index<PacketSize;Index++)
			{
				Sum+=(*Data)[Index]=uint8(Index % (CUInt8::Max()+1));
			}

			if (MClientSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClientManagerMessageRequestSocketWrite	Message(new CSocketTCPClientManagerMessageRequestSocketWrite(CSocketID(SocketName),CCSPSocketTCPClientManagerMessageContext(new CSocketTCPClientManagerMessageContext(CSocketTCPClientManagerMessageID())),Data,WriteExpirationTime));

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("MESSAGE [",Message,"] is SENT to SOCKET MANAGER !")));

				MClientSocketManager->SendRequest(Message);

				MNumberOfPacketsSends.Increment();

				MSocketStatistics.AddSocketSentBytes(SocketName,Data->GetLength(),Sum);
				MSocketStatistics.AddTotalSentBytes(Data->GetLength(),Sum);
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
	void CSocketTCPManagerMenu::MenuItemMultiSendLongPacketToSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(4);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			Size												NumberOfPackets=CommandParamsIterator.GetParamAsSize("NumberOfPackets");
			CExpirationTime										WriteExpirationTime=CExpirationTime(CommandParamsIterator.GetParamAsInt64("WriteExpirationTime"));
			Size												PacketSize=CommandParamsIterator.GetParamAsSize("PacketSize");
			CSPByteBuffer										Data=CSPByteBuffer(new CByteBuffer(PacketSize));
			Size												Sum=0;

			for(Size Index=0;Index<PacketSize;Index++)
			{
				Sum+=(*Data)[Index]=uint8(Index % (CUInt8::Max()+1));
			}

			if (MClientSocketCollection.Contains(SocketName)==true)
			{
				for(Size Index=0;Index<NumberOfPackets;Index++)
				{
					CSPSocketTCPClientManagerMessageRequestSocketWrite	Message(new CSocketTCPClientManagerMessageRequestSocketWrite(CSocketID(SocketName),CCSPSocketTCPClientManagerMessageContext(new CSocketTCPClientManagerMessageContext(CSocketTCPClientManagerMessageID())),Data,WriteExpirationTime));

					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("MESSAGE [",Message,"] is SENT to SOCKET MANAGER !")));

					MClientSocketManager->SendRequest(Message);

					MNumberOfPacketsSends.Increment();

					MSocketStatistics.AddSocketSentBytes(SocketName,Data->GetLength(),Sum);
					MSocketStatistics.AddTotalSentBytes(Data->GetLength(),Sum);
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
	void CSocketTCPManagerMenu::MenuItemGetSendBufferSize(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			
			if (MClientSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClient								Socket=MClientSocketCollection[SocketName].DynamicCast<CSocketTCPClient>();
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
	void CSocketTCPManagerMenu::MenuItemSetSendBufferSize(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			int32												SendBufferSize(CommandParamsIterator.GetParamAsInt32("SendBufferSize"));
			
			if (MClientSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClient								Socket=MClientSocketCollection[SocketName].DynamicCast<CSocketTCPClient>();
				
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
	void CSocketTCPManagerMenu::MenuItemGetReceiveBufferSize(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			
			if (MClientSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClient								Socket=MClientSocketCollection[SocketName].DynamicCast<CSocketTCPClient>();
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
	void CSocketTCPManagerMenu::MenuItemSetReceiveBufferSize(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			int32												ReceiveBufferSize(CommandParamsIterator.GetParamAsInt32("ReceiveBufferSize"));
			
			if (MClientSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClient								Socket=MClientSocketCollection[SocketName].DynamicCast<CSocketTCPClient>();
				
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
	void CSocketTCPManagerMenu::MenuItemExecuteCommand(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			Size												CommandNumber=CommandParamsIterator.GetParamAsSize("CommandNumber");

			if (CommandNumber==1)
			{
				ExecuteCommand("sq");
				ExecuteCommand("cq 2000");
				ExecuteCommand("sw");
				ExecuteCommand("cw");
			}
			else if (CommandNumber==2)
			{
				ExecuteCommand("sq");
				ExecuteCommand("cq 2000");
				ExecuteCommand("sw");
				ExecuteCommand("cw");

				ExecuteCommand("e aaa 1");
				ExecuteCommand("e bbb 0");
				ExecuteCommand("e ccc 0");

				ExecuteCommand("b aaa 0.0.0.0:10000");
				ExecuteCommand("t aaa 5");
				ExecuteCommand("as aaa");
			}
			else if (CommandNumber==3)
			{
				ExecuteCommand("sq");
				ExecuteCommand("cq 2000");
				ExecuteCommand("sw");
				ExecuteCommand("cw");

				ExecuteCommand("e aaa 1");
				ExecuteCommand("e bbb 0");
				ExecuteCommand("e ccc 0");

				ExecuteCommand("b aaa 0.0.0.0:11000");
				ExecuteCommand("t aaa 5");
				ExecuteCommand("as aaa");
			}
			else if (CommandNumber==4)
			{
				ExecuteCommand("sq");
				ExecuteCommand("cq 2000");
				ExecuteCommand("sw");
				ExecuteCommand("cw");

				ExecuteCommand("e aaa 1");
				ExecuteCommand("e bbb 0");
				ExecuteCommand("e ccc 0");

				ExecuteCommand("b aaa 0.0.0.0:10000");
				ExecuteCommand("t aaa 5");
				ExecuteCommand("as aaa");

				CThread::Sleep(100);

				ExecuteCommand("co bbb 127.0.0.1:10000");

				CThread::Sleep(100);

				ExecuteCommand("co ccc 127.0.0.1:10000");

				CThread::Sleep(100);

				ExecuteCommand("g bbb 1000");
				ExecuteCommand("j bbb 1000");
				ExecuteCommand("g C1 1000");
				ExecuteCommand("j C1 1000");

				ExecuteCommand("g ccc 1000");
				ExecuteCommand("j ccc 1000");
				ExecuteCommand("g C2 1000");
				ExecuteCommand("j C2 1000");
			}
			else if (CommandNumber==5)
			{
				ExecuteCommand("LMN bbb 10 999999999 1000000");
				ExecuteCommand("LMN ccc 10 999999999 1000000");
				ExecuteCommand("LMN C1 10 999999999 1000000");
				ExecuteCommand("LMN C2 10 999999999 1000000");
			}
			else if (CommandNumber==6)
			{
				ExecuteCommand("sq");
				ExecuteCommand("cq 2000");
				ExecuteCommand("sw");
				ExecuteCommand("cw");

				ExecuteCommand("e aaa 1");
				ExecuteCommand("e bbb 1");
				ExecuteCommand("e ccc 0");
				ExecuteCommand("e ddd 0");

				ExecuteCommand("b aaa 0.0.0.0:10000");
				ExecuteCommand("t aaa 5");
				ExecuteCommand("as aaa");

				ExecuteCommand("b bbb 0.0.0.0:11000");
				ExecuteCommand("t bbb 5");
				ExecuteCommand("as bbb");

				CThread::Sleep(100);

				ExecuteCommand("co ccc 127.0.0.1:10000");

				CThread::Sleep(100);

				ExecuteCommand("co ddd 127.0.0.1:11000");

				CThread::Sleep(100);

				ExecuteCommand("g ccc 1000");
				ExecuteCommand("j ccc 1000");
				ExecuteCommand("g C1 1000");
				ExecuteCommand("j C1 1000");

				ExecuteCommand("g ddd 1000");
				ExecuteCommand("j ddd 1000");
				ExecuteCommand("g C2 1000");
				ExecuteCommand("j C2 1000");
			}
			else if (CommandNumber==7)
			{
				ExecuteCommand("LMN ccc 10 999999999 1000000");
				ExecuteCommand("LMN ddd 10 999999999 1000000");
				ExecuteCommand("LMN C1 10 999999999 1000000");
				ExecuteCommand("LMN C2 10 999999999 1000000");
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
	void CSocketTCPManagerMenu::MenuItemStatistics(const CConsoleMenuItemCommandParams&)
	{
		CConsoleHelper::WriteLine("STATISTICS:");
		CConsoleHelper::WriteLine(CString::Format("\tSENDS [",MNumberOfPacketsSends.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tSEND SUCCESSES [",MNumberOfPacketsSendSuccesses.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tSEND FAILURES [",MNumberOfPacketsSendFailures.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tRECEIVES [",MNumberOfPacketsReceives.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tACCEPTS [",MNumberOfSocketsAccepts.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tCONNECTS [",MNumberOfSocketsConnects.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tCONNECT SUCCESSES [",MNumberOfSocketsConnectSuccesses.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tCONNECT FAILURES [",MNumberOfSocketsConnectFailures.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tSHUTDOWNS [",MNumberOfSocketsShutdowns.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tSHUTDOWN SUCCESSES [",MNumberOfSocketsShutdownSuccesses.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tSHUTDOWN FAILURES [",MNumberOfSocketsShutdownFailures.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tSERVER ADDS [",MNumberOfSocketsServerAdds.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tSERVER ADD SUCCESSES [",MNumberOfSocketsServerAddSuccesses.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tSERVER ADD FAILURES [",MNumberOfSocketsServerAddFailures.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tSERVER REMOVES [",MNumberOfSocketsServerRemoves.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tSERVER REMOVE SUCCESSES [",MNumberOfSocketsServerRemoveSuccesses.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tSERVER REMOVE FAILURES [",MNumberOfSocketsServerRemoveFailures.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tCLIENT ADDS [",MNumberOfSocketsClientAdds.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tCLIENT ADD SUCCESSES [",MNumberOfSocketsClientAddSuccesses.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tCLIENT ADD FAILURES [",MNumberOfSocketsClientAddFailures.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tCLIENT REMOVES [",MNumberOfSocketsClientRemoves.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tCLIENT REMOVE SUCCESSES [",MNumberOfSocketsClientRemoveSuccesses.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tCLIENT REMOVE FAILURES [",MNumberOfSocketsClientRemoveFailures.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tSERVER CLOSES [",MNumberOfSocketsServerCloses.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tSERVER ERRORS [",MNumberOfSocketsServerErrors.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tCLIENT CLOSINGS [",MNumberOfSocketsClientClosings.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tCLIENT CLOSES [",MNumberOfSocketsClientCloses.GetValue(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tCLIENT ERRORS [",MNumberOfSocketsClientErrors.GetValue(),"] !"));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPManagerMenu::MenuItemDataStatistics(const CConsoleMenuItemCommandParams&)
	{
		CConsoleHelper::WriteLine("DATA STATISTICS:");
		CConsoleHelper::WriteLine(CString::Format("\tTOTAL SENT BYTES [",MSocketStatistics.GetTotalNumberOfBytesSent(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tTOTAL RECEIVED BYTES [",MSocketStatistics.GetTotalNumberOfBytesReceived(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tTOTAL SUM SENT [",MSocketStatistics.GetTotalSumOfBytesSent(),"] !"));
		CConsoleHelper::WriteLine(CString::Format("\tTOTAL SUM RECEIVED [",MSocketStatistics.GetTotalSumOfBytesReceived(),"] !"));
		CConsoleHelper::WriteLine();

		for(const CClientSocketCollection::CKeyValuePair& Pair : MClientSocketCollection)
		{
			CConsoleHelper::WriteLine(CString::Format("\tSOCKET [",Pair.GetFirst(),"]\tSENT BYTES [",MSocketStatistics.GetSocketNumberOfBytesSent(Pair.GetFirst()),"] !"));
			CConsoleHelper::WriteLine(CString::Format("\tSOCKET [",Pair.GetFirst(),"]\tRECEIVED BYTES [",MSocketStatistics.GetSocketNumberOfBytesReceived(Pair.GetFirst()),"] !"));
			CConsoleHelper::WriteLine(CString::Format("\tSOCKET [",Pair.GetFirst(),"]\tSUM SENT [",MSocketStatistics.GetSocketSumOfBytesSent(Pair.GetFirst()),"] !"));
			CConsoleHelper::WriteLine(CString::Format("\tSOCKET [",Pair.GetFirst(),"]\tSUM RECEIVED [",MSocketStatistics.GetSocketSumOfBytesReceived(Pair.GetFirst()),"] !"));
			CConsoleHelper::WriteLine();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPManagerMenu::GetStatus(void) const
	{
		CString													Status;

		Status="SERVER STARTED: ";

		if (MIsServerManagerInitialized==true)
		{
			Status+=CConsoleHelper::AddEscapeSequences("YES",EConsoleColor::E_LIGHT_GREEN,EConsoleColor::E_DEFAULT,false);
		}
		else
		{
			Status+=CConsoleHelper::AddEscapeSequences("NO",EConsoleColor::E_LIGHT_RED,EConsoleColor::E_DEFAULT,false);
		}

		Status+=", CLIENT STARTED: ";

		if (MIsClientManagerInitialized==true)
		{
			Status+=CConsoleHelper::AddEscapeSequences("YES",EConsoleColor::E_LIGHT_GREEN,EConsoleColor::E_DEFAULT,false);
		}
		else
		{
			Status+=CConsoleHelper::AddEscapeSequences("NO",EConsoleColor::E_LIGHT_RED,EConsoleColor::E_DEFAULT,false);
		}

		Status+=", SERVER SOCKETS: ";
		Status+=CString(MServerSocketCollection.GetLength());

		Status+=", CLIENT SOCKETS: ";
		Status+=CString(MClientSocketCollection.GetLength());

		return(Status);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------