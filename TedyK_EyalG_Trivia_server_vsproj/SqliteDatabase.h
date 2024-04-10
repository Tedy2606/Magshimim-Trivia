#pragma once
#include "sqlite3.h"
#include "IDataBase.h"
#include <iostream>

class SqliteDatabase : public IDataBase
{
public:
	virtual bool open() override;
	virtual bool close() override;
	virtual bool doesUserExist(std::string username) override;
	virtual bool doesPasswordMatch(std::string username, std::string password) override;
	virtual bool addNewUser(std::string username, std::string password, std::string email) override;

private:
	sqlite3* _db;
};
