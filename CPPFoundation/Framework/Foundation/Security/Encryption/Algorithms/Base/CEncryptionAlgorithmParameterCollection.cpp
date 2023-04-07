//----------------------------------------------------------------------------------------------------------------------
#include "CEncryptionAlgorithmParameterCollection.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmParameterCollection::CEncryptionAlgorithmParameterCollection(void)
		: MDictionary()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmParameterCollection::CEncryptionAlgorithmParameterCollection(CSPEncryptionAlgorithmParameter Parameter)
		: MDictionary()
	{
		AddParameter(Parameter);
	}
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmParameterCollection::CEncryptionAlgorithmParameterCollection(std::initializer_list<CSPEncryptionAlgorithmParameter> Parameters)
		: MDictionary()
	{
		for(CSPEncryptionAlgorithmParameter Parameter : Parameters)
		{
			AddParameter(Parameter);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionAlgorithmParameterCollection::~CEncryptionAlgorithmParameterCollection(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CEncryptionAlgorithmParameterCollection::AddParameter(CSPEncryptionAlgorithmParameter Parameter)
	{
		MDictionary.Add(Parameter->GetParameterID(),Parameter);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPEncryptionAlgorithmParameter CEncryptionAlgorithmParameterCollection::GetParameter(const CEncryptionAlgorithmParameterID& ParameterID) const
	{
		CEncryptionAlgorithmParameterDictionary::CMapIteratorConst	Parameter=MDictionary.Find(ParameterID);

		if (Parameter!=MDictionary.End())
		{
			return(Parameter->GetSecond());
		}
		else
		{
			return(nullptr);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CEncryptionAlgorithmParameterCollection::HasParameter(const CEncryptionAlgorithmParameterID& ParameterID) const
	{
		bool													HasParameter=MDictionary.Contains(ParameterID);

		return(HasParameter);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------