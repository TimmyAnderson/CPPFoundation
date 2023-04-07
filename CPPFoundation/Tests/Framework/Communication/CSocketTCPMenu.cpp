//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPMenu.h"
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/Console/CConsoleHelper.h>
#include <Framework/Foundation/Console/CConsoleMenuItemCommandParamsIterator.h>
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketLibrary.h>
#include <Framework/Foundation/Communication/Networking/Sockets/ISocketWaitObject.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPReceiveParameters.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPReceiveResult.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPSendParameters.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPSendResult.h>
#include <Framework/Platform/Sockets/CSocketWaitObject.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Foundation;
	using namespace CPPFoundation::Platform;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPMenu::CSocketTCPMenu(CConsoleLogWriter& LogWriter)
		: CConsoleMenu(LogWriter,"SOCKET TCP"), MIsLibraryInitialized(false), MSocketServerCollection(), MSocketClientCollection()
	{
		AddMenuItem(CConsoleMenuItem("X","Exit","",EConsoleMenuItemType::E_ITEM_EXIT,CConsoleMenuItemCallbackMethod<CSocketTCPMenu>(this,&CSocketTCPMenu::MenuItemExit)));
		AddMenuItem(CConsoleMenuItem("Q","Initialize","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPMenu>(this,&CSocketTCPMenu::MenuItemInitialize)));
		AddMenuItem(CConsoleMenuItem("A","Uninitialize","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPMenu>(this,&CSocketTCPMenu::MenuItemUninitialize)));
		AddMenuItem(CConsoleMenuItem("W","Create Socket","[SocketName] [ServerSide]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPMenu>(this,&CSocketTCPMenu::MenuItemCreateSocket)));
		AddMenuItem(CConsoleMenuItem("S","Destroy Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPMenu>(this,&CSocketTCPMenu::MenuItemDestroySocket)));
		AddMenuItem(CConsoleMenuItem("B","Bind Socket","[SocketName] [IPEndpoint]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPMenu>(this,&CSocketTCPMenu::MenuItemBindSocket)));
		AddMenuItem(CConsoleMenuItem("C","Connect to Socket","[SocketName] [IPEndpoint]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPMenu>(this,&CSocketTCPMenu::MenuItemConnectToSocket)));
		AddMenuItem(CConsoleMenuItem("U","Shutdown Socket","[SocketName] [ShutdownFlags]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPMenu>(this,&CSocketTCPMenu::MenuItemShutdownSocket)));
		AddMenuItem(CConsoleMenuItem("T","Listen Socket","[SocketName] [MaximumNumberOfPendingConnections]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPMenu>(this,&CSocketTCPMenu::MenuItemListenSocket)));
		AddMenuItem(CConsoleMenuItem("Y","Accept Socket","[SocketName] [ClientSocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPMenu>(this,&CSocketTCPMenu::MenuItemAcceptSocket)));
		AddMenuItem(CConsoleMenuItem("N","Send Data to Socket","[SocketName] [Byte1] ... [ByteN]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPMenu>(this,&CSocketTCPMenu::MenuItemSendSocket)));
		AddMenuItem(CConsoleMenuItem("M","Receive Data from Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPMenu>(this,&CSocketTCPMenu::MenuItemReceiveSocket)));
		AddMenuItem(CConsoleMenuItem("NB","Send Data to Socket","[SocketName] [BufferOffset] [NumberOfBytesToSend] [Byte1] ... [ByteN]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPMenu>(this,&CSocketTCPMenu::MenuItemSendSocketCustomBuffer)));
		AddMenuItem(CConsoleMenuItem("MB","Receive Data from Socket","[SocketName] [BufferOffset] [NumberOfBytesToReceive]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPMenu>(this,&CSocketTCPMenu::MenuItemReceiveSocketCustomBuffer)));
		AddMenuItem(CConsoleMenuItem("L","Wait for Event","[TimeoutInMS] [WaitForWriteEvent] [SocketName1] ... [SocketNameN]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPMenu>(this,&CSocketTCPMenu::MenuItemWaitForEvent)));
		AddMenuItem(CConsoleMenuItem("F","Get Send Buffer Size","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPMenu>(this,&CSocketTCPMenu::MenuItemGetSendBufferSize)));
		AddMenuItem(CConsoleMenuItem("G","Set Send Buffer Size","[SocketName] [SendBufferSize]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPMenu>(this,&CSocketTCPMenu::MenuItemSetSendBufferSize)));
		AddMenuItem(CConsoleMenuItem("H","Get Receive Buffer Size","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPMenu>(this,&CSocketTCPMenu::MenuItemGetReceiveBufferSize)));
		AddMenuItem(CConsoleMenuItem("J","Set Receive Buffer Size","[SocketName] [ReceiveBufferSize]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPMenu>(this,&CSocketTCPMenu::MenuItemSetReceiveBufferSize)));
		AddMenuItem(CConsoleMenuItem("CC","Execute Command","[CommandNumber]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketTCPMenu>(this,&CSocketTCPMenu::MenuItemExecuteCommand)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPMenu::~CSocketTCPMenu(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPMenu::MenuItemExit(const CConsoleMenuItemCommandParams&)
	{
		// EMPTY.
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPMenu::MenuItemInitialize(const CConsoleMenuItemCommandParams&)
	{
		try
		{
			CSocketLibrary::Initialize();

			MIsLibraryInitialized=true;
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't INITIALIZE LIBRARY !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPMenu::MenuItemUninitialize(const CConsoleMenuItemCommandParams&)
	{
		try
		{
			CSocketLibrary::Uninitialize();

			MIsLibraryInitialized=false;
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't UNINITIALIZE LIBRARY !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPMenu::MenuItemCreateSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			bool												ServerSide=CommandParamsIterator.GetParamAsBool("ServerSide");

			if (MSocketServerCollection.Contains(SocketName)==false && MSocketClientCollection.Contains(SocketName)==false)
			{
				if (ServerSide==true)
				{
					CSPSocketTCPServer							SocketSharedPointer(new CSocketTCPServer(GetLogWriter(),SocketName));

					MSocketServerCollection.Add(SocketName,SocketSharedPointer);
				}
				else
				{
					CSPSocketTCPClient							SocketSharedPointer(new CSocketTCPClient(GetLogWriter(),SocketName));

					MSocketClientCollection.Add(SocketName,SocketSharedPointer);
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
	void CSocketTCPMenu::MenuItemDestroySocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MSocketServerCollection.Contains(SocketName)==true)
			{
				MSocketServerCollection.Erase(SocketName);
			}
			else if (MSocketClientCollection.Contains(SocketName)==true)
			{
				MSocketClientCollection.Erase(SocketName);
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
	void CSocketTCPMenu::MenuItemBindSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			CSocketTCPAddress									IPEndpoint=CSocketTCPAddress(CommandParamsIterator.GetParamAsIPv4Endpoint("IPEndpoint"));
			
			if (MSocketServerCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPServer								Socket=MSocketServerCollection[SocketName].DynamicCast<CSocketTCPServer>();

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
	void CSocketTCPMenu::MenuItemConnectToSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			CSocketTCPAddress									IPEndpoint=CSocketTCPAddress(CommandParamsIterator.GetParamAsIPv4Endpoint("IPEndpoint"));
			
			if (MSocketClientCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClient								Socket=MSocketClientCollection[SocketName].DynamicCast<CSocketTCPClient>();

				Socket->ConnectToAddress(IPEndpoint);
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't CONNECT TO SOCKET !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPMenu::MenuItemShutdownSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			ESocketTCPShutdownFlags								ShutdownFlags=ESocketTCPShutdownFlags(CommandParamsIterator.GetParamAsUInt8("ShutdownFlags","",0,false,1,3));
			
			if (MSocketClientCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClient								Socket=MSocketClientCollection[SocketName].DynamicCast<CSocketTCPClient>();

				Socket->Shutdown(ShutdownFlags);
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
	void CSocketTCPMenu::MenuItemListenSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			Size												MaximumNumberOfPendingConnections=CommandParamsIterator.GetParamAsSize("MaximumNumberOfPendingConnections");
			
			if (MSocketServerCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPServer								Socket=MSocketServerCollection[SocketName].DynamicCast<CSocketTCPServer>();

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
	void CSocketTCPMenu::MenuItemAcceptSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			CString												ClientSocketName=CommandParamsIterator.GetParamAsString();
			CSocketID											SocketID=ClientSocketName;
			
			if (MSocketServerCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPServer								Socket=MSocketServerCollection[SocketName].DynamicCast<CSocketTCPServer>();
				CSocketTCPAddress								IPEndpoint;
				ISPSocketTCPWrapper								SocketWrapper=Socket->Accept(IPEndpoint);
				CSPSocketTCPClient								ClientSocket(new CSocketTCPClient(GetLogWriter(),SocketID,SocketWrapper));

				if (ClientSocket!=nullptr)
				{
					MSocketClientCollection.Add(ClientSocketName,ClientSocket);
				}
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't ACCEPT SOCKET !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPMenu::MenuItemSendSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			CSPByteBuffer										Data=CSPByteBuffer(new CByteBuffer(CommandParamsIterator.GetRemainingParamsAsByteBuffer("Data","",0,true)));
			CSocketTCPSendParameters							SendParams(Data,0,Data->GetLength());
			
			if (MSocketClientCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClient								Socket=MSocketClientCollection[SocketName].DynamicCast<CSocketTCPClient>();
				CSocketTCPSendResult							Result;
				
				Socket->Send(SendParams,Result);

				CConsoleHelper::WriteLine(CString::Format("SOCKET [",SocketName,"] SENT [",Result.GetNumberOfSentBytes(),"] BYTES ! SENT BYTES [",Result.GetData()->ToString(false," ",Result.GetOffset(),Result.GetNumberOfSentBytes()),"] !"));
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
	void CSocketTCPMenu::MenuItemReceiveSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MSocketClientCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClient								Socket=MSocketClientCollection[SocketName].DynamicCast<CSocketTCPClient>();
				CSPByteBuffer									Data(new CByteBuffer(2000));
				CSocketTCPReceiveParameters						ReceiveParams(Data,0,2000);
				CSocketTCPReceiveResult							Result;
				
				Socket->Receive(ReceiveParams,Result);
				
				CConsoleHelper::WriteLine(CString::Format("SOCKET [",SocketName,"] RECEIVED [",Result.GetNumberOfReceivedBytes(),"] BYTES ! RECEIVED BYTES [",Result.GetData()->ToString(false," ",Result.GetOffset(),Result.GetNumberOfReceivedBytes()),"] !"));
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't RECEIVE DATA from SOCKET !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPMenu::MenuItemSendSocketCustomBuffer(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(3);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			Size												BufferOffset=CommandParamsIterator.GetParamAsSize("BufferOffset","",0,false);
			Size												NumberOfBytesToSend=CommandParamsIterator.GetParamAsSize("NumberOfBytesToSend","",0,false);
			CByteBuffer											UDPData(CommandParamsIterator.GetRemainingParamsAsByteBuffer("Data","",0,true));
			CSPByteBuffer										Data(new CByteBuffer(BufferOffset+NumberOfBytesToSend));

			for(Size Index=0;Index<UDPData.GetLength();Index++)
			{
				(*Data)[Index+BufferOffset]=UDPData[Index];
			}

			CSocketTCPSendParameters							SendParams(Data,BufferOffset,NumberOfBytesToSend);
			
			if (MSocketClientCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClient								Socket=MSocketClientCollection[SocketName].DynamicCast<CSocketTCPClient>();
				CSocketTCPSendResult							Result;
				
				Socket->Send(SendParams,Result);

				CConsoleHelper::WriteLine(CString::Format("SOCKET [",SocketName,"] SENT [",Result.GetNumberOfSentBytes(),"] BYTES ! BUFFER [",Result.GetData()->ToString(false," "),"] SENT BYTES [",Result.GetData()->ToString(false," ",Result.GetOffset(),Result.GetNumberOfSentBytes()),"] !"));
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
	void CSocketTCPMenu::MenuItemReceiveSocketCustomBuffer(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(3);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			Size												BufferOffset=CommandParamsIterator.GetParamAsSize("BufferOffset","",0,false);
			Size												NumberOfBytesToReceive=CommandParamsIterator.GetParamAsSize("NumberOfBytesToReceive","",0,false);

			if (MSocketClientCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClient								Socket=MSocketClientCollection[SocketName].DynamicCast<CSocketTCPClient>();
				CSPByteBuffer									Data(new CByteBuffer(BufferOffset+NumberOfBytesToReceive));
				CSocketTCPReceiveParameters						ReceiveParams(Data,BufferOffset,NumberOfBytesToReceive);
				CSocketTCPReceiveResult							Result;
				
				Socket->Receive(ReceiveParams,Result);
				
				CConsoleHelper::WriteLine(CString::Format("SOCKET [",SocketName,"] RECEIVED [",Result.GetNumberOfReceivedBytes(),"] BYTES ! BUFFER [",Result.GetData()->ToString(false," "),"] RECEIVED BYTES [",Result.GetData()->ToString(false," ",Result.GetOffset(),Result.GetNumberOfReceivedBytes()),"] !"));
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't RECEIVE DATA from SOCKET !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPMenu::MenuItemWaitForEvent(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CSteadyClock::Milliseconds							TimeoutInMS=CommandParamsIterator.GetParamAsInt64("TimeoutInMS");
			bool												WaitForWriteEvent=CommandParamsIterator.GetParamAsBool("WaitForWriteEvent");
			CVector<CSPSocket>									Sockets;

			while(CommandParamsIterator.GetNumberOfRemainingParams()>0)
			{
				CString											SocketName=CommandParamsIterator.GetParamAsString();

				if (MSocketServerCollection.Contains(SocketName)==true)
				{
					CSPSocketTCPServer							Socket=MSocketServerCollection[SocketName].DynamicCast<CSocketTCPServer>();

					Sockets.Add(Socket);
				}
				else if (MSocketClientCollection.Contains(SocketName)==true)
				{
					CSPSocketTCPClient							Socket=MSocketClientCollection[SocketName].DynamicCast<CSocketTCPClient>();

					Sockets.Add(Socket);
				}
				else
				{
					throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
				}
			}

			ISPSocketWaitObject									WaitObject(new CSocketWaitObject());
			CVector<CSocketWaitState>							SocketWaitStates;

			for(CSPSocket Socket : Sockets)
			{
				SocketWaitStates.Add(CSocketWaitState(Socket,(WaitForWriteEvent==false) ? ESocketWaitFlags::E_READ : (ESocketWaitFlags::E_READ | ESocketWaitFlags::E_WRITE)));
			}

			ESocketWaitEvent									WaitEvent=WaitObject->WaitForEvent(SocketWaitStates,CTimeout(TimeoutInMS));

			CConsoleHelper::WriteLine(CString::Format("SOCKET WAIT OBJECT detected EVENT [",WaitEvent,"] !"));

			for(const CSocketWaitState& SocketWaitState : SocketWaitStates)
			{
				CConsoleHelper::WriteLine(CString::Format("\tSOCKET [",SocketWaitState.GetSocket(),"] FLAGS [",SocketWaitState.GetWaitResultFlags(),"] !"));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't WAIT for EVENT from SOCKET !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPMenu::MenuItemGetSendBufferSize(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			
			if (MSocketClientCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClient								Socket=MSocketClientCollection[SocketName].DynamicCast<CSocketTCPClient>();
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
	void CSocketTCPMenu::MenuItemSetSendBufferSize(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			int32												SendBufferSize(CommandParamsIterator.GetParamAsInt32("SendBufferSize"));
			
			if (MSocketClientCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClient								Socket=MSocketClientCollection[SocketName].DynamicCast<CSocketTCPClient>();
				
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
	void CSocketTCPMenu::MenuItemGetReceiveBufferSize(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			
			if (MSocketClientCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClient								Socket=MSocketClientCollection[SocketName].DynamicCast<CSocketTCPClient>();
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
	void CSocketTCPMenu::MenuItemSetReceiveBufferSize(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			int32												ReceiveBufferSize(CommandParamsIterator.GetParamAsInt32("ReceiveBufferSize"));
			
			if (MSocketClientCollection.Contains(SocketName)==true)
			{
				CSPSocketTCPClient								Socket=MSocketClientCollection[SocketName].DynamicCast<CSocketTCPClient>();
				
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
	void CSocketTCPMenu::MenuItemExecuteCommand(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			Size												CommandNumber=CommandParamsIterator.GetParamAsSize("CommandNumber");

			if (CommandNumber==1)
			{
				ExecuteCommand("q");
				ExecuteCommand("w aaa 1");
				ExecuteCommand("w bbb 0");
				ExecuteCommand("b aaa 0.0.0.0:10000");
				ExecuteCommand("t aaa 5");
			}
			else if (CommandNumber==2)
			{
				ExecuteCommand("q");
				ExecuteCommand("w aaa 1");
				ExecuteCommand("w bbb 0");
				ExecuteCommand("b aaa 0.0.0.0:10000");
				ExecuteCommand("t aaa 5");
				ExecuteCommand("c bbb 127.0.0.1:10000");
				ExecuteCommand("y aaa ccc");
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
	CString CSocketTCPMenu::GetStatus(void) const
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

		Status+=", SERVER SOCKETS: ";
		Status+=CString(MSocketServerCollection.GetLength());

		Status+=", CLIENT SOCKETS: ";
		Status+=CString(MSocketClientCollection.GetLength());

		return(Status);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------