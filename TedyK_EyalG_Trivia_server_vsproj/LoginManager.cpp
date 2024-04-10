#include "LoginManager.h"

void LoginManager::signup(string name, string password, string mail)
{

	if (this->m_database->doesUserExist(name))
	{
		this->m_database->addNewUser(name, password, mail);
	}
}

void LoginManager::login(string name, string password)
{
	if (this->m_database->doesUserExist(name) && this->m_database->doesPasswordMatch(name, password))
	{
		LoggedUser user;
		//inser value into logged user


		// add the user to the logged ones 
		this->m_loggedUsers.push_back(user);
	}
}

void LoginManager::logout(string name)
{
	if (this->m_database->doesUserExist(name))
	{
		//do an error or something
		return;
	}

	//finds the position of the user in the vector 
	int count = 0;
	for (; count < this->m_loggedUsers.size(); count++)
	{
		if (this->m_loggedUsers[count].GetUserName() == name)
			break;

	}
	//removes from the vector
	this->m_loggedUsers.erase(this->m_loggedUsers.begin() + count);
}
