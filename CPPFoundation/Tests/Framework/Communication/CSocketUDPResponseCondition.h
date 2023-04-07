//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketID.h>
#include "CSocketUDPResponse.h"
#include "CSocketUDPResponseConditionData.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPResponseCondition final : public CPPFoundation::Foundation::CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			using												CConditionDataCollection=CPPFoundation::Foundation::CVector<CSocketUDPResponseConditionData>;

		private:
			bool												MUseSocketID;
			CPPFoundation::Foundation::CSocketID					MSocketID;
			bool												MUseAddress;
			CPPFoundation::Foundation::CSocketUDPAddress			MAddress;
			CConditionDataCollection							MConditionDataCollection;
			Size												MNumberOfBytesInConditionDataCollection;
			bool												MUseReceivedSocketAddress;
			CSPSocketUDPResponse								MResponse;

		public:
			static Size CalculateNumberOfBytes(const CConditionDataCollection& ConditionDataCollection) noexcept;

		public:
			bool GetUseSocketID(void) const noexcept;
			const CPPFoundation::Foundation::CSocketID& GetSocketID(void) const noexcept;
			bool GetUseAddress(void) const noexcept;
			const CPPFoundation::Foundation::CSocketUDPAddress& GetAddress(void) const noexcept;
			const CConditionDataCollection& GetConditionDataCollection(void) const noexcept;
			bool GetUseReceivedSocketAddress(void) const noexcept;
			CSPSocketUDPResponse GetResponse(void) const noexcept;
			bool CheckCondition(const CPPFoundation::Foundation::CSocketID& SocketID, const CPPFoundation::Foundation::CSocketUDPAddress Address, CPPFoundation::Foundation::CCSPByteBuffer Data) const noexcept;

		public:
			CSocketUDPResponseCondition(bool UseSocketID, const CPPFoundation::Foundation::CSocketID& SocketID, bool UseAddress, const CPPFoundation::Foundation::CSocketUDPAddress& Address, const CConditionDataCollection& ConditionDataCollection, bool UseReceivedSocketAddress, CSPSocketUDPResponse Response);
			virtual ~CSocketUDPResponseCondition(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDPResponseCondition=CPPFoundation::Foundation::CSharedPointer<CSocketUDPResponseCondition>;
	using														CSocketUDPResponseConditionCollection=CPPFoundation::Foundation::CVector<CSPSocketUDPResponseCondition>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------