#include "Game.h"

void Game::submitAnswer()
{
	
}

void Game::removePlayer()
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
