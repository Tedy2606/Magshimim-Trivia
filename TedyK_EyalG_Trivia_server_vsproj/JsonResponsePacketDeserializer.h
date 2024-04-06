#pragma once
#include <string>
#include <vector>
using std::string;

// uml says struct... dont really know where json comes in 

struct LoginRequest
{
	string name;
	string password;
};

struct SignupRequest
{
	string name;
	string password;
	string email;
};
class JsonResponsePacketDeserializer
{
public:
	LoginRequest desirializeLoginRequest(std::vector<unsigned char> buffer);
	SignupRequest desirializeSignupRequest(std::vector<unsigned char> buffer);

};

