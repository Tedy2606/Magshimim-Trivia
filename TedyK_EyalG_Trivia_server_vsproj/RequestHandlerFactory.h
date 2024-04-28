#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDataBase* database);

	LoginRequestHandler* createLoginRequestHandler();


	/*
	Getter for the m_logginManager field
	*/
	LoginManager& getLoginManager();

	IDataBase* getDatabase();



	//ver 2

	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);
	RoomManager& getRoomManagaer();
	StatisticsManager& getStatisticsManager();

private:
	LoginManager m_loginManager;
	IDataBase* m_database;
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager;
};