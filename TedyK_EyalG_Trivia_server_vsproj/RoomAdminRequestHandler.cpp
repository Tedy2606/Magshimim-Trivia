#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser user)
	: m_handlerFactory(handlerFactory), m_roomManager(handlerFactory.getRoomManager()), m_room(room), m_user(user)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.id == CLOSE_ROOM_REQ ||
		info.id == START_GAME_REQ ||
		info.id == GET_ROOM_STATS_REQ;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info)
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

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo info)
{
	return RequestResult();
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo info)
{
	return RequestResult();
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo info)
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
    result.newHandler = this->m_handlerFactory.createRoomMemberRequestHandler(this->m_user);
    result.buffer = seri.serializeResponse(response);

    return result;
}
