#pragma once
#include "Room.h"
#include <map>

using std::string;

class RoomManager
{
public:

	/***
	* function creates a room
	* @param RoomData - the data of the room
	* @param LoggedUser - the user that makes the room
	* @return none
	**/
	void createRoom(LoggedUser user, RoomData data);


	/***
	* function deletes a room
	* @param int ID - the id of the wanted room 
	* @return none
	**/
	void deleteRoom(int id);

	/***
	* function return the state that the room is in 
	* @param int ID - the id of the wanted room 
	* @return int - the state
	**/
	unsigned int getRoomState(int id);

	/***
	* function returns all rooms
	* @return vector full of all of the rooms data
	**/
	std::vector<RoomData> getRooms();

	/***
	* function returns a room based on its id
	* @param int ID - the id of the room
	* @return Room - the requested room 
	**/
	Room& getRoom(int id);

private:
	std::map<int, Room> m_rooms;
};
