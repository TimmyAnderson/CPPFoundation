//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CByteBuffer.h>
#include <Framework/Platform/FileSystem/CFileSystemHelper.h>
#include <Framework/Platform/Global/CConstants.h>
#include "EFileAccessMode.h"
#include "EFileOpenMode.h"
#include "EFileSeekMode.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CFileHelper final
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			static CPPFoundation::Platform::CFileSystemHelper::CFileHandle InitializeHandle(void);
			static CPPFoundation::Platform::CFileSystemHelper::CFileHandle Open(const CString& Path, EFileOpenMode OpenMode, EFileAccessMode AccessMode);
			static void Close(CPPFoundation::Platform::CFileSystemHelper::CFileHandle FileHandle);
			static Size Read(CPPFoundation::Platform::CFileSystemHelper::CFileHandle FileHandle, CByteBuffer& Buffer, Size Offset, Size NumberOfBytesToRead);
			static CByteBuffer ReadUntil(CPPFoundation::Platform::CFileSystemHelper::CFileHandle FileHandle, const CByteBuffer& EndSequence, bool KeepEndSequenceAtEnd, Size ReadBufferSize=128);
			static CByteBuffer ReadAll(CPPFoundation::Platform::CFileSystemHelper::CFileHandle FileHandle, Size BufferSize=512);
			static Size Write(CPPFoundation::Platform::CFileSystemHelper::CFileHandle FileHandle, const CByteBuffer& Buffer, Size Offset, Size NumberOfBytesToWrite);
			static int64 Seek(CPPFoundation::Platform::CFileSystemHelper::CFileHandle FileHandle, int64 Offset, EFileSeekMode SeekMode);
			static void Flush(CPPFoundation::Platform::CFileSystemHelper::CFileHandle FileHandle);
			static Size GetSize(CPPFoundation::Platform::CFileSystemHelper::CFileHandle FileHandle);
			static CDateTime GetFileLastAccessTime(CPPFoundation::Platform::CFileSystemHelper::CFileHandle FileHandle);
			static CDateTime GetFileLastModificationTime(CPPFoundation::Platform::CFileSystemHelper::CFileHandle FileHandle);

		public:
			static CString ReadString(CPPFoundation::Platform::CFileSystemHelper::CFileHandle FileHandle, Size NumberOfCharactersToRead);
			static CString ReadStringLine(CPPFoundation::Platform::CFileSystemHelper::CFileHandle FileHandle, const CString& EndOfLineSequence=CPPFoundation::Platform::CConstants::END_LINE, bool KeepEndOfLineSequenceAtEnd=false, Size ReadBufferSize=128);
			static CString ReadStringAll(CPPFoundation::Platform::CFileSystemHelper::CFileHandle FileHandle, Size BufferSize=512);
			static Size WriteString(CPPFoundation::Platform::CFileSystemHelper::CFileHandle FileHandle, const CString& Buffer);

		public:
			static bool Exists(const CString& Path);
			static void Copy(const CString& SourcePath, const CString& DestinationPath);
			static void Move(const CString& SourcePath, const CString& DestinationPath);
			static void Delete(const CString& Path);
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------