#pragma once

namespace systelab { namespace jwt {

	class ITokenBuilderService
	{
	public:
		virtual ~ITokenBuilderService() {};

		virtual std::string buildJWT(const std::string& key,
									 const std::vector< std::pair<std::string, std::string> >& claims) const = 0;
	};

}}

