#include "JsonResponsePacketDeserializer.h"

CreateRoomRequest JsonResponsePacketDeserializer::desirializeCreateRoomRequest(Buffer buffer)
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

JoinRoomRequest JsonResponsePacketDeserializer::desirializeJoinRoomRequest(Buffer buffer)
{
    json data_as_json = bufferToJson(buffer);

    //make the request
    JoinRoomRequest request;
    request.roomID = data_as_json["roomID"];
    return request;
}


GetPlayersInRoomRequest JsonResponsePacketDeserializer::desirializeGetPlayersInRoomRequest(Buffer buffer)
{
    json data_as_json = bufferToJson(buffer);
    //make the request
    GetPlayersInRoomRequest request;
    request.roomID = data_as_json["roomID"];
    return request;
}


LoginRequest JsonResponsePacketDeserializer::desirializeLoginRequest(Buffer buffer)
{

    //make the json
    json data_as_json = bufferToJson(buffer);

    //make the request
    LoginRequest request;
    request.name = data_as_json["username"];
    request.password = data_as_json["password"];

    return request;
}

SignupRequest JsonResponsePacketDeserializer::desirializeSignupRequest(Buffer buffer)
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

SubmitAnswerRequest JsonResponsePacketDeserializer::desirializeSubmitAnswerRequest(Buffer buffer)
{
    //make the json
    json data_as_json = bufferToJson(buffer);

    // make the request
    SubmitAnswerRequest request;
    request.answerID = data_as_json["answerID"];

    return request;
}

AddQuestionRequest JsonResponsePacketDeserializer::desirializeAddQuestionRequest(Buffer buffer)
{
    //make the json
    json data_as_json = bufferToJson(buffer);

    // make the request
    AddQuestionRequest request;
    request.question = data_as_json["question"];
    request.correctAnswer = data_as_json["correctAnswer"];
    request.answer1 = data_as_json["answer1"];
    request.answer2 = data_as_json["answer2"];
    request.answer3 = data_as_json["answer3"];

    return request;
}

json JsonResponsePacketDeserializer::bufferToJson(Buffer buffer)
{
    //get the data as a string
    string data_as_str(buffer.begin() + HEADER_END, buffer.end());
    //make the data a json
    json data_as_json = json::parse(data_as_str);

    return data_as_json;
}