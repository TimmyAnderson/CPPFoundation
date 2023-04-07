//----------------------------------------------------------------------------------------------------------------------
#include "CSocketWrapperTCP.h"
#if defined(PLATFORM_WINDOWS)
#include <WS2tcpip.h>
#elif defined(PLATFORM_LINUX)
#include <arpa/inet.h>
#include <cstring>
#include <fcntl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#else
#error UNSUPPORTED PLATFORM !
#endif
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPReceiveParameters.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPSendParameters.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPAddress.h>
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
#if defined(PLATFORM_WINDOWS)
	CSocketWrapperTCP::CSocketWrapperTCP(SOCKET Socket)
		: MSocket(Socket), MSocketEvent(WSA_INVALID_EVENT)
#elif defined(PLATFORM_LINUX)
	CSocketWrapperTCP::CSocketWrapperTCP(int Socket)
		: MSocket(Socket)
#else
#error UNSUPPORTED PLATFORM !
#endif
	{
		try
		{
#if defined(PLATFORM_WINDOWS)
			if ((MSocketEvent=WSACreateEvent())==WSA_INVALID_EVENT)
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("SOCKET FAILED to CREATE SOCKET EVENT !",ErrorCode,SocketExceptionCode));
			}

			if (WSAEventSelect(MSocket,MSocketEvent,FD_READ | FD_WRITE | FD_CLOSE | FD_CONNECT | FD_ACCEPT)==SOCKET_ERROR)
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("SOCKET FAILED to ASSOCIATE SOCKET EVENT !",ErrorCode,SocketExceptionCode));
			}

			ChangeBlockingState(false);
#elif defined(PLATFORM_LINUX)
			ChangeBlockingState(false);
#else
#error UNSUPPORTED PLATFORM !
#endif
		}
		catch(...)
		{
			Uninitialize();
			throw;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketWrapperTCP::CSocketWrapperTCP(void)
#if defined(PLATFORM_WINDOWS)
		: MSocket(INVALID_SOCKET), MSocketEvent(WSA_INVALID_EVENT)
#elif defined(PLATFORM_LINUX)
		: MSocket(-1)
#else
#error UNSUPPORTED PLATFORM !
#endif
	{
		try
		{
#if defined(PLATFORM_WINDOWS)
			MSocket=socket(AF_INET,SOCK_STREAM,0);

			if (MSocket==INVALID_SOCKET)
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("SOCKET FAILED to CREATE !",ErrorCode,SocketExceptionCode));
			}

			if ((MSocketEvent=WSACreateEvent())==WSA_INVALID_EVENT)
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("SOCKET FAILED to CREATE SOCKET EVENT !",ErrorCode,SocketExceptionCode));
			}

			if (WSAEventSelect(MSocket,MSocketEvent,FD_READ | FD_WRITE | FD_CLOSE | FD_CONNECT | FD_ACCEPT)==SOCKET_ERROR)
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("SOCKET FAILED to ASSOCIATE SOCKET EVENT !",ErrorCode,SocketExceptionCode));
			}

			ChangeBlockingState(false);
#elif defined(PLATFORM_LINUX)
			MSocket=static_cast<int32>(socket(AF_INET,SOCK_STREAM,0));

			if (MSocket==-1)
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("SOCKET FAILED to CREATE !",ErrorCode,SocketExceptionCode));
			}

			ChangeBlockingState(false);
