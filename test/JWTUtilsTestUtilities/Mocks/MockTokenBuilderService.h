#pragma once

#include "JWTUtils/Services/ITokenBuilderService.h"


namespace systelab { namespace jwt { namespace test_utility {

	class MockTokenBuilderService : public ITokenBuilderService
	{
	public:
		MockTokenBuilderService();
		virtual ~MockTokenBuilderService();

		MOCK_CONST_METHOD2(buildJWT, std::string(const std::string&, const std::vector< std::pair<std::string, std::string> >&));
	};

}}}

