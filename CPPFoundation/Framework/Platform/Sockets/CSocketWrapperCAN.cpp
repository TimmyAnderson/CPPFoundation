//----------------------------------------------------------------------------------------------------------------------
#include "CSocketWrapperCAN.h"
#if defined(PLATFORM_WINDOWS)
#elif defined(PLATFORM_LINUX)
#include <cstring>
#include <fcntl.h>
#include <linux/can.h>
#include <net/if.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <unistd.h>
#else
#error UNSUPPORTED PLATFORM !
#endif
#include <Framework/Foundation/Exceptions/CNotImplementedException.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANReceiveFromParameters.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANSendToParameters.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANAddress.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANFrame.h>
#include <Framework/Foundation/Exceptions/CNotImplementedException.h>
#include <Framework/Foundation/Exceptions/CSocketException.h>
#include "CSocketError.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Platform
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketWrapperCAN::CSocketWrapperCAN(void)
#if defined(PLATFORM_WINDOWS)
#elif defined(PLATFORM_LINUX)
		: MSocket(-1)
#else
#error UNSUPPORTED PLATFORM !
#endif
	{
#if defined(PLATFORM_WINDOWS)
#elif defined(PLATFORM_LINUX)
		try
		{
			MSocket=static_cast<int32>(socket(AF_CAN,SOCK_RAW,CAN_RAW));

			if (MSocket==-1)
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("SOCKET FAILED to CREATE !",ErrorCode,SocketExceptionCode));
			}

			ChangeBlockingState(false);
		}
		catch(...)
		{
			Uninitialize();
			throw;
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketWrapperCAN::~CSocketWrapperCAN(void)
	{
		Uninitialize();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketWrapperCAN::Uninitialize(void) noexcept
	{
#if defined(PLATFORM_WINDOWS)
#elif defined(PLATFORM_LINUX)
		if (MSocket!=-1)
		{
			close(MSocket);
			MSocket=-1;
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketWrapperCAN::ToString(void) const
	{
		return(CString::Format("CAN SOCKET WRAPPER [",GetSocketHandler(),"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSocketWrapperCAN::GetSocketHandler(void) const noexcept
	{
#if defined(PLATFORM_WINDOWS)
		return(0);
#elif defined(PLATFORM_LINUX)
		return(static_cast<int32>(MSocket));
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketPlaformData CSocketWrapperCAN::GetPlatformData(void) const
	{
#if defined(PLATFORM_WINDOWS)
		throw(CNotImplementedException("OPERATION is NOT SUPPORTED on WINDOWS PLATFORM !"));
#elif defined(PLATFORM_LINUX)
		return(CSocketPlaformData(MSocket));
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketWrapperCAN::BindToAddress(const CSocketCANAddress& Address)
	{
#if defined(PLATFORM_WINDOWS)
		static_cast<void>(Address);

		throw(CNotImplementedException("OPERATION is NOT SUPPORTED on WINDOWS PLATFORM !"));
#elif defined(PLATFORM_LINUX)
		sockaddr_can											SocketAddress;

		memset(&SocketAddress,0,sizeof(SocketAddress));

		SocketAddress.can_family=static_cast<sa_family_t>(AF_CAN);
		SocketAddress.can_ifindex=static_cast<int>(Address.GetNetworkInterfaceIndex());
		SocketAddress.can_addr.tp.rx_id=static_cast<canid_t>(Address.GetProtocolClassAddressReceiveID());
		SocketAddress.can_addr.tp.tx_id=static_cast<canid_t>(Address.GetProtocolClassAddressSendID());

		if (::bind(MSocket,reinterpret_cast<sockaddr*>(&SocketAddress),sizeof(SocketAddress))!=0)
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to BIND to ADDRESS !",ErrorCode,SocketExceptionCode));
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketWrapperCAN::SendTo(const CSocketCANSendToParameters& Parameters, CSocketCANSendToResult& OperationResult)
	{
#if defined(PLATFORM_WINDOWS)
		static_cast<void>(Parameters);
		static_cast<void>(OperationResult);

		throw(CNotImplementedException("OPERATION is NOT SUPPORTED on WINDOWS PLATFORM !"));
#elif defined(PLATFORM_LINUX)
		const CSocketCANAddress&								Address=Parameters.GetCANAddress();
		const uint8*											Data=Parameters.GetData()->GetRawData(Parameters.GetOffset());

		if ((Parameters.GetOffset()+Parameters.GetNumberOfBytesToSend())>Parameters.GetData()->GetLength())
		{
			throw(CSocketException("SOCKET FAILED to SEND DATA ! INVALID PARAMETERS !"));
		}

		CSocketCANFrame											CANFrame;

		CANFrame.Deserialize(CByteBuffer(Data,Parameters.GetNumberOfBytesToSend()));

		if (CANFrame.GetCANData().GetLength()>CSocketCANFrame::CAN_DATA_LENGTH)
		{
			throw(CSocketException("SOCKET FAILED to SEND DATA ! TOO MANY DATA to SEND !"));
		}

		const CByteBuffer&										RawData=CANFrame.GetCANData();
		sockaddr_can											SocketAddress;
		can_frame												Frame;

		memset(&SocketAddress,0,sizeof(SocketAddress));
		memset(&Frame,0,sizeof(can_frame));

		SocketAddress.can_family=static_cast<sa_family_t>(AF_CAN);
		SocketAddress.can_ifindex=static_cast<int>(Address.GetNetworkInterfaceIndex());
		SocketAddress.can_addr.tp.rx_id=static_cast<canid_t>(Address.GetProtocolClassAddressReceiveID());
		SocketAddress.can_addr.tp.tx_id=static_cast<canid_t>(Address.GetProtocolClassAddressSendID());

		Frame.can_id=static_cast<canid_t>(CANFrame.GetCANID().GetID());
		Frame.can_dlc=static_cast<__u8>(RawData.GetLength());

		for(Size Index=0;Index<RawData.GetLength();Index++)
		{
			Frame.data[Index]=static_cast<__u8>(RawData[Index]);
		}

		ssize_t													Result=sendto(static_cast<int>(MSocket),static_cast<const void*>(&Frame),sizeof(can_frame),0,reinterpret_cast<sockaddr*>(&SocketAddress),static_cast<socklen_t>(sizeof(SocketAddress)));

		if (Result!=-1)
		{
			if (Result==sizeof(can_frame))
			{
				// NUMBER of WRITTEN BYTES is EQUAL to NUMBER of the SIZE of (CANID+DATA).
				Size											NumberOfBytesWritten=Parameters.GetData()->GetLength();

				OperationResult.SetResult(Parameters.GetAddress(),Parameters.GetData(),Parameters.GetOffset(),NumberOfBytesWritten);
			}
			else
			{
				throw(CSocketException("SOCKET FAILED to SEND DATA to ADDRESS ! INCOMPLETE CAN FRAME SENT !"));
			}
		}
		else
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			if (ErrorCode==EAGAIN || ErrorCode==EWOULDBLOCK)
			{
				OperationResult.SetResult(Parameters.GetAddress(),Parameters.GetData(),Parameters.GetOffset(),0);
			}
			else
			{
				throw(CSocketException("SOCKET FAILED to SEND DATA to ADDRESS !",ErrorCode,SocketExceptionCode));
			}
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketWrapperCAN::ReceiveFrom(const CSocketCANReceiveFromParameters& Parameters, CSocketCANReceiveFromResult& OperationResult)
	{
#if defined(PLATFORM_WINDOWS)
		static_cast<void>(Parameters);
		static_cast<void>(OperationResult);
		
		throw(CNotImplementedException("OPERATION is NOT SUPPORTED on WINDOWS PLATFORM !"));
#elif defined(PLATFORM_LINUX)
		Char*													Data=reinterpret_cast<Char*>(Parameters.GetData()->GetRawData(Parameters.GetOffset()));

		if ((Parameters.GetOffset()+Parameters.GetNumberOfBytesToReceive())>Parameters.GetData()->GetLength())
		{
			throw(CSocketException("SOCKET FAILED to RECEIVE DATA ! BUFFER is TOO SHORT !"));
		}

		sockaddr_can											SocketAddress;
		can_frame												Frame;

		memset(&SocketAddress,0,sizeof(SocketAddress));
		memset(&Frame,0,sizeof(can_frame));

		socklen_t												SocketAddressLength=static_cast<socklen_t>(sizeof(SocketAddress));
		ssize_t													Result=recvfrom(MSocket,static_cast<void*>(&Frame),sizeof(can_frame),0,reinterpret_cast<sockaddr*>(&SocketAddress),&SocketAddressLength);

		if (Result!=-1)
		{
			if (Result!=sizeof(can_frame))
			{
				throw(CSocketException(CString::Format("SOCKET FAILED to RECEIVE DATA ! CAN FRAME wasn't READ COMPLETELY ! ONLY [",Result,"] BYTES were READ !")));
			}

			Size												DataSize=static_cast<Size>(Frame.can_dlc);

			if (DataSize>CSocketCANFrame::CAN_DATA_LENGTH)
			{
				throw(CSocketException(CString::Format("SOCKET FAILED to RECEIVE DATA ! CAN DATA is TOO LARGE containing [",DataSize,"] BYTES !")));
			}
			
			CSocketCANAddress									Address(static_cast<int32>(SocketAddress.can_ifindex),static_cast<uint32>(SocketAddress.can_addr.tp.rx_id),static_cast<uint32>(SocketAddress.can_addr.tp.tx_id));
			CSocketCANID										CANID(static_cast<uint32>(Frame.can_id));
			CSocketCANFrame										CANFrame(CANID,CByteBuffer(static_cast<const uint8*>(Frame.data),DataSize));
			CByteBuffer											RawData=CANFrame.Serialize();

			if (Parameters.GetNumberOfBytesToReceive()<RawData.GetLength())
			{
				throw(CSocketException("SOCKET FAILED to RECEIVE DATA ! BUFFER is TOO SHORT !"));
			}

			for(Size Index=0;Index<RawData.GetLength();Index++)
			{
				Data[Index]=static_cast<Char>(RawData[Index]);
			}

			// NUMBER of READ BYTES is EQUAL to NUMBER of the SIZE of (CANID+DATA).
			Size											NumberOfBytesRead=RawData.GetLength();

			OperationResult.SetResult(Parameters.GetData(),Parameters.GetOffset(),NumberOfBytesRead,Address);
		}
		else
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			if (ErrorCode==EAGAIN || ErrorCode==EWOULDBLOCK)
			{
				OperationResult.SetResult(Parameters.GetData(),Parameters.GetOffset(),0,CSocketCANAddress());
			}
			else
			{
				throw(CSocketException("SOCKET FAILED to RECEIVE DATA !",ErrorCode,SocketExceptionCode));
			}
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketWrapperCAN::ChangeBlockingState(bool BlockingState)
	{
#if defined(PLATFORM_WINDOWS)
		static_cast<void>(BlockingState);

		throw(CNotImplementedException("OPERATION is NOT SUPPORTED on WINDOWS PLATFORM !"));
#elif defined(PLATFORM_LINUX)
		int														Flags=fcntl(MSocket,F_GETFL,0);

		if (Flags!=-1)
		{
			if (BlockingState==true)
			{
				Flags=(Flags & ~O_NONBLOCK);
			}
			else
			{
				Flags=(Flags | O_NONBLOCK);
			}

			int													Result=fcntl(static_cast<int>(MSocket),F_SETFL,Flags);

			if (Result==-1)
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("SOCKET FAILED to CHANGE BLOCKING STATE ! SETTING BLOCKING STATE FAILED !",ErrorCode,SocketExceptionCode));
			}
		}
		else
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to CHANGE BLOCKING STATE ! GETTING BLOCKING STATE FAILED !",ErrorCode,SocketExceptionCode));
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketWrapperCAN::GetNetworkInterfaceName(int32 NetworkInterfaceIndex)
	{
#if defined(PLATFORM_WINDOWS)
		static_cast<void>(NetworkInterfaceIndex);

		throw(CNotImplementedException("OPERATION is NOT SUPPORTED on WINDOWS PLATFORM !"));
#elif defined(PLATFORM_LINUX)
		ifreq													Interface;

		Interface.ifr_ifindex=static_cast<int>(NetworkInterfaceIndex);

		int														Result=ioctl(static_cast<int>(MSocket),SIOCGIFNAME,&Interface);

		if (Result!=-1)
		{
			CString												NetworkInterfaceName(Interface.ifr_name);

			return(NetworkInterfaceName);
		}
		else
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to GET NETWORK INTERFACE NAME !",ErrorCode,SocketExceptionCode));
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSocketWrapperCAN::GetNetworkInterfaceIndex(const CString& NetworkInterfaceName)
	{
#if defined(PLATFORM_WINDOWS)
		static_cast<void>(NetworkInterfaceName);

		throw(CNotImplementedException("OPERATION is NOT SUPPORTED on WINDOWS PLATFORM !"));
#elif defined(PLATFORM_LINUX)
		ifreq													Interface;

		strcpy(Interface.ifr_name,NetworkInterfaceName.GetCharArray());

		int														Result=ioctl(static_cast<int>(MSocket),SIOCGIFINDEX,&Interface);

		if (Result!=-1)
		{
			return(static_cast<int32>(Interface.ifr_ifindex));
		}
		else
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to GET NETWORK INTERFACE INDEX !",ErrorCode,SocketExceptionCode));
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSocketWrapperCAN::GetSendBufferSize(void)
	{
#if defined(PLATFORM_WINDOWS)
		throw(CNotImplementedException("OPERATION is NOT SUPPORTED on WINDOWS PLATFORM !"));
#elif defined(PLATFORM_LINUX)
		int														SendBufferSize=0;
		socklen_t												SendBufferSizeLength=sizeof(SendBufferSize);

		if (getsockopt(MSocket,SOL_SOCKET,SO_SNDBUF,static_cast<void*>(&SendBufferSize),&SendBufferSizeLength)!=0 || SendBufferSizeLength!=sizeof(SendBufferSize))
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to GET SEND BUFFER SIZE !",ErrorCode,SocketExceptionCode));
		}

		return(static_cast<int32>(SendBufferSize));
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketWrapperCAN::SetSendBufferSize(int32 SendBufferSize)
	{
#if defined(PLATFORM_WINDOWS)
		static_cast<void>(SendBufferSize);

		throw(CNotImplementedException("OPERATION is NOT SUPPORTED on WINDOWS PLATFORM !"));
#elif defined(PLATFORM_LINUX)
		int														BufferSize=static_cast<int>(SendBufferSize);

		if (setsockopt(MSocket,SOL_SOCKET,SO_SNDBUF,static_cast<void*>(&BufferSize),sizeof(BufferSize))!=0)
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to SET SEND BUFFER SIZE !",ErrorCode,SocketExceptionCode));
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSocketWrapperCAN::GetReceiveBufferSize(void)
	{
#if defined(PLATFORM_WINDOWS)
		throw(CNotImplementedException("OPERATION is NOT SUPPORTED on WINDOWS PLATFORM !"));
#elif defined(PLATFORM_LINUX)
		int														ReceiveBufferSize=0;
		socklen_t												ReceiveBufferSizeLength=sizeof(ReceiveBufferSize);

		if (getsockopt(MSocket,SOL_SOCKET,SO_RCVBUF,static_cast<void*>(&ReceiveBufferSize),&ReceiveBufferSizeLength)!=0 || ReceiveBufferSizeLength!=sizeof(ReceiveBufferSize))
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to GET RECEIVE BUFFER SIZE !",ErrorCode,SocketExceptionCode));
		}

		return(static_cast<int32>(ReceiveBufferSize));
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketWrapperCAN::SetReceiveBufferSize(int32 ReceiveBufferSize)
	{
#if defined(PLATFORM_WINDOWS)
		static_cast<void>(ReceiveBufferSize);

		throw(CNotImplementedException("OPERATION is NOT SUPPORTED on WINDOWS PLATFORM !"));
#elif defined(PLATFORM_LINUX)
		int														BufferSize=static_cast<int>(ReceiveBufferSize);

		if (setsockopt(MSocket,SOL_SOCKET,SO_RCVBUF,static_cast<void*>(&BufferSize),sizeof(BufferSize))!=0)
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to SET RECEIVE BUFFER SIZE !",ErrorCode,SocketExceptionCode));
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------