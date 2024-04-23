#include "Question.h"

std::string Question::getQuestion() const
{
    return this->m_question;
}

std::vector<std::string> Question::getPossibleAnswers() const
{
    return this->m_possibleAnswers;
}

int Question::getCorrectAnswerId() const
{
    return 0;
}
