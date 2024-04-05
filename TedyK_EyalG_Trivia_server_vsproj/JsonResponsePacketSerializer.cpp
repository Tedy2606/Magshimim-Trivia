#include "JsonResponsePacketSerializer.h"
#include "json.hpp"
using json = nlohmann::json;
buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse response)
{
   
    return buffer();
}

buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse response)
{
    //make the data json 
    json data = json::parse(R"(
  {
    "status": 1,
  }
)");
    //make the buffer
    std::vector<unsigned char> buf;

   
    //should probably get the jso into the buffer usign memcpy (something like this)
    //memcpy(statusBytes, (char*)&response.status, sizeof(int));

    //insert bytes into the vector
    //buf.insert(buf.end(), statusBytes, statusBytes + sizeof(int));
    return buf;
}

buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse response)
{
    
    return buffer();
}
