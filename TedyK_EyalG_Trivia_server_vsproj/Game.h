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

	/**
	* function to submit the answer of the user
	*/
	const void submitAnswer();
	/**
	* funciton to remove the player from the vector of player in the game
	*/
	const void removePlayer();

	/**
	* function to get the questions for the user 
	* 
	*/
	const void getQuestionForUser();

private:
	int gameId;
	std::map<LoggedUser, GameData> m_players;
	std::vector<Question> m_questions;
};


