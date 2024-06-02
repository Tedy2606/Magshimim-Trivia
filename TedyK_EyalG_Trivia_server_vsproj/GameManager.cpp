#include "GameManager.h"

GameManager::GameManager(IDataBase* database)
{
	this->m_database = database;
}

Game GameManager::createGame()
{
	//god knows wtf im supposed to put here
	int id = this->m_games.size() + 1;						// idk what the questions num should be
	std::list<Question> questions = this->m_database->getQuestions(10);
	std::vector<Question> questionsVec(questions.begin(), questions.end());
	Game game = Game();

}

void GameManager::deleteGame()
{
}

void GameManager::submitGameStatisticsToDB(GameData game)
{
	//submit the statistics with the db
}
