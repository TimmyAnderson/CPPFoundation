//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CMap.h>
#include <Framework/Foundation/Threads/CLock.h>
#include <Framework/Foundation/Threads/CMutex.h>
#include "CSocketStatisticsRecord.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketStatistics final : public CPPFoundation::Foundation::CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												CSocketStatisticsCollection=CPPFoundation::Foundation::CMap<CPPFoundation::Foundation::CSocketID,CSPSocketStatisticsRecord>;

		private:
			mutable CPPFoundation::Foundation::CMutex				MMutex;
			CSocketStatisticsCollection							MSocketCollection;
			CPPFoundation::Foundation::CAtomic<Size>				MTotalNumberOfBytesSent;
			CPPFoundation::Foundation::CAtomic<Size>				MTotalSumOfBytesSent;
			CPPFoundation::Foundation::CAtomic<Size>				MTotalNumberOfBytesReceived;
			CPPFoundation::Foundation::CAtomic<Size>				MTotalSumOfBytesReceived;

		public:
			void AddSocket(const CPPFoundation::Foundation::CSocketID& SocketID);
			void RemoveSocket(const CPPFoundation::Foundation::CSocketID& SocketID);

		public:
			void AddSocketSentBytes(const CPPFoundation::Foundation::CSocketID& SocketID, Size NumberOfBytesSent, Size SumOfBytesSent);
			void AddSocketReceivedBytes(const CPPFoundation::Foundation::CSocketID& SocketID, Size NumberOfBytesReceived, Size SumOfBytesReceived);
			void AddTotalSentBytes(Size NumberOfBytesSent, Size SumOfBytesSent);
			void AddTotalReceivedBytes(Size NumberOfBytesReceived, Size SumOfBytesReceived);

		public:
			Size GetSocketNumberOfBytesSent(const CPPFoundation::Foundation::CSocketID& SocketID) const;
			Size GetSocketNumberOfBytesReceived(const CPPFoundation::Foundation::CSocketID& SocketID) const;
			Size GetSocketSumOfBytesSent(const CPPFoundation::Foundation::CSocketID& SocketID) const;
			Size GetSocketSumOfBytesReceived(const CPPFoundation::Foundation::CSocketID& SocketID) const;
			Size GetTotalNumberOfBytesSent(void) const noexcept;
			Size GetTotalSumOfBytesSent(void) const noexcept;
			Size GetTotalNumberOfBytesReceived(void) const noexcept;
			Size GetTotalSumOfBytesReceived(void) const noexcept;

		public:
			CSocketStatistics(void);
			virtual ~CSocketStatistics(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------