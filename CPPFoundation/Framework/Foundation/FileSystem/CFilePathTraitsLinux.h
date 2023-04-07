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
	class CFilePathTraitsLinux final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			static const Char									DIRECTORY_SEPARATOR='/';
			static const Char									EXTENSION_SEPARATOR='.';
			static const CString								CURRENT_DIRECTORY_NAME;
			static const CString								PARENT_DIRECTORY_NAME;

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