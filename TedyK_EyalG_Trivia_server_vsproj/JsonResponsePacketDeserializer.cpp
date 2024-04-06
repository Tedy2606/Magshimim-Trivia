#include "JsonResponsePacketDeserializer.h"
#include "json.hpp"
#include <iostream>>
#include <sstream>
using json = nlohmann::json;
LoginRequest JsonResponsePacketDeserializer::desirializeLoginRequest(std::vector<unsigned char> buffer)
{
    //this does not work, need to figure out a way to turn the buffer bytes to an int 
    int data_len = (buffer[1] << 8) | buffer[2] | buffer[3] | buffer[4];

    //erase the not needed stuff 
    buffer.erase(buffer.begin() + 4);
    //get the values as string (maybe)
    string data_as_str(buffer.begin(), buffer.begin() + data_len);

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
