#include "GameManager.h"

GameManager::GameManager(IDataBase* database)
{
	this->m_database = database;
}

Game GameManager::createGame(Room room)
{
	
	
	int id = this->m_games.size() + 1;
	std::list<Question> questions = this->m_database->getQuestions(room.getData().numOfQuestions);
	std::vector<Question> questionsVec(questions.begin(), questions.end());
	Game game = Game(id, questionsVec);
	this->m_games.push_back(game);
	return game;

}

void GameManager::deleteGame(const int& id)
{
	this->m_games.erase(this->m_games.begin() + id);

}

Game GameManager::getRoom(const int& id)
{
	return this->m_games[id];
}

void GameManager::submitGameStatisticsToDB(GameData game)
{
	//submit the statistics with the db
}
