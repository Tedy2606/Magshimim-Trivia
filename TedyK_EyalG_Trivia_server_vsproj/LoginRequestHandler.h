#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public: 
	LoginRequestHandler(RequestHandlerFactory& handlerFactory);

	/***
	* function checks if a request is relevant by compering its id to the login and sign up id 
	* @param RequestInfo info - the info (mainly the id) of the request
	* @return if the request matches or not 
	**/
	bool isRequestRelevant(RequestInfo info);


	/***
	* handles a log in request from the user - desirialise, procces, return response
	* @param RequestInfo info - the info (mainly the data) of the request
	* @return the result (serialised response and new handler)
	**/
	RequestResult handleRequest(RequestInfo info);

private:
	/*
	Method returns a response to the input login info
	@param info - the info of the request
	@return the result (serialised response and new handler)
	*/
	RequestResult login(RequestInfo info);

	/*
	Method returns a response to the input signup info
	@param info - the info of the request
	@return the result (serialised response and new handler)
	*/
	RequestResult signup(RequestInfo info);


	// fields
	RequestHandlerFactory& m_handlerFactory;
};
