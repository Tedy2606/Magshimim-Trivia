#pragma once
#include <vector>
#include <string>
#include "json.hpp"
#include "Room.h"
using json = nlohmann::json;

//v3.0/


struct CloseRoomResponse
{
	unsigned int status;
};

struct StartGameResponse
{
	unsigned int status;
};

struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	std::vector<string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

struct LeaveRoomResponse
{
	unsigned int status;
};




//v2.0/

struct LogoutResponse
{
	unsigned int status;
};
struct JoinRoomResponse
{
	unsigned int status;
};
struct CreateRoomResponse
{
	unsigned int status;
};
struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
};
struct GetPlayersInRoomResponse
{
	std::vector<string> players;
};
struct GetHighScoreResponse
{
	unsigned int status;
	std::vector<string> statistics;
};
struct GetPersonalStatsResponse
{
	unsigned int status;
	std::vector<string> statistics;
};





// v 1.0./
struct ErrorResponse
{
	string err;
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
	* serializes a signup Response to an array of bytes
	* @param response - the reponse the server wants to send back 
	* @return buffer - the array of bytes
	**/
	static buffer serializeResponse(SignupResponse response);


	//ver 2 functions 

	/***
	* serializes a logout Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static buffer serializeResponse(LogoutResponse response);
	/***
	* serializes a join room Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static buffer serializeResponse(JoinRoomResponse response);
	/***
	* serializes a create room Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static buffer serializeResponse(CreateRoomResponse response);
	/***
	* serializes a get personal stats Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static buffer serializeResponse(GetPersonalStatsResponse response);
	/***
	* serializes a get high score Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static buffer serializeResponse(GetHighScoreResponse response);
	/***
	* serializes a get players in room Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static buffer serializeResponse(GetPlayersInRoomResponse response);
	/***
	* serializes a get rooms Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static buffer serializeResponse(GetRoomsResponse response);


	//ver 3 functions

	/***
	* serializes a close room Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static buffer serializeResponse(CloseRoomResponse response);
	/***
	* serializes a start game Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static buffer serializeResponse(StartGameResponse response);
	/***
	* serializes a get room state Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static buffer serializeResponse(GetRoomStateResponse response);
	/***
	* serializes a leave room Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static buffer serializeResponse(LeaveRoomResponse response);









};


