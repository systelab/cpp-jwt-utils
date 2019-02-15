#include "stdafx.h"
#include "JWTUtils/Services/TokenParserService.h"

#include "RapidJSONAdapter/JSONAdapter.h"


using namespace testing;

namespace systelab { namespace jwt { namespace unit_test {

	namespace {

		struct TokenParserServiceTestData
		{
			std::string token;
			std::string key;
			bool expectedValidSignature;
			std::vector< std::pair<std::string, std::string> > expectedClaims;
		};

		// Scenarios generated using https://jwt.io
		std::vector<TokenParserServiceTestData> tokenValidatorServiceTestData =
		{
			// Valid tokens
			{
				"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoiMTUxNjIzOTAyMiJ9.5ODOvx-citIP2b7EbnG1TlSUcoAKmCeOyE-_Kw3-dLo",
				"your-256-bit-secret",
				true, { {"sub", "1234567890"}, {"name", "John Doe"}, {"iat", "1516239022"} }
			},
			{
				"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6ImRldmVsb3BlciJ9.QH1WdAZ955vcVJ2Cx1oWkuTZWxSiVfnOgPwZb3e67uw",
				"abcd-efgh-ijkl-mnop-qrst-uvwyz-12345-6789",
				true, { { "username", "developer" } }
			},
			{
				"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6Im9wZXJhdG9yIn0.EL_reHRde2mMH_4fbxjY0HGQCe-l8Zk8BcF8S-7w2MQ",
				"abcd-efgh-ijkl-mnop-qrst-uvwyz-12345-6789",
				true, { { "username", "operator" } },
			},
			{
				"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6InN1cGVyIiwiaWF0IjoiMTQ4NzAwMTY3MSJ9.ErX9JvS8ZfguFZVCiS741Ye92-AFtpGa8_NulXe-3HA",
				"abcd-efgh-ijkl-mnop-qrst-uvwyz-12345-6789",
				true, { { "username", "super" }, { "iat", std::to_string(1487001671)} }
			},
			{
				"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6InN1cGVyIiwiaWF0IjoiMTQ4NzAwMTY3MiJ9.zoz2piBJsqdAZqVV_PIUksueVNxjSObooM8t459NX4c",
				"abcd-efgh-ijkl-mnop-qrst-uvwyz-12345-6789",
				true, { { "username", "super" }, { "iat", std::to_string(1487001671+1)} }
			},

			// Invalid tokens
			{
				"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.e30.JWUVuXQuNrdh4xCw79gyFq-Jf95aPrzPZI2GV5GpoQI", // Empty payload
				"secret", false, {}
			},
			{
				"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpYXQiOiIxNDg.jBaCBqw0boPW9ODbGMly2zx9PML6_b6JTHSovaG4iHQ", // Incomplete payload
				"secret", false, {}
			},
			{
				"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpYXQiOjE0ODcwMDE2NzF9.fUAtBJiOvB1b98MJqgprXiczLT2G32MX9Qj1234bfZ5M", // Invalid signature
				"secret", false, {}
			},
			{
				"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9eyJpYXQiOjE0ODcwMDE2NzF9fUAtBJiOvB1b98MJqgprXiczLT2G32MX9QjQlMbfZ5M", // Invalid signature
				"secret", false, {}
			},
		};
	}

	class TokenParserServiceTest : public ::testing::TestWithParam<TokenParserServiceTestData>
	{
	public:
		void SetUp()
		{
			m_service = std::make_unique<TokenParserService>(m_jsonAdapter);
		}

	protected:
		std::unique_ptr<ITokenParserService> m_service;
		systelab::json::rapidjson::JSONAdapter m_jsonAdapter;
	};


	TEST_P(TokenParserServiceTest, testValidateJWTReturnsExpectedValidAndExpectedClaims)
	{
		std::vector< std::pair<std::string, std::string> > claims;
		ASSERT_EQ(GetParam().expectedValidSignature, m_service->validateJWT(GetParam().token, GetParam().key, claims));
		ASSERT_THAT(claims, UnorderedElementsAreArray(GetParam().expectedClaims));
	}

	INSTANTIATE_TEST_CASE_P(Test, TokenParserServiceTest, testing::ValuesIn(tokenValidatorServiceTestData));

}}}

