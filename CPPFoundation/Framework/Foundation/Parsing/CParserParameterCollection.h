//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Exceptions/CParserException.h>
#include <Framework/Foundation/Collections/CMap.h>
#include <Framework/Foundation/Objects/CObject.h>
#include "CParserParameter.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CParserParameterCollection final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												CParserParameterDictionary=CMap<CParserParameterID,CSPParserParameter>;

		private:
			CParserParameterDictionary							MDictionary;

		public:
			void AddParameter(CSPParserParameter Parameter);
			CSPParserParameter GetParameter(const CParserParameterID& ParameterID) const;

			template<typename TParserParameter>
			CSharedPointer<TParserParameter> GetParameterByType(const CParserParameterID& ParameterID) const
			{
				CSPParserParameter								ParserParameter=GetParameter(ParameterID);

				if (ParserParameter->IsTypeOf<TParserParameter>()==true)
				{
					return(ParserParameter.DynamicCast<TParserParameter>());
				}
				else
				{
					throw(CParserException(CString::Format("PARSER PARAMETER [",ParameterID.ToString(),"] NOT FOUND !")));
				}
			}

			template<typename TParserParameter>
			CSharedPointer<TParserParameter> GetParameterByTypeOrDefault(const CParserParameterID& ParameterID) const
			{
				if (HasParameter(ParameterID)==true)
				{
					CSPParserParameter							ParserParameter=GetParameter(ParameterID);

					if (ParserParameter->IsTypeOf<TParserParameter>()==true)
					{
						return(ParserParameter.DynamicCast<TParserParameter>());
					}
				}

				return(nullptr);
			}

			bool HasParameter(const CParserParameterID& ParameterID) const;

		public:
			CParserParameterCollection(void);
			CParserParameterCollection(CSPParserParameter Parameter);
			CParserParameterCollection(std::initializer_list<CSPParserParameter> Parameters);
			virtual ~CParserParameterCollection(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------