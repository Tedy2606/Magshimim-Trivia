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
    int res = sqlite3_exec(this->_db, ("SELECT * FROM users WHERE username=" + username + ";").c_str(), callback, &doesUserExist, &errMessage);
    if (res != SQLITE_OK) std::cerr << errMessage << std::endl;

    return doesUserExist;
}

bool SqliteDatabase::doesPasswordMatch(std::string username, std::string password)
{
    return false;
}

bool SqliteDatabase::addNewUser(std::string username, std::string password, std::string email)
{
    return false;
}
