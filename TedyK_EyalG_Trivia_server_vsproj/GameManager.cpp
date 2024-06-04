#include "GameManager.h"

GameManager::GameManager(IDataBase* database)
{
	this->m_database = database;
}

Game GameManager::createGame(Room room)
{
	
	//id is the same as its room id
	int id = room.getData().id;
	//get the questions
	std::list<Question> questions = this->m_database->getQuestions(room.getData().numOfQuestions);
	std::vector<Question> questionsVec(questions.begin(), questions.end());

	//get all users and set their data to 0 to start the game
	std::vector<string> users = room.getAllUsers();
	std::map<LoggedUser, GameData> userData;
	for (auto it : users)
	{
		LoggedUser user = LoggedUser(it);
		GameData data;
		data.avgAnswerTime = 0;
		data.correctAnswerCount = 0;
		data.wrongAnswerCount = 0;
		data.currentQuestion = questionsVec[0];
		userData[user] = data;
	}



	Game game = Game(id, questionsVec, userData);
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

void GameManager::submitGameStatisticsToDB(Game game)
{
	
	auto users = game.getUsers();
	for (auto it : users)
	{
		//submit the statistics with the db, first make the function in the database for it to work

	}

}
