#pragma once
#include <string>
#include <vector>
using std::string;


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

	/***
	* desirializes a login request from an array of bytes
	* @params buffer - the array of bytes 
	* @return loginRequest - the login request 
	**/
	LoginRequest desirializeLoginRequest(std::vector<unsigned char> buffer);

	/***
	* desirializes a signup request from an array of bytes
	* @params buffer - the array of bytes
	* @return signupRequest - the signup request
	**/
	SignupRequest desirializeSignupRequest(std::vector<unsigned char> buffer);

};

