#include "stdafx.h"
#include "JWTUtils/Services/TokenBuilderService.h"

#include "RapidJSONAdapter/JSONAdapter.h"


using namespace testing;

namespace systelab { namespace jwt { namespace unit_test {

	namespace {

		struct TokenBuilderServiceTestData
		{
			std::string key;
			std::vector< std::pair<std::string, std::string> > claims;
			std::string expectedToken;
		};

		// Scenarios generated using https://jwt.io
		std::vector<TokenBuilderServiceTestData> tokenBuilderServiceTestData =
		{
			{
				"your-256-bit-secret",
				{ {"sub", "1234567890"}, {"name", "John Doe"}, {"iat", "1516239022"} },
				"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoiMTUxNjIzOTAyMiJ9.5ODOvx-citIP2b7EbnG1TlSUcoAKmCeOyE-_Kw3-dLo"
			},
			{
				"abcd-efgh-ijkl-mnop-qrst-uvwyz-12345-6789",
				{ { "username", "developer" } },
				"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6ImRldmVsb3BlciJ9.QH1WdAZ955vcVJ2Cx1oWkuTZWxSiVfnOgPwZb3e67uw"
			},
			{
				"abcd-efgh-ijkl-mnop-qrst-uvwyz-12345-6789",
				{ { "username", "operator" } },
				"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6Im9wZXJhdG9yIn0.EL_reHRde2mMH_4fbxjY0HGQCe-l8Zk8BcF8S-7w2MQ"
			},
			{
				"abcd-efgh-ijkl-mnop-qrst-uvwyz-12345-6789",
				{ { "username", "super" }, { "iat", std::to_string(1487001671)} },
				"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6InN1cGVyIiwiaWF0IjoiMTQ4NzAwMTY3MSJ9.ErX9JvS8ZfguFZVCiS741Ye92-AFtpGa8_NulXe-3HA"
			},
			{
				"abcd-efgh-ijkl-mnop-qrst-uvwyz-12345-6789",
				{ { "username", "super" }, { "iat", std::to_string(1487001671+1)} },
				"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6InN1cGVyIiwiaWF0IjoiMTQ4NzAwMTY3MiJ9.zoz2piBJsqdAZqVV_PIUksueVNxjSObooM8t459NX4c"
			}
		};
	}

	class TokenBuilderServiceTest : public ::testing::TestWithParam<TokenBuilderServiceTestData>
	{
	public:
		void SetUp()
		{
			m_service = std::make_unique<TokenBuilderService>(m_jsonAdapter);
		}

	protected:
		std::unique_ptr<ITokenBuilderService> m_service;
		systelab::json::rapidjson::JSONAdapter m_jsonAdapter;
	};


	TEST_P(TokenBuilderServiceTest, testBuildJWTReturnsExpectedValue)
	{
		ASSERT_EQ(GetParam().expectedToken, m_service->buildJWT(GetParam().key, GetParam().claims));
	}

	INSTANTIATE_TEST_SUITE_P(Test, TokenBuilderServiceTest, testing::ValuesIn(tokenBuilderServiceTestData));

}}}

