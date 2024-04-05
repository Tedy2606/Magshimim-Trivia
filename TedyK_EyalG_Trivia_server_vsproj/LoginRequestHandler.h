#pragma once
#include "IRequestHandler.h"
class LoginRequestHandler : public IRequestHandler
{
public: 
	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);
};
