//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ctime>
#include <thread>
#include <Framework/Foundation/Types/Types.h>
#include <Framework/Foundation/Time/CTimePoint.h>
#include <Framework/Foundation/Time/CTimeout.h>
#include <Framework/Foundation/Strings/CString.h>
#include "EFileOpenFlags.h"
#include "EFileSeekOptions.h"
#include "Macros.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct in_addr;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Platform
{
//----------------------------------------------------------------------------------------------------------------------
	class CFunctions final
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			static CPPFoundation::Foundation::CString GetDemangledName(const char* Name);

		public:
			static void MainInit(void);
			static void ClearScreen(void);
			static void InitializeConsole(bool EnableAnsiSequences);
			static bool IsDaylightSavingTime(std::time_t Time);
			static int32 GetLocalTimeOffsetInSeconds(std::time_t Time);
			static float64 Floor(float64 Value);
			static float64 Ceil(float64 Value);

		public:
			static int32 GetLastErrorCode(void);
			static CPPFoundation::Foundation::CString GetLastErrorMessage(int32 ErrorCode);

		public:
			static int32 FileOpen(int32& Descriptor, const char* Name, EFileOpenFlags Flags);
			static int32 FileClose(int32 Descriptor);
			static int32 FileRead(int32 Descriptor, uint8* Buffer, Size BufferSize, int32& NumberOfBytesRead);
			static int32 FileWrite(int32 Descriptor, const uint8* Buffer, Size BufferSize, int32& NumberOfBytesWritten);
			static int32 FileSeek(int32 Descriptor, Size& Offset, EFileSeekOptions Direction);

		public:
		    static uint8 BitReverse8(uint8 Data);
		    static uint16 BitReverse16(uint16 Data);
		    static uint32 BitReverse32(uint32 Data);

		public:
			static void SetCurrentThreadName(const CPPFoundation::Foundation::CString& ThreadName);

		public:
			static uint32 GetCurrentPID(void);
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------