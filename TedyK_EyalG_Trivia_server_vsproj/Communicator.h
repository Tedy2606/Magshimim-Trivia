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

extern int usersDone;
class Communicator
{
public:
	
	~Communicator();

	/***
	* starts handeling request from clients
	* @return none
	**/
	void startHandleRequests();


	/*
	funciton returns the only instance of the Communicator, if there isnt one then it makes one
	@return a pointer to the instance of the Communicator
	*/
	static Communicator& getInstance(RequestHandlerFactory& handlerFactory);
	Communicator(const Communicator& obj) //delete anything that tries to be copied
		= delete;




private:
	Communicator(RequestHandlerFactory& handlerFactory);


	//this function is for easier readabilty of the code
	//bind and listen can be merged into it  
	void clientAccepter();


	/***
	* accepts a client and runs a thread of handeling  
	* @return none
	**/
	void bindAndListen();


	/***
	* handels a new client - add to list, handles login, etc
	* @param SOCKET client socket - the socket that the client is connected to 
	* @return none 
	**/
	void handleNewClient(SOCKET clientSocket);
	
	/***
	* gets the client packet from the socket
	* @param SOCKET sc - the socket that the client is connected to
	* @param int bytesnum - the numbert of bytes to get from the packet 
	* @param flags - coniditions on how t get the packet (not used)
	* @return char* - the data in bytes 
	**/
	char *getPartFromSocket(SOCKET sc, int bytesNum, int flags);

	/*
	Method to handle a request
	@param clientSocket - the socket of the request
	@param info - the info of the request
	@return a buffer which contains the response of the request
	*/
	Buffer requestHandler(SOCKET clientSocket, RequestInfo info);

	/***
	* sends a packet to the client 
	* @param SOCKET sc - the socket that the client is connected to
	* @param str message - the packet  in an array of bytes 
	* @return none 
	**/
	void sendData(SOCKET sc, std::string message);
	static Communicator* m_instance;
	std::map<SOCKET, IRequestHandler*> m_clients;
	SOCKET m_serverSocket;
	RequestHandlerFactory& m_handlerFactory;
};

