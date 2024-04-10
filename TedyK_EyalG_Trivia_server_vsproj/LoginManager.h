#pragma once
#include <string>
#include "SqliteDatabase.h"
#include "LoggedUser.h"
#include <vector>
using std::string;
class LoginManager
{
public:
	void signup(string name, string password, string mail);
	void login(string name, string password);
	void logout(string name);

private:
	std::vector<LoggedUser> m_loggedUsers;
	IDatabase* m_database;
};
