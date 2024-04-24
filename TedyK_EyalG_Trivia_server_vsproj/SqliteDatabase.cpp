#include "SqliteDatabase.h"

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
    }
    return true;
}

bool SqliteDatabase::close()
{
    int res = sqlite3_close(this->_db);
    if (res != SQLITE_OK)
    {
        std::cerr << "An error occured when trying to close the databse." << std::endl;
        return false;
    }

    this->_db = nullptr;
    return true;
}

bool SqliteDatabase::doesUserExist(std::string username)
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

bool SqliteDatabase::doesPasswordMatch(std::string username, std::string password)
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

bool SqliteDatabase::addNewUser(std::string username, std::string password, std::string email)
{
    if (this->doesUserExist(username))
    {
        return false; // user with the username already exists
    }

    std::string sqlQuery = "INSERT INTO users (username, password, email) VALUES ('" + username + "', '" + password + "', '" + email + "');";
    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, sqlQuery.c_str(), nullptr, nullptr, &errMessage);
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
                else if (std::string(azColName[i]) == "correctAnswer" || 
                    std::string(azColName[i]) == "wrongAnswer1" ||
                    std::string(azColName[i]) == "wrongAnswer2" ||
                    std::string(azColName[i]) == "wrongAnswer3")
                {
                    possibleAnswers.push_back(std::string(argv[i]));
                }
            }

            ((std::list<Question>*)data)->push_back(Question(question, possibleAnswers));
            return 0;
        };

    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, ("SELECT * FROM questions LIMIT " + std::to_string(questionsNum) + ";").c_str(), callback, &questions, &errMessage);
    if (res != SQLITE_OK) std::cerr << errMessage << std::endl;

    return questions;
}
