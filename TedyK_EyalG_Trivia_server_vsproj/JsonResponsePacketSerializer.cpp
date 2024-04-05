#include "JsonResponsePacketSerializer.h"

buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse response)
{
    //not really sure if this is correct or not

      // Make the buffer
    std::vector<unsigned char> buf;

    // Convert the error string to a char arr
    const char* errorStr = response.err.c_str();
    size_t strLength = response.err.length();


    //convert each char into unsigned and push it 
    for (size_t i = 0; i < strLength; ++i) {
        unsigned char byte = errorStr[i];
        buf.push_back(byte);
    }
    return buf;
}

buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse response)
{
    //make the buffer
    std::vector<unsigned char> buf;

    //make an array so we can copy the bytes
    unsigned char statusBytes[sizeof(int)];
    memcpy(statusBytes, (char*)&response.status, sizeof(int));

    //insert bytes into the vector
    buf.insert(buf.end(), statusBytes, statusBytes + sizeof(int));
    return buf;
}

buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse response)
{
    //make the buffer
    std::vector<unsigned char> buf;

    //make an array so we can copy the bytes
    unsigned char statusBytes[sizeof(int)];
    memcpy(statusBytes, (char*)&response.status, sizeof(int));

    //insert bytes into the vector
    buf.insert(buf.end(), statusBytes, statusBytes + sizeof(int));



    return buf;
}
