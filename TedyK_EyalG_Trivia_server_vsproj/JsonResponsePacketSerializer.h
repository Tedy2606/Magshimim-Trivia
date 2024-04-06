#pragma once
#include <vector>
#include <string>
#include "json.hpp"
using json = nlohmann::json;
struct ErrorResponse
{
	std::string err;
};
struct LoginResponse
{
	unsigned int status;
};
struct SignupResponse
{
	unsigned int status;
};
typedef std::vector<unsigned char> buffer;

class JsonResponsePacketSerializer
{
private:
	static buffer serializeResponseWithJson(json data);


public:

	static buffer serializeResponse(ErrorResponse response);
	static buffer serializeResponse(LoginResponse response);
	static buffer serializeResponse(SignupResponse response);
};


