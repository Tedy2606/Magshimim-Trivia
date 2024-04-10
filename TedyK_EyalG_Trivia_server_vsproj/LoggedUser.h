#pragma once
#include <string>
class LoggedUser
{
public:
	//getter for the user name
	std::string GetUserName();

private:
	std::string m_userName;
};
