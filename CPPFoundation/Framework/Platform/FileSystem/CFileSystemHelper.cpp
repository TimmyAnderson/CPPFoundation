//----------------------------------------------------------------------------------------------------------------------
#include "CFileSystemHelper.h"
#if defined(PLATFORM_WINDOWS)
#include <Shlwapi.h>
#include <chrono>
#elif defined(PLATFORM_LINUX)
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#else
#error UNSUPPORTED PLATFORM !
#endif
#include <Framework/Foundation/Exceptions/CFileException.h>
#include <Framework/Foundation/FileSystem/CFilePath.h>
#include <Framework/Foundation/Threads/CLock.h>
#include <Framework/Platform/Global/CFunctions.h>
#include <Framework/Platform/Global/Macros.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Platform
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace std::chrono;
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
	CMutex														CFileSystemHelper::MMutex;
#elif defined(PLATFORM_LINUX)
#else
#error UNSUPPORTED PLATFORM !
#endif
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CFileSystemHelper::CFileHandle CFileSystemHelper::InitializeHandle(void)
	{
#if defined(PLATFORM_WINDOWS)
		return(CFileSystemHelper::CFileHandle(INVALID_HANDLE_VALUE));
#elif defined(PLATFORM_LINUX)
		return(CFileSystemHelper::CFileHandle(-1));
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	CFileSystemHelper::CFileHandle CFileSystemHelper::OpenFile(const CString& Path, EFileOpenMode OpenMode, EFileAccessMode AccessMode)
	{
#if defined(PLATFORM_WINDOWS)
		DWORD													DesiredAccess=0;
		DWORD													ShareMode=0;
		DWORD													CreationDisposition=0;
		DWORD													FlagsAndAttributes=FILE_ATTRIBUTE_NORMAL;

		if (AccessMode==EFileAccessMode::E_READ)
		{
			DesiredAccess|=GENERIC_READ;
			ShareMode=FILE_SHARE_READ;
		}
		else if (AccessMode==EFileAccessMode::E_WRITE)
		{
			DesiredAccess|=GENERIC_WRITE;
			ShareMode=0;
		}
		else if (AccessMode==EFileAccessMode::E_READ_WRITE)
		{
			DesiredAccess|=(GENERIC_READ | GENERIC_WRITE);
			ShareMode=FILE_SHARE_READ;
		}
		else
		{
			throw(CFileException(CString::Format("FILE OPEN FAILED ! VALUE [",AccessMode,"] is an INVALID ACCESS MODE VALUE !")));
		}

		if (OpenMode==EFileOpenMode::E_CREATE)
		{
			CreationDisposition=CREATE_ALWAYS;
		}
		else if (OpenMode==EFileOpenMode::E_CREATE_NEW)
		{
			CreationDisposition=CREATE_NEW;
		}
		else if (OpenMode==EFileOpenMode::E_OPEN)
		{
			CreationDisposition=OPEN_EXISTING;
		}
		else if (OpenMode==EFileOpenMode::E_OPEN_OR_CREATE)
		{
			CreationDisposition=OPEN_ALWAYS;
		}
		else if (OpenMode==EFileOpenMode::E_OPEN_AND_TRUNCATE)
		{
			CreationDisposition=TRUNCATE_EXISTING;
		}
		else
		{
			throw(CFileException(CString::Format("FILE OPEN FAILED ! VALUE [",OpenMode,"] is an INVALID OPEN MODE VALUE !")));
		}

		CFileSystemHelper::CFileHandle							Handle=CreateFileA(Path.GetCharArray(),DesiredAccess,ShareMode,nullptr,CreationDisposition,FlagsAndAttributes,nullptr);

		if (Handle==INVALID_HANDLE_VALUE)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE OPEN FAILED !",ErrorCode));
		}

		return(Handle);
#elif defined(PLATFORM_LINUX)
		int														Flags=0;
		mode_t													Mode=0;

		if (OpenMode==EFileOpenMode::E_CREATE)
		{
			Flags|=(O_CREAT | O_TRUNC);
		}
		else if (OpenMode==EFileOpenMode::E_CREATE_NEW)
		{
			Flags|=(O_CREAT | O_EXCL);
		}
		else if (OpenMode==EFileOpenMode::E_OPEN)
		{
			Flags=0;
		}
		else if (OpenMode==EFileOpenMode::E_OPEN_OR_CREATE)
		{
			Flags|=O_CREAT;
		}
		else if (OpenMode==EFileOpenMode::E_OPEN_AND_TRUNCATE)
		{
			Flags|=O_TRUNC;
		}
		else
		{
			throw(CFileException(CString::Format("FILE OPEN FAILED ! VALUE [",OpenMode,"] is an INVALID OPEN MODE VALUE !")));
		}

		if (AccessMode==EFileAccessMode::E_READ)
		{
			Flags|=O_RDONLY;
			Mode|=(S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		}
		else if (AccessMode==EFileAccessMode::E_WRITE)
		{
			Flags|=O_WRONLY;
			Mode|=(S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		}
		else if (AccessMode==EFileAccessMode::E_READ_WRITE)
		{
			Flags|=O_RDWR;
			Mode|=(S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		}
		else
		{
			throw(CFileException(CString::Format("FILE OPEN FAILED ! VALUE [",AccessMode,"] is an INVALID ACCESS MODE VALUE !")));
		}

		CFileHandle												Handle=open(Path.GetCharArray(),Flags,Mode);

		if (Handle==-1)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE OPEN FAILED !",ErrorCode));
		}

		return(Handle);
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFileSystemHelper::CloseFile(CFileHandle FileHandle)
	{
#if defined(PLATFORM_WINDOWS)
		BOOL													Result=CloseHandle(FileHandle);

		if (Result==FALSE)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE CLOSE FAILED !",ErrorCode));
		}
#elif defined(PLATFORM_LINUX)
		int														Result=close(FileHandle);

		if (Result==-1)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE CLOSE FAILED !",ErrorCode));
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFileSystemHelper::ReadFile(CFileHandle FileHandle, uint8* Buffer, Size Offset, Size NumberOfBytesToRead)
	{
#if defined(PLATFORM_WINDOWS)
		DWORD													NumberOfBytesRead=0;
		BOOL													Result=::ReadFile(FileHandle,Buffer+Offset,static_cast<DWORD>(NumberOfBytesToRead),&NumberOfBytesRead,nullptr);

		if (Result==FALSE)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE READ FAILED !",ErrorCode));
		}

		return(static_cast<Size>(NumberOfBytesRead));
#elif defined(PLATFORM_LINUX)
		ssize_t													Result=read(FileHandle,Buffer+Offset,static_cast<size_t>(NumberOfBytesToRead));

		if (Result==-1)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE READ FAILED !",ErrorCode));
		}

		return(static_cast<Size>(Result));
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFileSystemHelper::WriteFile(CFileHandle FileHandle, const uint8* Buffer, Size Offset, Size NumberOfBytesToWrite)
	{
#if defined(PLATFORM_WINDOWS)
		DWORD													NumberOfBytesWritten=0;
		BOOL													Result=::WriteFile(FileHandle,Buffer+Offset,static_cast<DWORD>(NumberOfBytesToWrite),&NumberOfBytesWritten,nullptr);

		if (Result==FALSE)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE WRITE FAILED !",ErrorCode));
		}

		return(static_cast<Size>(NumberOfBytesWritten));
#elif defined(PLATFORM_LINUX)
		ssize_t													Result=write(FileHandle,Buffer+Offset,static_cast<size_t>(NumberOfBytesToWrite));

		if (Result==-1)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE WRITE FAILED !",ErrorCode));
		}

		return(static_cast<Size>(Result));
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CFileSystemHelper::SeekFile(CFileHandle FileHandle, int64 Offset, EFileSeekMode SeekMode)
	{
#if defined(PLATFORM_WINDOWS)
		LARGE_INTEGER											DistanceToMove;
		LARGE_INTEGER											NewFilePointer;
		DWORD													MoveMethod;

		DistanceToMove.QuadPart=static_cast<LONGLONG>(Offset);
		NewFilePointer.QuadPart=0;

		if (SeekMode==EFileSeekMode::E_BEGIN)
		{
			MoveMethod=FILE_BEGIN;
		}
		else if (SeekMode==EFileSeekMode::E_CURRENT)
		{
			MoveMethod=FILE_CURRENT;
		}
		else if (SeekMode==EFileSeekMode::E_END)
		{
			MoveMethod=FILE_END;
		}
		else
		{
			throw(CFileException(CString::Format("FILE SEEK FAILED ! VALUE [",SeekMode,"] is an INVALID SEEK MODE VALUE !")));
		}

		BOOL													Result=SetFilePointerEx(FileHandle,DistanceToMove,&NewFilePointer,MoveMethod);

		if (Result==FALSE)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE SEEK FAILED !",ErrorCode));
		}

		return(static_cast<int64>(NewFilePointer.QuadPart));
#elif defined(PLATFORM_LINUX)
		int														Whence;

		if (SeekMode==EFileSeekMode::E_BEGIN)
		{
			Whence=SEEK_SET;
		}
		else if (SeekMode==EFileSeekMode::E_CURRENT)
		{
			Whence=SEEK_CUR;
		}
		else if (SeekMode==EFileSeekMode::E_END)
		{
			Whence=SEEK_END;
		}
		else
		{
			throw(CFileException(CString::Format("FILE SEEK FAILED ! VALUE [",SeekMode,"] is an INVALID SEEK MODE VALUE !")));
		}

		off_t													Result=lseek(FileHandle,static_cast<off_t>(Offset),Whence);

		if (Result==static_cast<off_t>(-1))
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE SEEK FAILED !",ErrorCode));
		}

		return(static_cast<int64>(Result));
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFileSystemHelper::FlushFile(CFileHandle FileHandle)
	{
#if defined(PLATFORM_WINDOWS)
		BOOL													Result=FlushFileBuffers(FileHandle);

		if (Result==FALSE)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE FLUSH FAILED !",ErrorCode));
		}
