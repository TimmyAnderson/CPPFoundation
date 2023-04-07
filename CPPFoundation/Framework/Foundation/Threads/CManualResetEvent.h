//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <mutex>
#include <condition_variable>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Objects/CObject.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CManualResetEvent final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			mutable std::mutex									MMutex;
			mutable std::condition_variable						MConditionalVariable;
			bool												MIsSignalized;

		public:
			bool IsSignalized(void) const;
			void Set(void);
			void Reset(void);
			void Wait(void) const;
			bool Wait(uint64 Milliseconds) const;

		public:
			CManualResetEvent(void);
			CManualResetEvent(bool IsSignalized);
			virtual ~CManualResetEvent(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------