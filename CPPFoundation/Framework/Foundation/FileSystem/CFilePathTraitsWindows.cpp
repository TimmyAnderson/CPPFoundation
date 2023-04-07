//----------------------------------------------------------------------------------------------------------------------
#include "CFilePathTraitsWindows.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	const CString												CFilePathTraitsWindows::ROOT_NAME_LOGICAL_DISK_SEPARATOR=":";
	const CString												CFilePathTraitsWindows::ROOT_NAME_NETWORK_NAME_PREFIX="\\\\";
	const CString												CFilePathTraitsWindows::CURRENT_DIRECTORY_NAME=".";
	const CString												CFilePathTraitsWindows::PARENT_DIRECTORY_NAME="..";
	const Size													CFilePathTraitsWindows::ROOT_NAME_LOGICAL_DISK_SEPARATOR_SIZE=CFilePathTraitsWindows::ROOT_NAME_LOGICAL_DISK_SEPARATOR.GetLength();
	const Size													CFilePathTraitsWindows::ROOT_NAME_NETWORK_NAME_PREFIX_SIZE=CFilePathTraitsWindows::ROOT_NAME_NETWORK_NAME_PREFIX.GetLength();
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CFilePathTraitsWindows::GetPreferedDirectorySeparator(void)
	{
		return(CString::FromChar(DIRECTORY_SEPARATOR_1));
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CFilePathTraitsWindows::ExtensionSeparator(void)
	{
		return(CString::FromChar(EXTENSION_SEPARATOR));
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFilePathTraitsWindows::FindRootDirectoryOrFilenameIndex(const CString& Path)
	{
		if (Path.StartsWith(ROOT_NAME_NETWORK_NAME_PREFIX)==true)
		{
			Size												RootNameIndex=ROOT_NAME_NETWORK_NAME_PREFIX_SIZE;

			if (RootNameIndex<Path.GetLength())
			{
				if (Path[RootNameIndex]!=DIRECTORY_SEPARATOR_1 && Path[RootNameIndex]!=DIRECTORY_SEPARATOR_2)
				{
					Size										DirectorySeparatorIndex=FindNextSeparatorIndex(Path,RootNameIndex);

					return(DirectorySeparatorIndex);
				}
				else
				{
					return(0);
				}
			}
			else
			{
				return(0);
			}
		}
		else
		{
			Size												RootNameSeparatorPosition=Path.FindFirst(ROOT_NAME_LOGICAL_DISK_SEPARATOR);

			if (RootNameSeparatorPosition!=CString::END)
			{
				return(RootNameSeparatorPosition+ROOT_NAME_LOGICAL_DISK_SEPARATOR_SIZE);
			}
			else
			{
				return(0);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFilePathTraitsWindows::HasDirectorySeparator(const CString& Path, Size Index, CString& Separator)
	{
		if (Index<Path.GetLength())
		{
			if (Path[Index]==DIRECTORY_SEPARATOR_1 || Path[Index]==DIRECTORY_SEPARATOR_2)
			{
				Separator=CString::FromChar(Path[Index]);

				return(true);
			}
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFilePathTraitsWindows::StartsWithDirectorySeparator(const CString& Path)
	{
		if (Path.GetLength()>0)
		{
			Char												Character=Path[0];

			if (Character==DIRECTORY_SEPARATOR_1 || Character==DIRECTORY_SEPARATOR_2)
			{
				return(true);
			}
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFilePathTraitsWindows::EndsWithDirectorySeparator(const CString& Path)
	{
		if (Path.GetLength()>0)
		{
			Char												Character=Path[Path.GetLength()-1];

			if (Character==DIRECTORY_SEPARATOR_1 || Character==DIRECTORY_SEPARATOR_2)
			{
				return(true);
			}
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CFilePathTraitsWindows::RemoveDuplicateDirectorySeparators(const CString& Path)
	{
		CString													ModifiedPath;

		for(Size Index=0;Index<Path.GetLength();)
		{
			Char												Character=Path[Index];

			if (Character==DIRECTORY_SEPARATOR_1 || Character==DIRECTORY_SEPARATOR_2)
			{
				ModifiedPath.Append(Character);

				Index++;

				while(Index<Path.GetLength())
				{
					Character=Path[Index];

					if (Character!=DIRECTORY_SEPARATOR_1 && Character!=DIRECTORY_SEPARATOR_2)
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
	Size CFilePathTraitsWindows::FindNextSeparatorIndex(const CString& Path, Size Index)
	{
		for(;Index<Path.GetLength();Index++)
		{
			if (Path[Index]==DIRECTORY_SEPARATOR_1 || Path[Index]==DIRECTORY_SEPARATOR_2)
			{
				return(Index);
			}
		}

		return(CString::END);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFilePathTraitsWindows::FindNextSegmentIndex(const CString& Path, Size Index)
	{
		for(;Index<Path.GetLength();Index++)
		{
			if (Path[Index]!=DIRECTORY_SEPARATOR_1 && Path[Index]!=DIRECTORY_SEPARATOR_2)
			{
				return(Index);
			}
		}

		return(CString::END);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFilePathTraitsWindows::FindLastSegmentIndex(const CString& Path)
	{
		if (Path.GetLength()>0)
		{
			Size												LastDirectorySeparatorIndex=Path.GetLength();
			Size												Index=LastDirectorySeparatorIndex; 

			while(Index>0)
			{
				Index--;

				if (Path[Index]!=DIRECTORY_SEPARATOR_1 && Path[Index]!=DIRECTORY_SEPARATOR_2)
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
	bool CFilePathTraitsWindows::IsSpecialDirectoryName(const CString& Path)
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
	Size CFilePathTraitsWindows::FindExtensionSeparatorIndex(const CString& Path)
	{
		Size													ExtensionSeparatorIndex=Path.FindLast(EXTENSION_SEPARATOR);
		
		return(ExtensionSeparatorIndex);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CFilePathTraitsWindows::GetExtensionIndex(const CString& Path)
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
	bool CFilePathTraitsWindows::StartsWithExtensionSeparator(const CString& Path)
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