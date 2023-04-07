//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPMenu.h"
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/Console/CConsoleHelper.h>
#include <Framework/Foundation/Console/CConsoleMenuItemCommandParamsIterator.h>
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketLibrary.h>
#include <Framework/Foundation/Communication/Networking/Sockets/ISocketWaitObject.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/CSocketUDP.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/CSocketUDPReceiveFromParameters.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/CSocketUDPReceiveFromResult.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/CSocketUDPSendToParameters.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/CSocketUDPSendToResult.h>
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
	CSocketUDPMenu::CSocketUDPMenu(CConsoleLogWriter& LogWriter)
		: CConsoleMenu(LogWriter,"SOCKET UDP"), MIsLibraryInitialized(false), MSocketCollection()
	{
		AddMenuItem(CConsoleMenuItem("X","Exit","",EConsoleMenuItemType::E_ITEM_EXIT,CConsoleMenuItemCallbackMethod<CSocketUDPMenu>(this,&CSocketUDPMenu::MenuItemExit)));
		AddMenuItem(CConsoleMenuItem("Q","Initialize","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPMenu>(this,&CSocketUDPMenu::MenuItemInitialize)));
		AddMenuItem(CConsoleMenuItem("A","Uninitialize","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPMenu>(this,&CSocketUDPMenu::MenuItemUninitialize)));
		AddMenuItem(CConsoleMenuItem("W","Create Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPMenu>(this,&CSocketUDPMenu::MenuItemCreateSocket)));
		AddMenuItem(CConsoleMenuItem("S","Destroy Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPMenu>(this,&CSocketUDPMenu::MenuItemDestroySocket)));
		AddMenuItem(CConsoleMenuItem("B","Bind Socket","[SocketName] [IPEndpoint]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPMenu>(this,&CSocketUDPMenu::MenuItemBindSocket)));
		AddMenuItem(CConsoleMenuItem("N","Send Data to Socket","[SocketName] [RemoteIPEndpoint] [Byte1] ... [ByteN]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPMenu>(this,&CSocketUDPMenu::MenuItemSendToSocket)));
		AddMenuItem(CConsoleMenuItem("M","Receive Data from Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPMenu>(this,&CSocketUDPMenu::MenuItemReceiveFromSocket)));
		AddMenuItem(CConsoleMenuItem("NB","Send Data to Socket","[SocketName] [BufferOffset] [NumberOfBytesToSend] [RemoteIPEndpoint] [Byte1] ... [ByteN]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPMenu>(this,&CSocketUDPMenu::MenuItemSendToSocketCustomBuffer)));
		AddMenuItem(CConsoleMenuItem("MB","Receive Data from Socket","[SocketName] [BufferOffset] [NumberOfBytesToReceive]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPMenu>(this,&CSocketUDPMenu::MenuItemReceiveFromSocketCustomBuffer)));
		AddMenuItem(CConsoleMenuItem("L","Wait for Event","[TimeoutInMS] [WaitForWriteEvent] [SocketName1] ... [SocketNameN]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPMenu>(this,&CSocketUDPMenu::MenuItemWaitForEvent)));
		AddMenuItem(CConsoleMenuItem("F","Get Send Buffer Size","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPMenu>(this,&CSocketUDPMenu::MenuItemGetSendBufferSize)));
		AddMenuItem(CConsoleMenuItem("G","Set Send Buffer Size","[SocketName] [SendBufferSize]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPMenu>(this,&CSocketUDPMenu::MenuItemSetSendBufferSize)));
		AddMenuItem(CConsoleMenuItem("H","Get Receive Buffer Size","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPMenu>(this,&CSocketUDPMenu::MenuItemGetReceiveBufferSize)));
		AddMenuItem(CConsoleMenuItem("J","Set Receive Buffer Size","[SocketName] [ReceiveBufferSize]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketUDPMenu>(this,&CSocketUDPMenu::MenuItemSetReceiveBufferSize)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPMenu::~CSocketUDPMenu(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPMenu::MenuItemExit(const CConsoleMenuItemCommandParams&)
	{
		// EMPTY.
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPMenu::MenuItemInitialize(const CConsoleMenuItemCommandParams&)
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
	void CSocketUDPMenu::MenuItemUninitialize(const CConsoleMenuItemCommandParams&)
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
	void CSocketUDPMenu::MenuItemCreateSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MSocketCollection.Contains(SocketName)==false)
			{
				CSPSocketUDP									SocketSharedPointer(new CSocketUDP(GetLogWriter(),SocketName));

				MSocketCollection.Add(SocketName,SocketSharedPointer);
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
	void CSocketUDPMenu::MenuItemDestroySocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MSocketCollection.Contains(SocketName)==true)
			{
				MSocketCollection.Erase(SocketName);
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
	void CSocketUDPMenu::MenuItemBindSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			CSocketUDPAddress									IPEndpoint=CSocketUDPAddress(CommandParamsIterator.GetParamAsIPv4Endpoint("IPEndpoint"));
			
			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketUDP									Socket=MSocketCollection[SocketName].DynamicCast<CSocketUDP>();

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
	void CSocketUDPMenu::MenuItemSendToSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			CSocketUDPAddress									RemoteIPEndpoint(CommandParamsIterator.GetParamAsIPv4Endpoint("RemoteIPEndpoint"));
			CSPByteBuffer										Data=CSPByteBuffer(new CByteBuffer(CommandParamsIterator.GetRemainingParamsAsByteBuffer("Data","",0,true)));
			CSocketUDPSendToParameters							SendParams(RemoteIPEndpoint,Data,0,Data->GetLength());
			
			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketUDP									Socket=MSocketCollection[SocketName].DynamicCast<CSocketUDP>();
				CSocketUDPSendToResult							Result;
				
				Socket->SendTo(SendParams,Result);

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
	void CSocketUDPMenu::MenuItemReceiveFromSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketUDP									Socket=MSocketCollection[SocketName].DynamicCast<CSocketUDP>();
				CSPByteBuffer									Data(new CByteBuffer(2000));
				CSocketUDPReceiveFromParameters					ReceiveParams(Data,0,2000);
				CSocketUDPReceiveFromResult						Result;
				
				Socket->ReceiveFrom(ReceiveParams,Result);
				
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
	void CSocketUDPMenu::MenuItemSendToSocketCustomBuffer(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(4);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			Size												BufferOffset=CommandParamsIterator.GetParamAsSize("BufferOffset","",0,false);
			Size												NumberOfBytesToSend=CommandParamsIterator.GetParamAsSize("NumberOfBytesToSend","",0,false);
			CSocketUDPAddress									RemoteIPEndpoint(CommandParamsIterator.GetParamAsIPv4Endpoint("RemoteIPEndpoint"));
			CByteBuffer											UDPData(CommandParamsIterator.GetRemainingParamsAsByteBuffer("Data","",0,true));
			CSPByteBuffer										Data(new CByteBuffer(BufferOffset+NumberOfBytesToSend));

			for(Size Index=0;Index<UDPData.GetLength();Index++)
			{
				(*Data)[Index+BufferOffset]=UDPData[Index];
			}

			CSocketUDPSendToParameters							SendParams(RemoteIPEndpoint,Data,BufferOffset,NumberOfBytesToSend);
			
			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketUDP									Socket=MSocketCollection[SocketName].DynamicCast<CSocketUDP>();
				CSocketUDPSendToResult							Result;
				
				Socket->SendTo(SendParams,Result);

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
	void CSocketUDPMenu::MenuItemReceiveFromSocketCustomBuffer(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(3);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			Size												BufferOffset=CommandParamsIterator.GetParamAsSize("BufferOffset","",0,false);
			Size												NumberOfBytesToReceive=CommandParamsIterator.GetParamAsSize("NumberOfBytesToReceive","",0,false);

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketUDP									Socket=MSocketCollection[SocketName].DynamicCast<CSocketUDP>();
				CSPByteBuffer									Data(new CByteBuffer(BufferOffset+NumberOfBytesToReceive));
				CSocketUDPReceiveFromParameters					ReceiveParams(Data,BufferOffset,NumberOfBytesToReceive);
				CSocketUDPReceiveFromResult						Result;
				
				Socket->ReceiveFrom(ReceiveParams,Result);
				
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
	void CSocketUDPMenu::MenuItemWaitForEvent(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CSteadyClock::Milliseconds							TimeoutInMS=CommandParamsIterator.GetParamAsInt64("TimeoutInMS");
			bool												WaitForWriteEvent=CommandParamsIterator.GetParamAsBool("WaitForWriteEvent");
			CVector<CSPSocketUDP>								Sockets;

			while(CommandParamsIterator.GetNumberOfRemainingParams()>0)
			{
				CString											SocketName=CommandParamsIterator.GetParamAsString();

				if (MSocketCollection.Contains(SocketName)==true)
				{
					CSPSocketUDP								Socket=MSocketCollection[SocketName].DynamicCast<CSocketUDP>();

					Sockets.Add(Socket);
				}
				else
				{
					throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
				}
			}

			ISPSocketWaitObject									WaitObject(new CSocketWaitObject());
			CVector<CSocketWaitState>							SocketWaitStates;

			for(CSPSocketUDP Socket : Sockets)
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
	void CSocketUDPMenu::MenuItemGetSendBufferSize(const CConsoleMenuItemCommandParams& CommandParams)
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
	void CSocketUDPMenu::MenuItemSetSendBufferSize(const CConsoleMenuItemCommandParams& CommandParams)
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
	void CSocketUDPMenu::MenuItemGetReceiveBufferSize(const CConsoleMenuItemCommandParams& CommandParams)
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
	void CSocketUDPMenu::MenuItemSetReceiveBufferSize(const CConsoleMenuItemCommandParams& CommandParams)
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketUDPMenu::GetStatus(void) const
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