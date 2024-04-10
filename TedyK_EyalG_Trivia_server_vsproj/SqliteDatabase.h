#pragma once
#include "sqlite3.h"
#include "IDataBase.h"
#include <iostream>
#include <io.h>

#define DATABASE_PATH "database.sqlite"

class SqliteDatabase : public IDataBase
{
public:
	/*
	Method opens the database.
	@return whether or not the method succeeded.
	*/
	virtual bool open() override;
	virtual bool close() override;
	virtual bool doesUserExist(std::string username) override;
	virtual bool doesPasswordMatch(std::string username, std::string password) override;
	virtual bool addNewUser(std::string username, std::string password, std::string email) override;

private:
	sqlite3* _db;
};
