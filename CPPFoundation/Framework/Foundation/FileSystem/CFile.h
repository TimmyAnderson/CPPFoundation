//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CFileHelper.h"
#include "CFilePath.h"
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
	class CFile final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												CFileHandle=CPPFoundation::Platform::CFileSystemHelper::CFileHandle;

		private:
			CFileHandle											MFileHandle;

		public:
			static bool Exists(const CString& Path);
			static void Copy(const CString& SourcePath, const CString& DestinationPath);
			static void Move(const CString& SourcePath, const CString& DestinationPath);
			static void Delete(const CString& Path);

		public:
			// The BUFFER must be set to NUMBER of BYTES that should be READ.
			Size Read(CByteBuffer& Buffer);
			Size Read(CByteBuffer& Buffer, Size Offset, Size NumberOfBytesToRead);
			// READS FILE until the END SEQUENCE is FOUND or the END OF FILE is REACHED.
			CByteBuffer ReadUntil(const CByteBuffer& EndSequence, bool KeepEndSequenceAtEnd, Size BufferSize=128);
			CByteBuffer ReadAll(Size BufferSize=512);
			Size Write(const CByteBuffer& Buffer);
			Size Write(const CByteBuffer& Buffer, Size Offset, Size NumberOfBytesToWrite);
			int64 Seek(int64 Offset, EFileSeekMode SeekMode);
			void Flush(void);
			Size GetSize(void);
			CDateTime GetFileLastAccessTime(void);
			CDateTime GetFileLastModificationTime(void);

		public:
			CString ReadString(Size NumberOfCharactersToRead);
			CString ReadStringLine(const CString& EndOfLineSequence=CPPFoundation::Platform::CConstants::END_LINE, bool KeepEndOfLineSequenceAtEnd=false, Size ReadBufferSize=128);
			CString ReadStringAll(Size BufferSize=512);
			Size WriteString(const CString& Buffer);

		public:
			CFile(const CString& Path, EFileOpenMode OpenMode, EFileAccessMode AccessMode);
			virtual ~CFile(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPFile=CPPFoundation::Foundation::CSharedPointer<CFile>;
	using														CCSPFile=CPPFoundation::Foundation::CSharedPointer<const CFile>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------