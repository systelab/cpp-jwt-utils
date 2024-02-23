#include "stdafx.h"
#include "JWTUtils/Services/HMACSHA256SignatureService.h"


using namespace testing;

namespace systelab { namespace jwt { namespace unit_test {

	namespace {

		struct HMACSHA256SignatureServiceTestData
		{
			std::string message;
			std::string key;
			std::string expectedHMACSHA256;
		};

		std::vector<HMACSHA256SignatureServiceTestData> hmacsha256SignatureTestData =
		{
			// Basic cases - Generated using "HMAC calc" web utility and removing padding (final '=' chars)
			{ "A",								"MySecretKey",			"YBMQbGJMbPeB2NxrfaXVHXJ_71xTYicmiOFlZeiCfKM" },
			{ "Message to sign",				"MySecretKey",			"uoKL2NbzLV9d2cWUa07xKKlFkTJWN5N3KDsZTxE1QWI" },
			{ "Another message to sign",		"MySecretKey",			"y8Cf9Sfo9o3NCtkWDsTCjm_jHQ8-xvFwPqyf5mCNr64" },
			{ "Message to sign",				"AnotherSecretKey",		"suo4OP0Lr1PwBmIJnoHs49JBfNxro29o6iOJD0LymNQ" },

			// JWT cases - Generated using https://jwt.io/
			{ "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ",
			  "your-256-bit-secret",					"SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c" },

			{ "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ",
			  "MySecretKey",							"-rUA6p_U6nMrGI76SSOvS376iebCGDwtN5hxKjHFCFk" },

			{ "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ",
			  "1Shwd21fds-13s23-1313231321dsads",		"Cnan8msuFsx9WgkrYA3C9_pIwhtZOL_P1IVHJCj0ixE" }
		};
	}

	class HMACSHA256SignatureServiceTest : public ::testing::TestWithParam<HMACSHA256SignatureServiceTestData>
	{
	public:
		void SetUp()
		{
			m_service = std::make_unique<HMACSHA256SignatureService>();
		}

	protected:
		std::unique_ptr<IHMACSHA256SignatureService> m_service;
	};


	TEST_P(HMACSHA256SignatureServiceTest, testSignMessageReturnsExpectedValue)
	{
		ASSERT_EQ(GetParam().expectedHMACSHA256, m_service->signMessage(GetParam().key, GetParam().message));
	}

	INSTANTIATE_TEST_SUITE_P(Test, HMACSHA256SignatureServiceTest, testing::ValuesIn(hmacsha256SignatureTestData));
	
}}}