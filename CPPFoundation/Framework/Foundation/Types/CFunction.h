//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <functional>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Objects/CObject.h>
#include "ICallableObject.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TPrototype>
	class CFunction final : public ICallableObject<TPrototype>
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			virtual bool IsValid(void) const noexcept override
			{
				return(false);
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TResultType, typename... TParameters>
	class CFunction<TResultType(TParameters...)> final : public ICallableObject<TResultType(TParameters...)>
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												FunctionType=std::function<TResultType(TParameters...)>;

		private:
			FunctionType										MFunction;

		public:
			CFunction& operator=(const CFunction<TResultType(TParameters...)>& Other)
			{
				MFunction=Other.MFunction;

				return(*this);
			}

		protected:
			virtual TResultType InternalExecute(TParameters... Parameters) const override
			{
				return(MFunction(FUNCTION_FORWARD<TParameters>(Parameters)...));
			}

		public:
			TResultType operator()(TParameters... Parameters) const
			{
				return(MFunction(FUNCTION_FORWARD<TParameters>(Parameters)...));
			}

		public:
			virtual bool IsValid(void) const noexcept override
			{
				return(MFunction.operator bool());
			}

		public:
			CFunction(void) noexcept
				: MFunction()
			{
			}

			template<typename TFunction>
			CFunction(TFunction Function)
				: MFunction(FUNCTION_MOVE(Function))
			{
			}

			CFunction(const CFunction<TResultType(TParameters...)>& Other)
				: MFunction(Other.MFunction)
			{
			}

			virtual ~CFunction(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------