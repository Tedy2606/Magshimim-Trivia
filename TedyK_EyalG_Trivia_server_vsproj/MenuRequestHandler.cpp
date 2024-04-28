#include "MenuRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonResponsePacketDeserializer.h"

#define LOGOUT_MSG_CODE 104

#define JOIN_ROOM_MSG_CODE 105
#define CREATE_ROOM_MSG_CODE 106
#define GET_STATS_MSG_CODE 107
#define GET_HIGH_SCORE_MSG_CODE 108


#define GET_PLAYERS_IN_ROOM_MSG_CODE 109
#define GET_ROOMS_MSG_CODE 110


#define OK_RESPONSE 1

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user)
    : m_handlerFactory(handlerFactory), m_user(user)
{
}


bool MenuRequestHandler::isRequestRelevant(RequestInfo info)
{
    return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo info)
{
    return RequestResult();
}
