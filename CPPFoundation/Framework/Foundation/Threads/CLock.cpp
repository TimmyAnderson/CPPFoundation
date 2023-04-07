//----------------------------------------------------------------------------------------------------------------------
#include "CLock.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CLock::CLock(CAbstractMutex& Mutex, Size NumberOfSpins)
		: MMutex(Mutex)
	{
		for(Size Index=0;Index<NumberOfSpins;Index++)
		{
			if (MMutex.TryLock()==true)
			{
				return;
			}
		}

		MMutex.Lock();
	}
//----------------------------------------------------------------------------------------------------------------------
	CLock::~CLock(void)
	{
		MMutex.Unlock();
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------