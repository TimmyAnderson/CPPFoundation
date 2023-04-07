//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CMap.h>
#include <Framework/Foundation/Exceptions/CEncryptionException.h>
#include "CEncryptionAlgorithmParameter.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CEncryptionAlgorithmParameterCollection final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												CEncryptionAlgorithmParameterDictionary=CMap<CEncryptionAlgorithmParameterID,CSPEncryptionAlgorithmParameter>;

		private:
			CEncryptionAlgorithmParameterDictionary				MDictionary;

		public:
			void AddParameter(CSPEncryptionAlgorithmParameter Parameter);
			CSPEncryptionAlgorithmParameter GetParameter(const CEncryptionAlgorithmParameterID& ParameterID) const;

			template<typename TParserParameter>
			CSharedPointer<TParserParameter> GetParameterByType(const CEncryptionAlgorithmParameterID& ParameterID) const
			{
				CSPEncryptionAlgorithmParameter					EncryptionAlgorithmParameter=GetParameter(ParameterID);

				if (EncryptionAlgorithmParameter!=nullptr)
				{
					if (EncryptionAlgorithmParameter->IsTypeOf<TParserParameter>()==true)
					{
						return(EncryptionAlgorithmParameter.DynamicCast<TParserParameter>());
					}
				}

				return(nullptr);
			}

			bool HasParameter(const CEncryptionAlgorithmParameterID& ParameterID) const;

		public:
			CEncryptionAlgorithmParameterCollection(void);
			CEncryptionAlgorithmParameterCollection(CSPEncryptionAlgorithmParameter Parameter);
			CEncryptionAlgorithmParameterCollection(std::initializer_list<CSPEncryptionAlgorithmParameter> Parameters);
			virtual ~CEncryptionAlgorithmParameterCollection(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------