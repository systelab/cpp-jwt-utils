#include "TokenParserService.h"

#include "Services/Base64EncodeService.h"
#include "Services/HMACSHA256SignatureService.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"
#include "JSONAdapterInterface/IJSONValue.h"

#include <sstream>


namespace systelab { namespace jwt {

	TokenParserService::TokenParserService(json::IJSONAdapter& jsonAdapter)
		:m_jsonAdapter(jsonAdapter)
	{
	}

	TokenParserService::~TokenParserService() = default;

	bool TokenParserService::validateJWT(const std::string& token,
											const std::string& key,
											std::vector< std::pair<std::string, std::string> >& claims) const
	{
		std::vector<std::string> tokenElements = getTokenElements(token);
		if (tokenElements.size() != 3)
		{
			return false;
		}

		std::string jwtHeader = tokenElements[0];
		std::string jwtPayload = tokenElements[1];
		std::string jwtSignature = tokenElements[2];
		if (!validateSignature(jwtHeader, jwtPayload, jwtSignature, key))
		{
			return false;
		}

		return extractClaims(jwtPayload, claims);
	}

	std::vector<std::string> TokenParserService::getTokenElements(const std::string& token) const
	{
		std::vector<std::string> tokenElements;

		std::stringstream stream(token);
		while (stream.good())
		{
			std::string item;
			getline(stream, item, '.');
			tokenElements.push_back(item);
		}

		return tokenElements;
	}

	bool TokenParserService::validateSignature(const std::string& jwtHeader,
												  const std::string& jwtPayload,
												  const std::string& jwtSignature,
												  const std::string& key) const
	{
		HMACSHA256SignatureService hmacsha256SignatureService;
		std::string computedJWTSignature = hmacsha256SignatureService.signMessage(key, jwtHeader + "." + jwtPayload);

		std::string jwtSignatureClean = jwtSignature.substr(0, jwtSignature.find_first_of("="));
		std::string computedJWTSignatureClean = computedJWTSignature.substr(0, computedJWTSignature.find_first_of("="));

		return (jwtSignatureClean == computedJWTSignatureClean);
	}

	bool TokenParserService::extractClaims(const std::string& jwtPayload,
											  std::vector< std::pair<std::string, std::string> >& claims) const
	{
		Base64EncodeService base64EncodeService;
		std::string jwtPayloadDecoded = base64EncodeService.decodeString(jwtPayload);

		auto jsonPayloadDocument = m_jsonAdapter.buildDocumentFromString(jwtPayloadDecoded);
		if (!jsonPayloadDocument)
		{
			return false;
		}

		json::IJSONValue& jsonPayloadRoot = jsonPayloadDocument->getRootValue();
		auto memberNames = jsonPayloadRoot.getObjectMemberNames();
		size_t nMembers = memberNames.size();
		for (size_t i = 0; i < nMembers; i++)
		{
			std::string claimName = memberNames[i];
			json::IJSONValue& jsonClaimValue = jsonPayloadRoot.getObjectMemberValue(claimName);
			std::string claimValue = jsonClaimValue.getString();
			claims.push_back({ claimName, claimValue });
		}

		return true;
	}

}}