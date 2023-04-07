//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANMenu.h"
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/Console/CConsoleHelper.h>
#include <Framework/Foundation/Console/CConsoleMenuItemCommandParamsIterator.h>
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketLibrary.h>
#include <Framework/Foundation/Communication/Networking/Sockets/ISocketWaitObject.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCAN.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANFrame.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANReceiveFromParameters.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANReceiveFromResult.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANSendToParameters.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANSendToResult.h>
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
	CSocketCANMenu::CSocketCANMenu(CConsoleLogWriter& LogWriter)
		: CConsoleMenu(LogWriter,"SOCKET CAN"), MIsLibraryInitialized(false), MSocketCollection()
	{
		AddMenuItem(CConsoleMenuItem("X","Exit","",EConsoleMenuItemType::E_ITEM_EXIT,CConsoleMenuItemCallbackMethod<CSocketCANMenu>(this,&CSocketCANMenu::MenuItemExit)));
		AddMenuItem(CConsoleMenuItem("Q","Initialize","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANMenu>(this,&CSocketCANMenu::MenuItemInitialize)));
		AddMenuItem(CConsoleMenuItem("A","Uninitialize","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANMenu>(this,&CSocketCANMenu::MenuItemUninitialize)));
		AddMenuItem(CConsoleMenuItem("W","Create Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANMenu>(this,&CSocketCANMenu::MenuItemCreateSocket)));
		AddMenuItem(CConsoleMenuItem("S","Destroy Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANMenu>(this,&CSocketCANMenu::MenuItemDestroySocket)));
		AddMenuItem(CConsoleMenuItem("B","Bind Socket","[SocketName] [NetworkInterfaceIndex]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANMenu>(this,&CSocketCANMenu::MenuItemBindSocket)));
		AddMenuItem(CConsoleMenuItem("N","Send Data to Socket","[SocketName] [NetworkInterfaceIndex] [IsExtendedFrame] [IsRemoteFrame] [IsErrorFrame] [ID] [Byte1] ... [ByteN]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANMenu>(this,&CSocketCANMenu::MenuItemSendToSocket)));
		AddMenuItem(CConsoleMenuItem("M","Receive Data from Socket","[SocketName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANMenu>(this,&CSocketCANMenu::MenuItemReceiveFromSocket)));
		AddMenuItem(CConsoleMenuItem("NB","Send Data to Socket","[SocketName] [BufferOffset] [NumberOfBytesToSend] [NetworkInterfaceIndex] [IsExtendedFrame] [IsRemoteFrame] [IsErrorFrame] [ID] [Byte1] ... [ByteN]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANMenu>(this,&CSocketCANMenu::MenuItemSendToSocketCustomBuffer)));
		AddMenuItem(CConsoleMenuItem("MB","Receive Data from Socket Custom Buffer","[SocketName] [BufferOffset] [NumberOfBytesToReceive]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANMenu>(this,&CSocketCANMenu::MenuItemReceiveFromSocketCustomBuffer)));
		AddMenuItem(CConsoleMenuItem("L","Wait for Event","[TimeoutInMS] [WaitForWriteEvent] [SocketName1] ... [SocketNameN]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANMenu>(this,&CSocketCANMenu::MenuItemWaitForEvent)));
		AddMenuItem(CConsoleMenuItem("GN","Get Network Interface Name","[SocketName] [NetworkInterfaceIndex]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANMenu>(this,&CSocketCANMenu::MenuItemGetNetworkInterfaceNameForDevice)));
		AddMenuItem(CConsoleMenuItem("GI","Get Network Interface Index","[SocketName] [DeviceName]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketCANMenu>(this,&CSocketCANMenu::MenuItemGetNetworkInterfaceIndexForDevice)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANMenu::~CSocketCANMenu(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANMenu::MenuItemExit(const CConsoleMenuItemCommandParams&)
	{
		// EMPTY.
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANMenu::MenuItemInitialize(const CConsoleMenuItemCommandParams&)
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
	void CSocketCANMenu::MenuItemUninitialize(const CConsoleMenuItemCommandParams&)
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
	void CSocketCANMenu::MenuItemCreateSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParams.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MSocketCollection.Contains(SocketName)==false)
			{
				CSPSocketCAN									SocketSharedPointer(new CSocketCAN(GetLogWriter(),SocketName));

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
	void CSocketCANMenu::MenuItemDestroySocket(const CConsoleMenuItemCommandParams& CommandParams)
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
	void CSocketCANMenu::MenuItemBindSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			CSocketCANAddress									Address(CommandParamsIterator.GetParamAsInt32("NetworkInterfaceIndex"));

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketCAN									Socket=MSocketCollection[SocketName].DynamicCast<CSocketCAN>();

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
	void CSocketCANMenu::MenuItemSendToSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(6);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			CSocketCANAddress									RemoteAddress(CommandParamsIterator.GetParamAsInt32("NetworkInterfaceIndex"));
			bool												IsExtendedFrame=CommandParamsIterator.GetParamAsBool("IsExtendedFrame");
			bool												IsRemoteFrame=CommandParamsIterator.GetParamAsBool("IsRemoteFrame");
			bool												IsErrorFrame=CommandParamsIterator.GetParamAsBool("IsErrorFrame");
			uint32												ID=CommandParamsIterator.GetParamAsUInt32("ID","",0,true);
			CSocketCANAddress									Address(RemoteAddress);
			CSocketCANID										CANID(IsExtendedFrame,IsRemoteFrame,IsErrorFrame,ID);
			CByteBuffer											CANData(CommandParamsIterator.GetRemainingParamsAsByteBuffer("Data","",0,true));
			CSocketCANFrame										Frame(CANID,CANData);
			CSPByteBuffer										Data(new CByteBuffer(Frame.Serialize()));
			CSocketCANSendToParameters							SendParams(Address,Data,0,Data->GetLength());

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketCAN									Socket=MSocketCollection[SocketName].DynamicCast<CSocketCAN>();
				CSocketCANSendToResult							Result;
				
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
	void CSocketCANMenu::MenuItemReceiveFromSocket(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CString												SocketName=CommandParamsIterator.GetParamAsString();

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketCAN									Socket=MSocketCollection[SocketName].DynamicCast<CSocketCAN>();
				CSPByteBuffer									Data(new CByteBuffer(CSocketCANFrame::CAN_FRAME_LENGTH));
				CSocketCANReceiveFromParameters					ReceiveParams(Data,0,Data->GetLength());
				CSocketCANReceiveFromResult						Result;
				
				Socket->ReceiveFrom(ReceiveParams,Result);

				if (Result.GetNumberOfReceivedBytes()>0)
				{
					CSocketCANFrame								Frame;

					Frame.Deserialize(CByteBuffer(Data->GetRawData(),Result.GetNumberOfReceivedBytes()));

					CConsoleHelper::WriteLine(CString::Format("SOCKET [",SocketName,"] RECEIVED [",Result.GetNumberOfReceivedBytes(),"] BYTES ! RECEIVED BYTES [",Result.GetData()->ToString(false," ",Result.GetOffset(),Result.GetNumberOfReceivedBytes()),"] FRAME [",Frame,"] !"));
				}
				else
				{
					CConsoleHelper::WriteLine(CString::Format("SOCKET [",SocketName,"] RECEIVED [",Result.GetNumberOfReceivedBytes(),"] BYTES ! RECEIVED BYTES [",Result.GetData()->ToString(false," ",Result.GetOffset(),Result.GetNumberOfReceivedBytes()),"] !"));
				}
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
	void CSocketCANMenu::MenuItemSendToSocketCustomBuffer(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(8);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			Size												BufferOffset=CommandParamsIterator.GetParamAsSize("BufferOffset","",0,false);
			Size												NumberOfBytesToSend=CommandParamsIterator.GetParamAsSize("NumberOfBytesToSend","",0,false);
			CSocketCANAddress									RemoteAddress(CommandParamsIterator.GetParamAsInt32("NetworkInterfaceIndex"));
			bool												IsExtendedFrame=CommandParamsIterator.GetParamAsBool("IsExtendedFrame");
			bool												IsRemoteFrame=CommandParamsIterator.GetParamAsBool("IsRemoteFrame");
			bool												IsErrorFrame=CommandParamsIterator.GetParamAsBool("IsErrorFrame");
			uint32												ID=CommandParamsIterator.GetParamAsUInt32("ID","",0,true);
			CSocketCANAddress									Address(RemoteAddress);
			CSocketCANID										CANID(IsExtendedFrame,IsRemoteFrame,IsErrorFrame,ID);
			CByteBuffer											CANData(CommandParamsIterator.GetRemainingParamsAsByteBuffer("Data","",0,true));
			CSocketCANFrame										Frame(CANID,CANData);
			CByteBuffer											FrameData=Frame.Serialize();
			CSPByteBuffer										Data(new CByteBuffer(BufferOffset+NumberOfBytesToSend));

			for(Size Index=0;Index<FrameData.GetLength();Index++)
			{
				(*Data)[Index+BufferOffset]=FrameData[Index];
			}

			CSocketCANSendToParameters							SendParams(Address,Data,BufferOffset,NumberOfBytesToSend);

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketCAN									Socket=MSocketCollection[SocketName].DynamicCast<CSocketCAN>();
				CSocketCANSendToResult							Result;
				
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
	void CSocketCANMenu::MenuItemReceiveFromSocketCustomBuffer(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(3);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			Size												BufferOffset=CommandParamsIterator.GetParamAsSize("BufferOffset","",0,false);
			Size												NumberOfBytesToReceive=CommandParamsIterator.GetParamAsSize("NumberOfBytesToReceive","",0,false,CSocketCANFrame::CAN_ID_LENGTH);

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketCAN									Socket=MSocketCollection[SocketName].DynamicCast<CSocketCAN>();
				CSPByteBuffer									Data(new CByteBuffer(BufferOffset+NumberOfBytesToReceive));
				CSocketCANReceiveFromParameters					ReceiveParams(Data,BufferOffset,NumberOfBytesToReceive);
				CSocketCANReceiveFromResult						Result;
				
				Socket->ReceiveFrom(ReceiveParams,Result);

				if (Result.GetNumberOfReceivedBytes()>0)
				{
					CSocketCANFrame								Frame;

					Frame.Deserialize(CByteBuffer(Data->GetRawData(),Result.GetNumberOfReceivedBytes()));

					CConsoleHelper::WriteLine(CString::Format("SOCKET [",SocketName,"] RECEIVED [",Result.GetNumberOfReceivedBytes(),"] BYTES ! BUFFER [",Result.GetData()->ToString(false," "),"] RECEIVED BYTES [",ReceiveParams.GetData()->ToString(false," ",Result.GetOffset(),Result.GetNumberOfReceivedBytes()),"] FRAME [",Frame,"] !"));
				}
				else
				{
					CConsoleHelper::WriteLine(CString::Format("SOCKET [",SocketName,"] RECEIVED [",Result.GetNumberOfReceivedBytes(),"] BYTES ! BUFFER [",Result.GetData()->ToString(false," "),"] RECEIVED BYTES [",ReceiveParams.GetData()->ToString(false," ",Result.GetOffset(),Result.GetNumberOfReceivedBytes()),"] !"));
				}
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
	void CSocketCANMenu::MenuItemWaitForEvent(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CSteadyClock::Milliseconds							TimeoutInMS=CommandParamsIterator.GetParamAsInt64("TimeoutInMS");
			bool												WaitForWriteEvent=CommandParamsIterator.GetParamAsBool("WaitForWriteEvent");
			CVector<CSPSocketCAN>								Sockets;

			while(CommandParamsIterator.GetNumberOfRemainingParams()>0)
			{
				CString											SocketName=CommandParamsIterator.GetParamAsString();

				if (MSocketCollection.Contains(SocketName)==true)
				{
					CSPSocketCAN								Socket=MSocketCollection[SocketName].DynamicCast<CSocketCAN>();

					Sockets.Add(Socket);
				}
				else
				{
					throw(CInvalidOperationException(CString::Format("SOCKET [",SocketName,"] does NOT EXIST !")));
				}
			}

			ISPSocketWaitObject									WaitObject(new CSocketWaitObject());
			CVector<CSocketWaitState>							SocketWaitStates;

			for(CSPSocketCAN Socket : Sockets)
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
	void CSocketCANMenu::MenuItemGetNetworkInterfaceNameForDevice(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			int32												NetworkInterfaceIndex=CommandParamsIterator.GetParamAsInt32("NetworkInterfaceIndex");

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketCAN									Socket=MSocketCollection[SocketName].DynamicCast<CSocketCAN>();
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
	void CSocketCANMenu::MenuItemGetNetworkInterfaceIndexForDevice(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CString												SocketName=CommandParamsIterator.GetParamAsString();
			CString												DeviceName=CommandParamsIterator.GetParamAsString();

			if (MSocketCollection.Contains(SocketName)==true)
			{
				CSPSocketCAN									Socket=MSocketCollection[SocketName].DynamicCast<CSocketCAN>();
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketCANMenu::GetStatus(void) const
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