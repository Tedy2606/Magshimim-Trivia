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
	virtual bool doesUserExist(std::string username) override;
	virtual bool doesPasswordMatch(std::string username, std::string password) override;
	virtual bool addNewUser(std::string username, std::string password, std::string email) override;

private:
	sqlite3* _db;
};
