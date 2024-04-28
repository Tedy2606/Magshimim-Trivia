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



RequestResult MenuRequestHandler::signout(RequestInfo info)
{
    JsonResponsePacketSerializer seri;


    // ***Start making the response***
    LogoutResponse response;
    RequestResult result;

    // if logout succeeded make an ok response
    try
    {
        this->m_handlerFactory.getLoginManager().logout(this->m_user.GetUserName()); // logout

        response.status = OK_RESPONSE;
        result.newHandler = this->m_handlerFactory.createLoginRequestHandler();
        result.buffer = seri.serializeResponse(response);

    }
    catch (const std::exception& err) // logout failed, make a bad response
    {
        //make an error 
        ErrorResponse error;
        error.err = err.what();

        //return to the menu handler
        result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
        //send the error
        result.buffer = seri.serializeResponse(error);
    }
    return result;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo info)
{
    JsonResponsePacketSerializer seri;


    // ***Start making the response***
    GetRoomsResponse response;
    RequestResult result;

    // if GetRooms succeeded make an ok response
    try
    {

        response.rooms = this->m_handlerFactory.getRoomManagaer().getRooms(); // GetRooms

        response.status = OK_RESPONSE;
        result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
        result.buffer = seri.serializeResponse(response);

    }
    catch (const std::exception& err) // GetRooms failed, make a bad response
    {
        //make an error 
        ErrorResponse error;
        error.err = err.what();

        //return to the menu handler
        result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
        //send the error
        result.buffer = seri.serializeResponse(error);
    }
    return result;
}
