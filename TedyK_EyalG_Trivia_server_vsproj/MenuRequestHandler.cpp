#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory)
    : m_handlerFactory(handlerFactory)
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo info)
{
    return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo info)
{
    return RequestResult();
}
