#include "Base64EncodeService.h"

#include <openssl/hmac.h>
#include <openssl/err.h>
#include <iomanip>


namespace systelab { namespace jwt {

	Base64EncodeService::Base64EncodeService()
	{
	}

	Base64EncodeService::~Base64EncodeService() = default;

	std::string Base64EncodeService::encodeString(const std::string& stringToEncode) const
	{
		std::string ret;

		unsigned char const* bytesToEncode = (unsigned char*) stringToEncode.c_str();
		unsigned int nBytesToEncode = (int) stringToEncode.length();
		std::string base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

		int i = 0;
		int j = 0;
		unsigned char char_array_3[3];
		unsigned char char_array_4[4];

		while (nBytesToEncode--)
		{
			char_array_3[i++] = *(bytesToEncode++);

			if (i == 3)
			{
				char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
				char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
				char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
				char_array_4[3] = char_array_3[2] & 0x3f;

				for (i = 0; (i <4); i++)
					ret += base64Chars[char_array_4[i]];
				i = 0;
			}
		}

		if (i)
		{
			for (j = i; j < 3; j++)
			{
				char_array_3[j] = '\0';
			}

			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (j = 0; (j < i + 1); j++)
			{
				ret += base64Chars[char_array_4[j]];
			}

			// We do not want padding when encoding for JWT
			//while ((i++ < 3))
			//{
			//	ret += '=';
			//}
		}

		return ret;
	}

	std::string Base64EncodeService::decodeString(const std::string& encodedString) const
	{
		int nBytesToEncode = (int) encodedString.size();
		int i = 0;
		int j = 0;
		int in_ = 0;
		unsigned char char_array_4[4], char_array_3[3];
		std::string ret;

		std::string base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

		while (nBytesToEncode-- && (encodedString[in_] != '=') && isBase64(encodedString[in_]))
		{
			char_array_4[i++] = encodedString[in_]; in_++;
			if (i == 4)
			{
				for (i = 0; i < 4; i++)
				{
					char_array_4[i] = (unsigned char) base64Chars.find(char_array_4[i]);
				}

				char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
				char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
				char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

				for (i = 0; (i < 3); i++)
				{
					ret += char_array_3[i];
				}

				i = 0;
			}
		}

		if (i)
		{
			for (j = i; j < 4; j++)
			{
				char_array_4[j] = 0;
			}

			for (j = 0; j < 4; j++)
			{
				char_array_4[j] = (unsigned char) base64Chars.find(char_array_4[j]);
			}

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + (char_array_4[3] & 0x3f);

			for (j = 0; (j < i - 1); j++)
			{
				ret += char_array_3[j];
			}
		}

		return ret;
	}

	bool Base64EncodeService::isBase64(unsigned char c) const
	{
		return (isalnum(c) || (c == '-') || (c == '_'));
	}

}}