//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Logger/CLogWriter.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Strings/CString.h>
#include "CSocketID.h"
#include "ISocketWrapper.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocket : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CLogWriter&											MLogWriter;
			const CLogCategory									MLogCategorySocket;
			const CSocketID										MSocketID;

		public:
			CSocket& operator=(const CSocket& Other)=delete;

		protected:
			CLogWriter& GetLogWriter(void) const noexcept;
			const CLogCategory& GetLogCategorySocket(void) const noexcept;

		public:
			virtual CString ToString(void) const override;
			const CSocketID& GetSocketID(void) const noexcept;

		public:
			virtual int32 GetSocketHandler(void) const noexcept=0;
			virtual ISPSocketWrapper GetSocketWrapper(void) const noexcept=0;

		public:
			CSocket(CLogWriter& LogWriter, const CSocketID& SocketID);
			CSocket(const CSocket& Other)=delete;
			virtual ~CSocket(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocket=CSharedPointer<CSocket>;
	using														CCSPSocket=CSharedPointer<const CSocket>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------