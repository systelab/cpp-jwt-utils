#include "HMACSHA256SignatureService.h"

#include "Services/Base64EncodeService.h"

#include <iomanip>
#include <sstream>
#include <openssl/hmac.h>
#include <openssl/err.h>


namespace systelab { namespace jwt {

	HMACSHA256SignatureService::HMACSHA256SignatureService()
	{
	}

	HMACSHA256SignatureService::~HMACSHA256SignatureService() = default;

	std::string HMACSHA256SignatureService::signMessage(const std::string& key, const std::string& msg) const
	{
		unsigned int len = 32;
		unsigned char hash[32];

		HMAC(EVP_sha256(), &key[0], (int)(key.length()), (unsigned char*)(&msg[0]), msg.length(), hash, &len);

		std::stringstream ss;
		ss << std::setfill('0');

		for (unsigned int i = 0; i < len; i++)
		{
			ss  << hash[i];
		}

		Base64EncodeService base64EncodeService;
		return base64EncodeService.encodeString(ss.str());
	}

}}