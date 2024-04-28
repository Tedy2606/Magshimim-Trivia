#pragma once
#include "sqlite3.h"
#include "IDataBase.h"
#include <iostream>
#include <io.h>
#include <set>

#define DATABASE_PATH "database.sqlite"

class SqliteDatabase : public IDataBase
{
public:
	/*
	Method opens the database.
	@return whether or not the method succeeded.
	*/
	virtual bool open() override;

	/*
	Method closes the database.
	@return whether or not the method succeeded.
	*/
	virtual bool close() override;

	/*
	Method returns whether a user with the given username exists.
	@param username - the username to search
	@return whether or not the user exists
	*/
	virtual bool doesUserExist(std::string username) override;

	/*
	Method returns whether the input username has the input password.
	@param username - the username
	@param password - the password to check
	@return whether or not the password matches to the username
	*/
	virtual bool doesPasswordMatch(std::string username, std::string password) override;

	/*
	Method adds a new user to the users table in the database.
	@param username - the username of the user
	@param password - the password of the user
	@param email - the email of the user
	@return whether the user has been added to the users table in the database
	*/
	virtual bool addNewUser(std::string username, std::string password, std::string email) override;

	/*
	Method to get a list of questions from the database
	@param questionsNum - number of records to select from the database
	@return A list of questions
	*/
	virtual std::list<Question> getQuestions(int questionsNum) override;

	/*
	Method returns the input user's score
	@param username - the username of the user
	@return the score of the user
	*/
	virtual float getPlayerScore(std::string username) override;

	/*
	Method returns the number of games played by the input user
	@param username - the username of the user
	@return the number of games the user played
	*/
	virtual int getNumOfPlayerGames(std::string username) override;

	/*
	Method returns the number of answers the input user has answered
	@param username - the username of the user
	@return the number of answers the user has answered
	*/
	virtual int getNumOfTotalAnswers(std::string username) override;

	/*
	Method return the number of correct answers the input user has answered
	@param username - the username of the user
	@return the number of coorect answers the user has answered
	*/
	virtual int getNumOfCorrectAnswers(std::string username) override;

	/*
	Method calculates and returns the average answer time for a quetion of the input user
	@param username - the username of the user
	@return the average answer time of a queation of the user
	*/
	virtual float getPlayerAverageAnswerTime(std::string username) override;

private:
	sqlite3* _db;
};
