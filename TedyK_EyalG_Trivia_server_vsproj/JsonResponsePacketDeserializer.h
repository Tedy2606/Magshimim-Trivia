#pragma once
#include <string>
#include <vector>
#include "json.hpp"
#include "json.hpp"
#include <iostream>>
#include <sstream>

#define HEADER_END 5

using std::string;
using json = nlohmann::json;

typedef std::vector<unsigned char> Buffer;

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

struct SubmitAnswerRequest
{
	unsigned int answerID;
};

struct AddQuestionRequest
{
	string question;
	string correctAnswer;
	string answer1;
	string answer2;
	string answer3;
};

class JsonResponsePacketDeserializer
{
public:


	/***
	* desirializes a Create Room request from an array of bytes
	* @params buffer - the array of bytes
	* @return CreateRoomRequest - the Create Room request
	**/
	CreateRoomRequest desirializeCreateRoomRequest(Buffer buffer);

	/***
	* desirializes a Join Room request from an array of bytes
	* @params buffer - the array of bytes
	* @return JoinRoomRequest - the Join Room request
	**/
	JoinRoomRequest desirializeJoinRoomRequest(Buffer buffer);

	/***
	* desirializes a Get Players In Room request from an array of bytes
	* @params buffer - the array of bytes
	* @return GetPlayersInRoomRequest - the Players request
	**/
	GetPlayersInRoomRequest desirializeGetPlayersInRoomRequest(Buffer buffer);


	/***
	* desirializes a login request from an array of bytes
	* @params buffer - the array of bytes 
	* @return loginRequest - the login request 
	**/
	LoginRequest desirializeLoginRequest(Buffer buffer);

	/***
	* desirializes a signup request from an array of bytes
	* @params buffer - the array of bytes
	* @return signupRequest - the signup request
	**/
	SignupRequest desirializeSignupRequest(Buffer buffer);

	/*
	* desirializes a submit answer request from an array of bytes
	* @params buffer - the array of bytes
	* @return signupRequest - the submit answer request
	*/
	SubmitAnswerRequest desirializeSubmitAnswerRequest(Buffer buffer);

	/*
	* desirializes an add question request from an array of bytes
	* @params buffer - the array of bytes
	* @return signupRequest - the add question request
	*/
	AddQuestionRequest desirializeAddQuestionRequest(Buffer buffer);

private:

	/***
	* gets an array of bytes and turns it into a json
	* @params buffer - the array of bytes
	* @return json - the array of bytes as a json
	**/
	json bufferToJson(Buffer buffer);

};
