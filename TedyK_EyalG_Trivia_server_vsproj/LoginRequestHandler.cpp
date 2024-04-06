#include "LoginRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    return info.id == 2 || info.id == 3;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
    JsonResponsePacketSerializer seri;
    //should probably desirialise but since we dont do anything with it there is no need for now

    

    LoginResponse response;
    response.status = 1;
    RequestResult result;

    result.newHandler = nullptr; //for now 
    result.buffer = seri.serializeResponse(response);


    return result;
}
