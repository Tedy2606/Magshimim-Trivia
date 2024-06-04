#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDataBase* database)
    : m_loginManager(database), m_statisticsManager(database), m_roomManager(), m_gameManager(database)
{
    this->m_database = database;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return new LoginRequestHandler(*this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser& user)
{
    return new MenuRequestHandler(*this, user);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser& user, Room& room)
{
    return new RoomMemberRequestHandler(*this, room, user);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser& user, Room& room)
{
    return new RoomAdminRequestHandler(*this, room, user);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(LoggedUser& user, Game& game)
{
    return new GameRequestHandler(*this, game, user);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return this->m_loginManager;
}

IDataBase* RequestHandlerFactory::getDatabase()
{
    return this->m_database;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    return this->m_roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    return this->m_statisticsManager;
}

GameManager& RequestHandlerFactory::getGameManager()
{
    return this->m_gameManager;
}
