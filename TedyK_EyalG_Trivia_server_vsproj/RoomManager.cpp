#include "RoomManager.h"
void RoomManager::createRoom(LoggedUser user, RoomData data)
{
	Room room(data);
	room.addUser(user);
	//add the room to the map 
	this->m_rooms.emplace(room.getData().id, room);
}

void RoomManager::deleteRoom(int id)
{
	//erase in map removes by keyval
	this->m_rooms.erase(id);
}

unsigned int RoomManager::getRoomState(int id)
{
	
	return this->m_rooms[id].getData().isActive;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> data;
	//go over all of the rooms 
	for (auto it : this->m_rooms)
	{
		data.push_back(it.second.getData());
	}
	return data;
}

Room& RoomManager::getRoom(int id)
{
	return this->m_rooms[id];
}