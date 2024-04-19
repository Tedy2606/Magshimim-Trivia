#pragma once
#include <string>
#include "SqliteDatabase.h"
#include "LoggedUser.h"
#include <vector>
using std::string;
class LoginManager
{
public:
	/***
	* signs a user up (adds him to the database)
	* @param string name - the name of the user
	* @param string password - the password of the user
	* @param string mail - the mail of the user
	* @return whether the function succeeded
	**/
	bool signup(string name, string password, string mail);
	/***
	* logs a user in (adds him to the logged user vector)
	* @param string name - the name of the user
	* @param string password - the password of the user
	* @return whether the function succeeded
	**/
	bool login(string name, string password);
	/***
	* logs a user out (removes him from the logged user vector)
	* @param string name - the name of the user
	* @return whether the function succeeded
	**/
	bool logout(string name);

private:
	std::vector<LoggedUser> m_loggedUsers;
	IDataBase* m_database;
};