#elif defined(PLATFORM_LINUX)
		int														Result=fsync(FileHandle);

		if (Result==-1)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE FLUSH FAILED !",ErrorCode));
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFileSystemHelper::GetFileSize(CFileHandle FileHandle)
	{
#if defined(PLATFORM_WINDOWS)
		LARGE_INTEGER											FileSize{0};
		BOOL													Result=GetFileSizeEx(FileHandle,&FileSize);

		if (Result==FALSE)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE GET SIZE FAILED !",ErrorCode));
		}

		return(static_cast<Size>(FileSize.QuadPart));
#elif defined(PLATFORM_LINUX)
		struct stat												Statistics;
		int														Result=fstat(FileHandle,&Statistics);

		if (Result==-1)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE GET SIZE FAILED !",ErrorCode));
		}

		return(static_cast<Size>(Statistics.st_size));
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime CFileSystemHelper::GetFileLastAccessTime(CFileHandle FileHandle)
	{
#if defined(PLATFORM_WINDOWS)
		FILETIME												FileTimeLastAccessTime;
		BOOL													ResultGetFileTime=GetFileTime(FileHandle,nullptr,&FileTimeLastAccessTime,nullptr);

		if (ResultGetFileTime==FALSE)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE GET LAST ACCESS TIME FAILED !",ErrorCode));
		}

		SYSTEMTIME												SystemTimeLastAccessTime;
		BOOL													ResultFileTimeToSystemTime=FileTimeToSystemTime(&FileTimeLastAccessTime,&SystemTimeLastAccessTime);

		if (ResultFileTimeToSystemTime==FALSE)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE GET LAST ACCESS TIME FAILED to CONVERT TIME to SYSTEM TIME !",ErrorCode));
		}

		GetLocalTime(&SystemTimeLastAccessTime);

		try
		{
			CDateTime											Time(SystemTimeLastAccessTime.wYear,SystemTimeLastAccessTime.wMonth,SystemTimeLastAccessTime.wDay,SystemTimeLastAccessTime.wHour,SystemTimeLastAccessTime.wMinute,SystemTimeLastAccessTime.wSecond,SystemTimeLastAccessTime.wMilliseconds);

			return(Time);
		}
		catch(...)
		{
			throw(CFileException("FILE GET LAST ACCESS TIME FAILED to CONVERT TIME !"));
		}
