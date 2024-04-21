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


//ver 2
struct GetPlayersInRoomRequest
{
	unsigned int roomID;
};
struct JoinRoomRequest
{
	unsigned int roomID;
};


struct CreateRoomRequest
{
	string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};


//ver 2
struct GetPlayersInRoomRequest
{
	unsigned int roomID;
};
struct JoinRoomRequest
{
	unsigned int roomID;
};


struct CreateRoomRequest
{
	string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
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
private:

	/***
	* gets an array of bytes and turns it into a json
	* @params buffer - the array of bytes
	* @return json - the array of bytes as a json
	**/
	json bufferToJson(std::vector<unsigned char> buffer);

};

