//----------------------------------------------------------------------------------------------------------------------
#include "CParserParameterCollection.h"
#include <Framework/Foundation/Exceptions/CParserException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CParserParameterCollection::CParserParameterCollection(void)
		: MDictionary()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserParameterCollection::CParserParameterCollection(CSPParserParameter Parameter)
		: MDictionary()
	{
		AddParameter(Parameter);
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserParameterCollection::CParserParameterCollection(std::initializer_list<CSPParserParameter> Parameters)
		: MDictionary()
	{
		for(CSPParserParameter Parameter : Parameters)
		{
			AddParameter(Parameter);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserParameterCollection::~CParserParameterCollection(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CParserParameterCollection::AddParameter(CSPParserParameter Parameter)
	{
		MDictionary.Add(Parameter->GetParameterID(),Parameter);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPParserParameter CParserParameterCollection::GetParameter(const CParserParameterID& ParameterID) const
	{
		CParserParameterDictionary::CMapIteratorConst			Parameter=MDictionary.Find(ParameterID);

		if (Parameter!=MDictionary.End())
		{
			return(Parameter->GetSecond());
		}
		else
		{
			throw(CParserException(CString::Format("PARSER PARAMETER [",ParameterID.ToString(),"] NOT FOUND !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CParserParameterCollection::HasParameter(const CParserParameterID& ParameterID) const
	{
		bool													HasParameter=MDictionary.Contains(ParameterID);

		return(HasParameter);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------