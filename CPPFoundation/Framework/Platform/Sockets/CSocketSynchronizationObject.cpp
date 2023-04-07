//----------------------------------------------------------------------------------------------------------------------
#include "CSocketSynchronizationObject.h"
#if defined(PLATFORM_WINDOWS)
#include <WS2tcpip.h>
#elif defined(PLATFORM_LINUX)
#include <fcntl.h>
#include <unistd.h>
#else
#error UNSUPPORTED PLATFORM !
#endif
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
	CSocketSynchronizationObject::CSocketSynchronizationObject(void)
#if defined(PLATFORM_WINDOWS)
		: MSocket(INVALID_SOCKET), MEvent(WSA_INVALID_EVENT)
#elif defined(PLATFORM_LINUX)
		: MPipeMutex(), MPipeDescriptors{-1,-1}
#else
#error UNSUPPORTED PLATFORM !
#endif
	{
		try
		{
#if defined(PLATFORM_WINDOWS)
			if ((MSocket=socket(AF_INET,SOCK_DGRAM,0))==INVALID_SOCKET)
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("SOCKET FAILED to CREATE SOCKET !",ErrorCode,SocketExceptionCode));
			}

			if ((MEvent=WSACreateEvent())==WSA_INVALID_EVENT)
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("SOCKET FAILED to CREATE EVENT !",ErrorCode,SocketExceptionCode));
			}

			if (WSAEventSelect(MSocket,MEvent,0)==SOCKET_ERROR)
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("SOCKET FAILED to ASSOCIATE EVENT !",ErrorCode,SocketExceptionCode));
			}
#elif defined(PLATFORM_LINUX)
			if (pipe(MPipeDescriptors)==-1)
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("SOCKET FAILED to CREATE PIPE !",ErrorCode,SocketExceptionCode));
			}

			int													ReadDescriptorFlags=fcntl(MPipeDescriptors[0],F_GETFL,0);

			if (ReadDescriptorFlags!=-1)
			{
				ReadDescriptorFlags=(ReadDescriptorFlags | O_NONBLOCK);

				int												Result=fcntl(MPipeDescriptors[0],F_SETFL,ReadDescriptorFlags);

				if (Result==-1)
				{
					int32										ErrorCode=CSocketError::SocketGetLastErrorCode();
					ESocketExceptionCode						SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

					throw(CSocketException("SOCKET FAILED to SET NON-BLOCKING STATE for READ DESCRIPTOR !",ErrorCode,SocketExceptionCode));
				}
			}
			else
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("SOCKET FAILED to GET BLOCKING STATE for READ DESCRIPTOR !",ErrorCode,SocketExceptionCode));
			}

			int													WriteDescriptorFlags=fcntl(MPipeDescriptors[1],F_GETFL,0);

			if (WriteDescriptorFlags!=-1)
			{
				WriteDescriptorFlags=(WriteDescriptorFlags | O_NONBLOCK);

				int												Result=fcntl(MPipeDescriptors[1],F_SETFL,WriteDescriptorFlags);

				if (Result==-1)
				{
					int32										ErrorCode=CSocketError::SocketGetLastErrorCode();
					ESocketExceptionCode						SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

					throw(CSocketException("SOCKET FAILED to SET NON-BLOCKING STATE for WRITE DESCRIPTOR !",ErrorCode,SocketExceptionCode));
				}
			}
			else
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("SOCKET FAILED to GET BLOCKING STATE for WRITE DESCRIPTOR !",ErrorCode,SocketExceptionCode));
			}
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
	CSocketSynchronizationObject::~CSocketSynchronizationObject(void)
	{
		Uninitialize();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketSynchronizationObject::Uninitialize(void) noexcept
	{
#if defined(PLATFORM_WINDOWS)
		if (MEvent!=WSA_INVALID_EVENT)
		{
			WSACloseEvent(MEvent);
			MEvent=WSA_INVALID_EVENT;
		}

		if (MSocket!=INVALID_SOCKET)
		{
			closesocket(MSocket);
			MSocket=INVALID_SOCKET;
		}
#elif defined(PLATFORM_LINUX)
		if (MPipeDescriptors[0]!=-1)
		{
			close(MPipeDescriptors[0]);
			MPipeDescriptors[0]=-1;
		}

		if (MPipeDescriptors[1]!=-1)
		{
			close(MPipeDescriptors[1]);
			MPipeDescriptors[1]=-1;
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
	WSAEVENT CSocketSynchronizationObject::GetEvent(void) const noexcept
	{
		return(MEvent);
	}
#elif defined(PLATFORM_LINUX)
	int CSocketSynchronizationObject::GetDescriptor(void) const noexcept
	{
		return(MPipeDescriptors[0]);
	}
#else
#error UNSUPPORTED PLATFORM !
#endif
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketSynchronizationObject::SetEvent(void)
	{
#if defined(PLATFORM_WINDOWS)
		if (WSASetEvent(MEvent)==FALSE)
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to SET EVENT !",ErrorCode,SocketExceptionCode));
		}
#elif defined(PLATFORM_LINUX)
		CLock													Lock(MPipeMutex);
		{
			uint8												Byte=0;
			ssize_t												Result=write(MPipeDescriptors[1],&Byte,1);

			if (Result==-1)
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				if (ErrorCode!=EAGAIN && ErrorCode!=EWOULDBLOCK)
				{
					throw(CSocketException("SOCKET FAILED to WRITE DATA to PIPE !",ErrorCode,SocketExceptionCode));
				}
			}
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketSynchronizationObject::ResetEvent(void)
	{
#if defined(PLATFORM_WINDOWS)
		if (WSAResetEvent(MEvent)==FALSE)
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to RESET EVENT !",ErrorCode,SocketExceptionCode));
		}
#elif defined(PLATFORM_LINUX)
		CLock													Lock(MPipeMutex);
		{
			for(;;)
			{
				uint8											Byte;
				ssize_t											Result=read(MPipeDescriptors[0],&Byte,1);

				if (Result==-1)
				{
					int32										ErrorCode=CSocketError::SocketGetLastErrorCode();
					ESocketExceptionCode						SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

					if (ErrorCode==EAGAIN || ErrorCode==EWOULDBLOCK)
					{
						break;
					}
					else
					{
						throw(CSocketException("SOCKET FAILED to READ DATA from PIPE !",ErrorCode,SocketExceptionCode));
					}
				}
			}
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