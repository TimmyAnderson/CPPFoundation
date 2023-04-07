//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TCollectionType>
	class CIterator final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			TCollectionType&									MCollection;

		public:
			auto begin(void) -> decltype(MCollection.Begin())
			{
				return(MCollection.Begin());
			}

			auto end(void) -> decltype(MCollection.End())
			{
				return(MCollection.End());
			}
	
		public:
			CIterator(TCollectionType& Collection)
				: MCollection(Collection)
			{
			}

			virtual ~CIterator(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TCollectionType>
	class CIteratorConst final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			const TCollectionType&								MCollection;

		public:
			auto begin(void) -> decltype(MCollection.Begin())
			{
				return(MCollection.Begin());
			}

			auto end(void) -> decltype(MCollection.End())
			{
				return(MCollection.End());
			}

		public:
			CIteratorConst(const TCollectionType& Collection)
				: MCollection(Collection)
			{
			}

			virtual ~CIteratorConst(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TCollectionType>
	class CMapValueIterator final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			TCollectionType&									MCollection;

		public:
			auto begin(void) -> decltype(MCollection.BeginValue())
			{
				return(MCollection.BeginValue());
			}

			auto end(void) -> decltype(MCollection.EndValue())
			{
				return(MCollection.EndValue());
			}
	
		public:
			CMapValueIterator(TCollectionType& Collection)
				: MCollection(Collection)
			{
			}

			virtual ~CMapValueIterator(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TCollectionType>
	class CMapValueIteratorConst final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			const TCollectionType&								MCollection;

		public:
			auto begin(void) -> decltype(MCollection.BeginValue())
			{
				return(MCollection.BeginValue());
			}

			auto end(void) -> decltype(MCollection.EndValue())
			{
				return(MCollection.EndValue());
			}

		public:
			CMapValueIteratorConst(const TCollectionType& Collection)
				: MCollection(Collection)
			{
			}

			virtual ~CMapValueIteratorConst(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TCollection> 
	inline CIterator<TCollection> CreateIterator(TCollection& Collection)
	{
		return(CIterator<TCollection>(Collection));
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TCollection> 
	inline CIteratorConst<TCollection> CreateIterator(const TCollection& Collection)
	{
		return(CIteratorConst<TCollection>(Collection));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TCollection> 
	inline CMapValueIterator<TCollection> CreateMapValueIterator(TCollection& Collection)
	{
		return(CMapValueIterator<TCollection>(Collection));
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TCollection> 
	inline CMapValueIteratorConst<TCollection> CreateMapValueIterator(const TCollection& Collection)
	{
		return(CMapValueIteratorConst<TCollection>(Collection));
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------