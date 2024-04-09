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
	/***
	* serializes a request given the json data 
	* @param json data - the data to be serialized and sent 
	* @return buffer - the array of bytes
	* 
	**/
	static buffer serializeResponseWithJson(json data, int code);


public:
	/***
	* serializes a error Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static buffer serializeResponse(ErrorResponse response);
	/***
	* serializes a Login Response to an array of bytes
	* @param response - the reponse the server wants to send back 
	* @return buffer - the array of bytes
	**/
	static buffer serializeResponse(LoginResponse response);
	
	/***
	* serializes a Login Response to an array of bytes
	* @param response - the reponse the server wants to send back 
	* @return buffer - the array of bytes
	**/
	static buffer serializeResponse(SignupResponse response);
};


