//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Console/CConsoleHelper.h>
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/FileSystem/CFilePath.h>
#include <Framework/Testing/CTest.h>
#include "CFileSystemTestPathData.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CFileSystemTest final : public CTest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			template<typename TFilePathTraits>
			using												CTestFilePath=CPPFoundation::Foundation::CFilePath<TFilePathTraits>;

		private:
			template<typename TFilePathTraits>
			void CheckHasRootName(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, bool HasRoot) const
			{
				if (HasRoot==true)
				{
					if (Path.HasRootName()==false)
					{
						CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to FIND ROOT NAME !\n"));

						throw(CPPFoundation::Foundation::CInvalidOperationException("TEST HAS ROOT NAME FAILED !"));
					}
				}
				else
				{
					if (Path.HasRootName()==true)
					{
						CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] INCORRECTLY FOUND ROOT NAME !\n"));

						throw(CPPFoundation::Foundation::CInvalidOperationException("TEST HAS ROOT NAME FAILED !"));
					}
				}
			}

			template<typename TFilePathTraits>
			void CheckGetRootName(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, const CTestFilePath<TFilePathTraits>& RootName) const
			{
				CTestFilePath<TFilePathTraits>					CalculatedRootName=Path.GetRootName();

				if (CalculatedRootName!=RootName)
				{
					CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to FIND CORRECT ROOT NAME VALUE (",RootName,",",CalculatedRootName,") !\n"));

					throw(CPPFoundation::Foundation::CInvalidOperationException("TEST GET ROOT NAME FAILED !"));
				}
			}

			template<typename TFilePathTraits>
			void CheckHasRootDirectory(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, bool HasRootDirectory) const
			{
				if (HasRootDirectory==true)
				{
					if (Path.HasRootDirectory()==false)
					{
						CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to FIND ROOT DIRECTORY !\n"));

						throw(CPPFoundation::Foundation::CInvalidOperationException("TEST HAS ROOT DIRECTORY FAILED !"));
					}
				}
				else
				{
					if (Path.HasRootDirectory()==true)
					{
						CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] INCORRECTLY FOUND ROOT DIRECTORY !\n"));

						throw(CPPFoundation::Foundation::CInvalidOperationException("TEST HAS ROOT DIRECTORY FAILED !"));
					}
				}
			}

			template<typename TFilePathTraits>
			void CheckGetRootDirectory(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, const CTestFilePath<TFilePathTraits>& RootDirectory) const
			{
				CTestFilePath<TFilePathTraits>					CalculatedRootDirectory=Path.GetRootDirectory();

				if (CalculatedRootDirectory!=RootDirectory)
				{
					CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to FIND CORRECT ROOT DIRECTORY VALUE (",RootDirectory,",",CalculatedRootDirectory,") !\n"));

					throw(CPPFoundation::Foundation::CInvalidOperationException("TEST GET ROOT DIRECTORY FAILED !"));
				}
			}

			template<typename TFilePathTraits>
			void CheckHasRootPath(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, bool HasRootPath) const
			{
				if (HasRootPath==true)
				{
					if (Path.HasRootPath()==false)
					{
						CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to FIND ROOT PATH !\n"));

						throw(CPPFoundation::Foundation::CInvalidOperationException("TEST HAS ROOT PATH FAILED !"));
					}
				}
				else
				{
					if (Path.HasRootPath()==true)
					{
						CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] INCORRECTLY FOUND ROOT PATH !\n"));

						throw(CPPFoundation::Foundation::CInvalidOperationException("TEST HAS ROOT PATH FAILED !"));
					}
				}
			}

			template<typename TFilePathTraits>
			void CheckGetRootPath(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, const CTestFilePath<TFilePathTraits>& RootPath) const
			{
				CTestFilePath<TFilePathTraits>					CalculatedRootPath=Path.GetRootPath();

				if (CalculatedRootPath!=RootPath)
				{
					CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to FIND CORRECT ROOT PATH VALUE (",RootPath,",",CalculatedRootPath,") !\n"));

					throw(CPPFoundation::Foundation::CInvalidOperationException("TEST GET ROOT PATH FAILED !"));
				}
			}

			template<typename TFilePathTraits>
			void CheckHasParentPath(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, bool HasParentPath) const
			{
				if (HasParentPath==true)
				{
					if (Path.HasParentPath()==false)
					{
						CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to FIND PARENT PATH !\n"));

						throw(CPPFoundation::Foundation::CInvalidOperationException("TEST HAS PARENT PATH FAILED !"));
					}
				}
				else
				{
					if (Path.HasParentPath()==true)
					{
						CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] INCORRECTLY FOUND PARENT PATH !\n"));

						throw(CPPFoundation::Foundation::CInvalidOperationException("TEST HAS PARENT PATH FAILED !"));
					}
				}
			}

			template<typename TFilePathTraits>
			void CheckGetParentPath(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, const CTestFilePath<TFilePathTraits>& ParentPath) const
			{
				CTestFilePath<TFilePathTraits>					CalculatedParentPath=Path.GetParentPath();

				if (CalculatedParentPath!=ParentPath)
				{
					CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to FIND CORRECT PARENT PATH VALUE (",ParentPath,",",CalculatedParentPath,") !\n"));

					throw(CPPFoundation::Foundation::CInvalidOperationException("TEST GET PARENT PATH FAILED !"));
				}
			}

			template<typename TFilePathTraits>
			void CheckHasRelativePath(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, bool HasRelativePath) const
			{
				if (HasRelativePath==true)
				{
					if (Path.HasRelativePath()==false)
					{
						CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to FIND RELATIVE PATH !\n"));

						throw(CPPFoundation::Foundation::CInvalidOperationException("TEST HAS RELATIVE PATH FAILED !"));
					}
				}
				else
				{
					if (Path.HasRelativePath()==true)
					{
						CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] INCORRECTLY FOUND RELATIVE PATH !\n"));

						throw(CPPFoundation::Foundation::CInvalidOperationException("TEST HAS RELATIVE PATH FAILED !"));
					}
				}
			}

			template<typename TFilePathTraits>
			void CheckGetRelativePath(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, const CTestFilePath<TFilePathTraits>& RelativePath) const
			{
				CTestFilePath<TFilePathTraits>					CalculatedRelativePath=Path.GetRelativePath();

				if (CalculatedRelativePath!=RelativePath)
				{
					CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to FIND CORRECT RELATIVE PATH VALUE (",RelativePath,",",CalculatedRelativePath,") !\n"));

					throw(CPPFoundation::Foundation::CInvalidOperationException("TEST GET RELATIVE PATH FAILED !"));
				}
			}

			template<typename TFilePathTraits>
			void CheckHasFilename(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, bool HasFilename) const
			{
				if (HasFilename==true)
				{
					if (Path.HasFilename()==false)
					{
						CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to FIND FILENAME !\n"));

						throw(CPPFoundation::Foundation::CInvalidOperationException("TEST HAS FILENAME FAILED !"));
					}
				}
				else
				{
					if (Path.HasFilename()==true)
					{
						CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] INCORRECTLY FOUND FILENAME !\n"));

						throw(CPPFoundation::Foundation::CInvalidOperationException("TEST HAS FILENAME FAILED !"));
					}
				}
			}

			template<typename TFilePathTraits>
			void CheckGetFilename(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, const CTestFilePath<TFilePathTraits>& Filename) const
			{
				CTestFilePath<TFilePathTraits>					CalculatedFilename=Path.GetFilename();

				if (CalculatedFilename!=Filename)
				{
					CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to FIND CORRECT FILENAME VALUE (",Filename,",",CalculatedFilename,") !\n"));

					throw(CPPFoundation::Foundation::CInvalidOperationException("TEST GET FILENAME FAILED !"));
				}
			}

			template<typename TFilePathTraits>
			void CheckHasStem(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, bool HasStem) const
			{
				if (HasStem==true)
				{
					if (Path.HasStem()==false)
					{
						CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to FIND STEM !\n"));

						throw(CPPFoundation::Foundation::CInvalidOperationException("TEST HAS STEM FAILED !"));
					}
				}
				else
				{
					if (Path.HasStem()==true)
					{
						CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] INCORRECTLY FOUND STEM !\n"));

						throw(CPPFoundation::Foundation::CInvalidOperationException("TEST HAS STEM FAILED !"));
					}
				}
			}

			template<typename TFilePathTraits>
			void CheckGetStem(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, const CTestFilePath<TFilePathTraits>& Stem) const
			{
				CTestFilePath<TFilePathTraits>					CalculatedStem=Path.GetStem();

				if (CalculatedStem!=Stem)
				{
					CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to FIND CORRECT STEM VALUE (",Stem,",",CalculatedStem,") !\n"));

					throw(CPPFoundation::Foundation::CInvalidOperationException("TEST GET STEM FAILED !"));
				}
			}

			template<typename TFilePathTraits>
			void CheckHasExtension(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, bool HasExtension) const
			{
				if (HasExtension==true)
				{
					if (Path.HasExtension()==false)
					{
						CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to FIND EXTENSION !\n"));

						throw(CPPFoundation::Foundation::CInvalidOperationException("TEST HAS EXTENSION FAILED !"));
					}
				}
				else
				{
					if (Path.HasExtension()==true)
					{
						CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] INCORRECTLY FOUND EXTENSION !\n"));

						throw(CPPFoundation::Foundation::CInvalidOperationException("TEST HAS EXTENSION FAILED !"));
					}
				}
			}

			template<typename TFilePathTraits>
			void CheckGetExtension(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, const CTestFilePath<TFilePathTraits>& Extension) const
			{
				CTestFilePath<TFilePathTraits>					CalculatedExtension=Path.GetExtension();

				if (CalculatedExtension!=Extension)
				{
					CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to FIND CORRECT EXTENSION VALUE (",Extension,",",CalculatedExtension,") !\n"));

					throw(CPPFoundation::Foundation::CInvalidOperationException("TEST GET EXTENSION FAILED !"));
				}
			}

			template<typename TFilePathTraits>
			void CheckRemoveDuplicateDirectorySeparators(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, const CTestFilePath<TFilePathTraits>& ExpectedResultPath) const
			{
				CTestFilePath<TFilePathTraits>					ModifiedPath=Path.RemoveDuplicateDirectorySeparators();

				if (ModifiedPath!=ExpectedResultPath)
				{
					CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to REMOVE DUPLICATE SEPARATORS !\n"));

					throw(CPPFoundation::Foundation::CInvalidOperationException("TEST REMOVE DUPLICATE SEPARATORS FAILED !"));
				}
			}

			template<typename TFilePathTraits>
			void CheckOperatorDivide(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path1, const CTestFilePath<TFilePathTraits>& Path2, const CTestFilePath<TFilePathTraits>& ExpectedResultPath) const
			{
				CTestFilePath<TFilePathTraits>					AppendedPath=(Path1/Path2);

				if (AppendedPath!=ExpectedResultPath)
				{
					CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to apply OPERATOR DIVIDE !\n"));

					throw(CPPFoundation::Foundation::CInvalidOperationException("TEST OPERATOR DIVIDE FAILED !"));
				}
			}

			template<typename TFilePathTraits>
			void CheckAppend(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path1, const CTestFilePath<TFilePathTraits>& Path2, const CPPFoundation::Foundation::CString& Separator, const CTestFilePath<TFilePathTraits>& ExpectedResultPath) const
			{
				CTestFilePath<TFilePathTraits>					AppendedPath=Path1;

				AppendedPath.AppendPath(Path2,Separator);

				if (AppendedPath!=ExpectedResultPath)
				{
					CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to APPEND 2 PATHS !\n"));

					throw(CPPFoundation::Foundation::CInvalidOperationException("TEST APPEND 2 PATHS FAILED !"));
				}
			}

			template<typename TFilePathTraits>
			void CheckFilePathSegments(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, const CPPFoundation::Foundation::CFilePathSegmentCollection& ExpectedResult) const
			{
				CPPFoundation::Foundation::CFilePathSegmentCollection	Segments=Path.DividePathToSegements();
				bool											TestFailed=false;

				if (Segments.GetLength()==ExpectedResult.GetLength())
				{
					for(Size Index=0;Index<Segments.GetLength();Index++)
					{
						if (Segments[Index]!=ExpectedResult[Index])
						{
							TestFailed=true;
							break;
						}
					}
				}
				else
				{
					TestFailed=true;
				}

				if (TestFailed==true)
				{
					CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to DIVIDE PATH to SEGMENTS !\n"));

					throw(CPPFoundation::Foundation::CInvalidOperationException("TEST PATH to SEGMENTS FAILED !"));
				}
			}

			template<typename TFilePathTraits>
			void CheckRemoveFilename(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, const CTestFilePath<TFilePathTraits>& ExpectedResultPath) const
			{
				CTestFilePath<TFilePathTraits>					PathWithoutFilename=Path;

				PathWithoutFilename.RemoveFilename();

				if (PathWithoutFilename!=ExpectedResultPath)
				{
					CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to REMOVE FILENAME !\n"));

					throw(CPPFoundation::Foundation::CInvalidOperationException("TEST REMOVE FILENAME FAILED !"));
				}
			}

			template<typename TFilePathTraits>
			void CheckReplaceFilename(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, const CTestFilePath<TFilePathTraits>& FilenameReplacement, const CTestFilePath<TFilePathTraits>& ExpectedResultPath) const
			{
				CTestFilePath<TFilePathTraits>					PathWithReplacedFilename=Path;

				PathWithReplacedFilename.ReplaceFilename(FilenameReplacement);

				if (PathWithReplacedFilename!=ExpectedResultPath)
				{
					CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to REPLACE FILENAME !\n"));

					throw(CPPFoundation::Foundation::CInvalidOperationException("TEST REPLACE FILENAME FAILED !"));
				}
			}

			template<typename TFilePathTraits>
			void CheckReplaceExtension(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, const CTestFilePath<TFilePathTraits>& ExtensionReplacement, const CTestFilePath<TFilePathTraits>& ExpectedResultPath) const
			{
				CTestFilePath<TFilePathTraits>					PathWithReplacedExtension=Path;

				PathWithReplacedExtension.ReplaceExtension(ExtensionReplacement);

				if (PathWithReplacedExtension!=ExpectedResultPath)
				{
					CPPFoundation::Foundation::CConsoleHelper::WriteLine(CPPFoundation::Foundation::CString::Format("\tTEST [",TestNumber,"] FAILED to REPLACE EXTENSION !\n"));

					throw(CPPFoundation::Foundation::CInvalidOperationException("TEST REPLACE EXTENSION FAILED !"));
				}
			}

		private:
			template<typename TFilePathTraits>
			void CheckPath(Size TestNumber, const CTestFilePath<TFilePathTraits>& Path, const CFileSystemTestPathData& TestPathData) const
			{
				CheckHasRootName<TFilePathTraits>(TestNumber,Path,TestPathData.GetHasRootName());
				CheckGetRootName<TFilePathTraits>(TestNumber,Path,TestPathData.GetRootName());
				CheckHasRootDirectory<TFilePathTraits>(TestNumber,Path,TestPathData.GetHasRootDirectory());
				CheckGetRootDirectory<TFilePathTraits>(TestNumber,Path,TestPathData.GetRootDirectory());
				CheckHasRootPath<TFilePathTraits>(TestNumber,Path,TestPathData.GetHasRootPath());
				CheckGetRootPath<TFilePathTraits>(TestNumber,Path,TestPathData.GetRootPath());
				CheckHasParentPath<TFilePathTraits>(TestNumber,Path,TestPathData.GetHasParentPath());
				CheckGetParentPath<TFilePathTraits>(TestNumber,Path,TestPathData.GetParentPath());
				CheckHasRelativePath<TFilePathTraits>(TestNumber,Path,TestPathData.GetHasRelativePath());
				CheckGetRelativePath<TFilePathTraits>(TestNumber,Path,TestPathData.GetRelativePath());
				CheckHasFilename<TFilePathTraits>(TestNumber,Path,TestPathData.GetHasFilename());
				CheckGetFilename<TFilePathTraits>(TestNumber,Path,TestPathData.GetFilename());
				CheckHasStem<TFilePathTraits>(TestNumber,Path,TestPathData.GetHasStem());
				CheckGetStem<TFilePathTraits>(TestNumber,Path,TestPathData.GetStem());
				CheckHasExtension<TFilePathTraits>(TestNumber,Path,TestPathData.GetHasExtension());
				CheckGetExtension<TFilePathTraits>(TestNumber,Path,TestPathData.GetExtension());
			}

		private:
			bool TestFilePathWindows(void) const;
			bool TestFilePathLinux(void) const;
			bool TestFileOperationsOpenCloseReadWrite(void) const;
			bool TestFileOperationsSeek(void) const;
			bool TestFileOperationsGetFileSize(void) const;
			bool TestFileOperationsCopyMoveExistsDelete(void) const;
			bool TestFileOperationsReadUntil(void) const;
			bool TestFileOperationsStringInterface(void) const;
			bool TestFileOperationsGetTime(void) const;
			bool TestDirectoryOperations(void) const;

		public:
			virtual bool ExecuteTest(void) override;

		public:
			CFileSystemTest(CPPFoundation::Foundation::CLogWriter& LogWriter, const CPPFoundation::Foundation::CLogCategory& LogCategoryTest);
			virtual ~CFileSystemTest(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------