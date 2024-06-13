#include "SqliteDatabase.h"
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <cstdlib>
#include <io.h> // For _access function

bool SqliteDatabase::open()
{
    int file_exist = _access(DATABASE_PATH, 0);
    int res = sqlite3_open(DATABASE_PATH, &this->_db);
    if (res != SQLITE_OK)
    {
        this->_db = nullptr;
        std::cerr << "Failed to open DB" << std::endl;
        exit(-1);
    }

    if (file_exist != 0)
    {
        // create users table
        const char* sqlStatement1 = "CREATE TABLE IF NOT EXISTS users("
            "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            "username TEXT NOT NULL,"
            "password TEXT NOT NULL,"
            "email TEXT NOT NULL);";

        char* errMessage = nullptr;
        res = sqlite3_exec(this->_db, sqlStatement1, nullptr, nullptr, &errMessage);
        if (res != SQLITE_OK)
        {
            std::cerr << "Failed to add table to the new database" << std::endl;
            return false;
        }

        // create questions table
        const char* sqlStatement2 = "CREATE TABLE IF NOT EXISTS questions("
            "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            "question TEXT NOT NULL,"
            "correctAnswer TEXT NOT NULL,"
            "wrongAnswer1 TEXT NOT NULL,"
            "wrongAnswer2 TEXT NOT NULL,"
            "wrongAnswer3 TEXT NOT NULL);";

        errMessage = nullptr;
        res = sqlite3_exec(this->_db, sqlStatement2, nullptr, nullptr, &errMessage);
        if (res != SQLITE_OK)
        {
            std::cerr << "Failed to add table to the new database" << std::endl;
            return false;
        }

        // create statistics table
        const char* sqlStatement3 = "CREATE TABLE IF NOT EXISTS statistics("
            "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            "score REAL NOT NULL,"
            "games INTEGER NOT NULL,"
            "totalAnswers INTEGER NOT NULL,"
            "correctAnswers INTEGER NOT NULL,"
            "totalAnswerTime INTEGER NOT NULL,"
            "userID INTEGER NOT NULL,"
            "FOREIGN KEY(userID) REFERENCES users(id));";

        errMessage = nullptr;
        res = sqlite3_exec(this->_db, sqlStatement3, nullptr, nullptr, &errMessage);
        if (res != SQLITE_OK)
        {
            std::cerr << "Failed to add table to the new database" << std::endl;
            return false;
        }
    }
    return true;
}

bool SqliteDatabase::close()
{
    int res = sqlite3_close(this->_db);
    if (res != SQLITE_OK)
    {
        std::cerr << "An error occurred when trying to close the database." << std::endl;
        return false;
    }

    this->_db = nullptr;
    return true;
}

bool SqliteDatabase::doesUserExist(const std::string& username)
{
    bool doesUserExist = false;
    auto callback = [](void* data, int argc, char** argv, char** azColName)
        {
            *(bool*)data = true; // entered callback function, meaning at least 1 record was found (user exists)
            return 0;
        };

    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, ("SELECT * FROM users WHERE username='" + username + "';").c_str(), callback, &doesUserExist, &errMessage);
    if (res != SQLITE_OK) std::cerr << errMessage << std::endl;

    return doesUserExist;
}

bool SqliteDatabase::doesPasswordMatch(const std::string& username, const std::string& password)
{
    bool doesPasswordMatch = false;
    auto callback = [](void* data, int argc, char** argv, char** azColName)
        {
            *(bool*)data = true; // entered callback function, meaning at least 1 record was found (password matches to the username)
            return 0;
        };

    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, ("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "';").c_str(), callback, &doesPasswordMatch, &errMessage);
    if (res != SQLITE_OK) std::cerr << errMessage << std::endl;

    return doesPasswordMatch;
}

bool SqliteDatabase::addNewUser(const std::string& username, const std::string& password, const std::string& email)
{
    if (this->doesUserExist(username))
    {
        return false; // user with the username already exists
    }

    // insert new user
    std::string sqlQuery = "INSERT INTO users (username, password, email) VALUES ('" + username + "', '" + password + "', '" + email + "');";
    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, sqlQuery.c_str(), nullptr, nullptr, &errMessage);
    if (res != SQLITE_OK)
    {
        std::cerr << errMessage << std::endl;
        return false;
    }

    // insert clean statistics of the user
    sqlQuery = "INSERT INTO statistics (score, games, totalAnswers, correctAnswers, totalAnswerTime, userID) VALUES (0, 0, 0, 0, 0, (SELECT id FROM users WHERE username='" + username + "'));";
    errMessage = nullptr;
    res = sqlite3_exec(this->_db, sqlQuery.c_str(), nullptr, nullptr, &errMessage);
    if (res != SQLITE_OK)
    {
        std::cerr << errMessage << std::endl;
        return false;
    }

    return true;
}

std::list<Question> SqliteDatabase::getQuestions(int questionsNum)
{
    std::list<Question> questions;
    auto callback = [](void* data, int argc, char** argv, char** azColName)
        {
            std::string question;
            std::vector<std::string> possibleAnswers;

            for (int i = 0; i < argc; i++)
            {
                if (std::string(azColName[i]) == "question")
                {
                    question = std::string(argv[i]);
                }
                // count how many times the current column appears (if 1 it is the column, if 0 it is not the column (there are no other options))
                else if (std::set<std::string>{"correctAnswer", "wrongAnswer1", "wrongAnswer2", "wrongAnswer3"}.count(std::string(azColName[i])))
                {
                    possibleAnswers.push_back(std::string(argv[i]));
                }
            }

            ((std::list<Question>*)data)->push_back(Question(question, possibleAnswers));
            return 0;
        };

    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, ("SELECT * FROM questions ORDER BY RANDOM() LIMIT " + std::to_string(questionsNum) + ";").c_str(), callback, &questions, &errMessage);
    if (res != SQLITE_OK) std::cerr << errMessage << std::endl;

    return questions;
}

