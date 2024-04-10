#pragma once
#include <string>
class LoggedUser
{
public:
	std::string GetUserName();

private:
	std::string m_userName;
};
