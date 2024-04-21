#include "RoomManager.h"
#include "Room.h"
void RoomManager::createRoom(LoggedUser user, RoomData data)
{
	Room room(data);
	room.addUser(user);
	//add the room to the map 
	this->m_rooms.emplace(room.getData().id, room);
}

void RoomManager::deleteRoom(int ID)
{
	//erase in map removes by keyval
	this->m_rooms.erase(ID);
}

unsigned int RoomManager::getRoomState(int ID)
{
	//what is a state in terms of code? is the isActive field in data?
	return this->m_rooms[ID].getData().isActive;
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

Room& RoomManager::getRoom(int ID)
{
	return this->m_rooms[ID];
}