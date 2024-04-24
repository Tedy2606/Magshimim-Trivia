#include "Question.h"

Question::Question(std::string question, std::vector<std::string> possibleAnswers)
{
    this->m_question = question;
    this->m_possibleAnswers = possibleAnswers;
}

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
