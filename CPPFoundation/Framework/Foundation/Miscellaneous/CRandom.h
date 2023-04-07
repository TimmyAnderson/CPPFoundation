//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <random>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Types/CPrimitiveType.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TIntegerType>
	class CRandom final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		static_assert(std::is_same<TIntegerType,int16>::value==true || std::is_same<TIntegerType,uint16>::value==true || std::is_same<TIntegerType,int32>::value==true || std::is_same<TIntegerType,uint32>::value==true || std::is_same<TIntegerType,int64>::value==true || std::is_same<TIntegerType,uint64>::value==true || std::is_same<TIntegerType,Size>::value==true,"TYPE is NOT SUPPORTED for TEMPLATE [CRandom<TIntegerType>] !");

		private:
			std::random_device									MRandomDevice;
			std::mt19937										MGenerator;
			std::uniform_int_distribution<TIntegerType>			MDistribution;

		public:
			TIntegerType Min(void) const noexcept
			{
				return(MDistribution.min());
			}

			TIntegerType Max(void) const noexcept
			{
				return(MDistribution.max());
			}

		public:
			TIntegerType GetRandomValue(void)
			{
				return(MDistribution(MGenerator));
			}

		public:
			CRandom(TIntegerType Min=CPrimitiveType<TIntegerType>::Min(), TIntegerType Max=CPrimitiveType<TIntegerType>::Max())
				: MRandomDevice(), MGenerator(MRandomDevice()), MDistribution(Min,Max)
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<>
	class CRandom<int8> final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			std::random_device									MRandomDevice;
			std::mt19937										MGenerator;
			std::uniform_int_distribution<int16>				MDistribution;

		public:
			int8 Min(void) const noexcept
			{
				return(static_cast<int8>(MDistribution.min()));
			}

			int8 Max(void) const noexcept
			{
				return(static_cast<int8>(MDistribution.max()));
			}

		public:
			int8 GetRandomValue(void)
			{
				return(static_cast<int8>(MDistribution(MGenerator)));
			}

		public:
			CRandom(int8 Min=CPrimitiveType<int8>::Min(), int8 Max=CPrimitiveType<int8>::Max())
				: MRandomDevice(), MGenerator(MRandomDevice()), MDistribution(Min,Max)
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<>
	class CRandom<uint8> final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			std::random_device									MRandomDevice;
			std::mt19937										MGenerator;
			std::uniform_int_distribution<uint16>				MDistribution;

		public:
			uint8 Min(void) const noexcept
			{
				return(static_cast<uint8>(MDistribution.min()));
			}

			uint8 Max(void) const noexcept
			{
				return(static_cast<uint8>(MDistribution.max()));
			}

		public:
			uint8 GetRandomValue(void)
			{
				return(static_cast<uint8>(MDistribution(MGenerator)));
			}

		public:
			CRandom(uint8 Min=CPrimitiveType<uint8>::Min(), uint8 Max=CPrimitiveType<uint8>::Max())
				: MRandomDevice(), MGenerator(MRandomDevice()), MDistribution(Min,Max)
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------