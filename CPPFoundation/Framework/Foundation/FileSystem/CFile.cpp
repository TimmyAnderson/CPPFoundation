//----------------------------------------------------------------------------------------------------------------------
#include "CFile.h"
#include <Framework/Foundation/Exceptions/CFileException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Platform;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CFile::CFile(const CString& Path, EFileOpenMode OpenMode, EFileAccessMode AccessMode)
		: MFileHandle(CFileHelper::InitializeHandle())
	{
		MFileHandle=CFileHelper::Open(Path,OpenMode,AccessMode);
	}
//----------------------------------------------------------------------------------------------------------------------
	CFile::~CFile(void)
	{
		if (MFileHandle!=CFileHelper::InitializeHandle())
		{
			try
			{
				CFileHelper::Flush(MFileHandle);
			}
			catch(...)
			{
				// EXCEPTIONS are IGNORED.
			}

			try
			{
				CFileHelper::Close(MFileHandle);
			}
			catch(...)
			{
				// EXCEPTIONS are IGNORED.
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CFile::Exists(const CString& Path)
	{
		bool													FileExists=CFileHelper::Exists(Path);

		return(FileExists);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFile::Copy(const CString& SourcePath, const CString& DestinationPath)
	{
		CFileHelper::Copy(SourcePath,DestinationPath);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFile::Move(const CString& SourcePath, const CString& DestinationPath)
	{
		CFileHelper::Move(SourcePath,DestinationPath);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFile::Delete(const CString& Path)
	{
		CFileHelper::Delete(Path);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	Size CFile::Read(CByteBuffer& Buffer)
	{
		Size													NumberOfBytesRead=Read(Buffer,0,Buffer.GetLength());

		return(NumberOfBytesRead);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFile::Read(CByteBuffer& Buffer, Size Offset, Size NumberOfBytesToRead)
	{
		if (Buffer.GetLength()<(Offset+NumberOfBytesToRead))
		{
			throw(CFileException("FILE FAILED to READ ! BUFFER is too SHORT !"));
		}

		Size													NumberOfBytesRead=CFileHelper::Read(MFileHandle,Buffer,Offset,NumberOfBytesToRead);

		return(NumberOfBytesRead);
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CFile::ReadUntil(const CByteBuffer& EndSequence, bool KeepEndSequenceAtEnd, Size ReadBufferSize)
	{
		CByteBuffer												ReadBytes=CFileHelper::ReadUntil(MFileHandle,EndSequence,KeepEndSequenceAtEnd,ReadBufferSize);

		return(ReadBytes);
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CFile::ReadAll(Size BufferSize)
	{
		CByteBuffer												Buffer=CFileHelper::ReadAll(MFileHandle,BufferSize);

		return(Buffer);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFile::Write(const CByteBuffer& Buffer)
	{
		Size													NumberOfBytesWritten=Write(Buffer,0,Buffer.GetLength());

		return(NumberOfBytesWritten);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFile::Write(const CByteBuffer& Buffer, Size Offset, Size NumberOfBytesToWrite)
	{
		if (Buffer.GetLength()<(Offset+NumberOfBytesToWrite))
		{
			throw(CFileException("FILE FAILED to WRITE ! BUFFER is too SHORT !"));
		}

		Size													NumberOfBytesWritten=CFileHelper::Write(MFileHandle,Buffer,Offset,NumberOfBytesToWrite);

		return(NumberOfBytesWritten);
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CFile::Seek(int64 Offset, EFileSeekMode SeekMode)
	{
		int64													FilePosition=CFileHelper::Seek(MFileHandle,Offset,SeekMode);

		return(FilePosition);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFile::Flush(void)
	{
		CFileHelper::Flush(MFileHandle);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFile::GetSize(void)
	{
		Size													FileSize=CFileHelper::GetSize(MFileHandle);

		return(FileSize);
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime CFile::GetFileLastAccessTime(void)
	{
		CDateTime												FileLastAccessTime=CFileHelper::GetFileLastAccessTime(MFileHandle);

		return(FileLastAccessTime);
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime CFile::GetFileLastModificationTime(void)
	{
		CDateTime												FileLastModificationTime=CFileHelper::GetFileLastModificationTime(MFileHandle);

		return(FileLastModificationTime);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CFile::ReadString(Size NumberOfCharactersToRead)
	{
		CString													Buffer=CFileHelper::ReadString(MFileHandle,NumberOfCharactersToRead);

		return(Buffer);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CFile::ReadStringLine(const CString& EndOfLineSequence, bool KeepEndOfLineSequenceAtEnd, Size ReadBufferSize)
	{
		CString													Line=CFileHelper::ReadStringLine(MFileHandle,EndOfLineSequence,KeepEndOfLineSequenceAtEnd,ReadBufferSize);

		return(Line);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CFile::ReadStringAll(Size BufferSize)
	{
		CString													Buffer=CFileHelper::ReadStringAll(MFileHandle,BufferSize);

		return(Buffer);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFile::WriteString(const CString& Buffer)
	{
		Size													NumberOfCharactersWritten=CFileHelper::WriteString(MFileHandle,Buffer);

		return(NumberOfCharactersWritten);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------