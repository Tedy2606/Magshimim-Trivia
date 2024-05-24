#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomMemberRequestHandler;
class RoomAdminRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDataBase* database);

	// create request handlers
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser user, Room room);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser user, Room room);

	// getters
	LoginManager& getLoginManager();
	IDataBase* getDatabase();
	RoomManager& getRoomManager();
	StatisticsManager& getStatisticsManager();

private:
	LoginManager m_loginManager;
	IDataBase* m_database;
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager;
};