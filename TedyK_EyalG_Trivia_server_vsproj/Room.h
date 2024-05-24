#pragma once
#include <string>
#include "LoggedUser.h"
#include <vector>
using std::string;

struct RoomData
{ 
	int id;
	string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestions;
	unsigned int timePerQuestion;
	unsigned int isActive;
};

class Room
{
public:

	Room() = default;  // Default constructor
	/***
	* constructor for the room
	* @param RoomData data - the data of the room
	* 
	**/
	Room(RoomData data);

	/***
	* getter for the data of the room 
	* @return roomData - the data of the room 
	**/
	RoomData& getData();
	/***
	* function adds a user to the room 
	* @param LoggedUser user - the user to add to the room
	* @return none 
	**/
	void addUser(LoggedUser user);


	/***
	* function removes a user 
	* @param LoggedUser user - the user to remove from the room
	* @return none 
	**/
	void removeUser(LoggedUser user);


	/***
	* function returns all of the users
	* @return ia vector with all of the usernames
	**/
	std::vector<string> getAllUsers();



private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};

