#include "stdafx.h"
#include "TokenBuilderService.h"

#include "Services/Base64EncodeService.h"
#include "Services/HMACSHA256SignatureService.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"
#include "JSONAdapterInterface/IJSONValue.h"


namespace systelab { namespace jwt {

	TokenBuilderService::TokenBuilderService(json::IJSONAdapter& jsonAdapter)
		:m_jsonAdapter(jsonAdapter)
	{
	}

	TokenBuilderService::~TokenBuilderService() = default;

	std::string TokenBuilderService::buildJWT(const std::string& key,
											  const std::vector< std::pair<std::string, std::string> >& claims) const
	{
		std::string jwtHeader = buildJWTHeader();
		std::string jwtPayload = buildJWTPayload(claims);
		std::string jwtSignature = buildJWTSignature(jwtHeader, jwtPayload, key);
		std::string jwt = jwtHeader + "." + jwtPayload + "." + jwtSignature;

		return jwt;
	}

	std::string TokenBuilderService::buildJWTHeader() const
	{
		auto jsonDocument = m_jsonAdapter.buildEmptyDocument();
		json::IJSONValue& jsonRoot = jsonDocument->getRootValue();
		jsonRoot.setType(json::OBJECT_TYPE);
		jsonRoot.addMember("alg", "HS256");
		jsonRoot.addMember("typ", "JWT");
		std::string jwtHeader = jsonDocument->serialize();

		Base64EncodeService base64EncodeService;
		return base64EncodeService.encodeString(jwtHeader);
	}

	std::string TokenBuilderService::buildJWTPayload(const std::vector< std::pair<std::string, std::string> >& claims) const
	{
		auto jsonDocument = m_jsonAdapter.buildEmptyDocument();

		json::IJSONValue& jsonRoot = jsonDocument->getRootValue();
		jsonRoot.setType(systelab::json::OBJECT_TYPE);
		for (auto claim : claims)
		{
			jsonRoot.addMember(claim.first, claim.second);
		}

		std::string jwtPayload = jsonDocument->serialize();

		Base64EncodeService base64EncodeService;
		return base64EncodeService.encodeString(jwtPayload);
	}

	std::string TokenBuilderService::buildJWTSignature(const std::string& jwtHeader,
													   const std::string& jwtPayload,
													   const std::string& key) const
	{
		std::stringstream stream;
		stream << jwtHeader << "." << jwtPayload;
		std::string messageToSign = stream.str();

		HMACSHA256SignatureService hmacsha256SignatureService;
		return hmacsha256SignatureService.signMessage(key, messageToSign);
	}

}}