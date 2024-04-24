#pragma once
#include "SqliteDatabase.h"
#include <vector>

class StatisticsManager
{
public:
	/*
	A method to return the high scores in the database
	@return 5 highest scores from the database
	*/
	std::vector<std::string> getHighScore();

	/*
	The method returns the input username's statistics
	@param username - the username to get its statistics
	@return a vector with the username's statistics
	*/
	std::vector<std::string> getUserStatistics(std::string username);

private:
	IDataBase* m_database;
};
