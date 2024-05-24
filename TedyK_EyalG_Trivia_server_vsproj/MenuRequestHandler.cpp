#include "MenuRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonResponsePacketDeserializer.h"
#include "Codes.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user)
    : m_handlerFactory(handlerFactory), m_user(user)
{
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& info) const
{
    return info.id == LOGOUT_MSG_REQ ||
        info.id == JOIN_ROOM_MSG_REQ ||
        info.id == CREATE_ROOM_MSG_REQ ||
        info.id == GET_STATS_MSG_REQ ||
        info.id == GET_HIGH_SCORE_MSG_REQ ||
        info.id == GET_PLAYERS_IN_ROOM_MSG_REQ ||
        info.id == GET_ROOMS_MSG_REQ;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& info)
{
    RequestResult result;

    // create a lock guard
    std::lock_guard<std::mutex> lock(this->m_menuMutex);
    
    switch (info.id)
    {
    case LOGOUT_MSG_REQ:
        result = signout(info);
        break;
    case JOIN_ROOM_MSG_REQ:
        result = joinRoom(info);
        break;
    case CREATE_ROOM_MSG_REQ:
        result = createRoom(info);
        break;
    case GET_STATS_MSG_REQ:
        result = getPersonalStats(info);
        break;
    case GET_HIGH_SCORE_MSG_REQ:
        result = getHighScore(info);
        break;
    case GET_PLAYERS_IN_ROOM_MSG_REQ:
        result = getPlayersInRoom(info);
        break;
    case GET_ROOMS_MSG_REQ:
        result = getRooms(info);
        break;
    }

    return result;
}

RequestResult MenuRequestHandler::signout(const RequestInfo& info)
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
        // make an error
        ErrorResponse error;
        error.err = err.what();

        // return to the menu handler
        result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
        // send the error
        result.buffer = seri.serializeResponse(error);
    }
    return result;
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo& info)
{
    JsonResponsePacketSerializer seri;

    // ***Start making the response***
    GetRoomsResponse response;
    RequestResult result;

    // if GetRooms succeeded make an ok response
    response.rooms = this->m_handlerFactory.getRoomManager().getRooms(); // GetRooms

    response.status = OK_RESPONSE;
    result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
    result.buffer = seri.serializeResponse(response);
    // no need to check for errors since there are no possible errors
    // (assuming that there being no rooms is not an error)
    return result;
}

RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& info)
{
    JsonResponsePacketSerializer seri;
    JsonResponsePacketDeserializer desi;

    // ***Process the info***
    // deserialize the info into a get Players In Room request
    GetPlayersInRoomRequest request = desi.desirializeGetPlayersInRoomRequest(info.buffer);

    // ***Start making the response***
    GetPlayersInRoomResponse response;
    RequestResult result;

    // if get Players In Room succeeded make an ok response
    response.players = this->m_handlerFactory.getRoomManager().getRoom(request.roomID).getAllUsers(); // get Players In Room
    result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
    result.buffer = seri.serializeResponse(response);
    // no need to check for errors since there are no possible errors
    return result;
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& info)
{
    JsonResponsePacketSerializer seri;

    // ***Start making the response***
    GetPersonalStatsResponse response;
    RequestResult result;

    // if get stats succeeded make an ok response
    try
    {
        response.statistics = this->m_handlerFactory.getStatisticsManager().getUserStatistics(this->m_user.GetUserName()); // get stats

        response.status = OK_RESPONSE;
        result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
        result.buffer = seri.serializeResponse(response);
    }
    catch (const std::exception& err) // get stats failed, make a bad response
    {
        // make an error
        ErrorResponse error;
        error.err = err.what();

        // return to the menu handler
        result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
        // send the error
        result.buffer = seri.serializeResponse(error);
    }
    return result;
}

RequestResult MenuRequestHandler::getHighScore(const RequestInfo& info)
{
    JsonResponsePacketSerializer seri;

    // ***Start making the response***
    GetHighScoreResponse response;
    RequestResult result;

    // if get high score succeeded make an ok response
    try
    {
        response.statistics = this->m_handlerFactory.getStatisticsManager().getHighScore(); // get high score

        response.status = OK_RESPONSE;
        result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
        result.buffer = seri.serializeResponse(response);
    }
    catch (const std::exception& err) // get high score failed, make a bad response
    {
        // make an error
        ErrorResponse error;
        error.err = err.what();

        // return to the menu handler
        result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
        // send the error
        result.buffer = seri.serializeResponse(error);
    }
    return result;
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo& info)
{
    JsonResponsePacketSerializer seri;
    JsonResponsePacketDeserializer desi;

    // ***Process the info***
    // deserialize the info into a join room request
    JoinRoomRequest request = desi.desirializeJoinRoomRequest(info.buffer);
    

    // ***Start making the response***
    JoinRoomResponse response;
    RequestResult result;

    // if join room succeeded make an ok response
    try
    {
        this->m_handlerFactory.getRoomManager().getRoom(request.roomID).addUser(this->m_user.GetUserName()); // join room

        response.status = OK_RESPONSE;
        result.newHandler = this->m_handlerFactory.createRoomMemberRequestHandler(this->m_user, this->m_handlerFactory.getRoomManager().getRoom(request.roomID));
        result.buffer = seri.serializeResponse(response);
    }
    catch (const std::exception& err) // join room failed, make a bad response
    {
        // make an error
        ErrorResponse error;
        error.err = err.what();

        // return to the menu handler
        result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
        // send the error
        result.buffer = seri.serializeResponse(error);
    }
    return result;
}

RequestResult MenuRequestHandler::createRoom(const RequestInfo& info)
{
    JsonResponsePacketSerializer seri;
    JsonResponsePacketDeserializer desi;
    // ***Process the info***
    // deserialize the info into a create Room request
    CreateRoomRequest request = desi.desirializeCreateRoomRequest(info.buffer);
    

    // ***Start making the response***
    JoinRoomResponse response;
    RequestResult result;
    

    //make the data of the room
    RoomData data;
    data.name = request.roomName;
    data.numOfQuestions = request.questionCount;
    data.isActive = NOT_STARTED;
    data.timePerQuestion = request.answerTimeout;
    data.maxPlayers = request.maxUsers;

    // if create Room succeeded make an ok response
    try
    {
        int id = 0;
        // if there are no rooms then id is 0
        if (this->m_handlerFactory.getRoomManager().getRooms().size() != 0)
        {
            //get the id of the last room and add one
            std::vector<RoomData> rooms = this->m_handlerFactory.getRoomManager().getRooms();
            id = rooms.back().id;
            id++;
        }
        data.id = id;
        this->m_handlerFactory.getRoomManager().createRoom(this->m_user, data); // create Room

        response.status = OK_RESPONSE;
        result.newHandler = this->m_handlerFactory.createRoomAdminRequestHandler(this->m_user, this->m_handlerFactory.getRoomManager().getRoom(id));
        
        result.buffer = seri.serializeResponse(response);
    }
    catch (const std::exception& err) // create Room failed, make a bad response
    {
        // make an error
        ErrorResponse error;
        error.err = err.what();

        // return to the menu handler
        result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
        // send the error
        result.buffer = seri.serializeResponse(error);
    }
    return result;
}
