#include "LoginManager.h"

void LoginManager::signup(string name, string password, string mail)
{

	if (this->m_database->doesUserExists(name))
	{
		this->m_database->addNewUser(name, password, mail);
	}
}

void LoginManager::login(string name, string password)
{
	if (this->m_database->doesUserExists(name) && this->m_database->doesPasswordMatch(name, password))
	{
		LoggedUser user;
		//inser value into logged user


		// add the user to the logged ones 
		this->m_loggedUsers.push_back(user);
	}
}

void LoginManager::logout(string name)
{
}