#elif defined(PLATFORM_LINUX)
		struct stat												Statistics;
		int														Result=fstat(FileHandle,&Statistics);

		if (Result==-1)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE GET LAST ACCESS TIME FAILED !",ErrorCode));
		}

		// EPOCH TIME is NOT DEFINED by the C++ STANDARD but ALL IMPLEMENTATIONS use LINUX TIME.
		CDateTime												Time(1970,1,1,0,0,0,0);
		system_clock::time_point								TimePoint=system_clock::from_time_t(Statistics.st_atime);
		system_clock::time_point::duration						TimeSinceEpoch=TimePoint.time_since_epoch();
		milliseconds											MillisecondsSinceEpoch=duration_cast<milliseconds>(TimeSinceEpoch);
		
		Time.AddMilliseconds(static_cast<int64>(MillisecondsSinceEpoch.count()));

		return(Time);
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime CFileSystemHelper::GetFileLastModificationTime(CFileHandle FileHandle)
	{
#if defined(PLATFORM_WINDOWS)
		FILETIME												FileTimeLastModificationTime;
		BOOL													ResultGetFileTime=GetFileTime(FileHandle,nullptr,nullptr,&FileTimeLastModificationTime);

		if (ResultGetFileTime==FALSE)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE GET LAST MODIFICATION TIME FAILED !",ErrorCode));
		}

		SYSTEMTIME												SystemTimeLastModificationTime;
		BOOL													ResultFileTimeToSystemTime=FileTimeToSystemTime(&FileTimeLastModificationTime,&SystemTimeLastModificationTime);

		if (ResultFileTimeToSystemTime==FALSE)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE GET LAST MODIFICATION TIME FAILED to CONVERT TIME to SYSTEM TIME !",ErrorCode));
		}

		GetLocalTime(&SystemTimeLastModificationTime);

		try
		{
			CDateTime											Time(SystemTimeLastModificationTime.wYear,SystemTimeLastModificationTime.wMonth,SystemTimeLastModificationTime.wDay,SystemTimeLastModificationTime.wHour,SystemTimeLastModificationTime.wMinute,SystemTimeLastModificationTime.wSecond,SystemTimeLastModificationTime.wMilliseconds);

			return(Time);
		}
		catch(...)
		{
			throw(CFileException("FILE GET LAST MODIFICATION TIME FAILED to CONVERT TIME !"));
		}
