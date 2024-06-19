#pragma once
#include "sqlite3.h"
#include "IDataBase.h"
#include <iostream>
#include <set>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <io.h> // For _access function

#define DATABASE_PATH "database.sqlite"

class SqliteDatabase : public IDataBase {
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
    virtual bool doesUserExist(const std::string& username) override;

    /*
    Method returns whether the input username has the input password.
    @param username - the username
    @param password - the password to check
    @return whether or not the password matches to the username
    */
    virtual bool doesPasswordMatch(const std::string& username, const std::string& password) override;

    /*
    Method adds a new user to the users table in the database.
    @param username - the username of the user
    @param password - the password of the user
    @param email - the email of the user
    @return whether the user has been added to the users table in the database
    */
    virtual bool addNewUser(const std::string& username, const std::string& password, const std::string& email) override;

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
    virtual float getPlayerScore(const std::string& username) override;

    /*
    Method returns the number of games played by the input user
    @param username - the username of the user
    @return the number of games the user played
    */
    virtual int getNumOfPlayerGames(const std::string& username) override;

    /*
    Method returns the number of answers the input user has answered
    @param username - the username of the user
    @return the number of answers the user has answered
    */
    virtual int getNumOfTotalAnswers(const std::string& username) override;

    /*
    Method return the number of correct answers the input user has answered
    @param username - the username of the user
    @return the number of correct answers the user has answered
    */
    virtual int getNumOfCorrectAnswers(const std::string& username) override;

    /*
    Method calculates and returns the average answer time for a question of the input user
    @param username - the username of the user
    @return the average answer time of a question of the user
    */
    virtual float getPlayerAverageAnswerTime(const std::string& username) override;

    /*
    Method returns the top 5 highest scores in the statistics table
    @return a vector with the top 5 highest scores
    */
    virtual std::vector<std::string> getHighScores() override;

    /*
    Method updates the statistics of the input username
    @param username - the user to update
    @param correctAnswers - number of correct answers to add
    @param totalAnswers - number of total answers to add
    @param totalAnswerTime - number of total answer time to add
    @param score - amout of score to add
    */
    virtual void insertStatistics(const std::string& username, const int& correctAnswers, const int& totalAnswers, const int& totalAnswerTime, const float& score) override;

    /*
    Method inserts new question to the database
    @param question - the question
    @param correctAnswer - the correct answer
    @param answer1, answer2, answer3 - the wrong answers
    */
    virtual void insertQuestion(const std::string& question, const std::string& correctAnswer, const std::string& answer1, const std::string& answer2, const std::string& answer3) override;

private:
    sqlite3* _db;
};
