#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDataBase* database);

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();

	/*
	Getter for the m_logginManager field
	*/
	LoginManager& getLoginManager();

	IDataBase* getDatabase();

private:
	LoginManager m_loginManager;
	IDataBase* m_database;
};