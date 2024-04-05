#pragma once
#include <vector>
#include <ctime>

//declare the class in order to be able to ahve a struct with a pointer to it 
class IRequestHandler;

struct RequestInfo
{
	 int id;
	 // please finish this field
	 // ctime recival_time;
	 std::vector<unsigned char> buffer;
};

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
