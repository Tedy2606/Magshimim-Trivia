#pragma once
#include <string>
class LoggedUser
{
public:
	LoggedUser(std::string name);
	//getter for the user name
	std::string GetUserName() const;

private:
	std::string m_userName;
};
