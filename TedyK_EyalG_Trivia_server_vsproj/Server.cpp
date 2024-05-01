#include "Server.hpp"
#include "WSAInitializer.h"
#include <iostream>
#include <exception>
#include <thread>
#include "SqliteDatabase.h"
#include "RequestHandlerFactory.h"

Server* Server::instance = nullptr;

Server::Server()
    : m_handlerFactory(new SqliteDatabase()), m_communicator(Communicator::getInstance(this->m_handlerFactory))
{
    this->m_database = this->m_handlerFactory.getDatabase();
}

Server::~Server()
{
}

Server& Server::getInstance()
{
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);

    if (instance == nullptr) {
        instance = new Server();
    }
    return *instance;
}

void Server::run()
{
    try
    {
        this->m_database->open();
        m_communicator.startHandleRequests();
    }
    catch (std::exception& e)
    {
        std::cout << "Error occurred: " << e.what() << std::endl;
    }

    this->m_database->close();
    system("PAUSE");
    return;
}