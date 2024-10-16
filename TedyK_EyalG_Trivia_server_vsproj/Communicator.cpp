#include "Communicator.h"

Communicator* Communicator::m_instance = nullptr; // Definition of the static member variable
Communicator::Communicator(RequestHandlerFactory& handlerFactory)
	: m_handlerFactory(handlerFactory)
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
		std::string command = "";

		std::cout << ">>> ";

		std::cin >> command;

		if (command == "EXIT")
		{
			exit(0);
		}

	}

}

Communicator& Communicator::getInstance(RequestHandlerFactory& handlerFactory)
{
	
	static std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);
	
	if (m_instance == nullptr) {
		m_instance = new Communicator(handlerFactory);
	}
	return *m_instance;
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
	// set starting handler to login handler
	this->m_clients[clientSocket] = new LoginRequestHandler(this->m_handlerFactory);

	try
	{
		while (true)
		{
			//needs to be const unsinged char...
			const char* client_response_header = getPartFromSocket(clientSocket, HEADER_SIZE, 0);
			int data_len = ((unsigned char)client_response_header[1] << 24) | ((unsigned char)client_response_header[2] << 16) | ((unsigned char)client_response_header[3] << 8) | (unsigned char)client_response_header[4];
			const char* client_response_data = getPartFromSocket(clientSocket, data_len, 0);
			
			std::string client_response(client_response_header, HEADER_SIZE);
			client_response.append(client_response_data, data_len);
			//puts the client response int a vector
			Buffer buf(client_response.begin(), client_response.end());
			
			//make the info of the request 
			RequestInfo info;
			info.id = buf[0];
			info.buffer = buf;
			info.recival_time = time(nullptr);
			
			// handle the response
			Buffer response = this->requestHandler(clientSocket, info);

			//convert the vector to an str to send it
			std::string responseStr(response.begin(), response.end());
			
			sendData(clientSocket, responseStr);

			// free allocated data
			delete client_response_header;
			delete client_response_data;
		}
		
	}
	catch (const std::exception& e)
	{
		RequestInfo info;

		std::cerr << e.what() << std::endl;

		info.id = LEAVE_GAME_REQ;
		this->requestHandler(clientSocket, info);

		info.id = LEAVE_ROOM_REQ;
		this->requestHandler(clientSocket, info);

		info.id = CLOSE_ROOM_REQ;
		this->requestHandler(clientSocket, info);

		info.id = LOGOUT_MSG_REQ;
		this->requestHandler(clientSocket, info);

		closesocket(clientSocket);
	}

	std::cout << "Connection with a client has been closed." << std::endl;

	// delete login handler
	delete this->m_clients[clientSocket];
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

Buffer Communicator::requestHandler(SOCKET clientSocket, RequestInfo info)
{
	JsonResponsePacketSerializer seri;

	Buffer response;

	if (this->m_clients[clientSocket]->isRequestRelevant(info))
	{
		//handle requests 
		RequestResult res = this->m_clients[clientSocket]->handleRequest(info);
		response = res.buffer;

		// switch to new handle
		delete this->m_clients[clientSocket];
		this->m_clients[clientSocket] = res.newHandler;
	}
	else
	{
		//handle erros 
		ErrorResponse err;
		err.err = "ERROR";
		response = seri.serializeResponse(err);
	}

	return response;
}

void Communicator::sendData(SOCKET sc, std::string message)
{
	const char* data = message.c_str();

	if (send(sc, data, message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}