#elif defined(PLATFORM_LINUX)
		struct stat												Statistics;
		int														Result=fstat(FileHandle,&Statistics);

		if (Result==-1)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE GET LAST MODIFICATION TIME FAILED !",ErrorCode));
		}

		// EPOCH TIME is NOT DEFINED by the C++ STANDARD but ALL IMPLEMENTATIONS use LINUX TIME.
		CDateTime												Time(1970,1,1,0,0,0,0);
		system_clock::time_point								TimePoint=system_clock::from_time_t(Statistics.st_mtime);
		system_clock::time_point::duration						TimeSinceEpoch=TimePoint.time_since_epoch();
		milliseconds											MillisecondsSinceEpoch=duration_cast<milliseconds>(TimeSinceEpoch);
		
		Time.AddMilliseconds(static_cast<int64>(MillisecondsSinceEpoch.count()));

		return(Time);
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CFileSystemHelper::FileExists(const CString& Path)
	{
#if defined(PLATFORM_WINDOWS)
		BOOL													Result=PathFileExistsA(Path.GetCharArray());

		if (Result==TRUE)
		{
			return(true);
		}
		else
		{
			return(false);
		}
#elif defined(PLATFORM_LINUX)
		struct stat												Statistics;
		int														Result=stat(Path.GetCharArray(),&Statistics);

		if (Result!=-1)
		{
			return(true);
		}
		else
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			if (ErrorCode==ENOENT)
			{
				return(false);
			}
			else
			{
				throw(CFileException("FILE EXISTS FAILED !",ErrorCode));
			}
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFileSystemHelper::CopyFile(const CString& SourcePath, const CString& DestinationPath)
	{
#if defined(PLATFORM_WINDOWS)
		BOOL													Result=CopyFileA(SourcePath.GetCharArray(),DestinationPath.GetCharArray(),FALSE);

		if (Result==FALSE)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE COPY FAILED !",ErrorCode));
		}
#elif defined(PLATFORM_LINUX)
		CFileHandle												SourceHandle=InitializeHandle();
		CFileHandle												DestinationHandle=InitializeHandle();

		try
		{
			SourceHandle=OpenFile(SourcePath,EFileOpenMode::E_OPEN,EFileAccessMode::E_READ);
			DestinationHandle=OpenFile(DestinationPath,EFileOpenMode::E_CREATE,EFileAccessMode::E_WRITE);

			off_t												SourceFileLength=static_cast<off_t>(GetFileSize(SourceHandle));
			off_t												NumberOfBytesTransferred=0;

			while(NumberOfBytesTransferred<SourceFileLength)
			{
				size_t											NumberOfBytesToTransfer;
				off_t											NumberOfRemainingBytesToTransfer=(SourceFileLength-NumberOfBytesTransferred);

				if (NumberOfRemainingBytesToTransfer<=SSIZE_MAX)
				{
					NumberOfBytesToTransfer=static_cast<size_t>(NumberOfRemainingBytesToTransfer);
				}
				else
				{
					NumberOfBytesToTransfer=static_cast<size_t>(SSIZE_MAX);
				}

				ssize_t											Result=sendfile(DestinationHandle,SourceHandle,&NumberOfBytesTransferred,NumberOfBytesToTransfer);

				if (Result==-1)
				{
					int32										ErrorCode=CFunctions::GetLastErrorCode();

					throw(CFileException("FILE COPY FAILED !",ErrorCode));
				}
			}

			FlushFile(DestinationHandle);

			CloseFile(SourceHandle);
			CloseFile(DestinationHandle);
		}
		catch(...)
		{
			try
			{
				CloseFile(SourceHandle);
			}
			catch(...)
			{
			}

			try
			{
				CloseFile(DestinationHandle);
			}
			catch(...)
			{
			}

			try
			{
				DeleteFile(DestinationPath);
			}
			catch(...)
			{
			}

			throw;
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFileSystemHelper::MoveFile(const CString& SourcePath, const CString& DestinationPath)
	{
#if defined(PLATFORM_WINDOWS)
		BOOL													Result=MoveFileA(SourcePath.GetCharArray(),DestinationPath.GetCharArray());

		if (Result==FALSE)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE COPY FAILED !",ErrorCode));
		}
#elif defined(PLATFORM_LINUX)
		CFileHandle												SourceHandle=InitializeHandle();
		CFileHandle												DestinationHandle=InitializeHandle();

		try
		{
			SourceHandle=OpenFile(SourcePath,EFileOpenMode::E_OPEN,EFileAccessMode::E_READ);
			DestinationHandle=OpenFile(DestinationPath,EFileOpenMode::E_CREATE,EFileAccessMode::E_WRITE);

			off_t												SourceFileLength=static_cast<off_t>(GetFileSize(SourceHandle));
			off_t												NumberOfBytesTransferred=0;

			while(NumberOfBytesTransferred<SourceFileLength)
			{
				size_t											NumberOfBytesToTransfer;
				off_t											NumberOfRemainingBytesToTransfer=(SourceFileLength-NumberOfBytesTransferred);

				if (NumberOfRemainingBytesToTransfer<=SSIZE_MAX)
				{
					NumberOfBytesToTransfer=static_cast<size_t>(NumberOfRemainingBytesToTransfer);
				}
				else
				{
					NumberOfBytesToTransfer=static_cast<size_t>(SSIZE_MAX);
				}

				ssize_t											Result=sendfile(DestinationHandle,SourceHandle,&NumberOfBytesTransferred,NumberOfBytesToTransfer);

				if (Result==-1)
				{
					int32										ErrorCode=CFunctions::GetLastErrorCode();

					throw(CFileException("FILE COPY FAILED !",ErrorCode));
				}
			}

			FlushFile(DestinationHandle);

			CloseFile(SourceHandle);
			CloseFile(DestinationHandle);

			DeleteFile(SourcePath);
		}
		catch(...)
		{
			try
			{
				CloseFile(SourceHandle);
			}
			catch(...)
			{
			}

			try
			{
				CloseFile(DestinationHandle);
			}
			catch(...)
			{
			}

			try
			{
				DeleteFile(DestinationPath);
			}
			catch(...)
			{
			}

			throw;
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFileSystemHelper::DeleteFile(const CString& Path)
	{
#if defined(PLATFORM_WINDOWS)
		BOOL													Result=DeleteFileA(Path.GetCharArray());

		if (Result==FALSE)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE DELETE FAILED !",ErrorCode));
		}
#elif defined(PLATFORM_LINUX)
		int														Result=unlink(Path.GetCharArray());

		if (Result==-1)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("FILE DELETE FAILED !",ErrorCode));
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CFileSystemHelper::CreateDirectory(const CString& DirectoryName)
	{
#if defined(PLATFORM_WINDOWS)
		BOOL													Result=CreateDirectoryA(DirectoryName.GetCharArray(),nullptr);

		if (Result==FALSE)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("DIRECTORY CREATE FAILED !",ErrorCode));
		}
#elif defined(PLATFORM_LINUX)
		int														Result=mkdir(DirectoryName.GetCharArray(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

		if (Result==-1)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("DIRECTORY CREATE FAILED !",ErrorCode));
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFileSystemHelper::RemoveDirectory(const CString& DirectoryName)
	{
#if defined(PLATFORM_WINDOWS)
		BOOL													Result=RemoveDirectoryA(DirectoryName.GetCharArray());

		if (Result==FALSE)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("DIRECTORY REMOVE FAILED !",ErrorCode));
		}
#elif defined(PLATFORM_LINUX)
		int														Result=rmdir(DirectoryName.GetCharArray());

		if (Result==-1)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("DIRECTORY REMOVE FAILED !",ErrorCode));
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CCSPDirectoryEntry> CFileSystemHelper::GetDirectoryEntries(const CString& DirectoryName)
	{
		CVector<CCSPDirectoryEntry>								DirectoryEntries;
		
#if defined(PLATFORM_WINDOWS)
		CPath													Path(DirectoryName);

		Path/="*";

		WIN32_FIND_DATAA										DirectoryEntry;
		HANDLE													Handle=FindFirstFileA(Path.GetPath().GetCharArray(),&DirectoryEntry);

		if (Handle!=INVALID_HANDLE_VALUE)
		{
			while(true)
			{
				EDirectoryEntryType								EntryType=((DirectoryEntry.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)!=0) ? EDirectoryEntryType::E_DIRECTORY : EDirectoryEntryType::E_FILE;
				CCSPDirectoryEntry								Entry(new CDirectoryEntry(CString(DirectoryEntry.cFileName),EntryType));

				DirectoryEntries.Add(Entry);

				if (FindNextFileA(Handle,&DirectoryEntry)==FALSE)
				{
					int32										ErrorCode=CFunctions::GetLastErrorCode();

					if (ErrorCode==ERROR_NO_MORE_FILES)
					{
						break;
					}
					else
					{
						throw(CFileException("DIRECTORY READ FAILED !",ErrorCode));
					}
				}
			}

			if (FindClose(Handle)==FALSE)
			{
				int32											ErrorCode=CFunctions::GetLastErrorCode();

				throw(CFileException("DIRECTORY CLOSE FAILED !",ErrorCode));
			}
		}
		else
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			if (ErrorCode!=ERROR_FILE_NOT_FOUND)
			{
				throw(CFileException("DIRECTORY OPEN FAILED !",ErrorCode));
			}
		}
