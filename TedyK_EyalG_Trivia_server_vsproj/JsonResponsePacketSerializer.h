#pragma once
#include <vector>
struct ErrorResponse
{
	//complete this 
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
public:
	buffer serializeResponse(ErrorResponse);
	buffer serializeResponse(LoginResponse);
	buffer serializeResponse(SignupResponse);
};


