#pragma once
#include <string>
class LoggedUser
{
public:
	LoggedUser(std::string name);
	//getter for the user name
	std::string GetUserName() const;
	bool operator<(const LoggedUser& other) const {
		return this->m_userName < other.m_userName;
	}

private:
	std::string m_userName;
};
