#include "Room.h"
#include <stdexcept>
Room::Room(RoomData data)
{
	this->m_metadata = data;
	this->m_users = std::vector<LoggedUser>();
}

RoomData& Room::getData()
{
	return this->m_metadata;
}

void Room::addUser(LoggedUser user)
{
	if (this->m_metadata.maxPlayers == this->m_users.size())
	{
		throw std::runtime_error("error in add user, max user limit reached");
	}
	this->m_users.push_back(user);
}

void Room::removeUser(LoggedUser user)
{
	//go over all of the rooms andd erase the given one 
	
	for (auto it = this->m_users.begin(); it != this->m_users.end(); it++)
	{
		if (it->GetUserName() == user.GetUserName()) {
			this->m_users.erase(it);
			break;
		}
	}
	
}

std::vector<string> Room::getAllUsers()
{
	std::vector<string> names;
	//go over all of the users 
	for (auto it : this->m_users)
	{
		names.push_back(it.GetUserName());
	}

	return names;
}
