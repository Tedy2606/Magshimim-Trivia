#pragma comment (lib, "ws2_32.lib")

#include "Server.hpp"
#include "WSAInitializer.h"
#include "Communicator.h"
#include <iostream>
#include <exception>
#include <thread>
#include "Server.hpp"



//function for running the server
void Server::run()
{
	try
	{
		//start handeling the request
		m_communicator.startHandleRequests();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}

	system("PAUSE");
	return ;
}


