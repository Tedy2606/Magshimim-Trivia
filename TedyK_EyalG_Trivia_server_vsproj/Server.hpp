#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <queue>
#include <set>
#include <string>
#include "Communicator.h"
#include "SqliteDatabase.h"
#include "RequestHandlerFactory.h"
#include <map>



class Server
{
public:
	Server();
	~Server();

	void run();

private:
	IDataBase* m_database;
	RequestHandlerFactory m_handlerFactory;
	Communicator m_communicator;
};

