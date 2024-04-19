#pragma comment (lib, "ws2_32.lib")

#include "Server.hpp"
#include "WSAInitializer.h"
#include "Communicator.h"
#include <iostream>
#include <exception>
#include <thread>
#include "Server.hpp"
#include "SqliteDatabase.h"
#include "RequestHandlerFactory.h"


Server::Server()
	: m_handlerFactory(), m_communicator(this->m_handlerFactory)
{
	this->m_database = new SqliteDatabase();
}

Server::~Server()
{
}

//function for running the server
void Server::run()
{
	try
	{
		this->m_database->open();

		//start handeling the request
		m_communicator.startHandleRequests();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}

	this->m_database->close();
	system("PAUSE");
	return ;
}


