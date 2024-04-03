#pragma once
#include "LoginRequestHandler.h"
#include <WinSock2.h>
#include <Windows.h>
#include <queue>
#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <map>
#include "IRequestHandler.h"
class Communicator
{
public:
	Communicator();
	~Communicator();
	void startHandleRequests();

private:
	//this function is for easier readabilty of the code
	//bind and listen can be merged into it  
	void clientAccepter();



	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);
	

	char *getPartFromSocket(SOCKET sc, int bytesNum, int flags);
	void sendData(SOCKET sc, std::string message);

	std::map<SOCKET, IRequestHandler*> m_clients;
	SOCKET m_serverSocket;
};

