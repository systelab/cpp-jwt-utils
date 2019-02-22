#pragma once

#include <string>
#include <vector>


namespace systelab { namespace jwt {

	class ITokenParserService
	{
	public:
		virtual ~ITokenParserService() {};

		virtual bool validateJWT(const std::string& token, const std::string& key,
								 std::vector< std::pair<std::string, std::string> >& claims) const = 0;
	};

}}

