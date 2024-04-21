#include "Room.h"

Room::Room(RoomData data)
{
	this->m_metadata = data;
	m_users = std::vector<LoggedUser>();
}

RoomData Room::getData() const
{
	return this->m_metadata;
}

void Room::addUser(LoggedUser user)
{
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
