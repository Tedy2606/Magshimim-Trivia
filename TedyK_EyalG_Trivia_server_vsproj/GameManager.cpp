#include "GameManager.h"

GameManager::GameManager(IDataBase* database)
{
	this->m_database = database;
}

void GameManager::createGame(Room room)
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
		data.totalAnswerTime = 0;
		data.correctAnswerCount = 0;
		data.wrongAnswerCount = 0;
		data.currentQuestion = questionsVec[0];
		userData[user] = data;
	}

	Game game(id, questionsVec, userData);
	this->m_games.push_back(game);
}

void GameManager::deleteGame(const int& id)
{
	int i = 0;
	for (auto& it : this->m_games)
	{
		if (it.getGameID() == id)
		{
			this->submitGameStatisticsToDB(it);

			this->m_games.erase(this->m_games.begin() + i);
		}
		i++;
	}
}

Game& GameManager::getRoom(const int& id)
{
	for (auto& it : this->m_games)
	{
		if (it.getGameID() == id)
		{
			return it;
		}
	}
}

void GameManager::submitGameStatisticsToDB(Game game)
{
	auto& users = game.getUsers();
	for (auto& it : users)
	{
		//submit the statistics with the db
		this->m_database->insertStatistics(it.first.GetUserName(),		// username
			it.second.correctAnswerCount,								// correct answers
			it.second.wrongAnswerCount + it.second.correctAnswerCount,	// total answers
			it.second.totalAnswerTime,									// total time
			Game::calculateScore(it.second));							// score
	}
}
