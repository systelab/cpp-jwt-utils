#pragma once

#include "ITokenBuilderService.h"


namespace systelab { namespace json {
	class IJSONAdapter;
}}

namespace systelab { namespace jwt {

	class TokenBuilderService : public ITokenBuilderService
	{
	public:
		TokenBuilderService(json::IJSONAdapter&);
		virtual ~TokenBuilderService();

		std::string buildJWT(const std::string& key,
							 const std::vector< std::pair<std::string, std::string> >& claims) const;

	private:
		std::string buildJWTHeader() const;
		std::string buildJWTPayload(const std::vector< std::pair<std::string, std::string> >& claims) const;
		std::string buildJWTSignature(const std::string& jwtHeader,
									  const std::string& jwtPayload,
									  const std::string& key) const;

	private:
		json::IJSONAdapter& m_jsonAdapter;
	};

}}

