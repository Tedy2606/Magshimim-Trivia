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
	IRequestHandler() = default;
	virtual ~IRequestHandler() { };
	
	virtual bool isRequestRelevant(const RequestInfo& info) const = 0 ;
	virtual RequestResult handleRequest(const RequestInfo& info) = 0;

};
