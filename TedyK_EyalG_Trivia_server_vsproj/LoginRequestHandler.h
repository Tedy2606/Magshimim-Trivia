#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include <mutex>
#include "JsonResponsePacketSerializer.h"
#include "JsonResponsePacketDeserializer.h"
#include "Codes.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
    LoginRequestHandler(RequestHandlerFactory& handlerFactory);

    /***
    * function checks if a request is relevant by comparing its id to the login and sign up id
    * @param const RequestInfo& info - the info (mainly the id) of the request
    * @return if the request matches or not
    **/
    bool isRequestRelevant(const RequestInfo& info) const override;

    /***
    * handles a log in request from the user - desirialise, process, return response
    * @param const RequestInfo& info - the info (mainly the data) of the request
    * @return the result (serialized response and new handler)
    **/
    RequestResult handleRequest(const RequestInfo& info) override;

private:
    /*
    Method returns a response to the input login info
    @param const RequestInfo& info - the info of the request
    @return the result (serialized response and new handler)
    */
    RequestResult login(const RequestInfo& info);

    /*
    Method returns a response to the input signup info
    @param const RequestInfo& info - the info of the request
    @return the result (serialized response and new handler)
    */
    RequestResult signup(const RequestInfo& info);

    // fields
    RequestHandlerFactory& m_handlerFactory;
    std::mutex m_loginMutex;
};
