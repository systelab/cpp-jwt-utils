#pragma once

#include "ITokenParserService.h"


namespace systelab { namespace json {
	class IJSONAdapter;
}}

namespace systelab { namespace jwt {

	class TokenParserService : public ITokenParserService
	{
	public:
		TokenParserService(json::IJSONAdapter&);
		virtual ~TokenParserService();

		bool validateJWT(const std::string& token, const std::string& key,
						 std::vector< std::pair<std::string, std::string> >& claims) const;

	private:
		std::vector<std::string> getTokenElements(const std::string& token) const;
		bool validateSignature(const std::string& jwtHeader, const std::string& jwtPayload,
							   const std::string& jwtSignature, const std::string& key) const;
		bool extractClaims(const std::string& jwtPayload,
						   std::vector< std::pair<std::string, std::string> >& claims) const;

	private:
		json::IJSONAdapter& m_jsonAdapter;
	};

}}