#else
#error UNSUPPORTED PLATFORM !
#endif
		}
		catch(...)
		{
			Uninitialize();
			throw;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketWrapperTCP::~CSocketWrapperTCP(void)
	{
		Uninitialize();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketWrapperTCP::Uninitialize(void) noexcept
	{
#if defined(PLATFORM_WINDOWS)
		if (MSocketEvent!=WSA_INVALID_EVENT)
		{
			WSACloseEvent(MSocketEvent);
			MSocketEvent=WSA_INVALID_EVENT;
		}

		if (MSocket!=INVALID_SOCKET)
		{
			closesocket(MSocket);
			MSocket=INVALID_SOCKET;
		}
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
	CString CSocketWrapperTCP::ToString(void) const
	{
		return(CString::Format("TCP SOCKET WRAPPER [",GetSocketHandler(),"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CSocketWrapperTCP::GetSocketHandler(void) const noexcept
	{
#if defined(PLATFORM_WINDOWS)
		return(static_cast<int32>(MSocket));
#elif defined(PLATFORM_LINUX)
		return(static_cast<int32>(MSocket));
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketPlaformData CSocketWrapperTCP::GetPlatformData(void) const
	{
#if defined(PLATFORM_WINDOWS)
		return(CSocketPlaformData(MSocket,MSocketEvent));
#elif defined(PLATFORM_LINUX)
		return(CSocketPlaformData(MSocket));
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	CSharedPointer<ISocketTCPWrapper> CSocketWrapperTCP::Accept(CSocketTCPAddress& Address)
	{
		sockaddr_in												SocketAddress;

		memset(&SocketAddress,0,sizeof(SocketAddress));

#if defined(PLATFORM_WINDOWS)
		int														SocketAddressLength=static_cast<int>(sizeof(SocketAddress));
		SOCKET													SocketDescriptor=accept(MSocket,reinterpret_cast<sockaddr*>(&SocketAddress),&SocketAddressLength);

		if (SocketDescriptor!=SOCKET_ERROR)
		{
			Address=CSocketTCPAddress(CSocketIPEndpoint(CSocketIPAddress(SocketAddress.sin_addr.S_un.S_un_b.s_b1,SocketAddress.sin_addr.S_un.S_un_b.s_b2,SocketAddress.sin_addr.S_un.S_un_b.s_b3,SocketAddress.sin_addr.S_un.S_un_b.s_b4),static_cast<uint16>(ntohs(SocketAddress.sin_port))));

			CSharedPointer<ISocketTCPWrapper>					Socket(new CSocketWrapperTCP(SocketDescriptor));

			return(Socket);
		}
		else
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			if (ErrorCode==WSAEWOULDBLOCK)
			{
				return(nullptr);
			}
			else
			{
				throw(CSocketException("SOCKET FAILED to ACCEPT SOCKET !",ErrorCode,SocketExceptionCode));
			}
		}
#elif defined(PLATFORM_LINUX)
		socklen_t												SocketAddressLength=static_cast<socklen_t>(sizeof(SocketAddress));
		int														SocketDescriptor=accept(MSocket,reinterpret_cast<sockaddr*>(&SocketAddress),&SocketAddressLength);

		if (SocketDescriptor!=-1)
		{
			Char												RawIPAddress[INET_ADDRSTRLEN];

			if (inet_ntop(AF_INET,&(SocketAddress.sin_addr),RawIPAddress,INET_ADDRSTRLEN)!=nullptr)
			{
				CSocketIPAddress								IPAddress;

				if (CSocketIPAddress::ParseIPv4Address(RawIPAddress,IPAddress)==true)
				{
					Address=CSocketTCPAddress(CSocketIPEndpoint(IPAddress,static_cast<uint16>(ntohs(SocketAddress.sin_port))));

					CSharedPointer<ISocketTCPWrapper>			Socket(new CSocketWrapperTCP(SocketDescriptor));

					return(Socket);
				}
				else
				{
					throw(CSocketException("SOCKET FAILED to ACCEPT SOCKET ! PARSING of ADDRESS FAILED !"));
				}
			}
			else
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("SOCKET FAILED to ACCEPT SOCKET ! CONVERSION of ADDRESS to STRING FAILED !",ErrorCode,SocketExceptionCode));
			}
		}
		else
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			if (ErrorCode==EAGAIN || ErrorCode==EWOULDBLOCK)
			{
				return(nullptr);
			}
			else
			{
				throw(CSocketException("SOCKET FAILED to ACCEPT SOCKET !",ErrorCode,SocketExceptionCode));
			}
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketWrapperTCP::BindToAddress(const CSocketTCPAddress& Address)
	{
		const CSocketIPAddress&									IPAddress=Address.GetIPEndpoint().GetIPAddress();
		uint16													Port=Address.GetIPEndpoint().GetPort();
		sockaddr_in												SocketAddress;

		SocketAddress.sin_family=AF_INET;
		SocketAddress.sin_port=htons(Port);

#if defined(PLATFORM_WINDOWS)
		if (InetPtonA(AF_INET,IPAddress.ToString().GetCharArray(),&SocketAddress.sin_addr)!=1)
		{
			throw(CSocketException("SOCKET FAILED to BIND to ADDRESS ! CONVERSION of ADDRESS to NUMERIC FORM FAILED !"));
		}

		if (::bind(MSocket,reinterpret_cast<sockaddr*>(&SocketAddress),sizeof(SocketAddress))!=0)
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to BIND to ADDRESS !",ErrorCode,SocketExceptionCode));
		}
#elif defined(PLATFORM_LINUX)
		if (inet_aton(IPAddress.ToString().GetCharArray(),reinterpret_cast<in_addr*>(&SocketAddress.sin_addr.s_addr))==0)
		{
			throw(CSocketException("SOCKET FAILED to BIND to ADDRESS ! CONVERSION of ADDRESS to NUMERIC FORM FAILED !"));
		}

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
	bool CSocketWrapperTCP::ConnectToAddress(const CSocketTCPAddress& Address)
	{
		uint16													Port=Address.GetIPEndpoint().GetPort();
		sockaddr_in												SocketAddress;

		SocketAddress.sin_family=AF_INET;
		SocketAddress.sin_port=htons(Port);

#if defined(PLATFORM_WINDOWS)
		if (InetPtonA(AF_INET,Address.GetIPEndpoint().GetIPAddress().ToString().GetCharArray(),&SocketAddress.sin_addr)!=1)
		{
			throw(CSocketException("SOCKET FAILED to CONNECT to ADDRESS ! CONVERSION of ADDRESS to NUMERIC FORM FAILED !"));
		}

		int														Result=connect(MSocket,reinterpret_cast<sockaddr*>(&SocketAddress),sizeof(SocketAddress));

		if (Result!=SOCKET_ERROR)
		{
			return(true);
		}
		else
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			if (ErrorCode==WSAEWOULDBLOCK)
			{
				return(false);
			}
			else
			{
				throw(CSocketException("SOCKET FAILED to CONNECT to ADDRESS !",ErrorCode,SocketExceptionCode));
			}
		}
#elif defined(PLATFORM_LINUX)
		if (inet_aton(Address.GetIPEndpoint().GetIPAddress().ToString().GetCharArray(),reinterpret_cast<in_addr*>(&SocketAddress.sin_addr.s_addr))==0)
		{
			throw(CSocketException("SOCKET FAILED to CONNECT to ADDRESS ! CONVERSION of ADDRESS to NUMERIC FORM FAILED !"));
		}

		int														Result=connect(MSocket,reinterpret_cast<sockaddr*>(&SocketAddress),static_cast<socklen_t>(sizeof(SocketAddress)));

		if (Result!=-1)
		{
			return(true);
		}
		else
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			if (ErrorCode==EINPROGRESS)
			{
				return(false);
			}
			else
			{
				throw(CSocketException("SOCKET FAILED to CONNECT to ADDRESS !",ErrorCode,SocketExceptionCode));
			}
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketWrapperTCP::Listen(Size MaximumNumberOfPendingConnections)
	{
#if defined(PLATFORM_WINDOWS)
		int														Result=listen(MSocket,static_cast<int>(MaximumNumberOfPendingConnections));

		if (Result==SOCKET_ERROR)
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to LISTEN !",ErrorCode,SocketExceptionCode));
		}
#elif defined(PLATFORM_LINUX)
		int														Result=listen(MSocket,static_cast<int>(MaximumNumberOfPendingConnections));

		if (Result==-1)
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to LISTEN !",ErrorCode,SocketExceptionCode));
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketWrapperTCP::Shutdown(ESocketTCPShutdownFlags ShutdownFlags)
	{
#if defined(PLATFORM_WINDOWS)
		int														Flags=0;

		if (ShutdownFlags==ESocketTCPShutdownFlags::E_READ_WRITE)
		{
			Flags=SD_BOTH;
		}
		else
		{
			if ((ShutdownFlags & ESocketTCPShutdownFlags::E_READ)!=ESocketTCPShutdownFlags::E_NONE)
			{
				Flags|=SD_RECEIVE;
			}

			if ((ShutdownFlags & ESocketTCPShutdownFlags::E_WRITE)!=ESocketTCPShutdownFlags::E_NONE)
			{
				Flags|=SD_SEND;
			}
		}

		int														Result=shutdown(MSocket,Flags);

		if (Result==SOCKET_ERROR)
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to SHUTDOWN SOCKET !",ErrorCode,SocketExceptionCode));
		}
#elif defined(PLATFORM_LINUX)
		int														Flags=0;

		if (ShutdownFlags==ESocketTCPShutdownFlags::E_READ_WRITE)
		{
			Flags=SHUT_RDWR;
		}
		else
		{
			if ((ShutdownFlags & ESocketTCPShutdownFlags::E_READ)!=ESocketTCPShutdownFlags::E_NONE)
			{
				Flags|=SHUT_RD;
			}

			if ((ShutdownFlags & ESocketTCPShutdownFlags::E_WRITE)!=ESocketTCPShutdownFlags::E_NONE)
			{
				Flags|=SHUT_WR;
			}
		}

		int														Result=shutdown(MSocket,Flags);

		if (Result==-1)
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to SHUTDOWN SOCKET !",ErrorCode,SocketExceptionCode));
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketWrapperTCP::Send(const CSocketTCPSendParameters& Parameters, CSocketTCPSendResult& OperationResult)
	{
		int														DataLength=static_cast<int>(Parameters.GetNumberOfBytesToSend());
		
		if ((Parameters.GetOffset()+Parameters.GetNumberOfBytesToSend())>Parameters.GetData()->GetLength())
		{
			throw(CSocketException("SOCKET FAILED to SEND DATA ! INVALID PARAMETERS !"));
		}
		
#if defined(PLATFORM_WINDOWS)
		const Char*												Data=reinterpret_cast<const Char*>(Parameters.GetData()->GetRawData(Parameters.GetOffset()));
		int														Result=send(MSocket,Data,DataLength,0);

		if (Result!=SOCKET_ERROR)
		{
			OperationResult.SetResult(Parameters.GetData(),Parameters.GetOffset(),static_cast<Size>(Result));
		}
		else
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			if (ErrorCode==WSAEWOULDBLOCK)
			{
				OperationResult.SetResult(Parameters.GetData(),Parameters.GetOffset(),0);
			}
			else
			{
				throw(CSocketException("SOCKET FAILED to SEND DATA !",ErrorCode,SocketExceptionCode));
			}
		}
#elif defined(PLATFORM_LINUX)
		const void*												Data=static_cast<const void*>(Parameters.GetData()->GetRawData(Parameters.GetOffset()));
		ssize_t													Result=send(MSocket,Data,DataLength,0);

		if (Result!=-1)
		{
			OperationResult.SetResult(Parameters.GetData(),Parameters.GetOffset(),static_cast<Size>(Result));
		}
		else
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			if (ErrorCode==EAGAIN || ErrorCode==EWOULDBLOCK)
			{
				OperationResult.SetResult(Parameters.GetData(),Parameters.GetOffset(),0);
			}
			else
			{
				throw(CSocketException("SOCKET FAILED to SEND DATA !",ErrorCode,SocketExceptionCode));
			}
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketWrapperTCP::Receive(const CSocketTCPReceiveParameters& Parameters, CSocketTCPReceiveResult& OperationResult)
	{
		int														DataLength=static_cast<int>(Parameters.GetNumberOfBytesToReceive());

		if ((Parameters.GetOffset()+Parameters.GetNumberOfBytesToReceive())>Parameters.GetData()->GetLength())
		{
			throw(CSocketException("SOCKET FAILED to RECEIVE DATA ! BUFFER is TOO SHORT !"));
		}

#if defined(PLATFORM_WINDOWS)
		char*													Data=reinterpret_cast<char*>(Parameters.GetData()->GetRawData(Parameters.GetOffset()));
		int														Result=recv(MSocket,Data,DataLength,0);

		if (Result!=SOCKET_ERROR)
		{
			OperationResult.SetResult(true,Parameters.GetData(),Parameters.GetOffset(),static_cast<Size>(Result));
		}
		else
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			if (ErrorCode==WSAEWOULDBLOCK)
			{
				OperationResult.SetResult(false,Parameters.GetData(),Parameters.GetOffset(),0);
			}
			else
			{
				throw(CSocketException("SOCKET FAILED to RECEIVE DATA !",ErrorCode,SocketExceptionCode));
			}
		}
#elif defined(PLATFORM_LINUX)
		void*													Data=static_cast<void*>(Parameters.GetData()->GetRawData(Parameters.GetOffset()));
		ssize_t													Result=recv(MSocket,Data,DataLength,0);

		if (Result!=-1)
		{
			OperationResult.SetResult(true,Parameters.GetData(),Parameters.GetOffset(),static_cast<Size>(Result));
		}
		else
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			if (ErrorCode==EAGAIN || ErrorCode==EWOULDBLOCK)
			{
				OperationResult.SetResult(false,Parameters.GetData(),Parameters.GetOffset(),0);
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
	void CSocketWrapperTCP::ChangeBlockingState(bool BlockingState)
	{
#if defined(PLATFORM_WINDOWS)
		u_long													Mode=static_cast<u_long>((BlockingState==true) ? 0 : 1);

		int														Result=ioctlsocket(MSocket,FIONBIO,&Mode);

		if (Result==SOCKET_ERROR)
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to CHANGE BLOCKING STATE ! SETTING BLOCKING STATE FAILED !",ErrorCode,SocketExceptionCode));
		}
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
	int32 CSocketWrapperTCP::GetSendBufferSize(void)
	{
#if defined(PLATFORM_WINDOWS)
		int														SendBufferSize=0;
		int														SendBufferSizeLength=sizeof(SendBufferSize);

		if (getsockopt(MSocket,SOL_SOCKET,SO_SNDBUF,reinterpret_cast<Char*>(&SendBufferSize),&SendBufferSizeLength)!=0 || SendBufferSizeLength!=sizeof(SendBufferSize))
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to GET SEND BUFFER SIZE !",ErrorCode,SocketExceptionCode));
		}

		return(static_cast<int32>(SendBufferSize));
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
	void CSocketWrapperTCP::SetSendBufferSize(int32 SendBufferSize)
	{
#if defined(PLATFORM_WINDOWS)
		int														BufferSize=static_cast<int>(SendBufferSize);

		if (setsockopt(MSocket,SOL_SOCKET,SO_SNDBUF,reinterpret_cast<Char*>(&BufferSize),sizeof(BufferSize))!=0)
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to SET SEND BUFFER SIZE !",ErrorCode,SocketExceptionCode));
		}
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
	int32 CSocketWrapperTCP::GetReceiveBufferSize(void)
	{
#if defined(PLATFORM_WINDOWS)
		int														ReceiveBufferSize=0;
		int														ReceiveBufferSizeLength=sizeof(ReceiveBufferSize);

		if (getsockopt(MSocket,SOL_SOCKET,SO_RCVBUF,reinterpret_cast<Char*>(&ReceiveBufferSize),&ReceiveBufferSizeLength)!=0 || ReceiveBufferSizeLength!=sizeof(ReceiveBufferSize))
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to GET RECEIVE BUFFER SIZE !",ErrorCode,SocketExceptionCode));
		}

		return(static_cast<int32>(ReceiveBufferSize));
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
	void CSocketWrapperTCP::SetReceiveBufferSize(int32 ReceiveBufferSize)
	{
#if defined(PLATFORM_WINDOWS)
		int														BufferSize=static_cast<int>(ReceiveBufferSize);

		if (setsockopt(MSocket,SOL_SOCKET,SO_RCVBUF,reinterpret_cast<Char*>(&BufferSize),sizeof(BufferSize))!=0)
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to SET RECEIVE BUFFER SIZE !",ErrorCode,SocketExceptionCode));
		}
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