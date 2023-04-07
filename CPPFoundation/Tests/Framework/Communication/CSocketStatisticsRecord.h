//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketID.h>
#include <Framework/Foundation/Threads/CAtomic.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketStatisticsRecord final : public CPPFoundation::Foundation::CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CPPFoundation::Foundation::CSocketID					MSocketID;
			CPPFoundation::Foundation::CAtomic<Size>				MNumberOfBytesSent;
			CPPFoundation::Foundation::CAtomic<Size>				MSumOfBytesSent;
			CPPFoundation::Foundation::CAtomic<Size>				MNumberOfBytesReceived;
			CPPFoundation::Foundation::CAtomic<Size>				MSumOfBytesReceived;

		public:
			void AddSentBytes(Size NumberOfBytesSent, Size SumOfBytesSent);
			void AddReceivedBytes(Size NumberOfBytesReceived, Size SumOfBytesReceived);

		public:
			const CPPFoundation::Foundation::CSocketID& GetSocketID(void) const noexcept;
			Size GetNumberOfBytesSent(void) const noexcept;
			Size GetSumOfBytesSent(void) const noexcept;
			Size GetNumberOfBytesReceived(void) const noexcept;
			Size GetSumOfBytesReceived(void) const noexcept;

		public:
			CSocketStatisticsRecord(const CPPFoundation::Foundation::CSocketID& SocketID);
			virtual ~CSocketStatisticsRecord(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketStatisticsRecord=CPPFoundation::Foundation::CSharedPointer<CSocketStatisticsRecord>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------