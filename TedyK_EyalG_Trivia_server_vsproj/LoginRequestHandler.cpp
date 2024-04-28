#include "LoginRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonResponsePacketDeserializer.h"

#define LOGIN_REQ 101
#define SIGNUP_REQ 102

#define BAD_RESPONSE 2
#define OK_RESPONSE 1
#define ERROR_RESPONSE 0

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory)
    : m_handlerFactory(handlerFactory)
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    return info.id == LOGIN_REQ || info.id == SIGNUP_REQ;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
    RequestResult result;

    switch (info.id)
    {
    case LOGIN_REQ:
        result = login(info);
        break;

    case SIGNUP_REQ:
        result = signup(info);
        break;
    }

    return result;
}

RequestResult LoginRequestHandler::login(RequestInfo info)
{
    JsonResponsePacketSerializer seri;
    JsonResponsePacketDeserializer desi;

    // ***Process the info***
    // deserialize the info into a login request
    LoginRequest request = desi.desirializeLoginRequest(info.buffer);


    // ***Start making the response***
    LoginResponse response;
    RequestResult result;

    // if login succeeded make an ok response
    try
    {
        this->m_handlerFactory.getLoginManager().login(request.name, request.password); // login
        LoggedUser user(request.name);
        response.status = OK_RESPONSE;
        result.newHandler = this->m_handlerFactory.createMenuRequestHandler(user);
        result.buffer = seri.serializeResponse(response);

    }
    catch (const std::exception& err) // login failed, make a bad response
    {
        //make an error 
        ErrorResponse error;
        error.err = err.what();

        //return to the login handler
        result.newHandler = this->m_handlerFactory.createLoginRequestHandler();
        //send the error
        result.buffer = seri.serializeResponse(error);
    }
    return result;
}

RequestResult LoginRequestHandler::signup(RequestInfo info)
{
    JsonResponsePacketSerializer seri;
    JsonResponsePacketDeserializer desi;

    // ***Process the info***
    // deserialize the info into a login request
    SignupRequest request = desi.desirializeSignupRequest(info.buffer);


    // ***Start making the response***
    SignupResponse response;
    RequestResult result;

    // if signup succeeded make an ok response
    try
    {
        this->m_handlerFactory.getLoginManager().signup(request.name, request.password, request.email); // signup
        LoggedUser user(request.name);
        response.status = OK_RESPONSE;
        result.newHandler = this->m_handlerFactory.createMenuRequestHandler(user);
        result.buffer = seri.serializeResponse(response);

    }
    catch (const std::exception& err) // signup failed, make a bad response
    {
        //make an error 
        ErrorResponse error;
        error.err = err.what();

        //return to the login handler
        result.newHandler = this->m_handlerFactory.createLoginRequestHandler();
        //send the error
        result.buffer = seri.serializeResponse(error);
    }

    return result;
}
