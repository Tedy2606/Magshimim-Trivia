#pragma once
#include "Game.h"
#include "IDataBase.h"
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
	Game createGame();

	/**
	* deletes a game 
	*/
	void deleteGame();

private:
	void submitGameStatisticsToDB(GameData game);
	IDataBase* m_database;
	std::vector<Game> m_games;
};

