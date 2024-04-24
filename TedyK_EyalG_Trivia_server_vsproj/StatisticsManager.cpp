#include "StatisticsManager.h"

std::vector<std::string> StatisticsManager::getHighScore()
{
    return this->m_database.getHighScores();
}

std::vector<std::string> StatisticsManager::getUserStatistics(std::string username)
{
    return std::vector<std::string>();
}
