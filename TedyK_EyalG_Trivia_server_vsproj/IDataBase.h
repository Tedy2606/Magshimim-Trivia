#pragma once
#include <string>
#include <list>
#include "Question.h"

class IDataBase
{
public:
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual bool doesUserExist(std::string username) = 0;
	virtual bool doesPasswordMatch(std::string username, std::string password) = 0;
	virtual bool addNewUser(std::string username, std::string password, std::string email) = 0;
	virtual std::list<Question> getQuestions(int questionsNum) = 0;
};
