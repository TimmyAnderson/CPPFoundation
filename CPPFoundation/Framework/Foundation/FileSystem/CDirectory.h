//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CVector.h>
#include "CDirectoryEntry.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CDirectory final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			static void CreateDirectory(const CString& DirectoryName);
			static void RemoveDirectory(const CString& DirectoryName);
			static CVector<CCSPDirectoryEntry> GetDirectoryEntries(const CString& DirectoryName);
			static CString GetCurrentDirectory(void);
			static void SetCurrentDirectory(const CString& DirectoryName);
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------