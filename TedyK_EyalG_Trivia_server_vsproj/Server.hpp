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
#include <mutex>

class Server
{
public:
    ~Server();
    static Server& getInstance();
    Server(const Server& obj) = delete;
    void run();

private:
    Server();
    static Server* m_instance;
    IDataBase* m_database;
    RequestHandlerFactory m_handlerFactory;
    Communicator& m_communicator;
};