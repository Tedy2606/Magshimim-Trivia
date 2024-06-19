#include "Server.hpp"

Server* Server::m_instance = nullptr;

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

    if (m_instance == nullptr) {
        m_instance = new Server();
    }
    return *m_instance;
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
