//----------------------------------------------------------------------------------------------------------------------
#include "CDirectoryEntry.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CDirectoryEntry::CDirectoryEntry(const CString& EntryName, EDirectoryEntryType EntryType)
		: MEntryName(EntryName), MEntryType(EntryType)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CDirectoryEntry::~CDirectoryEntry(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CString& CDirectoryEntry::GetEntryName(void) const noexcept
	{
		return(MEntryName);
	}
//----------------------------------------------------------------------------------------------------------------------
	EDirectoryEntryType CDirectoryEntry::GetEntryType(void) const noexcept
	{
		return(MEntryType);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------