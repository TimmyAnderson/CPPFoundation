//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Platform/FileSystem/CFileSystemHelper.h>
#include "CFilePathSegment.h"
#include "CFilePathTraitsLinux.h"
#include "CFilePathTraitsWindows.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TFilePathTraits>
	class CFilePath final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CString												MPath;

		public:
			CFilePath& operator=(const CFilePath& Other)
			{
				MPath=Other.MPath;

				return(*this);
			}

			CFilePath& operator=(CFilePath&& Other)
			{
				MPath=FUNCTION_MOVE(Other.MPath);

				return(*this);
			}

		public:
			bool operator==(const CFilePath& Other) const
			{
				return(MPath==Other.MPath);
			}

			bool operator!=(const CFilePath& Other) const
			{
				return(MPath!=Other.MPath);
			}

		public:
			CFilePath& operator/=(const CFilePath& Other)
			{
				return(AppendPath(Other,TFilePathTraits::GetPreferedDirectorySeparator()));
			}

			CFilePath& operator/=(const CString& Other)
			{
				return(AppendPath(Other,TFilePathTraits::GetPreferedDirectorySeparator()));
			}

			CFilePath operator/(const CFilePath& Other) const
			{
				CFilePath										Path(MPath);

				Path/=Other;

				return(Path);
			}

			CFilePath operator/(const CString& Other) const
			{
				CFilePath										Path(MPath);

				Path/=CFilePath(Other);

				return(Path);
			}

		public:
			CFilePath& operator+=(const CFilePath& Other)
			{
				MPath+=Other.GetPath();

				return(*this);
			}

			CFilePath& operator+=(const CString& Other)
			{
				MPath+=Other;

				return(*this);
			}

		public:
			virtual CString ToString(void) const override
			{
				return(MPath);
			}

			const CString& GetPath(void) const noexcept
			{
				return(MPath);
			}

			bool IsEmpty(void) const noexcept
			{
				return(MPath.IsEmpty());
			}

		public:
			bool HasRootName(void) const
			{
				return(GetRootName().IsEmpty()==false);
			}

			bool HasRootDirectory(void) const
			{
				return(GetRootDirectory().IsEmpty()==false);
			}

			bool HasRootPath(void) const
			{
				return(GetRootPath().IsEmpty()==false);
			}

			bool HasParentPath(void) const
			{
				return(GetParentPath().IsEmpty()==false);
			}

			bool HasRelativePath(void) const
			{
				return(GetRelativePath().IsEmpty()==false);
			}

			bool HasFilename(void) const
			{
				return(GetFilename().IsEmpty()==false);
			}

			bool HasStem(void) const
			{
				return(GetStem().IsEmpty()==false);
			}

			bool HasExtension(void) const
			{
				return(GetExtension().IsEmpty()==false);
			}

		public:
			CFilePath GetRootName(void) const
			{
				Size											RootDirectoryOrFilenameIndex=TFilePathTraits::FindRootDirectoryOrFilenameIndex(MPath);

				if (RootDirectoryOrFilenameIndex>0)
				{
					CFilePath									RootName(MPath.SubString(0,RootDirectoryOrFilenameIndex));

					return(RootName);
				}
				else
				{
					return(CFilePath());
				}
			}

			CFilePath GetRootDirectory(void) const
			{
				Size											RootDirectoryOrFilenameIndex=TFilePathTraits::FindRootDirectoryOrFilenameIndex(MPath);
				CString											RootDirectoryPath;

				if (TFilePathTraits::HasDirectorySeparator(MPath,RootDirectoryOrFilenameIndex,RootDirectoryPath)==true)
				{
					CFilePath									RootDirectory(RootDirectoryPath);

					return(RootDirectory);
				}
				else
				{
					return(CFilePath());
				}
			}

			CFilePath GetRootPath(void) const
			{
				Size											RootDirectoryOrFilenameIndex=TFilePathTraits::FindRootDirectoryOrFilenameIndex(MPath);
				CString											RootDirectory;

				if (TFilePathTraits::HasDirectorySeparator(MPath,RootDirectoryOrFilenameIndex,RootDirectory)==true)
				{
					CFilePath									RootPath(MPath.SubString(0,RootDirectoryOrFilenameIndex+RootDirectory.GetLength()));

					return(RootPath);
				}
				else
				{
					CFilePath									RootPath(MPath.SubString(0,RootDirectoryOrFilenameIndex));

					return(RootPath);
				}
			}

			CFilePath GetParentPath(void) const
			{
				Size											NumberOfSegments=0;
				Size											RootDirectoryOrFilenameIndex=TFilePathTraits::FindRootDirectoryOrFilenameIndex(MPath);
				Size											ParentPathEndIndex=RootDirectoryOrFilenameIndex;

				if (RootDirectoryOrFilenameIndex>0)
				{
					NumberOfSegments++;
				}

				Size											SearchIndex=ParentPathEndIndex;
				CString											RootDirectory;

				if (TFilePathTraits::HasDirectorySeparator(MPath,SearchIndex,RootDirectory)==true)
				{
					NumberOfSegments++;

					Size										SegmentIndex=TFilePathTraits::FindNextSegmentIndex(MPath,SearchIndex);

					if (SegmentIndex!=CString::END)
					{
						ParentPathEndIndex=SegmentIndex;
					}

					SearchIndex=SegmentIndex;
				}

				while(SearchIndex!=CString::END)
				{
					Size										SeparatorIndex=TFilePathTraits::FindNextSeparatorIndex(MPath,SearchIndex);

					if (SeparatorIndex!=CString::END)
					{
						ParentPathEndIndex=SeparatorIndex;
						NumberOfSegments++;

						Size									SegmentIndex=TFilePathTraits::FindNextSegmentIndex(MPath,SeparatorIndex);

						if (SegmentIndex!=CString::END)
						{
							SearchIndex=SegmentIndex;
						}
						else
						{
							break;
						}
					}
					else
					{
						if (ParentPathEndIndex<MPath.GetLength())
						{
							NumberOfSegments++;
						}

						break;
					}
				}

				if (NumberOfSegments>1)
				{
					CFilePath									ParentPath(MPath.SubString(0,ParentPathEndIndex));

					return(ParentPath);
				}
				else
				{
					return(CFilePath());
				}
			}

			CFilePath GetRelativePath(void) const
			{
				Size											RootDirectoryOrFilenameIndex=TFilePathTraits::FindRootDirectoryOrFilenameIndex(MPath);
				Size											RelativePathIndex=TFilePathTraits::FindNextSegmentIndex(MPath,RootDirectoryOrFilenameIndex);

				if (RelativePathIndex!=CString::END)
				{
					CFilePath									RelativePath(MPath.SubString(RelativePathIndex));

					return(RelativePath);
				}
				else
				{
					return(CFilePath());
				}
			}

			CFilePath GetFilename(void) const
			{
				Size											LastSegmentIndex=TFilePathTraits::FindLastSegmentIndex(MPath);

				if (LastSegmentIndex!=CString::END)
				{
					CFilePath									Filename(MPath.SubString(LastSegmentIndex));

					return(Filename);
				}
				else
				{
					return(CFilePath(MPath));
				}
			}

			CFilePath GetStem(void) const
			{
				Size											LastSegmentIndex=TFilePathTraits::FindLastSegmentIndex(MPath);

				if (LastSegmentIndex!=CString::END)
				{
					CString										Filename=MPath.SubString(LastSegmentIndex);

					if (TFilePathTraits::IsSpecialDirectoryName(Filename)==true)
					{
						CFilePath								Stem(Filename);

						return(Stem);
					}
					else
					{
						Size									ExtensionSeparatorIndex=TFilePathTraits::FindExtensionSeparatorIndex(Filename);
				
						if (ExtensionSeparatorIndex!=CString::END)
						{
							CFilePath							Stem(Filename.SubString(0,ExtensionSeparatorIndex));

							return(Stem);
						}
						else
						{
							CFilePath							Stem(Filename);

							return(Stem);
						}
					}
				}

				return(CFilePath());
			}

			CFilePath GetExtension(void) const
			{
				Size											LastSegmentIndex=TFilePathTraits::FindLastSegmentIndex(MPath);

				if (LastSegmentIndex!=CString::END)
				{
					CString										Filename=MPath.SubString(LastSegmentIndex);

					if (TFilePathTraits::IsSpecialDirectoryName(Filename)==true)
					{
						return(CFilePath());
					}
					else
					{
						Size									ExtensionIndex=TFilePathTraits::GetExtensionIndex(Filename);

						if (ExtensionIndex!=CString::END)
						{
							CFilePath							Extension(Filename.SubString(TFilePathTraits::GetExtensionIndex(Filename)));

							return(Extension);
						}
					}
				}

				return(CFilePath());
			}

		public:
			CFilePath& AppendPath(const CFilePath& PathToAdd, const CString& Separator)
			{
				if (MPath.IsEmpty()==false && PathToAdd.IsEmpty()==false)
				{
					if (TFilePathTraits::EndsWithDirectorySeparator(MPath)==false && TFilePathTraits::StartsWithDirectorySeparator(PathToAdd.GetPath())==false)
					{
						MPath.Append(Separator);
					}
				}

				MPath.Append(PathToAdd.GetPath());

				return(*this);
			}

			CFilePath RemoveDuplicateDirectorySeparators(void) const
			{
				CFilePath										Path(TFilePathTraits::RemoveDuplicateDirectorySeparators(MPath));

				return(Path);
			}

			CFilePathSegmentCollection DividePathToSegements(void) const
			{
				CFilePathSegmentCollection						SegmentCollection;
				Size											Index=TFilePathTraits::FindRootDirectoryOrFilenameIndex(MPath);

				if (Index>0)
				{
					SegmentCollection.Add(CFilePathSegment(EFilePathSegmentType::E_ROOT,MPath.SubString(0,Index)));
				}

				CString											RootDirectoryPath;

				if (TFilePathTraits::HasDirectorySeparator(MPath,Index,RootDirectoryPath)==true)
				{
					SegmentCollection.Add(CFilePathSegment(EFilePathSegmentType::E_ROOT_DIRECTORY,MPath.SubString(Index,RootDirectoryPath.GetLength())));

					Index+=RootDirectoryPath.GetLength();
				}

				while(true)
				{
					Index=TFilePathTraits::FindNextSegmentIndex(MPath,Index);
			
					if (Index!=CString::END)
					{
						Size									SeparatorIndex=TFilePathTraits::FindNextSeparatorIndex(MPath,Index);

						if (SeparatorIndex!=CString::END)
						{
							SegmentCollection.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,MPath.SubString(Index,SeparatorIndex-Index)));

							Index=SeparatorIndex;
						}
						else
						{
							SegmentCollection.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,MPath.SubString(Index,MPath.GetLength()-Index)));
							break;
						}
					}
					else
					{
						break;
					}
				}

				return(SegmentCollection);
			}

			CFilePath& RemoveFilename(void)
			{
				Size											LastSegmentIndex=TFilePathTraits::FindLastSegmentIndex(MPath);

				if (LastSegmentIndex!=CString::END)
				{
					MPath.Erase(LastSegmentIndex);
				}
				else
				{
					MPath.Clear();
				}

				return(*this);
			}

			CFilePath& ReplaceFilename(const CFilePath& Filename)
			{
				RemoveFilename();

				operator/=(Filename);

				return(*this);
			}

			CFilePath& ReplaceExtension(const CFilePath& Extension)
			{
				Size											LastSegmentIndex=TFilePathTraits::FindLastSegmentIndex(MPath);

				if (LastSegmentIndex!=CString::END)
				{
					CString										Filename=MPath.SubString(LastSegmentIndex);

					if (TFilePathTraits::IsSpecialDirectoryName(Filename)==false)
					{
						Size									ExtensionIndex=TFilePathTraits::GetExtensionIndex(MPath);

						if (ExtensionIndex!=CString::END)
						{
							if (ExtensionIndex>=LastSegmentIndex)
							{
								MPath.Erase(ExtensionIndex);

								MPath.Append(Extension.MPath);
							}
						}
						else
						{
							MPath.Append(Extension.MPath);
						}
					}
				}

				return(*this);
			}

		public:
			CFilePath(void)
				: MPath("")
			{
			}

			CFilePath(const CString& Path)
				: MPath(Path)
			{
			}

			CFilePath(CString&& Path)
				: MPath(FUNCTION_MOVE(Path))
			{
			}

			CFilePath(const CFilePath& Other)
				: MPath(Other.MPath)
			{
			}

			CFilePath(CFilePath&& Other)
				: MPath(FUNCTION_MOVE(Other.MPath))
			{
			}

			virtual ~CFilePath(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TFilePathTraits>
	using														CSPFilePath=CPPFoundation::Foundation::CSharedPointer<CFilePath<TFilePathTraits>>;
	template<typename TFilePathTraits>
	using														CCSPFilePath=CPPFoundation::Foundation::CSharedPointer<const CFilePath<TFilePathTraits>>;
	using														CPath=CFilePath<CPPFoundation::Platform::CFileSystemHelper::CFilePathTraits>;
	using														CSPPath=CPPFoundation::Foundation::CSharedPointer<CFilePath<CPath>>;
	using														CCSPPath=CPPFoundation::Foundation::CSharedPointer<const CFilePath<CPath>>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------