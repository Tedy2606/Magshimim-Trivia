#include "Server.hpp"
#include <iostream>
#pragma comment (lib, "ws2_32.lib")
#include "WSAInitializer.h"
int main()
{
	try
	{

		WSAInitializer wsaInit;
		Server server;
		//run the server
		server.run();
	}
	catch (const std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	
	
	return 0;
}