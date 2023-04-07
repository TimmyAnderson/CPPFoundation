//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPResponseManagerMenu.h"
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
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Manager/CSocketUDPManagerMessageResponseSocketRemove.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Manager/CSocketUDPManagerMessageResponseSocketWrite.h>
#include <Framework/Foundation/Parsing/CParserHelper.h>
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
	CSocketUDPResponseManagerMenu::CSocketUDPResponseManagerMenu(CConsoleLogWriter& LogWriter)
		: CConsoleMenu(LogWriter,"SOCKET"), MIsLibraryInitialized(false), MSocketCollection(), MSocketManager(), MSocketUDPResponseManager(), MResponseConditionCollection()
	{
		AddMenuItem(CConsoleMenuItem("X","Exit","",EConsoleMenuItemType::E_ITEM_EXIT,CConsoleMenuItemCallbackMethod<CSocketUDPResponseManagerMenu>(this,&CSocketUDPResponseManagerMenu::MenuItemExit)));
		AddMenuItem(CConsoleMenuItem("Q","Initialize","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPResponseManagerMenu>(this,&CSocketUDPResponseManagerMenu::MenuItemInitialize)));
		AddMenuItem(CConsoleMenuItem("A","Uninitialize","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPResponseManagerMenu>(this,&CSocketUDPResponseManagerMenu::MenuItemUninitialize)));
		AddMenuItem(CConsoleMenuItem("W","Start Socket Manager","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPResponseManagerMenu>(this,&CSocketUDPResponseManagerMenu::MenuItemStartSocketManager)));
		AddMenuItem(CConsoleMenuItem("S","Stop Socket Manager","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPResponseManagerMenu>(this,&CSocketUDPResponseManagerMenu::MenuItemStopSocketManager)));
		AddMenuItem(CConsoleMenuItem("E","Start Response Manager","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPResponseManagerMenu>(this,&CSocketUDPResponseManagerMenu::MenuItemStartResponseManager)));
		AddMenuItem(CConsoleMenuItem("D","Stop Response Manager","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPResponseManagerMenu>(this,&CSocketUDPResponseManagerMenu::MenuItemStopResponseManager)));
		AddMenuItem(CConsoleMenuItem("R","Create Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPResponseManagerMenu>(this,&CSocketUDPResponseManagerMenu::MenuItemCreateSocket)));
		AddMenuItem(CConsoleMenuItem("F","Destroy Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPResponseManagerMenu>(this,&CSocketUDPResponseManagerMenu::MenuItemDestroySocket)));
		AddMenuItem(CConsoleMenuItem("B","Bind Socket","[SocketName] [IPEndpoint]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPResponseManagerMenu>(this,&CSocketUDPResponseManagerMenu::MenuItemBindSocket)));
		AddMenuItem(CConsoleMenuItem("AS","Add Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPResponseManagerMenu>(this,&CSocketUDPResponseManagerMenu::MenuItemAddSocket)));
		AddMenuItem(CConsoleMenuItem("RS","Remove Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPResponseManagerMenu>(this,&CSocketUDPResponseManagerMenu::MenuItemRemoveSocket)));
		AddMenuItem(CConsoleMenuItem("N","Send Data to Socket","[SocketName] [RemoteIPEndpoint] [WriteExpirationTime] [Byte1] ... [ByteN]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPResponseManagerMenu>(this,&CSocketUDPResponseManagerMenu::MenuItemSendToSocket)));
		AddMenuItem(CConsoleMenuItem("C","Execute Command","[CommandNumber]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPResponseManagerMenu>(this,&CSocketUDPResponseManagerMenu::MenuItemExecuteCommand)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPResponseManagerMenu::~CSocketUDPResponseManagerMenu(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPResponseManagerMenu::CheckForResponse(CCSPSocketUDPManagerMessageResponseSocketRead MessageResponse)
	{
		for(CSPSocketUDPResponseCondition ResponseCondition : MResponseConditionCollection)
		{
			if (ResponseCondition->CheckCondition(MessageResponse->GetSocketID(),MessageResponse->GetSourceAddress(),MessageResponse->GetData())==true)
			{
				CSPSocketUDPResponse							NewResponse;

				if (ResponseCondition->GetUseReceivedSocketAddress()==false)
				{
					// DEEP COPY MUST be CREATED.
					NewResponse=CSPSocketUDPResponse(new CSocketUDPResponse(MessageResponse->GetData(),ResponseCondition->GetResponse()->CreateResponseItemCollection()));
				}
				else
				{
					// DEEP COPY MUST be CREATED.
					NewResponse=CSPSocketUDPResponse(new CSocketUDPResponse(MessageResponse->GetData(),ResponseCondition->GetResponse()->CreateResponseItemCollection(MessageResponse->GetSourceAddress())));
				}

				MSocketUDPResponseManager->SendResponse(NewResponse);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPResponseManagerMenu::ProcessMessageResponse(CCSPSocketUDPManagerMessageResponse MessageResponse)
	{
		if (MessageResponse.IsTypeOfAsConst<CSocketUDPManagerMessageResponseSocketAdd>()==true)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketUDPManagerMessageResponseSocketRemove>()==true)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketUDPManagerMessageResponseSocketRead>()==true)
		{
			CCSPSocketUDPManagerMessageResponseSocketRead		TypedMessageResponse=MessageResponse.DynamicCastAsConst<CSocketUDPManagerMessageResponseSocketRead>();

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));

			CheckForResponse(TypedMessageResponse);
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketUDPManagerMessageResponseSocketWrite>()==true)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketUDPManagerMessageResponseSocketClose>()==true)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));
		}
		else if (MessageResponse.IsTypeOfAsConst<CSocketUDPManagerMessageResponseSocketError>()==true)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("!!!!! RESPONSE MESSAGE [",MessageResponse.ToString(),"] ! !!!!!")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPResponseManagerMenu::MenuItemExit(const CConsoleMenuItemCommandParams&)
	{
		// EMPTY.
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPResponseManagerMenu::MenuItemInitialize(const CConsoleMenuItemCommandParams&)
	{
		try
		{
			CSocketLibrary::Initialize();

			MSocketManager=CSPSocketUDPManager(new CSocketUDPManager(GetLogWriter(),2000));

			MIsLibraryInitialized=true;

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET LIBRARY is INITIALIZED !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("INITIALIZATION FAILED !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPResponseManagerMenu::MenuItemUninitialize(const CConsoleMenuItemCommandParams&)
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
	void CSocketUDPResponseManagerMenu::MenuItemStartSocketManager(const CConsoleMenuItemCommandParams&)
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
	void CSocketUDPResponseManagerMenu::MenuItemStopSocketManager(const CConsoleMenuItemCommandParams&)
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
	void CSocketUDPResponseManagerMenu::MenuItemStartResponseManager(const CConsoleMenuItemCommandParams&)
	{
		try
		{
			if (MSocketUDPResponseManager==nullptr)
			{
				MSocketUDPResponseManager=CSPSocketUDPResponseManager(new CSocketUDPResponseManager(GetLogWriter(),MSocketManager));

				MSocketUDPResponseManager->StartThread();

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET RESPONSE MANAGER STARTED !")));
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET RESPONSE MANAGER is ALREADY STARTED !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't CREATE SOCKET !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPResponseManagerMenu::MenuItemStopResponseManager(const CConsoleMenuItemCommandParams&)
	{
		try
		{
			if (MSocketUDPResponseManager!=nullptr)
			{
				MSocketUDPResponseManager->StopThread();

				MSocketUDPResponseManager=nullptr;

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET RESPONSE MANAGER STOPPED !")));
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET RESPONSE MANAGER is NOT STARTED !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't DESTROY SOCKET !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPResponseManagerMenu::MenuItemCreateSocket(const CConsoleMenuItemCommandParams& CommandParams)
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
	void CSocketUDPResponseManagerMenu::MenuItemDestroySocket(const CConsoleMenuItemCommandParams& CommandParams)
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
	void CSocketUDPResponseManagerMenu::MenuItemBindSocket(const CConsoleMenuItemCommandParams& CommandParams)
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
	void CSocketUDPResponseManagerMenu::MenuItemAddSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketUDP									Socket=MSocketCollection[SocketName];
				CSPSocketUDPManagerMessageRequestSocketAdd		Message(new CSocketUDPManagerMessageRequestSocketAdd(CCSPSocketUDPManagerMessageContext(new  CSocketUDPManagerMessageContext(CSocketUDPManagerMessageID())),Socket));

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("MESSAGE [",Message,"] is SENT to SOCKET MANAGER !")));

				MSocketManager->SendRequest(Message);
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
	void CSocketUDPResponseManagerMenu::MenuItemRemoveSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketUDP									Socket=MSocketCollection[SocketName];
				CSPSocketUDPManagerMessageRequestSocketRemove	Message(new CSocketUDPManagerMessageRequestSocketRemove(CSocketID(SocketName),CCSPSocketUDPManagerMessageContext(new  CSocketUDPManagerMessageContext(CSocketUDPManagerMessageID()))));

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("MESSAGE [",Message,"] is SENT to SOCKET MANAGER !")));

				MSocketManager->SendRequest(Message);
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
	void CSocketUDPResponseManagerMenu::MenuItemSendToSocket(const CConsoleMenuItemCommandParams& CommandParams)
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
				CSPSocketUDPManagerMessageRequestSocketWrite	Message(new CSocketUDPManagerMessageRequestSocketWrite(CSocketID(SocketName),CCSPSocketUDPManagerMessageContext(new  CSocketUDPManagerMessageContext(CSocketUDPManagerMessageID())),RemoteIPEndpoint,Data,WriteExpirationTime));

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("MESSAGE [",Message,"] is SENT to SOCKET MANAGER !")));

				MSocketManager->SendRequest(Message);
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
	void CSocketUDPResponseManagerMenu::MenuItemExecuteCommand(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			Size												CommandNumber=CommandParamsIterator.GetParamAsSize("CommandNumber");

			if (CommandNumber==1)
			{
				ExecuteCommand("q");
				ExecuteCommand("w");
				ExecuteCommand("e");
			}
			else if (CommandNumber==2)
			{
				ExecuteCommand("q");
				ExecuteCommand("w");
				ExecuteCommand("e");

				ExecuteCommand("r aaa");
				ExecuteCommand("r bbb");

				ExecuteCommand("b aaa 127.0.0.1:11000");
				ExecuteCommand("b bbb 127.0.0.1:12000");

				ExecuteCommand("as aaa");
				ExecuteCommand("as bbb");
			}
			else if (CommandNumber==3)
			{
				ExecuteCommand("q");
				ExecuteCommand("w");
				ExecuteCommand("e");

				ExecuteCommand("r aaa");
				ExecuteCommand("r bbb");
				ExecuteCommand("r ccc");
				ExecuteCommand("r ddd");

				ExecuteCommand("b aaa 127.0.0.1:15001");
				ExecuteCommand("b bbb 127.0.0.1:15002");
				ExecuteCommand("b ccc 127.0.0.1:15003");
				ExecuteCommand("b ddd 127.0.0.1:15010");

				ExecuteCommand("as aaa");
				ExecuteCommand("as bbb");
				ExecuteCommand("as ccc");
				ExecuteCommand("as ddd");
			}
			else if (CommandNumber==4)
			{
				ExecuteCommand("q");
				ExecuteCommand("w");
				ExecuteCommand("e");

				ExecuteCommand("r aaa");

				ExecuteCommand("b aaa 127.0.0.1:10002");

				ExecuteCommand("as aaa");
			}
			else if (CommandNumber==5)
			{
				ExecuteCommand("q");
				ExecuteCommand("w");
				ExecuteCommand("e");

				ExecuteCommand("r aaa");
				ExecuteCommand("r bbb");
				ExecuteCommand("r ccc");
				ExecuteCommand("r ddd");
				ExecuteCommand("r eee");
				ExecuteCommand("r fff");
				ExecuteCommand("r ggg");
				ExecuteCommand("r hhh");
				ExecuteCommand("r iii");
				ExecuteCommand("r jjj");
				ExecuteCommand("r kkk");
				ExecuteCommand("r lll");

				ExecuteCommand("b aaa 127.0.0.1:10011");
				ExecuteCommand("b bbb 127.0.0.1:10012");
				ExecuteCommand("b ccc 127.0.0.1:10021");
				ExecuteCommand("b ddd 127.0.0.1:10022");
				ExecuteCommand("b eee 127.0.0.1:10031");
				ExecuteCommand("b fff 127.0.0.1:10032");
				ExecuteCommand("b ggg 127.0.0.1:10041");
				ExecuteCommand("b hhh 127.0.0.1:10042");
				ExecuteCommand("b iii 127.0.0.1:10111");
				ExecuteCommand("b jjj 127.0.0.1:10112");
				ExecuteCommand("b kkk 127.0.0.1:10121");
				ExecuteCommand("b lll 127.0.0.1:10122");

				ExecuteCommand("as aaa");
				ExecuteCommand("as bbb");
				ExecuteCommand("as ccc");
				ExecuteCommand("as ddd");
				ExecuteCommand("as eee");
				ExecuteCommand("as fff");
				ExecuteCommand("as ggg");
				ExecuteCommand("as hhh");
				ExecuteCommand("as iii");
				ExecuteCommand("as jjj");
				ExecuteCommand("as kkk");
				ExecuteCommand("as lll");
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketUDPResponseManagerMenu::GetStatus(void) const
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