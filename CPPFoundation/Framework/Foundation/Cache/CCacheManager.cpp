//----------------------------------------------------------------------------------------------------------------------
#include "CCacheManager.h"
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CCacheManager::CCacheManager(void)
		: MCacheEntryCollection(), MExpirationTime()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CCacheManager::~CCacheManager(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CCacheManager::AddCacheEntry(CSPCacheEntry CacheEntry)
	{
		if (MCacheEntryCollection.Contains(CacheEntry->GetID())==false)
		{
			MCacheEntryCollection.Add(CacheEntry->GetID(),CacheEntry);

			MExpirationTime=CExpirationTime::Min(MExpirationTime,CacheEntry->GetExpirationTime());
		}
		else
		{
			throw(CInvalidOperationException(CString::Format("CACHE ENTRY [",CacheEntry->GetID(),"] is already PRESENT !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CCacheManager::AddOrUpdateCacheEntry(CSPCacheEntry CacheEntry)
	{
		RemoveCacheEntryByID(CacheEntry->GetID());

		AddCacheEntry(CacheEntry);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CCacheManager::RemoveCacheEntryByID(const CCacheEntryID& CacheEntryID)
	{
		MCacheEntryCollection.Erase(CacheEntryID);

		MExpirationTime.Reset();

		for(CCacheEntryCollection::CMapIteratorConst Iterator=MCacheEntryCollection.ConstBegin();Iterator!=MCacheEntryCollection.ConstEnd();Iterator++)
		{
			MExpirationTime=CExpirationTime::Min(MExpirationTime,Iterator->GetSecond()->GetExpirationTime());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CCacheManager::RemoveCacheEntriesByTime(CSteadyClock::Milliseconds Time)
	{
		if (MExpirationTime.HasExpired(Time)==false)
		{
			return;
		}

		MExpirationTime.Reset();

		for(CCacheEntryCollection::CMapIteratorConst Iterator=MCacheEntryCollection.ConstBegin();Iterator!=MCacheEntryCollection.ConstEnd();)
		{
			if (Iterator->GetSecond()->GetExpirationTime().HasExpired(Time)==true)
			{
				CCacheEntryCollection::CMapIteratorConst		RemoveIterator=Iterator++;

				MCacheEntryCollection.Erase(RemoveIterator);
			}
			else
			{
				MExpirationTime=CExpirationTime::Min(MExpirationTime,Iterator->GetSecond()->GetExpirationTime());

				Iterator++;
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CCacheManager::Clear(void)
	{
		MCacheEntryCollection.Clear();
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CCacheManager::GetExpirationTime(CSteadyClock::Milliseconds Time) const
	{
		CTimeout												Timeout=MExpirationTime.CalculateTimeout(Time);

		return(Timeout);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CCacheManager::GetLength(void) const
	{
		return(MCacheEntryCollection.GetLength());
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPCacheEntry CCacheManager::GetCacheEntry(const CCacheEntryID& CacheEntryID) const
	{
		if (MCacheEntryCollection.Contains(CacheEntryID)==true)
		{
			return(MCacheEntryCollection[CacheEntryID]);
		}
		else
		{
			return(nullptr);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CCacheManager::CCacheEntryCollection::CMapValueIterator CCacheManager::Begin(void)
	{
		return(MCacheEntryCollection.BeginValue());
	}
//----------------------------------------------------------------------------------------------------------------------
	CCacheManager::CCacheEntryCollection::CMapValueIterator CCacheManager::End(void)
	{
		return(MCacheEntryCollection.EndValue());
	}
//----------------------------------------------------------------------------------------------------------------------
	CCacheManager::CCacheEntryCollection::CMapValueIteratorConst CCacheManager::Begin(void) const
	{
		return(MCacheEntryCollection.BeginValue());
	}
//----------------------------------------------------------------------------------------------------------------------
	CCacheManager::CCacheEntryCollection::CMapValueIteratorConst CCacheManager::End(void) const
	{
		return(MCacheEntryCollection.EndValue());
	}
//----------------------------------------------------------------------------------------------------------------------
	CCacheManager::CCacheEntryCollection::CMapValueIterator CCacheManager::begin(void)
	{
		return(MCacheEntryCollection.BeginValue());
	}
//----------------------------------------------------------------------------------------------------------------------
	CCacheManager::CCacheEntryCollection::CMapValueIterator CCacheManager::end(void)
	{
		return(MCacheEntryCollection.EndValue());
	}
//----------------------------------------------------------------------------------------------------------------------
	CCacheManager::CCacheEntryCollection::CMapValueIteratorConst CCacheManager::begin(void) const
	{
		return(MCacheEntryCollection.BeginValue());
	}
//----------------------------------------------------------------------------------------------------------------------
	CCacheManager::CCacheEntryCollection::CMapValueIteratorConst CCacheManager::end(void) const
	{
		return(MCacheEntryCollection.EndValue());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------