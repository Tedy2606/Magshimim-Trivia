#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser user)
    : m_handlerFactory(handlerFactory), m_roomManager(handlerFactory.getRoomManager()), m_room(room), m_user(user)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo& info) const
{
    return info.id == LEAVE_ROOM_REQ ||
        info.id == GET_ROOM_STATS_REQ;
}

RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& info)
{
    RequestResult result;

    switch (info.id)
    {
    case LEAVE_ROOM_REQ:
        result = leaveRoom(info);
        break;
    case GET_ROOM_STATS_REQ:
        result = getRoomState(info);
        break;
    }

    return result;
}

RequestResult RoomMemberRequestHandler::leaveRoom(const RequestInfo& info)
{
    JsonResponsePacketSerializer seri;
    LeaveRoomResponse response;
    RequestResult result;

    // leave the room
    this->m_roomManager.getRoom(this->m_room.getData().id).removeUser(this->m_user);

    // make a response and serialize it
    response.status = OK_RESPONSE;
    result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
    result.buffer = seri.serializeResponse(response);

    return result;
}

RequestResult RoomMemberRequestHandler::getRoomState(const RequestInfo& info)
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
    result.newHandler = this->m_handlerFactory.createRoomMemberRequestHandler(this->m_user, this->m_room);
    result.buffer = seri.serializeResponse(response);

    return result;
}
