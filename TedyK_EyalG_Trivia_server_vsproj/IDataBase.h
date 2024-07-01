#pragma once
#include <string>
#include <list>
#include "Question.h"

class IDataBase {
public:
    virtual bool open() = 0;
    virtual bool close() = 0;

    // users table
    virtual bool doesUserExist(const std::string& username) = 0;
    virtual bool doesPasswordMatch(const std::string& username, const std::string& password) = 0;
    virtual bool addNewUser(const std::string& username, const std::string& password, const std::string& email) = 0;

    // questions table
    virtual std::list<Question> getQuestions(int questionsNum) = 0;

    // statistics table
    virtual float getPlayerScore(const std::string& username) = 0;
    virtual int getNumOfPlayerGames(const std::string& username) = 0;
    virtual int getNumOfTotalAnswers(const std::string& username) = 0;
    virtual int getNumOfCorrectAnswers(const std::string& username) = 0;
    virtual float getPlayerAverageAnswerTime(const std::string& username) = 0;
    virtual std::vector<std::string> getHighScores() = 0;
    virtual void insertStatistics(const std::string& username, const int& correctAnswers, const int& totalAnswers, const int& totalAnswerTime, const float& score) = 0;
    virtual void insertQuestion(const std::string& question, const std::string& correctAnswer, const std::string& answer1, const std::string& answer2, const std::string& answer3) = 0;
};
