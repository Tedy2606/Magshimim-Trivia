#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include <mutex>
#include "JsonResponsePacketSerializer.h"
#include "JsonResponsePacketDeserializer.h"
#include "Codes.h"

#define NOT_STARTED 1

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
    MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user);

    virtual bool isRequestRelevant(const RequestInfo& info) const override;
    virtual RequestResult handleRequest(const RequestInfo& info) override;

private:
    /*
    Method returns a response to the input signout info
    @param info - the info of the request
    @return the result (serialised response and new handler)
    */
    RequestResult signout(const RequestInfo& info);

    /*
    Method returns a response to the input getRooms info
    @param info - the info of the request
    @return the result (serialised response and new handler)
    */
    RequestResult getRooms(const RequestInfo& info);

    /*
    Method returns a response to the input getPlayersInRoom info
    @param info - the info of the request
    @return the result (serialised response and new handler)
    */
    RequestResult getPlayersInRoom(const RequestInfo& info);

    /*
    Method returns a response to the input getPersonalStats info
    @param info - the info of the request
    @return the result (serialised response and new handler)
    */
    RequestResult getPersonalStats(const RequestInfo& info);

    /*
    Method returns a response to the input getHighScore info
    @param info - the info of the request
    @return the result (serialised response and new handler)
    */
    RequestResult getHighScore(const RequestInfo& info);

    /*
    Method returns a response to the input joinRoom info
    @param info - the info of the request
    @return the result (serialised response and new handler)
    */
    RequestResult joinRoom(const RequestInfo& info);

    /*
    Method returns a response to the input createRoom info
    @param info - the info of the request
    @return the result (serialised response and new handler)
    */
    RequestResult createRoom(const RequestInfo& info);

    /*
    Method returns a response to the input add question info
    @param info - the info of the request
    @return the result (serialised response and new handler)
    */
    RequestResult addQuestion(const RequestInfo& info);

    RequestHandlerFactory& m_handlerFactory;
    LoggedUser m_user;
    std::mutex m_menuMutex;
};
