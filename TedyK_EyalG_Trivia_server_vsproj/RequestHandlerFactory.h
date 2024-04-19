#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"

class RequestHandlerFactory
{
public:
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();

	/*
	Getter for the m_logginManager field
	*/
	LoginManager& getLoginManager();

private:
	LoginManager m_loginManager;
	IDataBase* m_database;
};