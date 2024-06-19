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
	*/
	void createGame(Room room);

	/**
	* deletes a game 
	*/
	void deleteGame(const int& id);

	/**
	* function to return a game based on its id 
	* @return Game - the wanted game 
	*/
	Game& getRoom(const int& id);

private:
	//changed from game data to game cus submitiing only the statistics of one user is stupid
	void submitGameStatisticsToDB(Game game);

	IDataBase* m_database;
	std::vector<Game> m_games;
};
