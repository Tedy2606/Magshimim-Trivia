#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser user)
	: m_handlerFactory(handlerFactory), m_roomManager(handlerFactory.getRoomManager()), m_room(room), m_user(user)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
    return info.id == LEAVE_ROOM_REQ ||
        info.id == GET_ROOM_STATS_REQ;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info)
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

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo info)
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

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo info)
{
	return RequestResult();
}