#elif defined(PLATFORM_LINUX)
		DIR*													Handle=opendir(DirectoryName.GetCharArray());

		if (Handle!=nullptr)
		{
			while(true)
			{
				errno=0;

				struct dirent*									DirectoryEntry=readdir(Handle);

				if (DirectoryEntry!=nullptr)
				{
					EDirectoryEntryType							EntryType=(DirectoryEntry->d_type==DT_DIR) ? EDirectoryEntryType::E_DIRECTORY : EDirectoryEntryType::E_FILE;
					CCSPDirectoryEntry							Entry(new CDirectoryEntry(CString(DirectoryEntry->d_name),EntryType));

					DirectoryEntries.Add(Entry);
				}
				else
				{
					int32										ErrorCode=CFunctions::GetLastErrorCode();
					
					if (ErrorCode==0)
					{
						break;
					}
					else
					{
						closedir(Handle);

						throw(CFileException("DIRECTORY READ FAILED !",ErrorCode));
					}
				}
			}

			if (closedir(Handle)==-1)
			{
				int32											ErrorCode=CFunctions::GetLastErrorCode();

				throw(CFileException("DIRECTORY CLOSE FAILED !",ErrorCode));
			}
		}
		else
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("DIRECTORY OPEN FAILED !",ErrorCode));
		}
