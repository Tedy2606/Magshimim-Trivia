#include "LoginManager.h"

bool LoginManager::signup(string name, string password, string mail)
{

	if (!this->m_database->doesUserExist(name))
	{
		this->m_database->addNewUser(name, password, mail);

		return true;
	}

	return false;
}

bool LoginManager::login(string name, string password)
{
	if (this->m_database->doesPasswordMatch(name, password))
	{
		LoggedUser user(name);
		// add the user to the logged ones 
		this->m_loggedUsers.push_back(user);

		return true;
	}

	return false;
}

bool LoginManager::logout(string name)
{
	

	//finds the position of the user in the vector 
	int count = 0;
	for (; count < this->m_loggedUsers.size(); count++)
	{
		if (this->m_loggedUsers[count].GetUserName() == name)
			break;

	}
	// remove user from vector only if he exists in the vector
	if (count != this->m_loggedUsers.size())
	{
		//removes from the vector
		this->m_loggedUsers.erase(this->m_loggedUsers.begin() + count);

		return true;
	}
	return false;
}
