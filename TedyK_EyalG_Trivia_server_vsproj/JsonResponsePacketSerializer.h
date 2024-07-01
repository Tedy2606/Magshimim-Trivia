#pragma once
#include <vector>
#include <string>
#include "json.hpp"
#include "Room.h"
#include "Game.h"
#include "Codes.h"
#include <sstream>

#define LENGHT_IN_BYTES 4

using json = nlohmann::json;

typedef std::vector<unsigned char> Buffer;

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
	int hasGameBegun;
	std::vector<string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

struct LeaveRoomResponse
{
	unsigned int status;
};

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

struct AddQuestionResponse
{
	unsigned int status;
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

struct LeaveGameResponse
{
	unsigned int status;
};

struct GetQuestionResponse
{
	unsigned int status;
	string question;
	std::map<unsigned int, string> answers;
};

struct SubmitAnswerResponse
{
	unsigned int status;
	unsigned int isCorrect;
};

struct PlayerResults
{
	string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int totalAnswerTime;
};

struct GetGameResultsResponse
{
	unsigned int status;
	std::vector<PlayerResults> results;
};

class JsonResponsePacketSerializer
{
private:
	/***
	* serializes a request given the json data 
	* @param json data - the data to be serialized and sent 
	* @return buffer - the array of bytes
	* 
	**/
	static Buffer serializeResponseWithJson(const json& data, int code);

public:
	/***
	* serializes a error Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static Buffer serializeResponse(const ErrorResponse& response);

	/***
	* serializes a Login Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static Buffer serializeResponse(const LoginResponse& response);

	/***
	* serializes a signup Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static Buffer serializeResponse(const SignupResponse& response);

	/***
	* serializes a logout Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static Buffer serializeResponse(const LogoutResponse& response);

	/***
	* serializes a join room Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static Buffer serializeResponse(const JoinRoomResponse& response);

	/***
	* serializes a create room Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static Buffer serializeResponse(const CreateRoomResponse& response);

	/***
	* serializes a get personal stats Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static Buffer serializeResponse(const GetPersonalStatsResponse& response);

	/***
	* serializes a get high score Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static Buffer serializeResponse(const GetHighScoreResponse& response);

	/***
	* serializes a get players in room Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static Buffer serializeResponse(const GetPlayersInRoomResponse& response);

	/***
	* serializes a get rooms Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static Buffer serializeResponse(const GetRoomsResponse& response);

	/***
	* serializes a close room Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static Buffer serializeResponse(const CloseRoomResponse& response);

	/***
	* serializes a start game Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static Buffer serializeResponse(const StartGameResponse& response);

	/***
	* serializes a get room state Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static Buffer serializeResponse(const GetRoomStateResponse& response);

	/***
	* serializes a leave room Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static Buffer serializeResponse(const LeaveRoomResponse& response);

	/***
	* serializes a get game results Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static Buffer serializeResponse(const GetGameResultsResponse& response);

	/***
	* serializes a submit answer Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static Buffer serializeResponse(const SubmitAnswerResponse& response);

	/***
	* serializes a get question Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static Buffer serializeResponse(const GetQuestionResponse& response);

	/***
	* serializes a leave game Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static Buffer serializeResponse(const LeaveGameResponse& response);

	/***
	* serializes an add question Response to an array of bytes
	* @param response - the reponse the server wants to send back
	* @return buffer - the array of bytes
	**/
	static Buffer serializeResponse(const AddQuestionResponse& response);
};
