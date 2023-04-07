//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <functional>
#include <type_traits>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Types/CFunction.h>
#include <Framework/Foundation/Types/CMethod.h>
#include "CMutex.h"
#include "CLock.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType>
	class CAtomic final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			mutable CMutex										MMutex;
			TType												MValue;

		public:
			CAtomic<TType>& operator=(const CAtomic<TType>& Other);
			CAtomic<TType>& operator=(CAtomic<TType>&& Other);

		public:
			TType GetValue(void) const
			{
				CLock											Lock(MMutex);
				{
					return(MValue);
				}
			}

			void SetValue(const TType& Value)
			{
				CLock											Lock(MMutex);
				{
					MValue=Value;
				}
			}

			void Execute(const ICallableObject<void(TType&)>& CodeToExecute)
			{
				CLock											Lock(MMutex);
				{
					CodeToExecute(std::ref(MValue));
				}
			}

			void Execute(const std::function<void(TType&)>& CodeToExecute)
			{
				CLock											Lock(MMutex);
				{
					CodeToExecute(std::ref(MValue));
				}
			}

			template<typename TParameter=TType>
			typename std::enable_if<std::is_integral<TParameter>::value==true,TType>::type Increment(void)
			{
				CLock											Lock(MMutex);
				{
					MValue++;

					return(MValue);
				}
			}

			template<typename TParameter=TType>
			typename std::enable_if<std::is_integral<TParameter>::value==true,TType>::type Increment(TParameter Value)
			{
				CLock											Lock(MMutex);
				{
					MValue+=Value;

					return(MValue);
				}
			}

			template<typename TParameter=TType>
			typename std::enable_if<std::is_integral<TParameter>::value==true,TType>::type Decrement(void)
			{
				CLock											Lock(MMutex);
				{
					MValue--;

					return(MValue);
				}
			}

			template<typename TParameter=TType>
			typename std::enable_if<std::is_integral<TParameter>::value==true,TType>::type Decrement(TParameter Value)
			{
				CLock											Lock(MMutex);
				{
					MValue-=Value;

					return(MValue);
				}
			}

		public:
			CAtomic(void)
				: MMutex(), MValue()
			{
			}

			CAtomic(const TType& Value)
				: MMutex(), MValue(Value)
			{
			}

			CAtomic(const CAtomic<TType>&)=delete;
			CAtomic(CAtomic<TType>&&)=delete;

			virtual ~CAtomic(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------