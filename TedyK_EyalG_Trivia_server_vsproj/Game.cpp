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
    int index = -1;
    for (size_t i = 0; i < this->m_questions.size(); ++i) {
        if (this->m_questions[i] == this->m_players[user].currentQuestion) {
            index = i;
            break;
        }
    }

    // Check if the index is valid and update the current question
    if (index != -1 && index < this->m_questions.size() - 1) {
        this->m_players[user].currentQuestion = this->m_questions[index + 1];
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

std::map<LoggedUser, GameData>& Game::getUsers()
{
	return this->m_players;
}

std::vector<Question>& Game::getQuestions()
{
    return this->m_questions;
}

float Game::calculateScore(GameData data)
{
    int averageAnswerTime = data.totalAnswerTime ? (data.correctAnswerCount + data.wrongAnswerCount) / data.totalAnswerTime : 0;

    return averageAnswerTime ? data.correctAnswerCount / averageAnswerTime : 0;
}
