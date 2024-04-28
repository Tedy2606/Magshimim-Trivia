#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user);

	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;






private:
	/*
	Method returns a response to the input signout info
	@param info - the info of the request
	@return the result (serialised response and new handler)
	*/
	RequestResult signout(RequestInfo info);

	/*
	Method returns a response to the input getRooms info
	@param info - the info of the request
	@return the result (serialised response and new handler)
	*/
	RequestResult getRooms(RequestInfo info);

	/*
	Method returns a response to the input getPlayersInRoom info
	@param info - the info of the request
	@return the result (serialised response and new handler)
	*/
	RequestResult getPlayersInRoom(RequestInfo info);


	/*
	Method returns a response to the input getPersonalStats info
	@param info - the info of the request
	@return the result (serialised response and new handler)
	*/
	RequestResult getPersonalStats(RequestInfo info);


	/*
	Method returns a response to the input getHighScore info
	@param info - the info of the request
	@return the result (serialised response and new handler)
	*/
	RequestResult getHighScore(RequestInfo info);


	/*
	Method returns a response to the input joinRoom info
	@param info - the info of the request
	@return the result (serialised response and new handler)
	*/
	RequestResult joinRoom(RequestInfo info);


	/*
	Method returns a response to the input createRoom info
	@param info - the info of the request
	@return the result (serialised response and new handler)
	*/
	RequestResult createRoom(RequestInfo info);

	RequestHandlerFactory& m_handlerFactory;
	LoggedUser m_user;
};