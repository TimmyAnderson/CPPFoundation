//----------------------------------------------------------------------------------------------------------------------
#include "CFileSystemTestPathData.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CFileSystemTestPathData::CFileSystemTestPathData(void)
		: MHasRootName(false), MRootName(), MHasRootDirectory(false), MRootDirectory(), MHasRootPath(false), MRootPath(), MHasParentPath(false), MParentPath(), MHasRelativePath(false), MRelativePath(), MHasFilename(false), MFilename(), MHasStem(false), MStem(), MHasExtension(false), MExtension()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CFileSystemTestPathData::~CFileSystemTestPathData(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CFileSystemTestPathData::GetHasRootName(void) const noexcept
	{
		return(MHasRootName);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CString& CFileSystemTestPathData::GetRootName(void) const noexcept
	{
		return(MRootName);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFileSystemTestPathData::GetHasRootDirectory(void) const noexcept
	{
		return(MHasRootDirectory);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CString& CFileSystemTestPathData::GetRootDirectory(void) const noexcept
	{
		return(MRootDirectory);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFileSystemTestPathData::GetHasRootPath(void) const noexcept
	{
		return(MHasRootPath);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CString& CFileSystemTestPathData::GetRootPath(void) const noexcept
	{
		return(MRootPath);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFileSystemTestPathData::GetHasParentPath(void) const noexcept
	{
		return(MHasParentPath);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CString& CFileSystemTestPathData::GetParentPath(void) const noexcept
	{
		return(MParentPath);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFileSystemTestPathData::GetHasRelativePath(void) const noexcept
	{
		return(MHasRelativePath);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CString& CFileSystemTestPathData::GetRelativePath(void) const noexcept
	{
		return(MRelativePath);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFileSystemTestPathData::GetHasFilename(void) const noexcept
	{
		return(MHasFilename);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CString& CFileSystemTestPathData::GetFilename(void) const noexcept
	{
		return(MFilename);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFileSystemTestPathData::GetHasStem(void) const noexcept
	{
		return(MHasStem);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CString& CFileSystemTestPathData::GetStem(void) const noexcept
	{
		return(MStem);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFileSystemTestPathData::GetHasExtension(void) const noexcept
	{
		return(MHasExtension);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CString& CFileSystemTestPathData::GetExtension(void) const noexcept
	{
		return(MExtension);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CFileSystemTestPathData::Reset(void)
	{
		MHasRootName=false;
		MRootName="";
		MHasRootDirectory=false;
		MRootDirectory="";
		MHasRootPath=false;
		MRootPath="";
		MHasParentPath=false;
		MParentPath="";
		MHasRelativePath=false;
		MRelativePath="";
		MHasFilename=false;
		MFilename="";
		MHasStem=false;
		MStem="";
		MHasExtension=false;
		MExtension="";
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFileSystemTestPathData::SetRootName(bool HasRootName, const CString& RootName)
	{
		MHasRootName=HasRootName;
		MRootName=RootName;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFileSystemTestPathData::SetRootDirectory(bool HasRootDirectory, const CString& RootDirectory)
	{
		MHasRootDirectory=HasRootDirectory;
		MRootDirectory=RootDirectory;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFileSystemTestPathData::SetRootPath(bool HasRootPath, const CString& RootPath)
	{
		MHasRootPath=HasRootPath;
		MRootPath=RootPath;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFileSystemTestPathData::SetParentPath(bool HasParentPath, const CString& ParentPath)
	{
		MHasParentPath=HasParentPath;
		MParentPath=ParentPath;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFileSystemTestPathData::SetRelativePath(bool HasRelativePath, const CString& RelativePath)
	{
		MHasRelativePath=HasRelativePath;
		MRelativePath=RelativePath;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFileSystemTestPathData::SetFilename(bool HasFilename, const CString& Filename)
	{
		MHasFilename=HasFilename;
		MFilename=Filename;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFileSystemTestPathData::SetStem(bool HasStem, const CString& Stem)
	{
		MHasStem=HasStem;
		MStem=Stem;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CFileSystemTestPathData::SetExtension(bool HasExtension, const CString& Extension)
	{
		MHasExtension=HasExtension;
		MExtension=Extension;
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------