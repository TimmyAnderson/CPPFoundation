//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Collections/CArray.h>
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Exceptions/CValueOutOfRangeException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<Size NUMBER_OF_EVENTS>
	class CManualResetMultiEvent final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			mutable std::mutex									MMutex;
			mutable std::condition_variable						MConditionalVariable;
			bool												MIsSignalized[NUMBER_OF_EVENTS];

		private:
			void CheckEvent(Size Event) const
			{
				if (Event>=NUMBER_OF_EVENTS)
				{
					throw(CValueOutOfRangeException("INDEX is OUT of RANGE !"));
				}
			}

			bool GetFirstSignalized(Size& SignalizedEventIndex) const
			{
				for(Size Index=0;Index<NUMBER_OF_EVENTS;Index++)
				{
					if (MIsSignalized[Index]==true)
					{
						SignalizedEventIndex=Index;

						return(true);
					}
				}

				SignalizedEventIndex=0;

				return(false);
			}

			bool AnySignalized(void) const
			{
				for(Size Index=0;Index<NUMBER_OF_EVENTS;Index++)
				{
					if (MIsSignalized[Index]==true)
					{
						return(true);
					}
				}

				return(false);
			}

			bool AllSignalized(void) const
			{
				for(Size Index=0;Index<NUMBER_OF_EVENTS;Index++)
				{
					if (MIsSignalized[Index]==false)
					{
						return(false);
					}
				}

				return(true);
			}

		public:
			bool IsSignalized(Size Event) const
			{
				CheckEvent(Event);

				std::unique_lock<std::mutex>					Lock(MMutex);
				{
					return(MIsSignalized[Event]);
				}
			}

			void Set(Size Event)
			{
				CheckEvent(Event);

				std::unique_lock<std::mutex>					Lock(MMutex);
				{
					MIsSignalized[Event]=true;

					MConditionalVariable.notify_all();
				}
			}

			void Reset(Size Event)
			{
				CheckEvent(Event);

				std::unique_lock<std::mutex>					Lock(MMutex);
				{
					MIsSignalized[Event]=false;
				}
			}

			void ResetAll(void)
			{
				std::unique_lock<std::mutex>					Lock(MMutex);
				{
					for(Size Index=0;Index<NUMBER_OF_EVENTS;Index++)
					{
						MIsSignalized[Index]=false;
					}
				}
			}

			bool WaitAny(Size& SignalizedEventIndex) const
			{
				std::unique_lock<std::mutex>					Lock(MMutex);
				{
					MConditionalVariable.wait(Lock,[this]{return(AnySignalized());});

					bool										IsSignalized=GetFirstSignalized(SignalizedEventIndex);

					return(IsSignalized);
				}
			}

			bool WaitAny(uint64 Milliseconds, Size& SignalizedEventIndex) const
			{
				std::unique_lock<std::mutex>					Lock(MMutex);
				{
					std::chrono::duration<uint64,std::milli>	Timeout(Milliseconds);
					
					MConditionalVariable.wait_for(Lock,Timeout,[this]{return(AnySignalized());});

					bool										IsSignalized=GetFirstSignalized(SignalizedEventIndex);

					return(IsSignalized);
				}
			}

			void WaitAll(void) const
			{
				std::unique_lock<std::mutex>					Lock(MMutex);
				{
					MConditionalVariable.wait(Lock,[this]{return(AllSignalized());});
				}
			}

			bool WaitAll(uint64 Milliseconds) const
			{
				std::unique_lock<std::mutex>					Lock(MMutex);
				{
					std::chrono::duration<uint64,std::milli>	Timeout(Milliseconds);
					bool										IsSignalized=MConditionalVariable.wait_for(Lock,Timeout,[this]{return(AllSignalized());});

					return(IsSignalized);
				}
			}

		public:
			CManualResetMultiEvent(void)
				: MMutex(), MConditionalVariable()
			{
				for(Size Index=0;Index<NUMBER_OF_EVENTS;Index++)
				{
					MIsSignalized[Index]=false;
				}
			}

			CManualResetMultiEvent(const CArray<bool,NUMBER_OF_EVENTS>& Values)
				: MMutex(), MConditionalVariable()
			{
				for(Size Index=0;Index<NUMBER_OF_EVENTS;Index++)
				{
					MIsSignalized[Index]=Values[Index];
				}
			}

			virtual ~CManualResetMultiEvent(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------