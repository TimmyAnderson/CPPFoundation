//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <mutex>
#include <condition_variable>
#include <ratio>
#include <Framework/Foundation/Collections/CArray.h>
#include <Framework/Foundation/Exceptions/CValueOutOfRangeException.h>
#include <Framework/Platform/Global/Macros.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<Size NUMBER_OF_EVENTS>
	class CAutoResetMultiEvent final : public CObject
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

			bool GetFirstSignalized(Size& SignalizedEventIndex)
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

			bool AnySignalized(void)
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

			bool AllSignalized(void)
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

			bool WaitAny(Size& SignalizedEventIndex)
			{
				std::unique_lock<std::mutex>					Lock(MMutex);
				{
					MConditionalVariable.wait(Lock,[this]{return(AnySignalized());});

					bool										IsSignalized=GetFirstSignalized(SignalizedEventIndex);

					if (IsSignalized==true)
					{
						MIsSignalized[SignalizedEventIndex]=false;
					}

					return(IsSignalized);
				}
			}

			bool WaitAny(uint64 Milliseconds, Size& SignalizedEventIndex)
			{
				std::unique_lock<std::mutex>					Lock(MMutex);
				{
					std::chrono::duration<uint64,std::milli>	Timeout(Milliseconds);
					
					MConditionalVariable.wait_for(Lock,Timeout,[this]{return(AnySignalized());});

					bool										IsSignalized=GetFirstSignalized(SignalizedEventIndex);

					if (IsSignalized==true)
					{
						MIsSignalized[SignalizedEventIndex]=false;
					}

					return(IsSignalized);
				}
			}

			void WaitAll(void)
			{
				std::unique_lock<std::mutex>					Lock(MMutex);
				{
					MConditionalVariable.wait(Lock,[this]{return(AllSignalized());});

					for(Size Index=0;Index<NUMBER_OF_EVENTS;Index++)
					{
						MIsSignalized[Index]=false;
					}
				}
			}

			bool WaitAll(uint64 Milliseconds)
			{
				std::unique_lock<std::mutex>					Lock(MMutex);
				{
					std::chrono::duration<uint64,std::milli>	Timeout(Milliseconds);
					bool										IsSignalized=MConditionalVariable.wait_for(Lock,Timeout,[this]{return(AllSignalized());});

					for(Size Index=0;Index<NUMBER_OF_EVENTS;Index++)
					{
						MIsSignalized[Index]=false;
					}

					return(IsSignalized);
				}
			}

		public:
			CAutoResetMultiEvent(void)
				: MMutex(), MConditionalVariable(), MIsSignalized()
			{
				for(Size Index=0;Index<NUMBER_OF_EVENTS;Index++)
				{
					MIsSignalized[Index]=false;
				}
			}

			CAutoResetMultiEvent(const CArray<bool,NUMBER_OF_EVENTS>& Values)
				: MMutex(), MConditionalVariable()
			{
				for(Size Index=0;Index<NUMBER_OF_EVENTS;Index++)
				{
					MIsSignalized[Index]=Values[Index];
				}
			}

			virtual ~CAutoResetMultiEvent(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------