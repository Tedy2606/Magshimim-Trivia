#include "Game.h"

Game::Game(int id, std::vector<Question> questions)
{
	this->_gameId = id;
	this->m_questions = questions;
}

void Game::submitAnswer()
{
	//idk what to really add here
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
