//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Strings/CString.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CFilePathTraitsWindows final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			static const Char									DIRECTORY_SEPARATOR_1='\\';
			static const Char									DIRECTORY_SEPARATOR_2='/';
			static const Char									EXTENSION_SEPARATOR='.';
			static const CString								ROOT_NAME_LOGICAL_DISK_SEPARATOR;
			static const CString								ROOT_NAME_NETWORK_NAME_PREFIX;
			static const CString								CURRENT_DIRECTORY_NAME;
			static const CString								PARENT_DIRECTORY_NAME;
			static const Size									ROOT_NAME_LOGICAL_DISK_SEPARATOR_SIZE;
			static const Size									ROOT_NAME_NETWORK_NAME_PREFIX_SIZE;

		public:
			static CString GetPreferedDirectorySeparator(void);
			static CString ExtensionSeparator(void);
			static Size FindRootDirectoryOrFilenameIndex(const CString& Path);
			static bool HasDirectorySeparator(const CString& Path, Size Index, CString& Separator);
			static bool StartsWithDirectorySeparator(const CString& Path);
			static bool EndsWithDirectorySeparator(const CString& Path);
			static CString RemoveDuplicateDirectorySeparators(const CString& Path);
			static Size FindNextSeparatorIndex(const CString& Path, Size Index);
			static Size FindNextSegmentIndex(const CString& Path, Size Index);
			static Size FindLastSegmentIndex(const CString& Path);
			static bool IsSpecialDirectoryName(const CString& Path);
			static Size FindExtensionSeparatorIndex(const CString& Path);
			static Size GetExtensionIndex(const CString& Path);
			static bool StartsWithExtensionSeparator(const CString& Path);
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------