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
* desirializes a Create Room request from an array of bytes
* @params buffer - the array of bytes
* @return CreateRoomRequest - the Create Room request
**/
	CreateRoomRequest desirializeCreateRoomRequest(std::vector<unsigned char> buffer);

	/***
	* desirializes a Join Room request from an array of bytes
	* @params buffer - the array of bytes
	* @return JoinRoomRequest - the Join Room request
	**/
	JoinRoomRequest desirializeJoinRoomRequest(std::vector<unsigned char> buffer);

	/***
	* desirializes a Get Players In Room request from an array of bytes
	* @params buffer - the array of bytes
	* @return GetPlayersInRoomRequest - the Players request
	**/
	GetPlayersInRoomRequest desirializeGetPlayersInRoomRequest(std::vector<unsigned char> buffer);


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

