#pragma once

#include "JWTUtils/Services/IHMACSHA256SignatureService.h"


namespace systelab { namespace jwt { namespace test_utility {

	class MockHMACSHA256SignatureService : public IHMACSHA256SignatureService
	{
	public:
		MockHMACSHA256SignatureService();
		virtual ~MockHMACSHA256SignatureService();

		MOCK_CONST_METHOD2(signMessage, std::string(const std::string&, const std::string&));
	};

}}}

