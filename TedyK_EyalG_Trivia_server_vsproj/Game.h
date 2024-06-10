#pragma once
#include "Question.h"
#include "LoggedUser.h"
#include "map"

using std::string;

#define CORRECT 1
#define INCORRECT 0

struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int totalAnswerTime;
};

class Game
{
public:
	Game(int id, std::vector<Question> questions, std::map<LoggedUser, GameData> players);
	/**
	* function to submit the answer of the user
	*/
	int submitAnswer(const LoggedUser& user, const int& answerId);
	/**
	* funciton to remove the player from the vector of player in the game
	*/
	void removePlayer(const LoggedUser& user);

	/**
	* function to get the questions for the user 
	*/
	Question getQuestionForUser(const LoggedUser& user);

	/*
	getter of m_gameID field
	*/
	int getGameID() const;

	// getter for m_players
	std::map<LoggedUser, GameData>& getUsers();

	// getter for m_questions
	std::vector<Question>& getQuestions();

	/*
	Calculates the score of the user
	@param data - the data of the game
	@return the score of the game
	*/
	static float calculateScore(GameData data);

private:
	int m_gameID;
	std::map<LoggedUser, GameData> m_players;
	std::vector<Question> m_questions;
};


