//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "EFilePathSegmentType.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CFilePathSegment final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			EFilePathSegmentType								MSegmentType;
			CString												MSegment;

		public:
			bool operator==(const CFilePathSegment& Other) const;
			bool operator!=(const CFilePathSegment& Other) const;

		public:
			EFilePathSegmentType GetSegmentType(void) const noexcept;
			CString GetSegment(void) const noexcept;

		public:
			CFilePathSegment(EFilePathSegmentType SegmentType, const CString& Segment);
			CFilePathSegment(EFilePathSegmentType SegmentType, CString&& Segment);
			virtual ~CFilePathSegment(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPFilePathSegment=CPPFoundation::Foundation::CSharedPointer<CFilePathSegment>;
	using														CCSPFilePathSegment=CPPFoundation::Foundation::CSharedPointer<const CFilePathSegment>;
	using														CFilePathSegmentCollection=CPPFoundation::Foundation::CVector<CFilePathSegment>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------