#else
#error UNSUPPORTED PLATFORM !
#endif

		return(DirectoryEntries);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CFileSystemHelper::GetCurrentDirectory(void)
	{
#if defined(PLATFORM_WINDOWS)
		// FUNCTION GetCurrentDirectoryA() is NOT THREAD SAFE.
		CLock													Lock(MMutex);
		{
			char												Buffer[1024+1];
			BOOL												Result=GetCurrentDirectoryA(sizeof(Buffer),Buffer);

			if (Result!=FALSE)
			{
				CString											CurrentDirectory(Buffer);

				return(CurrentDirectory);
			}
			else
			{
				int32											ErrorCode=CFunctions::GetLastErrorCode();

				throw(CFileException("DIRECTORY GET FAILED !",ErrorCode));
			}
		}
#elif defined(PLATFORM_LINUX)
		char													Buffer[1024+1];
		char*													Result=getcwd(Buffer,sizeof(Buffer));

		if (Result!=nullptr)
		{
			CString												CurrentDirectory(Buffer);

			return(CurrentDirectory);
		}
		else
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("DIRECTORY GET FAILED !",ErrorCode));
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFileSystemHelper::SetCurrentDirectory(const CString& DirectoryName)
	{
#if defined(PLATFORM_WINDOWS)
		// FUNCTION SetCurrentDirectoryA() is NOT THREAD SAFE.
		CLock													Lock(MMutex);
		{
			BOOL												Result=SetCurrentDirectoryA(DirectoryName.GetCharArray());

			if (Result==FALSE)
			{
				int32											ErrorCode=CFunctions::GetLastErrorCode();

				throw(CFileException("DIRECTORY SET FAILED !",ErrorCode));
			}
		}
#elif defined(PLATFORM_LINUX)
		int														Result=chdir(DirectoryName.GetCharArray());

		if (Result==-1)
		{
			int32												ErrorCode=CFunctions::GetLastErrorCode();

			throw(CFileException("DIRECTORY SET FAILED !",ErrorCode));
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------