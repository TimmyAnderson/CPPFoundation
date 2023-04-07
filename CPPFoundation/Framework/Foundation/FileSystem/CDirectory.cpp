//----------------------------------------------------------------------------------------------------------------------
#include "CDirectory.h"
#include <Framework/Platform/FileSystem/CFileSystemHelper.h>
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
	void CDirectory::CreateDirectory(const CString& DirectoryName)
	{
		CFileSystemHelper::CreateDirectory(DirectoryName);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CDirectory::RemoveDirectory(const CString& DirectoryName)
	{
		CFileSystemHelper::RemoveDirectory(DirectoryName);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CCSPDirectoryEntry> CDirectory::GetDirectoryEntries(const CString& DirectoryName)
	{
		CVector<CCSPDirectoryEntry>								DirectoryEntries=CFileSystemHelper::GetDirectoryEntries(DirectoryName);

		return(DirectoryEntries);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CDirectory::GetCurrentDirectory(void)
	{
		CString													CurrentDirectory=CFileSystemHelper::GetCurrentDirectory();

		return(CurrentDirectory);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CDirectory::SetCurrentDirectory(const CString& DirectoryName)
	{
		CFileSystemHelper::SetCurrentDirectory(DirectoryName);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------