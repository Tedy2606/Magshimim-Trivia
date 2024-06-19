#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonResponsePacketDeserializer.h"
#include "Codes.h"

#define ANSWERS_NUM 4

class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler
{
public:
    GameRequestHandler(RequestHandlerFactory& handlerFactory, int gameID, LoggedUser user);

    /***
    * function checks if a request is relevant
    * @param const RequestInfo& info - the info (mainly the id) of the request
    * @return if the request matches or not
    **/
    virtual bool isRequestRelevant(const RequestInfo& info) const override;

    /***
    * handles a game request from the user - desirialise, procces, return response
    * @param const RequestInfo& info - the info (mainly the data) of the request
    * @return the result (serialised response and new handler)
    **/
    virtual RequestResult handleRequest(const RequestInfo& info) override;

private:
    /*
    Returns a Request Result with the requested question
    @param const RequestInfo& info - the info of the request
    @return the result of the request
    */
    RequestResult getQuestion(const RequestInfo& info);

    /*
    Submits an answer to a question
    @param const RequestInfo& info - the info of the request
    @return the result of the request
    */
    RequestResult submitAnswer(const RequestInfo& info);

    /*
    Returns the results of the game
    @param const RequestInfo& info - the info of the request
    @return the result of the request
    */
    RequestResult getGameResults(const RequestInfo& info);

    /*
    Leaves the game and room
    @param const RequestInfo& info - the info of the request
    @return the result of the request
    */
    RequestResult leaveGame(const RequestInfo& info);

    int m_gameID;
    LoggedUser m_user;
    GameManager& m_gameManager;
    RequestHandlerFactory& m_handlerFactory;
};
