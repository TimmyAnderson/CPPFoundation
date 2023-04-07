//----------------------------------------------------------------------------------------------------------------------
#include "CSocketWaitObject.h"
#if defined(PLATFORM_WINDOWS)
#include <WS2tcpip.h>
#include <cstring>
#elif defined(PLATFORM_LINUX)
#include <poll.h>
#include <cstring>
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
	const Size													CSocketWaitObject::MAXIMUM_NUMBER_OF_SOCKETS=50;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketWaitObject::CSocketWaitObject(void)
		: MSynchronizationObject()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketWaitObject::~CSocketWaitObject(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketWaitObject::GetMaximumNumberOfSocket(void) const
	{
		return(MAXIMUM_NUMBER_OF_SOCKETS);
	}
//----------------------------------------------------------------------------------------------------------------------
	ESocketWaitEvent CSocketWaitObject::WaitForEvent(CVector<CSocketWaitState>& Sockets, const CTimeout& Timeout)
	{
		if (Sockets.GetLength()>MAXIMUM_NUMBER_OF_SOCKETS)
		{
			throw(CSocketException("Too many SOCKETS !"));
		}

#if defined(PLATFORM_WINDOWS)
		WSAEVENT												Events[MAXIMUM_NUMBER_OF_SOCKETS+1];

		memset(Events,0,sizeof(Events));

		Events[0]=MSynchronizationObject.GetEvent();

		for(Size Index=0;Index<Sockets.GetLength();Index++)
		{
			const CSocketWaitState&								SocketWaitState=Sockets[Index];
			WSAEVENT											Event=SocketWaitState.GetSocket()->GetSocketWrapper()->GetPlatformData().GetEvent();

			Events[Index+1]=Event;
		}

		DWORD													TimeoutInMS;
		
		if (Timeout.IsInfinite()==false)
		{
			TimeoutInMS=static_cast<DWORD>(Timeout.GetTimeoutInMS());
		}
		else
		{
			TimeoutInMS=WSA_INFINITE;
		}

		DWORD													Result=WSAWaitForMultipleEvents(static_cast<DWORD>(Sockets.GetLength()+1),Events,FALSE,TimeoutInMS,TRUE);

		if (Result==WSA_WAIT_TIMEOUT)
		{
			return(ESocketWaitEvent::E_TIMEOUT);
		}
		else if (Result==(WSA_WAIT_EVENT_0+0))
		{
			MSynchronizationObject.ResetEvent();

			return(ESocketWaitEvent::E_SIGNALIZATION_EVENT_SET);
		}
		else if (Result>=(WSA_WAIT_EVENT_0+1) && Result<=(WSA_WAIT_EVENT_0+Sockets.GetLength()))
		{
			ESocketWaitEvent									WaitEvent=ESocketWaitEvent::E_NONE;

			for(Size Index=0;Index<Sockets.GetLength();Index++)
			{
				CSocketWaitState&								SocketWaitState=Sockets[Index];
				SOCKET											Socket=SocketWaitState.GetSocket()->GetSocketWrapper()->GetPlatformData().GetSocket();
				ESocketWaitResultFlags							WaitResultFlags=ESocketWaitResultFlags::E_NONE;
				WSANETWORKEVENTS								NetworkEvents;

				memset(&NetworkEvents,0,sizeof(NetworkEvents));

				// FUNCTION WSAEnumNetworkEvents() RESETS MANUAL RESET EVENT 'Events[Index]' to NON-SIGNALIZED STATE.
				if (WSAEnumNetworkEvents(Socket,Events[Index+1],&NetworkEvents)==0)
				{
					if ((NetworkEvents.lNetworkEvents & FD_READ)!=0)
					{
						WaitResultFlags|=ESocketWaitResultFlags::E_READ;
						WaitEvent|=ESocketWaitEvent::E_SOCKET_EVENT_SET;

						if (NetworkEvents.iErrorCode[FD_READ_BIT]!=0)
						{
							WaitResultFlags|=ESocketWaitResultFlags::E_ERROR;
						}
					}

					if ((NetworkEvents.lNetworkEvents & FD_WRITE)!=0)
					{
						WaitResultFlags|=ESocketWaitResultFlags::E_WRITE;
						WaitEvent|=ESocketWaitEvent::E_SOCKET_EVENT_SET;

						if (NetworkEvents.iErrorCode[FD_WRITE_BIT]!=0)
						{
							WaitResultFlags|=ESocketWaitResultFlags::E_ERROR;
						}
					}

					if ((NetworkEvents.lNetworkEvents & FD_CONNECT)!=0)
					{
						// CONNECT is reported as a WRITE OPERATION to be compatible with LINUX.
						WaitResultFlags|=ESocketWaitResultFlags::E_WRITE;
						WaitEvent|=ESocketWaitEvent::E_SOCKET_EVENT_SET;

						if (NetworkEvents.iErrorCode[FD_CONNECT_BIT]!=0)
						{
							WaitResultFlags|=ESocketWaitResultFlags::E_ERROR;
						}
					}

					if ((NetworkEvents.lNetworkEvents & FD_ACCEPT)!=0)
					{
						// ACCEPT is reported as a READ OPERATION to be compatible with LINUX.
						WaitResultFlags|=ESocketWaitResultFlags::E_READ;
						WaitEvent|=ESocketWaitEvent::E_SOCKET_EVENT_SET;

						if (NetworkEvents.iErrorCode[FD_ACCEPT_BIT]!=0)
						{
							WaitResultFlags|=ESocketWaitResultFlags::E_ERROR;
						}
					}

					// !!!!! EVENT [FD_CLOSE] is sent when REMOTE SIDE SHUTDOWN or CLOSED its connection.
					// !!!!! EVENT [FD_CLOSE] is NOT SENT when LOCAL SIDE CALLED SHUTDOWN.
					if ((NetworkEvents.lNetworkEvents & FD_CLOSE)!=0)
					{
						WaitResultFlags|=ESocketWaitResultFlags::E_CLOSE;
						WaitEvent|=ESocketWaitEvent::E_SOCKET_EVENT_SET;

						if (NetworkEvents.iErrorCode[FD_CLOSE_BIT]!=0)
						{
							WaitResultFlags|=ESocketWaitResultFlags::E_ERROR;
						}
					}
				}
				else
				{
					WaitResultFlags|=ESocketWaitResultFlags::E_ERROR;
					WaitEvent|=ESocketWaitEvent::E_SOCKET_EVENT_SET;
				}

				SocketWaitState.SetWaitResultFlags(WaitResultFlags);
			}

			return(WaitEvent);
		}
		else
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to WAIT for SOCKET STATE !",ErrorCode,SocketExceptionCode));
		}
#elif defined(PLATFORM_LINUX)
		pollfd													FileDescriptors[MAXIMUM_NUMBER_OF_SOCKETS+1];

		memset(FileDescriptors,0,sizeof(FileDescriptors));

		FileDescriptors[0].fd=static_cast<int>(MSynchronizationObject.GetDescriptor());
		FileDescriptors[0].events=POLLIN | POLLRDHUP;

		for(Size Index=0;Index<Sockets.GetLength();Index++)
		{
			const CSocketWaitState&								SocketWaitState=Sockets[Index];
			ESocketWaitFlags									WaitFlags=SocketWaitState.GetWaitFlags();
			short												Events=0;

			if ((WaitFlags & ESocketWaitFlags::E_READ)!=ESocketWaitFlags::E_NONE)
			{
				Events|=POLLIN;
			}

			if ((WaitFlags & ESocketWaitFlags::E_WRITE)!=ESocketWaitFlags::E_NONE)
			{
				Events|=POLLOUT;
			}

			if ((WaitFlags & ESocketWaitFlags::E_CLOSE)!=ESocketWaitFlags::E_NONE)
			{
				Events|=POLLRDHUP;
			}

			FileDescriptors[Index+1].fd=static_cast<int>(SocketWaitState.GetSocket()->GetSocketHandler());
			FileDescriptors[Index+1].events=Events;
		}

		int														TimeoutInMS;

		if (Timeout.IsInfinite()==false)
		{
			TimeoutInMS=static_cast<int>(Timeout.GetTimeoutInMS());
		}
		else
		{
			TimeoutInMS=-1;
		}

		int														Result=poll(FileDescriptors,static_cast<nfds_t>(Sockets.GetLength()+1),TimeoutInMS);

		if (Result==0)
		{
			return(ESocketWaitEvent::E_TIMEOUT);
		}
		else if (Result>0)
		{
			ESocketWaitEvent									WaitEvent=ESocketWaitEvent::E_NONE;

			if ((FileDescriptors[0].revents & POLLERR)!=0)
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("SOCKET FAILED to WAIT for SOCKET STATE ! ERROR in SIGNALIZATION EVENT DETECTED !",ErrorCode,SocketExceptionCode));
			}

			if ((FileDescriptors[0].revents & POLLNVAL)!=0)
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("SOCKET FAILED to WAIT for SOCKET STATE ! INVALID VALUE in SIGNALIZATION EVENT DETECTED !",ErrorCode,SocketExceptionCode));
			}

			if ((FileDescriptors[0].revents & POLLRDHUP)!=0)
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("SOCKET FAILED to WAIT for SOCKET STATE ! EVENT READ CLOSE in SIGNALIZATION EVENT DETECTED !",ErrorCode,SocketExceptionCode));
			}

			if ((FileDescriptors[0].revents & POLLHUP)!=0)
			{
				int32											ErrorCode=CSocketError::SocketGetLastErrorCode();
				ESocketExceptionCode							SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

				throw(CSocketException("SOCKET FAILED to WAIT for SOCKET STATE ! EVENT CLOSE in SIGNALIZATION EVENT DETECTED !",ErrorCode,SocketExceptionCode));
			}

			if ((FileDescriptors[0].revents & POLLIN)!=0)
			{
				MSynchronizationObject.ResetEvent();

				WaitEvent|=ESocketWaitEvent::E_SIGNALIZATION_EVENT_SET;
			}

			for(Size Index=0;Index<Sockets.GetLength();Index++)
			{
				CSocketWaitState&								SocketWaitState=Sockets[Index];
				ESocketWaitResultFlags							WaitResultFlags=ESocketWaitResultFlags::E_NONE;

				if ((FileDescriptors[Index+1].revents & POLLERR)!=0)
				{
					WaitResultFlags|=ESocketWaitResultFlags::E_ERROR;
					WaitEvent|=ESocketWaitEvent::E_SOCKET_EVENT_SET;
				}

				if ((FileDescriptors[Index+1].revents & POLLNVAL)!=0)
				{
					WaitResultFlags|=ESocketWaitResultFlags::E_ERROR;
					WaitEvent|=ESocketWaitEvent::E_SOCKET_EVENT_SET;
				}

				if ((FileDescriptors[Index+1].revents & POLLIN)!=0)
				{
					WaitResultFlags|=ESocketWaitResultFlags::E_READ;
					WaitEvent|=ESocketWaitEvent::E_SOCKET_EVENT_SET;
				}

				if ((FileDescriptors[Index+1].revents & POLLOUT)!=0)
				{
					WaitResultFlags|=ESocketWaitResultFlags::E_WRITE;
					WaitEvent|=ESocketWaitEvent::E_SOCKET_EVENT_SET;
				}

				// !!!!! EVENT [POLLRDHUP] is sent when REMOTE SIDE SHUTDOWN or CLOSED its connection.
				// !!!!! EVENT [POLLRDHUP] is NOT SENT when LOCAL SIDE CALLED SHUTDOWN.
				if ((FileDescriptors[Index+1].revents & POLLRDHUP)!=0)
				{
					WaitResultFlags|=ESocketWaitResultFlags::E_CLOSE;
					WaitEvent|=ESocketWaitEvent::E_SOCKET_EVENT_SET;
				}

				// !!!!! EVENT [POLLHUP] is sent when LOCAL SIDE CALLED SHUTDOWN or CONNECTION FAILED.
				if ((FileDescriptors[Index+1].revents & POLLHUP)!=0)
				{
					WaitResultFlags|=ESocketWaitResultFlags::E_CLOSE;
					WaitEvent|=ESocketWaitEvent::E_SOCKET_EVENT_SET;
				}

				SocketWaitState.SetWaitResultFlags(WaitResultFlags);
			}

			return(WaitEvent);
		}
		else
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("SOCKET FAILED to WAIT for SOCKET STATE !",ErrorCode,SocketExceptionCode));
		}
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketWaitObject::SetEvent(void)
	{
		MSynchronizationObject.SetEvent();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketWaitObject::ResetEvent(void)
	{
		MSynchronizationObject.ResetEvent();
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------