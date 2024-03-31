#pragma once

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


	//std::map<SOCKET, IRequestHandler*>;
	SOCKET m_serverSocket;
};

