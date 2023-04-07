//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
#include <winsock2.h>
#include <Windows.h>
#elif defined(PLATFORM_LINUX)
#else
#error UNSUPPORTED PLATFORM !
#endif
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/FileSystem/CDirectoryEntry.h>
#include <Framework/Foundation/FileSystem/CFilePathTraitsLinux.h>
#include <Framework/Foundation/FileSystem/CFilePathTraitsWindows.h>
#include <Framework/Foundation/FileSystem/EFileAccessMode.h>
#include <Framework/Foundation/FileSystem/EFileOpenMode.h>
#include <Framework/Foundation/FileSystem/EFileSeekMode.h>
#include <Framework/Foundation/Time/CDateTime.h>
#include <Framework/Foundation/Threads/CMutex.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Platform
{
//----------------------------------------------------------------------------------------------------------------------
	class CFileSystemHelper final
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
#if defined(PLATFORM_WINDOWS)
			using												CFilePathTraits=CPPFoundation::Foundation::CFilePathTraitsWindows;
			using												CFileHandle=HANDLE;
#elif defined(PLATFORM_LINUX)
			using												CFilePathTraits=CPPFoundation::Foundation::CFilePathTraitsLinux;
			using												CFileHandle=int;
#else
#error UNSUPPORTED PLATFORM !
#endif

#if defined(PLATFORM_WINDOWS)
		private:
			static CPPFoundation::Foundation::CMutex				MMutex;
#elif defined(PLATFORM_LINUX)
#else
#error UNSUPPORTED PLATFORM !
#endif

		public:
			static CFileHandle InitializeHandle(void);
			static CFileHandle OpenFile(const CPPFoundation::Foundation::CString& Path, CPPFoundation::Foundation::EFileOpenMode OpenMode, CPPFoundation::Foundation::EFileAccessMode AccessMode);
			static void CloseFile(CFileHandle FileHandle);
			static Size ReadFile(CFileHandle FileHandle, uint8* Buffer, Size Offset, Size NumberOfBytesToRead);
			static Size WriteFile(CFileHandle FileHandle, const uint8* Buffer, Size Offset, Size NumberOfBytesToWrite);
			static int64 SeekFile(CFileHandle FileHandle, int64 Offset, CPPFoundation::Foundation::EFileSeekMode SeekMode);
			static void FlushFile(CFileHandle FileHandle);
			static Size GetFileSize(CFileHandle FileHandle);
			static CPPFoundation::Foundation::CDateTime GetFileLastAccessTime(CFileHandle FileHandle);
			static CPPFoundation::Foundation::CDateTime GetFileLastModificationTime(CFileHandle FileHandle);

		public:
			static bool FileExists(const CPPFoundation::Foundation::CString& Path);
			static void CopyFile(const CPPFoundation::Foundation::CString& SourcePath, const CPPFoundation::Foundation::CString& DestinationPath);
			static void MoveFile(const CPPFoundation::Foundation::CString& SourcePath, const CPPFoundation::Foundation::CString& DestinationPath);
			static void DeleteFile(const CPPFoundation::Foundation::CString& Path);

		public:
			static void CreateDirectory(const CPPFoundation::Foundation::CString& DirectoryName);
			static void RemoveDirectory(const CPPFoundation::Foundation::CString& DirectoryName);
			static CPPFoundation::Foundation::CVector<CPPFoundation::Foundation::CCSPDirectoryEntry> GetDirectoryEntries(const CPPFoundation::Foundation::CString& DirectoryName);
			static CPPFoundation::Foundation::CString GetCurrentDirectory(void);
			static void SetCurrentDirectory(const CPPFoundation::Foundation::CString& DirectoryName);
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------