#include "JsonResponsePacketDeserializer.h"
#include "json.hpp"
#include <iostream>>
#include <sstream>
using json = nlohmann::json;
#define HEADER_END 5
CreateRoomRequest JsonResponsePacketDeserializer::desirializeCreateRoomRequest(std::vector<unsigned char> buffer)
{
    //make the json
    json data_as_json = bufferToJson(buffer);
    //make the request
    CreateRoomRequest request;
    request.answerTimeout = data_as_json["answerTimeout"];
    request.maxUsers = data_as_json["maxUsers"];
    request.questionCount = data_as_json["questionCount"];
    request.roomName = data_as_json["roomName"];
    return request;
}

JoinRoomRequest JsonResponsePacketDeserializer::desirializeJoinRoomRequest(std::vector<unsigned char> buffer)
{
    json data_as_json = bufferToJson(buffer);

    //make the request
    JoinRoomRequest request;
    request.roomID = data_as_json["roomID"];

    return request;
}

LoginRequest JsonResponsePacketDeserializer::desirializeLoginRequest(std::vector<unsigned char> buffer)
{

    //make the json
    json data_as_json = bufferToJson(buffer);

    //make the request
    LoginRequest request;
    request.name = data_as_json["username"];
    request.password = data_as_json["password"];

    return request;
}

SignupRequest JsonResponsePacketDeserializer::desirializeSignupRequest(std::vector<unsigned char> buffer)
{
    //make the json
    json data_as_json = bufferToJson(buffer);


    //make the request
    SignupRequest request;
    request.name = data_as_json["username"];
    request.password = data_as_json["password"];
    request.email = data_as_json["mail"];

    return request;
}

json JsonResponsePacketDeserializer::bufferToJson(std::vector<unsigned char> buffer)
{
    //dark magic (uses bit shift to combine the bits into an int)
    int data_len = (buffer[1] << 24) | (buffer[2] << 16) | (buffer[3] << 8) | buffer[4];
    //turn the data in the buffer to str
    string data_as_str(reinterpret_cast<char*>(&buffer[HEADER_END]), data_len);
    //make the data a json
    json data_as_json = json::parse(data_as_str);

    return data_as_json;
}