//----------------------------------------------------------------------------------------------------------------------
#include "CFileHelper.h"
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
	CFileSystemHelper::CFileHandle CFileHelper::InitializeHandle(void)
	{
		return(CFileSystemHelper::InitializeHandle());
	}
//----------------------------------------------------------------------------------------------------------------------
	CFileSystemHelper::CFileHandle CFileHelper::Open(const CString& Path, EFileOpenMode OpenMode, EFileAccessMode AccessMode)
	{
		CFileSystemHelper::CFileHandle							FileHandle=CFileSystemHelper::OpenFile(Path,OpenMode,AccessMode);

		return(FileHandle);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFileHelper::Close(CFileSystemHelper::CFileHandle FileHandle)
	{
		CFileSystemHelper::CloseFile(FileHandle);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFileHelper::Read(CFileSystemHelper::CFileHandle FileHandle, CByteBuffer& Buffer, Size Offset, Size NumberOfBytesToRead)
	{
		if (Buffer.GetLength()<(Offset+NumberOfBytesToRead))
		{
			throw(CFileException("FILE FAILED to READ ! BUFFER is too SHORT !"));
		}

		Size													NumberOfBytesRead=CFileSystemHelper::ReadFile(FileHandle,Buffer.GetRawData(),Offset,NumberOfBytesToRead);

		return(NumberOfBytesRead);
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CFileHelper::ReadUntil(CFileSystemHelper::CFileHandle FileHandle, const CByteBuffer& EndSequence, bool KeepEndSequenceAtEnd, Size ReadBufferSize)
	{
		CByteBuffer												ReadBuffer(ReadBufferSize);
		CByteBuffer												ReadBytes;

		if (EndSequence.GetLength()>0)
		{
			Size												EndSequencePosition=0;
		
			while(true)
			{
				Size											NumberOfBytesRead=Read(FileHandle,ReadBuffer,0,ReadBuffer.GetLength());

				if (NumberOfBytesRead>0)
				{
					for(Size Index=0;Index<NumberOfBytesRead;Index++)
					{
						uint8									Value=ReadBuffer[Index];
						uint8									EndSequenceValue=EndSequence[EndSequencePosition];

						ReadBytes.Add(Value);

						if (Value==EndSequenceValue)
						{
							EndSequencePosition++;

							if (EndSequencePosition==EndSequence.GetLength())
							{
								Seek(FileHandle,1+(Index-NumberOfBytesRead),EFileSeekMode::E_CURRENT);

								if (KeepEndSequenceAtEnd==false)
								{
									ReadBytes.Resize(ReadBytes.GetLength()-EndSequence.GetLength());
								}

								return(ReadBytes);
							}
						}
						else
						{
							EndSequencePosition=0;
						}
					}
				}
				else
				{
					break;
				}
			}
		}

		return(ReadBytes);
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CFileHelper::ReadAll(CFileSystemHelper::CFileHandle FileHandle, Size BufferSize)
	{
		Size													FileSize=GetSize(FileHandle);
		CByteBuffer												Buffer;
		CByteBuffer												ReadBuffer(BufferSize);

		while(true)
		{
			Size												NumberOfBytesRead=Read(FileHandle,ReadBuffer,0,BufferSize);

			if (NumberOfBytesRead>0)
			{
				Buffer.Add(ReadBuffer.GetRawData(),NumberOfBytesRead);
			}
			else
			{
				break;
			}
		}

		if (Buffer.GetLength()!=FileSize)
		{
			throw(CFileException("FILE FAILED to READ ! NOT ALL BYTES were READ !"));
		}

		return(Buffer);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFileHelper::Write(CFileSystemHelper::CFileHandle FileHandle, const CByteBuffer& Buffer, Size Offset, Size NumberOfBytesToWrite)
	{
		if (Buffer.GetLength()<(Offset+NumberOfBytesToWrite))
		{
			throw(CFileException("FILE FAILED to WRITE ! BUFFER is too SHORT !"));
		}

		Size													NumberOfBytesWritten=CFileSystemHelper::WriteFile(FileHandle,Buffer.GetRawData(),Offset,NumberOfBytesToWrite);

		return(NumberOfBytesWritten);
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CFileHelper::Seek(CFileSystemHelper::CFileHandle FileHandle, int64 Offset, EFileSeekMode SeekMode)
	{
		int64													FilePosition=CFileSystemHelper::SeekFile(FileHandle,Offset,SeekMode);

		return(FilePosition);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFileHelper::Flush(CFileSystemHelper::CFileHandle FileHandle)
	{
		CFileSystemHelper::FlushFile(FileHandle);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFileHelper::GetSize(CFileSystemHelper::CFileHandle FileHandle)
	{
		Size													FileSize=CFileSystemHelper::GetFileSize(FileHandle);

		return(FileSize);
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime CFileHelper::GetFileLastAccessTime(CFileSystemHelper::CFileHandle FileHandle)
	{
		return(CFileSystemHelper::GetFileLastAccessTime(FileHandle));
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime CFileHelper::GetFileLastModificationTime(CFileSystemHelper::CFileHandle FileHandle)
	{
		return(CFileSystemHelper::GetFileLastModificationTime(FileHandle));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CFileHelper::ReadString(CFileSystemHelper::CFileHandle FileHandle, Size NumberOfCharactersToRead)
	{
		CByteBuffer												ByteBuffer(NumberOfCharactersToRead);
		Size													NumberOfCharactersRead=CFileSystemHelper::ReadFile(FileHandle,ByteBuffer.GetRawData(),0,NumberOfCharactersToRead);

		ByteBuffer.Resize(NumberOfCharactersRead);

		CString													Buffer(ByteBuffer);

		return(Buffer);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CFileHelper::ReadStringLine(CFileSystemHelper::CFileHandle FileHandle, const CString& EndOfLineSequence, bool KeepOfEndLineSequenceAtEnd, Size ReadBufferSize)
	{
		CByteBuffer												EndSequence=EndOfLineSequence.GetByteBuffer();
		CByteBuffer												ReadBytes=ReadUntil(FileHandle,EndSequence,KeepOfEndLineSequenceAtEnd,ReadBufferSize);
		CString													Line(reinterpret_cast<const Char*>(ReadBytes.GetRawData()),ReadBytes.GetLength());

		return(Line);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CFileHelper::ReadStringAll(CFileSystemHelper::CFileHandle FileHandle, Size BufferSize)
	{
		CByteBuffer												ByteBuffer=ReadAll(FileHandle,BufferSize);
		CString													Buffer(reinterpret_cast<const Char*>(ByteBuffer.GetRawData()),ByteBuffer.GetLength());

		return(Buffer);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFileHelper::WriteString(CFileSystemHelper::CFileHandle FileHandle, const CString& Buffer)
	{
		Size													NumberOfCharactersWritten=CFileSystemHelper::WriteFile(FileHandle,reinterpret_cast<const uint8*>(Buffer.GetCharArray()),0,Buffer.GetLength());

		return(NumberOfCharactersWritten);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CFileHelper::Exists(const CString& Path)
	{
		bool													FileExists=CFileSystemHelper::FileExists(Path);

		return(FileExists);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFileHelper::Copy(const CString& SourcePath, const CString& DestinationPath)
	{
		CFileSystemHelper::CopyFile(SourcePath,DestinationPath);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFileHelper::Move(const CString& SourcePath, const CString& DestinationPath)
	{
		CFileSystemHelper::MoveFile(SourcePath,DestinationPath);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFileHelper::Delete(const CString& Path)
	{
		CFileSystemHelper::DeleteFile(Path);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------