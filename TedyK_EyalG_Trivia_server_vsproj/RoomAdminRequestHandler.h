#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser user);
	
	/***
	* function checks if a request is relevant
	* @param RequestInfo info - the info (mainly the id) of the request
	* @return if the request matches or not
	**/
	virtual bool isRequestRelevant(RequestInfo info);

	/***
	* handles a room admin request from the user - desirialise, procces, return response
	* @param RequestInfo info - the info (mainly the data) of the request
	* @return the result (serialised response and new handler)
	**/
	virtual RequestResult handleRequest(RequestInfo info);

private:
	/*
	closes the room
	@param info - the info of the request
	@return the result of the request
	*/
	RequestResult closeRoom(RequestInfo info);

	/*
	starts the game
	@param info - the info of the request
	@return the result of the request
	*/
	RequestResult startGame(RequestInfo info);

	/*
	Leaves the room
	@param info - the info of the request
	@return the result of the request
	*/
	RequestResult getRoomState(RequestInfo info);

	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
};
