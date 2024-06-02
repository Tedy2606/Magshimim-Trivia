#pragma once
#include "Game.h"
#include "IDataBase.h"
#include "RoomManager.h"
using std::string;
class GameManager
{
public:
	/**
	* constructor for the class
	*/
	GameManager(IDataBase* database);

	/**
	* creates a game
	* @return Game - the game created
	*/
	Game createGame(Room room);

	/**
	* deletes a game 
	*/
	void deleteGame(const int& id);
	/**
	* function to return a game based on its id 
	* @return Game - the wanted game 
	*/
	Game getRoom(const int& id);

private:
	void submitGameStatisticsToDB(GameData game);
	IDataBase* m_database;
	std::vector<Game> m_games;
};

