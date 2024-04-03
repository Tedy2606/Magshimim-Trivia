#include "Communicator.h"
#include <exception>
#include <iostream>
#include <string>
#include <thread>
#include "IRequestHandler.h"
#define MAX_MSG_LEN 1024
#define NAME_LEN_IN_BYTES 2
#define PORT 56812
using std::cout;
using std::endl;


Communicator::Communicator()
{

	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	m_serverSocket = socket(AF_INET,  SOCK_STREAM,  IPPROTO_TCP); 

	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(m_serverSocket);
	}
	catch (...) {}
}

//this is the main thread (probably)
void Communicator::startHandleRequests()
{
	//makes a thread for each client then detaches it
	std::thread client_thread(&Communicator::clientAccepter, this);
	client_thread.detach();
	//beacuse we detach the threads we want to makesure that the program dosnt stop running
	while (true)
	{
	}

}


void Communicator::clientAccepter()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << PORT << std::endl;

	while (true)
	{

		std::cout << "Waiting for client connection request" << std::endl;
		bindAndListen();

	}
}

void Communicator::bindAndListen()
{

	// this accepts the client and create a specific socket from server to this client
	// the process will not continue until a client connects to the server
	SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Server and client can speak" << std::endl;
	// the function that handle the conversation with the client

	//make a thread here
	std::thread clientHandle(&Communicator::handleNewClient, this, client_socket);
	clientHandle.detach();
}


void Communicator::handleNewClient(SOCKET clientSocket)
{
	LoginRequestHandler loginReq;
	this->m_clients[clientSocket] = &loginReq;
	try
	{
		std::string second_user_name = "";
		std::string file_content = "";

		std::string client_response = getPartFromSocket(clientSocket, MAX_MSG_LEN, 0);
		
		
		std::cout << client_response << std::endl;
	}
	catch (const std::exception& e)
	{
		closesocket(clientSocket);
	}


}

char* Communicator::getPartFromSocket(SOCKET sc, int bytesNum, int flags)
{
	if (bytesNum == 0)
	{
		return (char*)"";
	}

	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, flags);

	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}

	data[bytesNum] = 0;
	return data;
}
