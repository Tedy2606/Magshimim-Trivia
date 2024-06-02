#include "Game.h"

Game::Game(int id, std::vector<Question> questions)
{
	this->_gameId = id;
	this->m_questions = questions;
}

void Game::submitAnswer()
{
	
}

void Game::removePlayer(const LoggedUser& user)
{
	//remove a player from the player from the map 
}

void Game::getQuestionForUser(const LoggedUser& user)
{
	//find what question he is on right now, give him the next one 
	auto it = std::find(this->m_questions.begin(), this->m_questions.end(), this->m_players[user].currentQuestion);
	if ( it != this->m_questions.end())
	{
		this->m_players[user].currentQuestion = *(it++);
	}
	else
	{

		//throw exception that question wasnt found or smth 
	}

}
