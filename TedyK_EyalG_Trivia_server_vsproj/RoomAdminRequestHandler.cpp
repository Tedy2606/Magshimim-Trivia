#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser user)
	: m_handlerFactory(handlerFactory), m_roomManager(handlerFactory.getRoomManager()), m_room(room), m_user(user)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& info) const
{
	return info.id == CLOSE_ROOM_REQ ||
		info.id == START_GAME_REQ ||
		info.id == GET_ROOM_STATS_REQ;
}

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& info)
{
    RequestResult result;

    switch (info.id)
    {
    case CLOSE_ROOM_REQ:
        result = closeRoom(info);
        break;
    case START_GAME_REQ:
        result = startGame(info);
        break;
    case GET_ROOM_STATS_REQ:
        result = getRoomState(info);
        break;
    }

    return result;
}

RequestResult RoomAdminRequestHandler::closeRoom(const RequestInfo& info)
{
    JsonResponsePacketSerializer seri;
    CloseRoomResponse response;
    RequestResult result;

    // close the room
    this->m_roomManager.getRoom(this->m_room.getData().id).getData().isActive = CLOSED_ROOM;

    // leave the room
    this->m_roomManager.getRoom(this->m_room.getData().id).removeUser(this->m_user);
    
    response.status = OK_RESPONSE;

    // make a response and serialize it
    result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
    result.buffer = seri.serializeResponse(response);

    return result;
}

RequestResult RoomAdminRequestHandler::startGame(const RequestInfo& info)
{
    JsonResponsePacketSerializer seri;
    StartGameResponse response;
    RequestResult result;

    // start the game
    this->m_roomManager.getRoom(this->m_room.getData().id).getData().isActive = STARTED;
    response.status = OK_RESPONSE;

    // make a response and serialize it
    this->m_handlerFactory.getGameManager().createGame(this->m_roomManager.getRoom(this->m_room.getData().id));
    
    result.newHandler = this->m_handlerFactory.createGameRequestHandler(this->m_user, 
        this->m_room.getData().id);
    result.buffer = seri.serializeResponse(response);

    return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(const RequestInfo& info)
{
    JsonResponsePacketSerializer seri;
    GetRoomStateResponse response;
    RequestResult result;

    // get the room state
    response.hasGameBegun = this->m_roomManager.getRoom(this->m_room.getData().id).getData().isActive;
    response.answerTimeout = this->m_roomManager.getRoom(this->m_room.getData().id).getData().timePerQuestion;
    response.questionCount = this->m_roomManager.getRoom(this->m_room.getData().id).getData().numOfQuestions;
    response.players = this->m_roomManager.getRoom(this->m_room.getData().id).getAllUsers();
    response.status = OK_RESPONSE;

    // make a response and serialize it
    result.newHandler = this->m_handlerFactory.createRoomAdminRequestHandler(this->m_user, this->m_room);
    result.buffer = seri.serializeResponse(response);

    return result;
}
