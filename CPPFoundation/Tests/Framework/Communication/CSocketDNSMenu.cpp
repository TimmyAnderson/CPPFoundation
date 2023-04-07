//----------------------------------------------------------------------------------------------------------------------
#include "CSocketDNSMenu.h"
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSMenu::CSocketDNSMenu(CConsoleLogWriter& LogWriter)
		: CConsoleMenu(LogWriter,"SOCKET DNS"), MIsLibraryInitialized(false), MSocketDNSResolver()
	{
		AddMenuItem(CConsoleMenuItem("X","Exit","",EConsoleMenuItemType::E_ITEM_EXIT,CConsoleMenuItemCallbackMethod<CSocketDNSMenu>(this,&CSocketDNSMenu::MenuItemExit)));
		AddMenuItem(CConsoleMenuItem("Q","Initialize","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketDNSMenu>(this,&CSocketDNSMenu::MenuItemInitialize)));
		AddMenuItem(CConsoleMenuItem("A","Uninitialize","",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketDNSMenu>(this,&CSocketDNSMenu::MenuItemUninitialize)));
		AddMenuItem(CConsoleMenuItem("H","Host Name To IP Address","[HostName] [AddressType] [Protocol]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketDNSMenu>(this,&CSocketDNSMenu::MenuItemHostNameToIPAddress)));
		AddMenuItem(CConsoleMenuItem("I4","IPv4 Address To Host Name","[IPv4Address] [HostNameRequired]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketDNSMenu>(this,&CSocketDNSMenu::MenuItemIPv4AddressToHostName)));
		AddMenuItem(CConsoleMenuItem("I6","IPv6 Address To Host Name","[IPv6Address] [HostNameRequired]",EConsoleMenuItemType::E_ITEM_NORMAL,CConsoleMenuItemCallbackMethod<CSocketDNSMenu>(this,&CSocketDNSMenu::MenuItemIPv6AddressToHostName)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSMenu::~CSocketDNSMenu(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketDNSMenu::MenuItemExit(const CConsoleMenuItemCommandParams&)
	{
		// EMPTY.
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketDNSMenu::MenuItemInitialize(const CConsoleMenuItemCommandParams&)
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
	void CSocketDNSMenu::MenuItemUninitialize(const CConsoleMenuItemCommandParams&)
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
	void CSocketDNSMenu::MenuItemHostNameToIPAddress(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(3);

			CString												HostName=CommandParamsIterator.GetParamAsString();
			ESocketDNSAddressType								AddressType=CommandParamsIterator.GetParamAsEnum<ESocketDNSAddressType>("AddressType");
			ESocketDNSProtocolType								ProtocolType=CommandParamsIterator.GetParamAsEnum<ESocketDNSProtocolType>("ProtocolType");
			CVector<CSocketIPAddress>							IPAddresses=MSocketDNSResolver.ConvertDNSAddressToIPAddress(HostName,AddressType,ProtocolType);

			for(const CSocketIPAddress& IPAddress : IPAddresses)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("IP ADDRESS [",IPAddress,"] !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't CONVERT HOST NAME to IP ADDRESS !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketDNSMenu::MenuItemIPv4AddressToHostName(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(2);

			CSocketIPAddress									SocketIPAddress=CommandParamsIterator.GetParamAsIPv4Address("SocketIPAddress");
			bool												HostNameRequired=CommandParamsIterator.GetParamAsBool("HostNameRequired");
			CSocketDNSAddress									HostName=MSocketDNSResolver.ConvertIPAddressToDNSAddress(SocketIPAddress,HostNameRequired);

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("HOSTNAME [",HostName,"] !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't CONVERT IP ADDRESS to HOST NAME !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketDNSMenu::MenuItemIPv6AddressToHostName(const CConsoleMenuItemCommandParams& CommandParams)
	{
		try
		{
			CConsoleMenuItemCommandParamsIterator				CommandParamsIterator(CommandParams);

			CommandParamsIterator.CheckNumberOfParams(1);

			CSocketIPAddress									SocketIPAddress=CommandParamsIterator.GetParamAsIPv6Address("SocketIPAddress");
			bool												HostNameRequired=CommandParamsIterator.GetParamAsBool("HostNameRequired");
			CSocketDNSAddress									HostName=MSocketDNSResolver.ConvertIPAddressToDNSAddress(SocketIPAddress,HostNameRequired);

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("HOSTNAME [",HostName,"] !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryMenu(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("Can't CONVERT IP ADDRESS to HOST NAME !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketDNSMenu::GetStatus(void) const
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

		return(Status);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------