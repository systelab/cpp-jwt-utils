#include "stdafx.h"
#include "JWTUtils/Services/Base64EncodeService.h"


using namespace testing;

namespace systelab { namespace jwt { namespace unit_test {

	namespace {

		struct Base64EncodeServiceTestData
		{
			std::string decodedString;
			std::string encodedString;
		};

		// Scenarios generated using https://www.base64encode.org/ and removing the padding (final '=' chars)
		std::vector<Base64EncodeServiceTestData> base64EncodeServiceTestData =
		{
			// Basic cases
			{ "",			"" },
			{ "f",			"Zg" },
			{ "fo",			"Zm8" },
			{ "foo",		"Zm9v" },
			{ "foob",		"Zm9vYg" },
			{ "fooba",		"Zm9vYmE" },
			{ "foobar",		"Zm9vYmFy" },

			// JSONs
			{ "{}",										"e30" },
			{ "{\"att\": 123}",							"eyJhdHQiOiAxMjN9" },
			{ "{\"att\": \"value\"}",					"eyJhdHQiOiAidmFsdWUifQ" },
			{ "{\"att\": true}",						"eyJhdHQiOiB0cnVlfQ" },
			{ "{\"att\": []}",							"eyJhdHQiOiBbXX0" },
			{ "{\"att\": [1,2,3]}",						"eyJhdHQiOiBbMSwyLDNdfQ" },
			{ "{\"att1\": \"A\", \"att2\": \"B\"}",		"eyJhdHQxIjogIkEiLCAiYXR0MiI6ICJCIn0" },
			{ "{\"att1\": {}, \"att2\": {}}",			"eyJhdHQxIjoge30sICJhdHQyIjoge319" }
		};
	}

	class Base64EncodeServiceTest : public ::testing::TestWithParam<Base64EncodeServiceTestData>
	{
	public:
		void SetUp()
		{
			m_service = std::make_unique<Base64EncodeService>();
		}

	protected:
		std::unique_ptr<IBase64EncodeService> m_service;
	};

		
	TEST_P(Base64EncodeServiceTest, testEncodeStringReturnsExpectedValue)
	{
		ASSERT_EQ(GetParam().encodedString, m_service->encodeString(GetParam().decodedString));
	}

	TEST_P(Base64EncodeServiceTest, testDecodeStringReturnsExpectedValue)
	{
		ASSERT_EQ(GetParam().decodedString, m_service->decodeString(GetParam().encodedString));
	}

	INSTANTIATE_TEST_CASE_P(Test, Base64EncodeServiceTest, testing::ValuesIn(base64EncodeServiceTestData));

}}}
