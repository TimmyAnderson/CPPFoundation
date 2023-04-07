//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <winsock2.h>
#include <Windows.h>
#include <io.h>
#pragma warning(disable : 4996)
#elif defined(PLATFORM_LINUX)
#include <cstring>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <cxxabi.h>
#endif
#include <cmath>
#include <cstring>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/Exceptions/CInvalidValueException.h>
#include <Framework/Foundation/Exceptions/CNotImplementedException.h>
#include <Framework/Foundation/Mathematics/CMathematics.h>
#include "CFunctions.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Platform
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace std;
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CFunctions::GetDemangledName(const char* Name)
	{
#if defined(PLATFORM_WINDOWS)
		if (Name!=nullptr)
		{
			return(Name);
		}
		else
		{
			return("");
		}
#elif defined(PLATFORM_LINUX)
		if (Name!=nullptr)
		{
			int													Status=0;
			char*												DemangledName=abi::__cxa_demangle(Name,nullptr,nullptr,&Status);

			if (DemangledName!=nullptr)
			{
				try
				{
					CString										TypeName(DemangledName);

					free(DemangledName);
					DemangledName=nullptr;

					return(TypeName);
				}
				catch(...)
				{
					free(DemangledName);
					DemangledName=nullptr;

					return(Name);
				}
			}
			else
			{
				return(Name);
			}
		}
		else
		{
			return("");
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CFunctions::MainInit(void)
	{
#if defined(PLATFORM_WINDOWS)
		// !!!!! FLAGS [_CRTDBG_DELAY_FREE_MEM_DF and _CRTDBG_ALLOC_MEM_DF] SHOULD NEVER be USED because they EXTREMELY SLOW DOWN PROGRAM.
		// !!! FLAG [_CRTDBG_CHECK_CRT_DF] should not be used, because it marks some INTERNAL CRT ALLOCATIONS as the MEMORY LEAKS.
		_CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF);
		_CrtSetReportMode(_CRT_ASSERT, 0);
#elif defined(PLATFORM_LINUX)
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFunctions::ClearScreen(void)
	{
#if defined(PLATFORM_WINDOWS)
		HANDLE													Handle;
		CONSOLE_SCREEN_BUFFER_INFO								ScreenInfo;
		DWORD													Count;
		DWORD													CellCount;
		COORD													HomeCoordinates={0,0};

		Handle=GetStdHandle(STD_OUTPUT_HANDLE);

		if (Handle==INVALID_HANDLE_VALUE)
		{
			return;
		}

		if (GetConsoleScreenBufferInfo(Handle,&ScreenInfo)==FALSE)
		{
			return;
		}

		CellCount=static_cast<DWORD>(ScreenInfo.dwSize.X*ScreenInfo.dwSize.Y);

		if (FillConsoleOutputCharacter(Handle,L' ',CellCount,HomeCoordinates,&Count)==FALSE)
		{
			return;
		}

		if (FillConsoleOutputAttribute(Handle,ScreenInfo.wAttributes,CellCount,HomeCoordinates,&Count)==FALSE)
		{
			return;
		}

		SetConsoleCursorPosition(Handle,HomeCoordinates);
#elif defined(PLATFORM_LINUX)
		cout << string(25,'\n');
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFunctions::InitializeConsole(bool EnableAnsiSequences)
	{
#if defined(PLATFORM_WINDOWS)
		if (EnableAnsiSequences==true)
		{
			HANDLE												ConsoleOutputHandle=CreateFileA("CONOUT$",GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

			if (ConsoleOutputHandle!=INVALID_HANDLE_VALUE)
			{
				try
				{
					DWORD										Mode=0;

					if (GetConsoleMode(ConsoleOutputHandle,&Mode)==FALSE)
					{
						int32									ErrorCode=GetLastErrorCode();
						CString									ErrorMessage=GetLastErrorMessage(ErrorCode);

						throw(CInvalidOperationException(CString::Format("Can't get CONSOLE MODE ! ERROR MESSAGE [",ErrorMessage,"] !")));
					}

					Mode|=ENABLE_VIRTUAL_TERMINAL_PROCESSING;

					if (SetConsoleMode(ConsoleOutputHandle,Mode)==FALSE)
					{
						int32									ErrorCode=GetLastErrorCode();
						CString									ErrorMessage=GetLastErrorMessage(ErrorCode);

						throw(CInvalidOperationException(CString::Format("Can't get CONSOLE MODE ! ERROR MESSAGE [",ErrorMessage,"] !")));
					}

					CloseHandle(ConsoleOutputHandle);
				}
				catch(...)
				{
					CloseHandle(ConsoleOutputHandle);
				}
			}
			else
			{
				int32											ErrorCode=GetLastErrorCode();
				CString											ErrorMessage=GetLastErrorMessage(ErrorCode);

				throw(CInvalidOperationException(CString::Format("Can't get CONSOLE OUTPUT HANDLE ! ERROR MESSAGE [",ErrorMessage,"] !")));
			}
		}
#elif defined(PLATFORM_LINUX)
		(void) EnableAnsiSequences;
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFunctions::IsDaylightSavingTime(time_t Time)
	{
#if defined(PLATFORM_WINDOWS)
		tm														LocalTime;

		if (localtime_s(&LocalTime,&Time)!=0)
		{
			throw(CInvalidValueException("INVALID TIME VALUE !"));
		}

		if (LocalTime.tm_isdst!=0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
#elif defined(PLATFORM_LINUX)
		tm														LocalTime=*localtime(&Time);

		if (LocalTime.tm_isdst!=0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CFunctions::GetLocalTimeOffsetInSeconds(time_t Time)
	{
#if defined(PLATFORM_WINDOWS)
		tm														LocalTime;
		tm														UTCTime;

		if (localtime_s(&LocalTime,&Time)!=0)
		{
			throw(CInvalidValueException("INVALID TIME VALUE !"));
		}

		if (gmtime_s(&UTCTime,&Time)!=0)
		{
			throw(CInvalidValueException("INVALID TIME VALUE !"));
		}

		time_t													LocalTimePoint=mktime(&LocalTime);
		time_t													UTCTimePoint=mktime(&UTCTime);
		int32													DifferenceInSeconds=static_cast<int32>(difftime(LocalTimePoint,UTCTimePoint));

		if (LocalTime.tm_isdst!=0)
		{
			DifferenceInSeconds+=3600;
		}

		return(DifferenceInSeconds);
#elif defined(PLATFORM_LINUX)
		tm														LocalTime=*localtime(&Time);
		tm														UTCTime=*gmtime(&Time);
		time_t													LocalTimePoint=mktime(&LocalTime);
		time_t													UTCTimePoint=mktime(&UTCTime);
		int32													DifferenceInSeconds=static_cast<int32>(difftime(LocalTimePoint,UTCTimePoint));

		if (LocalTime.tm_isdst!=0)
		{
			DifferenceInSeconds+=3600;
		}

		return(DifferenceInSeconds);
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	float64 CFunctions::Floor(float64 Value)
	{
#if defined(PLATFORM_WINDOWS)
		float64													CalculatedValue=static_cast<float64>(floor(static_cast<double>(Value)));

		return(CalculatedValue);
#elif defined(PLATFORM_LINUX)
		float64													CalculatedValue=static_cast<float64>(floor(static_cast<double>(Value)));

		return(CalculatedValue);
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	float64 CFunctions::Ceil(float64 Value)
	{
#if defined(PLATFORM_WINDOWS)
		float64													CalculatedValue=static_cast<float64>(ceil(static_cast<double>(Value)));

		return(CalculatedValue);
#elif defined(PLATFORM_LINUX)
		float64													CalculatedValue=static_cast<float64>(ceil(static_cast<double>(Value)));

		return(CalculatedValue);
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int32 CFunctions::GetLastErrorCode(void)
	{
#if defined(PLATFORM_WINDOWS)
		int32													ErrorCode=static_cast<int32>(GetLastError());

		return(ErrorCode);
#elif defined(PLATFORM_LINUX)
		int32													ErrorCode=static_cast<int32>(errno);

		return(ErrorCode);
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CFunctions::GetLastErrorMessage(int32 ErrorCode)
	{
#if defined(PLATFORM_WINDOWS)
		CString													ErrorMessage;
		const DWORD												BufferSize=1024;
		wchar_t													WideCharBuffer[BufferSize+1];

		if (FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,NULL,DWORD(ErrorCode),MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),WideCharBuffer,BufferSize,NULL)>0)
		{
			char												Buffer[BufferSize+1];
			size_t												ConvertedCharacters;

			if (wcstombs_s(&ConvertedCharacters,Buffer,WideCharBuffer,BufferSize)==0)
			{
				ErrorMessage=Buffer;
				ErrorMessage.ReplaceAll("\r","");
				ErrorMessage.ReplaceAll("\n","");
			}
		}
		else
		{
			ErrorMessage="UNKNOWN ERROR !!!";
		}

		return(ErrorMessage);
#elif defined(PLATFORM_LINUX)
		CString													ErrorMessage;

		ErrorMessage=strerror(ErrorCode);
		ErrorMessage.ReplaceAll("\r","");
		ErrorMessage.ReplaceAll("\n","");

		return(ErrorMessage);
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int32 CFunctions::FileOpen(int32& Descriptor, const char* Name, EFileOpenFlags Flags)
	{
#if defined(PLATFORM_WINDOWS)
		Descriptor=static_cast<int32>(_open(Name,static_cast<int>(Flags)));

		if (Descriptor!=-1)
		{
			return(0);
		}
		else
		{
			int32												ErrorCode=GetLastErrorCode();

			return(ErrorCode);
		}
#elif defined(PLATFORM_LINUX)
		Descriptor=static_cast<int32>(open(Name,static_cast<int>(Flags)));

		if (Descriptor!=-1)
		{
			return(0);
		}
		else
		{
			int32												ErrorCode=GetLastErrorCode();

			return(ErrorCode);
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CFunctions::FileClose(int32 Descriptor)
	{
#if defined(PLATFORM_WINDOWS)
		int														Result=_close(static_cast<int>(Descriptor));

		if (Result!=-1)
		{
			return(0);
		}
		else
		{
			int32												ErrorCode=GetLastErrorCode();

			return(ErrorCode);
		}
#elif defined(PLATFORM_LINUX)
		int														Result=close(static_cast<int>(Descriptor));

		if (Result!=-1)
		{
			return(0);
		}
		else
		{
			int32												ErrorCode=GetLastErrorCode();

			return(ErrorCode);
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CFunctions::FileRead(int32 Descriptor, uint8* Buffer, Size BufferSize, int32& NumberOfBytesRead)
	{
#if defined(PLATFORM_WINDOWS)
		int														Result=_read(static_cast<int>(Descriptor),Buffer,static_cast<unsigned int>(BufferSize));

		if (Result!=-1)
		{
			NumberOfBytesRead=static_cast<int32>(Result);

			return(0);
		}
		else
		{
			int32												ErrorCode=GetLastErrorCode();

			return(ErrorCode);
		}
#elif defined(PLATFORM_LINUX)
		ssize_t													Result=read(static_cast<int>(Descriptor),Buffer,static_cast<size_t>(BufferSize));

		if (Result!=-1)
		{
			NumberOfBytesRead=static_cast<int32>(Result);

			return(0);
		}
		else
		{
			int32												ErrorCode=GetLastErrorCode();

			return(ErrorCode);
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CFunctions::FileWrite(int32 Descriptor, const uint8* Buffer, Size BufferSize, int32& NumberOfBytesWritten)
	{
#if defined(PLATFORM_WINDOWS)
		int														Result=_write(static_cast<int>(Descriptor),Buffer,static_cast<unsigned int>(BufferSize));

		if (Result!=-1)
		{
			NumberOfBytesWritten=static_cast<int32>(Result);

			return(0);
		}
		else
		{
			int32												ErrorCode=GetLastErrorCode();

			return(ErrorCode);
		}
#elif defined(PLATFORM_LINUX)
		ssize_t													Result=write(static_cast<int>(Descriptor),Buffer,static_cast<size_t>(BufferSize));

		if (Result!=-1)
		{
			NumberOfBytesWritten=static_cast<int32>(Result);

			return(0);
		}
		else
		{
			int32												ErrorCode=GetLastErrorCode();

			return(ErrorCode);
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CFunctions::FileSeek(int32 Descriptor, Size& Offset, EFileSeekOptions Direction)
	{
#if defined(PLATFORM_WINDOWS)
		long 													Result=_lseek(static_cast<int>(Descriptor),static_cast<long>(Offset),static_cast<int>(Direction));

		if (Result!=-1)
		{
			Offset=static_cast<Size>(Result);

			return(0);
		}
		else
		{
			int32												ErrorCode=GetLastErrorCode();

			return(ErrorCode);
		}
#elif defined(PLATFORM_LINUX)
		off_t 													Result=lseek(static_cast<int>(Descriptor),static_cast<off_t>(Offset),static_cast<int>(Direction));

		if (Result!=-1)
		{
			Offset=static_cast<Size>(Result);

			return(0);
		}
		else
		{
			int32												ErrorCode=GetLastErrorCode();

			return(ErrorCode);
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	uint8 CFunctions::BitReverse8(uint8 Data)
	{
	    return(static_cast<uint8>(((Data * 0x0802LU & 0x22110LU) | (Data * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint16 CFunctions::BitReverse16(uint16 Data)
	{
	    uint8													Data1=static_cast<uint8>(Data >> 8);
	    uint8													Data0=static_cast<uint8>(Data);

	    return(static_cast<uint16>((BitReverse8(Data0) << 8) | BitReverse8(Data1)));
	}
//----------------------------------------------------------------------------------------------------------------------
	uint32 CFunctions::BitReverse32(uint32 Data)
	{
	    uint8													Data3=static_cast<uint8>(Data >> 24);
	    uint8													Data2=static_cast<uint8>(Data >> 16);
	    uint8													Data1=static_cast<uint8>(Data >> 8);
	    uint8													Data0=static_cast<uint8>(Data);

	    return(static_cast<uint8>((BitReverse8(Data0) << 24) | (BitReverse8(Data1) << 16) | (BitReverse8(Data2) << 8) | BitReverse8(Data3)));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CFunctions::SetCurrentThreadName(const CString& ThreadName)
	{
#if defined(PLATFORM_WINDOWS)
		HANDLE													CurrentThread=GetCurrentThread();
		const Size												BUFFER_LENGTH=1024;
		wchar_t													ConvertedString[BUFFER_LENGTH];

		if (MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,ThreadName.GetCharArray(),-1,ConvertedString,BUFFER_LENGTH)==0)
		{
			int32												ErrorCode=GetLastErrorCode();
			CString												ErrorMessage=GetLastErrorMessage(ErrorCode);

			throw(CInvalidOperationException(CString::Format("Can't set THREAD NAME ! STRING CONVERSION FAILED ! ERROR MESSAGE [",ErrorMessage,"] !")));
		}
		
		HRESULT													Result=SetThreadDescription(CurrentThread,ConvertedString);
		
		if (FAILED(Result)==TRUE)
		{
			int32												ErrorCode=GetLastErrorCode();
			CString												ErrorMessage=GetLastErrorMessage(ErrorCode);

			throw(CInvalidOperationException(CString::Format("Can't set THREAD NAME ! ERROR MESSAGE [",ErrorMessage,"] !")));
		}
#elif defined(PLATFORM_LINUX)
		const Size												MAX_THREAD_LENGTH=15;
		pthread_t												CurrentThread=pthread_self();
		Size													Length=CMathematics::Mininum(ThreadName.GetLength(),MAX_THREAD_LENGTH);
		CString													RealThreadName=ThreadName.SubString(0,Length);
		int32													Result=static_cast<int32>(pthread_setname_np(CurrentThread,RealThreadName.GetCharArray()));

		if (Result!=0)
		{
			CString												ErrorMessage=GetLastErrorMessage(Result);

			throw(CInvalidOperationException(CString::Format("Can't set THREAD NAME ! ERROR MESSAGE [",ErrorMessage,"] !")));
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	uint32 CFunctions::GetCurrentPID(void)
	{
#if defined(PLATFORM_WINDOWS)
		uint32													PID=static_cast<uint32>(GetCurrentProcessId());

		return(PID);
#elif defined(PLATFORM_LINUX)
		uint32													PID=static_cast<uint32>(getpid());

		return(PID);
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------