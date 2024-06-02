#pragma once
#include "Question.h"
#include "LoggedUser.h"
#include "map"

using std::string;

struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int avgAnswerTime;
};

class Game
{
public:
	Game(int id, std::vector<Question> questions);
	/**
	* function to submit the answer of the user
	*/
	void submitAnswer();
	/**
	* funciton to remove the player from the vector of player in the game
	*/
	void removePlayer(const LoggedUser& user);

	/**
	* function to get the questions for the user 
	*/
	void getQuestionForUser(const LoggedUser& user);

private:
	int _gameId;
	std::map<LoggedUser, GameData> m_players;
	std::vector<Question> m_questions;
};


