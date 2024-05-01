#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDataBase* database)
    : m_loginManager(database), m_statisticsManager(database), m_roomManager()
{
    this->m_database = database;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return new LoginRequestHandler(*this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
    return new MenuRequestHandler(*this, user);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return this->m_loginManager;
}

IDataBase* RequestHandlerFactory::getDatabase()
{
    return this->m_database;
}

RoomManager& RequestHandlerFactory::getRoomManagaer()
{
    return this->m_roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    return this->m_statisticsManager;
}