#pragma once

#include "JWTUtils/Services/ITokenParserService.h"


namespace systelab { namespace jwt { namespace test_utility {

	class MockTokenParserService : public ITokenParserService
	{
	public:
		MockTokenParserService();
		virtual ~MockTokenParserService();

		MOCK_CONST_METHOD3(validateJWT, bool(const std::string&, const std::string&, 
											 const std::vector< std::pair<std::string, std::string> >&));
	};

}}}

