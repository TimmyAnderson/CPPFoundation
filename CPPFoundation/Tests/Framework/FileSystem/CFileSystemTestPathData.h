//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/FileSystem/CFilePath.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CFileSystemTestPathData final : public CPPFoundation::Foundation::CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			bool												MHasRootName;
			CPPFoundation::Foundation::CString						MRootName;
			bool												MHasRootDirectory;
			CPPFoundation::Foundation::CString						MRootDirectory;
			bool												MHasRootPath;
			CPPFoundation::Foundation::CString						MRootPath;
			bool												MHasParentPath;
			CPPFoundation::Foundation::CString						MParentPath;
			bool												MHasRelativePath;
			CPPFoundation::Foundation::CString						MRelativePath;
			bool												MHasFilename;
			CPPFoundation::Foundation::CString						MFilename;
			bool												MHasStem;
			CPPFoundation::Foundation::CString						MStem;
			bool												MHasExtension;
			CPPFoundation::Foundation::CString						MExtension;

		public:
			bool GetHasRootName(void) const noexcept;
			const CPPFoundation::Foundation::CString& GetRootName(void) const noexcept;
			bool GetHasRootDirectory(void) const noexcept;
			const CPPFoundation::Foundation::CString& GetRootDirectory(void) const noexcept;
			bool GetHasRootPath(void) const noexcept;
			const CPPFoundation::Foundation::CString& GetRootPath(void) const noexcept;
			bool GetHasParentPath(void) const noexcept;
			const CPPFoundation::Foundation::CString& GetParentPath(void) const noexcept;
			bool GetHasRelativePath(void) const noexcept;
			const CPPFoundation::Foundation::CString& GetRelativePath(void) const noexcept;
			bool GetHasFilename(void) const noexcept;
			const CPPFoundation::Foundation::CString& GetFilename(void) const noexcept;
			bool GetHasStem(void) const noexcept;
			const CPPFoundation::Foundation::CString& GetStem(void) const noexcept;
			bool GetHasExtension(void) const noexcept;
			const CPPFoundation::Foundation::CString& GetExtension(void) const noexcept;

		public:
			void Reset(void);
			void SetRootName(bool HasRootName, const CPPFoundation::Foundation::CString& RootName="");
			void SetRootDirectory(bool HasRootDirectory, const CPPFoundation::Foundation::CString& RootDirectory="");
			void SetRootPath(bool HasRootPath, const CPPFoundation::Foundation::CString& RootPath="");
			void SetParentPath(bool HasParentPath, const CPPFoundation::Foundation::CString& ParentPath="");
			void SetRelativePath(bool HasRelativePath, const CPPFoundation::Foundation::CString& RelativePath="");
			void SetFilename(bool HasFilename, const CPPFoundation::Foundation::CString& Filename="");
			void SetStem(bool HasStem, const CPPFoundation::Foundation::CString& Stem="");
			void SetExtension(bool HasExtension, const CPPFoundation::Foundation::CString& Extension="");

		public:
			CFileSystemTestPathData(void);
			virtual ~CFileSystemTestPathData(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------