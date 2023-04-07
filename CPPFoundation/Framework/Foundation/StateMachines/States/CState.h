//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Types/TypeTraits.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CState final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			bool												MIsValidState;
			int32												MState;
			bool												MIsFinalState;
			CString												MStateName;

		public:
			CState& operator=(const CState& Other);
			CState& operator=(CState&& Other) noexcept;
			bool operator==(const CState& Other) const;
			bool operator!=(const CState& Other) const;
			bool operator<(const CState& Other) const;
			bool operator>(const CState& Other) const;
			bool operator<=(const CState& Other) const;
			bool operator>=(const CState& Other) const;

		public:
			virtual CString ToString(void) const override;
			int32 GetState(void) const noexcept;
			void SetState(int32 State) noexcept;
			void ResetState(void) noexcept;
			bool IsValidState(void) const noexcept;
			bool IsFinalState(void) const noexcept;
			const CString& GetStateName(void) const noexcept;
			bool IsEqual(const CState& Other) const noexcept;

		public:
			CState(void);
			CState(int32 State, bool IsFinalState, const CString& StateName);

			template<typename TEnumType>
			CState(TEnumType State, bool IsFinalState, const CString& StateName)
				: MIsValidState(true), MState(static_cast<int32>(State)), MIsFinalState(IsFinalState), MStateName(StateName)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"CONSTRUCTOR can NOT be used for NON ENUM TYPES !");
			}

			CState(const CState& Other);
			CState(CState&& Other) noexcept;
			virtual ~CState(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------