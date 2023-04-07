//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <Framework/Foundation/Objects/CObject.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	struct SBool final
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			bool												MValue;

		public:
			operator bool(void) const noexcept;

		public:
			SBool& operator=(const SBool& Other) noexcept;
			SBool& operator=(bool Other) noexcept;

		public:
			bool operator==(const SBool& Other) const noexcept;
			bool operator==(bool Other) const noexcept;
			bool operator!=(const SBool& Other) const noexcept;
			bool operator!=(bool Other) const noexcept;

		public:
			bool GetValue(void) const noexcept;

		public:
			SBool(void);
			SBool(bool Value);
			~SBool(void);
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline std::ostream& operator<<(std::ostream& Stream, SBool Value)
	{
		if (Value.GetValue()==true)
		{
			Stream << "1";
		}
		else
		{
			Stream << "0";
		}

		return(Stream);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------