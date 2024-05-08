#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser user)
	: m_handlerFactory(handlerFactory), m_roomManager(handlerFactory.getRoomManager()), m_room(room), m_user(user)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
	return false;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info)
{
	return RequestResult();
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo info)
{
	return RequestResult();
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo info)
{
	return RequestResult();
}
