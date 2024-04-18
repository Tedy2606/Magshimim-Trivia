#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string name)
{
    this->m_userName = name;
}

std::string LoggedUser::GetUserName()
{
    return this->m_userName;
}
