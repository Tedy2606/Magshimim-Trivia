#include "Game.h"

Game::Game(int id, std::vector<Question> questions, std::map<LoggedUser, GameData> players)
{
	this->m_gameID = id;
	this->m_questions = questions;
	this->m_players = players;
}

void Game::submitAnswer(const LoggedUser& user, const int& answerId)
{
	//figure out wtf do we do with avg time 

	if (this->m_players[user].currentQuestion.getCorrectAnswerId() == answerId)
	{
		this->m_players[user].correctAnswerCount++;
	}
	else
	{
		this->m_players[user].wrongAnswerCount++;
	}
	getQuestionForUser(user);
}

void Game::removePlayer(const LoggedUser& user)
{
	this->m_players.erase(user);
}

void Game::getQuestionForUser(const LoggedUser& user)
{
	//find what question he is on right now, give him the next one 
	auto it = std::find(this->m_questions.begin(), this->m_questions.end(), this->m_players[user].currentQuestion);
	if ( it != this->m_questions.end() - 1 || it != this->m_questions.end())
	{
		this->m_players[user].currentQuestion = *(it++);
	}
	else
	{

		//throw exception that question wasnt found or he was on the last question 
	}

}

int Game::getGameID() const
{
	return this->m_gameID;
}

std::map<LoggedUser, GameData> Game::getUsers()
{
	return this->m_players;
}


