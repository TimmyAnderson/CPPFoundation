//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Threads/CMutex.h>
#include <Framework/Foundation/Threads/CLock.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CRandom.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CID : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			using												CCSPString=CSharedPointer<const CString>;

		private:
			static const Size									MAXIMUM_VALUE;
			static const Size									PAD_SIZE;

		private:
			static CMutex										MMutex;
			static CRandom<uint64>								MRandom;

		private:
			CCSPString											MID;

		public:
			friend bool operator==(const CID& Left, const CID& Right);
			friend bool operator!=(const CID& Left, const CID& Right);
			friend bool operator<(const CID& Left, const CID& Right);
			friend bool operator<=(const CID& Left, const CID& Right);
			friend bool operator>(const CID& Left, const CID& Right);
			friend bool operator>=(const CID& Left, const CID& Right);

		public:
			CID& operator=(const CID& Other);
			CID& operator=(CID&& Other) noexcept;

		public:
			static CID CreateID(void);
			static CID CreateEmptyID(void);
			static CString CreateEmptyIDAsString(void);

		public:
			virtual CString ToString(void) const override;
			CCSPString GetRawID(void) const noexcept;
			const CString& GetID(void) const noexcept;
			bool IsEmpty(void) const noexcept;

		public:
			CID(const CString& ID);
			CID(CString&& ID);
			CID(CCSPString ID);
			CID(const CID& Other);
			CID(CID&& Other) noexcept;
			virtual ~CID(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool operator==(const CID& Left, const CID& Right);
	bool operator!=(const CID& Left, const CID& Right);
	bool operator<(const CID& Left, const CID& Right);
	bool operator<=(const CID& Left, const CID& Right);
	bool operator>(const CID& Left, const CID& Right);
	bool operator>=(const CID& Left, const CID& Right);
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------