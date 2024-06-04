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

	//find what question he is on right now, give him the next one 
	auto it = std::find(this->m_questions.begin(), this->m_questions.end(), this->m_players[user].currentQuestion);
	if (it != this->m_questions.end() - 1 || it != this->m_questions.end())
	{
		this->m_players[user].currentQuestion = *(it++);
	}
}

void Game::removePlayer(const LoggedUser& user)
{
	this->m_players.erase(user);
}

Question Game::getQuestionForUser(const LoggedUser& user)
{
	return this->m_players[user].currentQuestion;
}

int Game::getGameID() const
{
	return this->m_gameID;
}

std::map<LoggedUser, GameData> Game::getUsers()
{
	return this->m_players;
}


