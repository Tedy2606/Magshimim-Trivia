#pragma once
#include <string>
#include <list>
#include "Question.h"

class IDataBase
{
public:
	virtual bool open() = 0;
	virtual bool close() = 0;

	// users table
	virtual bool doesUserExist(std::string username) = 0;
	virtual bool doesPasswordMatch(std::string username, std::string password) = 0;
	virtual bool addNewUser(std::string username, std::string password, std::string email) = 0;

	// questions table
	virtual std::list<Question> getQuestions(int questionsNum) = 0;

	// statistics table
	virtual float getPlayerScore(std::string username) = 0;
	virtual int getNumOfPlayerGames(std::string username) = 0;
	virtual int getNumOfTotalAnswers(std::string username) = 0;
	virtual int getNumOfCorrectAnswers(std::string username) = 0;
	virtual float getPlayerAverageAnswerTime(std::string username) = 0;
	virtual std::vector<std::string> getHighScores() = 0;
};
