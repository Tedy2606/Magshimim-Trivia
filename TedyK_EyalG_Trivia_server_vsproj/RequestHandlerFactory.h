#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"

class RequestHandlerFactory
{
public:
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();

private:
	LoginManager m_loginManager;
	IDataBase* m_database;
};