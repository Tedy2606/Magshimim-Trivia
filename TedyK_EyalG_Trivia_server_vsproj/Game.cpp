#include "Game.h"

Game::Game(int id, std::vector<Question> questions, std::map<LoggedUser, GameData> players) :
	m_questions(questions), m_players(players)
{
	this->m_gameID = id;
}

int Game::submitAnswer(const LoggedUser& user, const int& answerId)
{
    //figure out wtf do we do with avg time 
    int isCorrect = INCORRECT;

    if (this->m_players[user].currentQuestion.getCorrectAnswerId() == answerId)
    {
        this->m_players[user].correctAnswerCount++;
        isCorrect = CORRECT;
    }
    else
    {
        this->m_players[user].wrongAnswerCount++;
    }

    //find what question he is on right now, give him the next one 
    //does not work for some reason 
    auto it = std::find(this->m_questions.begin(), this->m_questions.end(), this->m_players[user].currentQuestion);
    if (it != this->m_questions.end() - 1 || it != this->m_questions.end())
    {
        this->m_players[user].currentQuestion = *(it++);
    }

    return isCorrect;
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


