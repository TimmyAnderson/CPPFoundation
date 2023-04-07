//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CMap.h>
#include <Framework/Foundation/Collections/CMultiMap.h>
#include "CCacheEntry.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CCacheManager final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			using												CCacheEntryCollection=CMap<CCacheEntryID,CSPCacheEntry>;

		private:
			CCacheEntryCollection								MCacheEntryCollection;
			CExpirationTime										MExpirationTime;

		public:
			void AddCacheEntry(CSPCacheEntry CacheEntry);
			void AddOrUpdateCacheEntry(CSPCacheEntry CacheEntry);
			void RemoveCacheEntryByID(const CCacheEntryID& CacheEntryID);
			void RemoveCacheEntriesByTime(CSteadyClock::Milliseconds Time);
			void Clear(void);
			CTimeout GetExpirationTime(CSteadyClock::Milliseconds Time) const;
			Size GetLength(void) const;
			CSPCacheEntry GetCacheEntry(const CCacheEntryID& CacheEntryID) const;

		public:
			template<typename TCacheEntry>
			bool HasCacheEntry(const CCacheEntryID& CacheEntryID) const
			{
				static_assert(STypeTraitIsBaseOf<CCacheEntry,TCacheEntry>::Value()==true,"TYPE PARAMETER MUST be a CLASS DERIVED from CLASS [CCacheEntry] !");

				if (MCacheEntryCollection.Contains(CacheEntryID)==true)
				{
					CSPCacheEntry								CacheEntry=MCacheEntryCollection[CacheEntryID];

					if (CacheEntry->IsTypeOf<TCacheEntry>()==true)
					{
						return(true);
					}
				}

				return(false);
			}

			template<typename TCacheEntry>
			CSharedPointer<TCacheEntry> GetCacheEntry(const CCacheEntryID& CacheEntryID) const
			{
				static_assert(STypeTraitIsBaseOf<CCacheEntry,TCacheEntry>::Value()==true,"TYPE PARAMETER MUST be a CLASS DERIVED from CLASS [CCacheEntry] !");

				if (MCacheEntryCollection.Contains(CacheEntryID)==true)
				{
					CSPCacheEntry								CacheEntry=MCacheEntryCollection[CacheEntryID];

					if (CacheEntry->IsTypeOf<TCacheEntry>()==true)
					{
						CSharedPointer<TCacheEntry>				TypedCacheEntry=CacheEntry.DynamicCast<TCacheEntry>();

						return(TypedCacheEntry);
					}
				}

				return(nullptr);
			}

		public:
			CCacheEntryCollection::CMapValueIterator Begin(void);
			CCacheEntryCollection::CMapValueIterator End(void);
			CCacheEntryCollection::CMapValueIteratorConst Begin(void) const;
			CCacheEntryCollection::CMapValueIteratorConst End(void) const;
			CCacheEntryCollection::CMapValueIterator begin(void);
			CCacheEntryCollection::CMapValueIterator end(void);
			CCacheEntryCollection::CMapValueIteratorConst begin(void) const;
			CCacheEntryCollection::CMapValueIteratorConst end(void) const;

		public:
			CCacheManager(void);
			virtual ~CCacheManager(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------