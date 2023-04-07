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
	template<typename TClassName, typename TPrototype>
	class CMethod final : public ICallableObject<TPrototype>
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
	template<typename TClassType, typename TResultType, typename... TParameters>
	class CMethod<TClassType,TResultType(TParameters...)> final : public ICallableObject<TResultType(TParameters...)>
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												MethodType=std::function<TResultType(TClassType*,TParameters...)>;

		private:
			TClassType*											MObject;
			MethodType											MFunction;

		public:
			CMethod& operator=(const CMethod<TClassType,TResultType(TParameters...)>& Other)
			{
				MObject=Other.MObject;
				MFunction=Other.MFunction;

				return(*this);
			}

		protected:
			virtual TResultType InternalExecute(TParameters... Parameters) const override
			{
				return(MFunction(MObject,FUNCTION_FORWARD<TParameters>(Parameters)...));
			}

		public:
			TResultType operator()(TParameters... Parameters) const
			{
				return(MFunction(MObject,FUNCTION_FORWARD<TParameters>(Parameters)...));
			}

		public:
			virtual bool IsValid(void) const noexcept override
			{
				return(MFunction.operator bool());
			}

		public:
			template<typename TFunction>
			CMethod(TClassType* Object, TFunction Function)
				: MObject(Object), MFunction(FUNCTION_MOVE(Function))
			{
			}

			CMethod(const CMethod<TClassType,TResultType(TParameters...)>& Other)
				: MObject(Other.MObject), MFunction(Other.MFunction)
			{
			}

			virtual ~CMethod(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------