#pragma once

#include "JWTUtils/Services/IBase64EncodeService.h"


namespace systelab { namespace jwt { namespace test_utility {

	class MockBase64EncodeService : public IBase64EncodeService
	{
	public:
		MockBase64EncodeService();
		virtual ~MockBase64EncodeService();

		MOCK_CONST_METHOD1(encodeString, std::string(const std::string&));
		MOCK_CONST_METHOD1(decodeString, std::string(const std::string&));
	};

}}}

