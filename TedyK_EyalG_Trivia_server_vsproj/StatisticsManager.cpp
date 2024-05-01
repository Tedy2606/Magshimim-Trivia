#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDataBase* database)
{
    this->m_database = database;
}

std::vector<std::string> StatisticsManager::getHighScore()
{
    return this->m_database->getHighScores();
}

std::vector<std::string> StatisticsManager::getUserStatistics(std::string username)
{
    std::vector<std::string> userStatistics;

    // push all the statistics to the vector
    userStatistics.push_back(std::to_string(this->m_database->getPlayerScore(username)));
    userStatistics.push_back(std::to_string(this->m_database->getNumOfPlayerGames(username)));
    userStatistics.push_back(std::to_string(this->m_database->getNumOfTotalAnswers(username)));
    userStatistics.push_back(std::to_string(this->m_database->getNumOfCorrectAnswers(username)));
    userStatistics.push_back(std::to_string(this->m_database->getPlayerAverageAnswerTime(username)));

    return userStatistics;
}
