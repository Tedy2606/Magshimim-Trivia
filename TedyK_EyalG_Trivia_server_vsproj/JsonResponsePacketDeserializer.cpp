#include "JsonResponsePacketDeserializer.h"
#include "json.hpp"
#include <iostream>>
#include <sstream>
using json = nlohmann::json;
LoginRequest JsonResponsePacketDeserializer::desirializeLoginRequest(std::vector<unsigned char> buffer)
{
    //dark magic (uses bit shift to get the len ( 0x43, 0x21 -> 0x4321))
    int data_len = (buffer[1] << 8) | buffer[2] | buffer[3] | buffer[4];

    //erase the not needed stuff 
    buffer.erase(buffer.begin() + 4);
    //get the values as string (maybe)
    string data_as_str(buffer.begin(), buffer.end());

    //make the data a json
    json data_as_json;
    std::stringstream(data_as_str) >> data_as_json;

    LoginRequest request;
    request.name = data_as_json["username"];
    request.password = data_as_json["password"];


    return request;
}

SignupRequest JsonResponsePacketDeserializer::desirializeSignupRequest(std::vector<unsigned char> buffer)
{
    
    return SignupRequest();
}
