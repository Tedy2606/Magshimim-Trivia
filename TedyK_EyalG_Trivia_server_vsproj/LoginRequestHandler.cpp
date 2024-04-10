#include "LoginRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#define LOGIN_REQ 2
#define SIGNUP_REQ 3
#define OK_RESPONSE 1
bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    return info.id == LOGIN_REQ || info.id == SIGNUP_REQ;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
    JsonResponsePacketSerializer seri;
    //should probably desirialise but since we dont do anything with it there is no need for now

    
    //make the response (code 1 will probably be changed based on desi in the future)
    LoginResponse response;
    response.status = OK_RESPONSE;
    RequestResult result;

    result.newHandler = nullptr; //for now no handler cus we didnt make the next state
    result.buffer = seri.serializeResponse(response);

    return result;
}
