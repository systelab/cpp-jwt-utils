#include "stdafx.h"
#include "JWTUtils/Services/TokenBuilderService.h"
#include "JWTUtils/Services/TokenParserService.h"

#include "RapidJSONAdapter/JSONAdapter.h"


using namespace testing;

namespace systelab { namespace jwt { namespace unit_test {

	namespace {

		struct JWTRoundtripTestData
		{
			std::string key;
			std::vector< std::pair<std::string, std::string> > claims;
		};

		std::vector<JWTRoundtripTestData> jwtRoundtripTestData =
		{
			{
				"your-256-bit-secret",
				{ }
			},
			{
				"your-256-bit-secret",
				{ {"username", "developer"} }
			},
			{
				"abcd-efgh-ijkl-mnop-qrst-uvwyz-12345-6789",
				{ {"sub", "1234567890"}, {"name", "John Doe"}, {"iat", "1516239022"} }
			},
			{
				"my-ultra-super-super-super-super-super-super-super-super-super-super-super-super-strong-secret",
				{ {"sub", "1234567890"}, {"name", "John Doe"}, {"iat", "1516239022"} }
			}
		};
	}

	class JWTRoundtripTest : public ::testing::TestWithParam<JWTRoundtripTestData>
	{
	public:
		void SetUp()
		{
			m_builderService = std::make_unique<TokenBuilderService>(m_jsonAdapter);
			m_parserService = std::make_unique<TokenParserService>(m_jsonAdapter);
		}

	protected:
		std::unique_ptr<ITokenBuilderService> m_builderService;
		std::unique_ptr<ITokenParserService> m_parserService;
		systelab::json::rapidjson::JSONAdapter m_jsonAdapter;
	};


	TEST_P(JWTRoundtripTest, testClaimsAreExtractedProperlyAfterRoundtrip)
	{
		std::string token = m_builderService->buildJWT(GetParam().key, GetParam().claims);

		std::vector< std::pair<std::string, std::string> > extractedClaims;
		ASSERT_TRUE(m_parserService->validateJWT(token, GetParam().key, extractedClaims));
		ASSERT_THAT(extractedClaims, UnorderedElementsAreArray(GetParam().claims));
	}

	TEST_P(JWTRoundtripTest, testTokensIsNotValidWhenValidatingWithAnotherKey)
	{
		std::string token = m_builderService->buildJWT(GetParam().key, GetParam().claims);

		std::string anotherKey = GetParam().key + "666";
		std::vector< std::pair<std::string, std::string> > extractedClaims;
		ASSERT_FALSE(m_parserService->validateJWT(token, anotherKey, extractedClaims));
	}

	INSTANTIATE_TEST_SUITE_P(Test, JWTRoundtripTest, testing::ValuesIn(jwtRoundtripTestData));

}}}

