#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <queue>
#include <set>
#include <string>
#include "Communicator.h"
#include <map>



class Server
{
public:
	void run();

private:
	Communicator m_communicator;
};

