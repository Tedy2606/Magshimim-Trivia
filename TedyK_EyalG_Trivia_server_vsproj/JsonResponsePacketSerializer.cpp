#include "JsonResponsePacketSerializer.h"

buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse)
{
    //here we probably only need the first byte (char)
    return buffer();
}

buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse)
{
    return buffer();
}

buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse)
{
    return buffer();
}
