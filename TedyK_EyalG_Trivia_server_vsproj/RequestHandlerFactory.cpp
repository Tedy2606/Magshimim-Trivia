#include "RequestHandlerFactory.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return new LoginRequestHandler(*this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{
    return nullptr;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return this->m_loginManager;
}
