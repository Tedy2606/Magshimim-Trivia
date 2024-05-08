#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser user)
	: m_handlerFactory(handlerFactory), m_roomManager(handlerFactory.getRoomManager()), m_room(room), m_user(user)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info)
{
	return false;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info)
{
	return RequestResult();
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
	return RequestResult();
}
