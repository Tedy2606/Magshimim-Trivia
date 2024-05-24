#include "LoginManager.h"

LoginManager::LoginManager(IDataBase* database)
{
	this->m_database = database;
}

void LoginManager::signup(string name, string password, string mail)
{

	if (!this->m_database->doesUserExist(name))
	{
		this->m_database->addNewUser(name, password, mail);
		LoggedUser user(name);
		// add the user to the logged ones 
		this->m_loggedUsers.push_back(user);
	}
	else
	{
		throw std::runtime_error("error in signup, user already exists");
	}
}

void LoginManager::login(string name, string password)
{
	if (this->isLogged(name))
	{
		throw std::runtime_error("error in login, user is already logged in");
	}
	else if (this->m_database->doesPasswordMatch(name, password))
	{
		LoggedUser user(name);

		// add the user to the logged ones 
		this->m_loggedUsers.push_back(user);
	}
	else
	{
		throw std::runtime_error("error in login, username or password do not match");
	}
}

void LoginManager::logout(string name)
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
	}
	else
	{
		throw std::runtime_error("error loggin out, user is not logged in");
	}
}

const bool LoginManager::isLogged(const std::string& username) const
{
	LoggedUser user(username);
	for (size_t i = 0; i < this->m_loggedUsers.size(); i++)
	{
		if (username == this->m_loggedUsers[i].GetUserName())
		{
			return true;
		}
	}

	return false;
}
