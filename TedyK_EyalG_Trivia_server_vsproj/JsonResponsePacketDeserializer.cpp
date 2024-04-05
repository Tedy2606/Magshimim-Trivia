#include "JsonResponsePacketDeserializer.h"

LoginRequest JsonResponsePacketDeserializer::desirializeLoginRequest(std::vector<unsigned char> buffer)
{
    return LoginRequest();
}

LoginRequest JsonResponsePacketDeserializer::desirializeSignupRequest(std::vector<unsigned char> buffer)
{
    return LoginRequest();
}
