//----------------------------------------------------------------------------------------------------------------------
#include "CSocketStatistics.h"
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
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
	CSocketStatistics::CSocketStatistics(void)
		: MMutex(), MSocketCollection(), MTotalNumberOfBytesSent(), MTotalSumOfBytesSent(), MTotalNumberOfBytesReceived(), MTotalSumOfBytesReceived()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketStatistics::~CSocketStatistics(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketStatistics::AddSocket(const CSocketID& SocketID)
	{
		CLock													Lock(MMutex);
		{
			MSocketCollection.Add(SocketID,CSPSocketStatisticsRecord(new CSocketStatisticsRecord(SocketID)));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketStatistics::RemoveSocket(const CSocketID& SocketID)
	{
		CLock													Lock(MMutex);
		{
			MSocketCollection.Erase(SocketID);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketStatistics::AddSocketSentBytes(const CSocketID& SocketID, Size NumberOfBytesSent, Size SumOfBytesSent)
	{
		CLock													Lock(MMutex);
		{
			if (MSocketCollection.Contains(SocketID)==false)
			{
				throw(CInvalidOperationException("SOCKET doesn't EXIST !"));
			}

			MSocketCollection[SocketID]->AddSentBytes(NumberOfBytesSent,SumOfBytesSent);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketStatistics::AddSocketReceivedBytes(const CSocketID& SocketID, Size NumberOfBytesReceived, Size SumOfBytesReceived)
	{
		CLock													Lock(MMutex);
		{
			if (MSocketCollection.Contains(SocketID)==false)
			{
				throw(CInvalidOperationException("SOCKET doesn't EXIST !"));
			}

			MSocketCollection[SocketID]->AddReceivedBytes(NumberOfBytesReceived,SumOfBytesReceived);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketStatistics::AddTotalSentBytes(Size NumberOfBytesSent, Size SumOfBytesSent)
	{
		CLock													Lock(MMutex);
		{
			MTotalNumberOfBytesSent.Increment(NumberOfBytesSent);
			MTotalSumOfBytesSent.Increment(SumOfBytesSent);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketStatistics::AddTotalReceivedBytes(Size NumberOfBytesReceived, Size SumOfBytesReceived)
	{
		CLock													Lock(MMutex);
		{
			MTotalNumberOfBytesReceived.Increment(NumberOfBytesReceived);
			MTotalSumOfBytesReceived.Increment(SumOfBytesReceived);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketStatistics::GetSocketNumberOfBytesSent(const CSocketID& SocketID) const
	{
		CLock													Lock(MMutex);
		{
			if (MSocketCollection.Contains(SocketID)==false)
			{
				throw(CInvalidOperationException("SOCKET doesn't EXIST !"));
			}

			return(MSocketCollection[SocketID]->GetNumberOfBytesSent());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketStatistics::GetSocketSumOfBytesSent(const CSocketID& SocketID) const
	{
		CLock													Lock(MMutex);
		{
			if (MSocketCollection.Contains(SocketID)==false)
			{
				throw(CInvalidOperationException("SOCKET doesn't EXIST !"));
			}

			return(MSocketCollection[SocketID]->GetSumOfBytesSent());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketStatistics::GetSocketNumberOfBytesReceived(const CSocketID& SocketID) const
	{
		CLock													Lock(MMutex);
		{
			if (MSocketCollection.Contains(SocketID)==false)
			{
				throw(CInvalidOperationException("SOCKET doesn't EXIST !"));
			}

			return(MSocketCollection[SocketID]->GetNumberOfBytesReceived());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketStatistics::GetSocketSumOfBytesReceived(const CSocketID& SocketID) const
	{
		CLock													Lock(MMutex);
		{
			if (MSocketCollection.Contains(SocketID)==false)
			{
				throw(CInvalidOperationException("SOCKET doesn't EXIST !"));
			}

			return(MSocketCollection[SocketID]->GetSumOfBytesReceived());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketStatistics::GetTotalNumberOfBytesSent(void) const noexcept
	{
		CLock													Lock(MMutex);
		{
			return(MTotalNumberOfBytesSent.GetValue());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketStatistics::GetTotalSumOfBytesSent(void) const noexcept
	{
		CLock													Lock(MMutex);
		{
			return(MTotalSumOfBytesSent.GetValue());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketStatistics::GetTotalNumberOfBytesReceived(void) const noexcept
	{
		CLock													Lock(MMutex);
		{
			return(MTotalNumberOfBytesReceived.GetValue());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketStatistics::GetTotalSumOfBytesReceived(void) const noexcept
	{
		CLock													Lock(MMutex);
		{
			return(MTotalSumOfBytesReceived.GetValue());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------