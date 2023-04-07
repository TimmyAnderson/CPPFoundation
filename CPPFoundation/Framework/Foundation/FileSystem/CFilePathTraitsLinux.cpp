//----------------------------------------------------------------------------------------------------------------------
#include "CFilePathTraitsLinux.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	const CString												CFilePathTraitsLinux::CURRENT_DIRECTORY_NAME=".";
	const CString												CFilePathTraitsLinux::PARENT_DIRECTORY_NAME="..";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CFilePathTraitsLinux::GetPreferedDirectorySeparator(void)
	{
		return(CString::FromChar(DIRECTORY_SEPARATOR));
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CFilePathTraitsLinux::ExtensionSeparator(void)
	{
		return(CString::FromChar(EXTENSION_SEPARATOR));
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFilePathTraitsLinux::FindRootDirectoryOrFilenameIndex(const CString&)
	{
		return(0);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFilePathTraitsLinux::HasDirectorySeparator(const CString& Path, Size Index, CString& Separator)
	{
		if (Index<Path.GetLength())
		{
			if (Path[Index]==DIRECTORY_SEPARATOR)
			{
				Separator=CString::FromChar(Path[Index]);

				return(true);
			}
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFilePathTraitsLinux::StartsWithDirectorySeparator(const CString& Path)
	{
		if (Path.GetLength()>0)
		{
			Char												Character=Path[0];

			if (Character==DIRECTORY_SEPARATOR)
			{
				return(true);
			}
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFilePathTraitsLinux::EndsWithDirectorySeparator(const CString& Path)
	{
		if (Path.GetLength()>0)
		{
			Char												Character=Path[Path.GetLength()-1];

			if (Character==DIRECTORY_SEPARATOR)
			{
				return(true);
			}
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CFilePathTraitsLinux::RemoveDuplicateDirectorySeparators(const CString& Path)
	{
		CString													ModifiedPath;

		for(Size Index=0;Index<Path.GetLength();)
		{
			Char												Character=Path[Index];

			if (Character==DIRECTORY_SEPARATOR)
			{
				ModifiedPath.Append(Character);

				Index++;

				while(Index<Path.GetLength())
				{
					Character=Path[Index];

					if (Character!=DIRECTORY_SEPARATOR)
					{
						ModifiedPath.Append(Character);
						
						Index++;

						break;
					}
					else
					{
						Index++;
					}
				}
			}
			else
			{
				ModifiedPath.Append(Character);

				Index++;
			}
		}

		return(ModifiedPath);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFilePathTraitsLinux::FindNextSeparatorIndex(const CString& Path, Size Index)
	{
		for(;Index<Path.GetLength();Index++)
		{
			if (Path[Index]==DIRECTORY_SEPARATOR)
			{
				return(Index);
			}
		}

		return(CString::END);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFilePathTraitsLinux::FindNextSegmentIndex(const CString& Path, Size Index)
	{
		for(;Index<Path.GetLength();Index++)
		{
			if (Path[Index]!=DIRECTORY_SEPARATOR)
			{
				return(Index);
			}
		}

		return(CString::END);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFilePathTraitsLinux::FindLastSegmentIndex(const CString& Path)
	{
		if (Path.GetLength()>0)
		{
			Size												LastDirectorySeparatorIndex=Path.GetLength();
			Size												Index=LastDirectorySeparatorIndex;

			while(Index>0)
			{
				Index--;

				if (Path[Index]!=DIRECTORY_SEPARATOR)
				{
					LastDirectorySeparatorIndex=Index;
				}
				else
				{
					break;
				}
			}

			return(LastDirectorySeparatorIndex);
		}
		else
		{
			return(CString::END);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFilePathTraitsLinux::IsSpecialDirectoryName(const CString& Path)
	{
		if (Path==CURRENT_DIRECTORY_NAME)
		{
			return(true);
		}
		else if (Path==PARENT_DIRECTORY_NAME)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFilePathTraitsLinux::FindExtensionSeparatorIndex(const CString& Path)
	{
		Size													ExtensionSeparatorIndex=Path.FindLast(EXTENSION_SEPARATOR);
		
		return(ExtensionSeparatorIndex);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFilePathTraitsLinux::GetExtensionIndex(const CString& Path)
	{
		Size													ExtensionSeparatorIndex=Path.FindLast(EXTENSION_SEPARATOR);

		if (ExtensionSeparatorIndex!=CString::END)
		{
			Size												ExtensionIndex=(ExtensionSeparatorIndex+1);

			return(ExtensionIndex);
		}
		else
		{
			return(CString::END);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFilePathTraitsLinux::StartsWithExtensionSeparator(const CString& Path)
	{
		if (Path.GetLength()>0)
		{
			Char												Character=Path[0];

			if (Character==EXTENSION_SEPARATOR)
			{
				return(true);
			}
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------