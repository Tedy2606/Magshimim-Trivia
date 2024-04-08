#pragma once
#include <vector>
#include <ctime>

//declare the class in order to be able to ahve a struct with a pointer to it 
class IRequestHandler;
//the info of the request 
struct RequestInfo
{
	 int id;
	 time_t recival_time;
	 std::vector<unsigned char> buffer;
};
// the result of the request 
struct RequestResult
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler;
};


class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual RequestResult handleRequest(RequestInfo info) = 0;

};