float SqliteDatabase::getPlayerScore(const std::string& username)
{
    float score = 0;
    auto callback = [](void* data, int argc, char** argv, char** azColName)
        {
            *(float*)data = std::atof(argv[0]); // select first column's value which is the score since we only selected the score
            return 0;
        };

    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, ("SELECT score FROM statistics WHERE userID=(SELECT id FROM users WHERE username='" + username + "');").c_str(), callback, &score, &errMessage);
    if (res != SQLITE_OK) std::cerr << errMessage << std::endl;

    return score;
}

int SqliteDatabase::getNumOfPlayerGames(const std::string& username)
{
    int playerGames = 0;
    auto callback = [](void* data, int argc, char** argv, char** azColName)
        {
            *(int*)data = std::atoi(argv[0]); // select first column's value which is the num of games since we only selected the score
            return 0;
        };

    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, ("SELECT games FROM statistics WHERE userID=(SELECT id FROM users WHERE username='" + username + "');").c_str(), callback, &playerGames, &errMessage);
    if (res != SQLITE_OK) std::cerr << errMessage << std::endl;

    return playerGames;
}

int SqliteDatabase::getNumOfTotalAnswers(const std::string& username)
{
    int totalAnswers = 0;
    auto callback = [](void* data, int argc, char** argv, char** azColName)
        {
            *(int*)data = std::atoi(argv[0]); // select first column's value which is the num of total answers since we only selected the score
            return 0;
        };

    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, ("SELECT totalAnswers FROM statistics WHERE userID=(SELECT id FROM users WHERE username='" + username + "');").c_str(), callback, &totalAnswers, &errMessage);
    if (res != SQLITE_OK) std::cerr << errMessage << std::endl;

    return totalAnswers;
}

int SqliteDatabase::getNumOfCorrectAnswers(const std::string& username)
{
    int correctAnswers = 0;
    auto callback = [](void* data, int argc, char** argv, char** azColName)
        {
            *(int*)data = std::atoi(argv[0]); // select first column's value which is the num of correct answers since we only selected the score
            return 0;
        };

    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, ("SELECT correctAnswers FROM statistics WHERE userID=(SELECT id FROM users WHERE username='" + username + "');").c_str(), callback, &correctAnswers, &errMessage);
    if (res != SQLITE_OK) std::cerr << errMessage << std::endl;

    return correctAnswers;
}

float SqliteDatabase::getPlayerAverageAnswerTime(const std::string& username)
{
    // find the total answer time
    int totalAnswerTime = 0;
    auto callback = [](void* data, int argc, char** argv, char** azColName)
        {
            *(int*)data = std::atoi(argv[0]); // select first column's value which is the totalAnswerTime since we only selected the score
            return 0;
        };

    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, ("SELECT totalAnswerTime FROM statistics WHERE userID=(SELECT id FROM users WHERE username='" + username + "');").c_str(), callback, &totalAnswerTime, &errMessage);
    if (res != SQLITE_OK) std::cerr << errMessage << std::endl;

    // find the number of total answers
    int totalAnswersNum = this->getNumOfTotalAnswers(username);

    // return the average answer time
    if (totalAnswersNum == 0) // extreme case
    {
        return 0;
    }

    return (float)totalAnswerTime / totalAnswersNum;
}

std::vector<std::string> SqliteDatabase::getHighScores()
{
    std::vector<std::string> highScores;
    auto callback = [](void* data, int argc, char** argv, char** azColName)
        {
            std::string score = "";
            for (int i = 0; i < argc; i++)
            {
                if (std::string(azColName[i]) == "username")
                {
                    score += std::string(argv[i]) + ": ";
                }
                else if (std::string(azColName[i]) == "score")
                {
                    score += std::string(argv[i]);
                }
            }

            ((std::vector<std::string>*)data)->push_back(score);
            return 0;
        };

    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, "SELECT users.username, statistics.score FROM statistics INNER JOIN users ON users.id = statistics.userID ORDER BY score DESC LIMIT 5;", callback, &highScores, &errMessage);
    if (res != SQLITE_OK) std::cerr << errMessage << std::endl;

    return highScores;
}

void SqliteDatabase::insertStatistics(const std::string& username, const int& correctAnswers, const int& totalAnswers, const int& totalAnswerTime, const float& score)
{
    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, ("UPDATE statistics SET "
        "score = score + " + std::to_string(score) + ", "
        "games = games + 1, "
        "totalAnswers = totalAnswers + " + std::to_string(totalAnswers) + ", "
        "correctAnswers = correctAnswers + " + std::to_string(correctAnswers) + ", "
        "totalAnswerTime = totalAnswerTime + " + std::to_string(totalAnswerTime) + " "
        "WHERE userID = (SELECT id FROM users WHERE username='" + username + "');").c_str(), NULL, NULL, &errMessage);
    if (res != SQLITE_OK) std::cerr << errMessage << std::endl;
}
