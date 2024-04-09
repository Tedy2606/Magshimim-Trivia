#include "JsonResponsePacketSerializer.h"
#define ERROR_MSG_CODE 4
#define SIGNUP_MSG_CODE 3
#define LOGIN_MSG_CODE 2
#define LENGHT_IN_BYTES 4

buffer JsonResponsePacketSerializer::serializeResponseWithJson(json data, int code)
{
    //make the buffer
    std::vector<unsigned char> buf;

    std::string data_as_str = data.dump();

    buf.push_back(code); // enter the msg code 
    int len = data_as_str.length();

    //messege len is 4 byte 
    unsigned char msg_len_as_bytes[LENGHT_IN_BYTES];
    memcpy(msg_len_as_bytes, (char*)&len, LENGHT_IN_BYTES);


    //probably not the best way to do this but it can be improved after we know it works
    for (unsigned char c : msg_len_as_bytes)
    {
        buf.push_back(c);
    }

    //insert bytes into the vector
    for (char c : data_as_str) {
        buf.push_back(static_cast<unsigned char>(c));
    }

    return buf;
}

buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse response)
{
    //make the data json 
    json data = {
  {"status", response.err},
    };
    
    return serializeResponseWithJson(data, ERROR_MSG_CODE);
}

buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse response)
{
    //make the data json 
    json data = {
  {"status", response.status},
    };
    
    return serializeResponseWithJson(data, LOGIN_MSG_CODE);
}

buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse response)
{
    //for now the result is the same so to cut in lines this is what weill be done (WILL BE CHANGED AFTER DATABASE)
    LoginResponse loginRes;
    loginRes.status = response.status;

    return serializeResponse(loginRes);
}
