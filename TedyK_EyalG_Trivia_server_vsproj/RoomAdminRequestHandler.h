#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonResponsePacketDeserializer.h"

#define CLOSE_ROOM_REQ 113
#define START_GAME_REQ 114
#define GET_ROOM_STATS_REQ 115

#define OK_RESPONSE 1

#define CLOSED_ROOM 0
#define STARTED 2

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
	virtual bool isRequestRelevant(const RequestInfo& info) const override;

	/***
	* handles a room admin request from the user - desirialise, procces, return response
	* @param RequestInfo info - the info (mainly the data) of the request
	* @return the result (serialised response and new handler)
	**/
	virtual RequestResult handleRequest(const RequestInfo& info) override;

private:
	/*
	closes the room
	@param info - the info of the request
	@return the result of the request
	*/
	RequestResult closeRoom(const RequestInfo& info);

	/*
	starts the game
	@param info - the info of the request
	@return the result of the request
	*/
	RequestResult startGame(const RequestInfo& info);

	/*
	Returns the state of the room
	@param info - the info of the request
	@return the result of the request
	*/
	RequestResult getRoomState(const RequestInfo& info);

	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
};
