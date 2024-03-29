//----------------------------------------------------------------------------------------------------------------------
#include "CSocketStatisticsRecord.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketStatisticsRecord::CSocketStatisticsRecord(const CSocketID& SocketID)
		: MSocketID(SocketID), MNumberOfBytesSent(0), MSumOfBytesSent(0), MNumberOfBytesReceived(0), MSumOfBytesReceived(0)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketStatisticsRecord::~CSocketStatisticsRecord(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketStatisticsRecord::AddSentBytes(Size NumberOfBytesSent, Size SumOfBytesSent)
	{
		MNumberOfBytesSent.Increment(NumberOfBytesSent);
		MSumOfBytesSent.Increment(SumOfBytesSent);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketStatisticsRecord::AddReceivedBytes(Size NumberOfBytesReceived, Size SumOfBytesReceived)
	{
		MNumberOfBytesReceived.Increment(NumberOfBytesReceived);
		MSumOfBytesReceived.Increment(SumOfBytesReceived);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketID& CSocketStatisticsRecord::GetSocketID(void) const noexcept
	{
		return(MSocketID);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketStatisticsRecord::GetNumberOfBytesSent(void) const noexcept
	{
		return(MNumberOfBytesSent.GetValue());
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketStatisticsRecord::GetSumOfBytesSent(void) const noexcept
	{
		return(MSumOfBytesSent.GetValue());
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketStatisticsRecord::GetNumberOfBytesReceived(void) const noexcept
	{
		return(MNumberOfBytesReceived.GetValue());
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketStatisticsRecord::GetSumOfBytesReceived(void) const noexcept
	{
		return(MSumOfBytesReceived.GetValue());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------