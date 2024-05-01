#pragma once
#include <string>
#include <vector>

class Question
{
public:
	// constructors
	Question() = default;
	Question(std::string question, std::vector<std::string> possibleAnswers);

	/*
	Getter of m_question field
	@return m_question field
	*/
	std::string getQuestion() const;

	/*
	Getter of m_possibleAnswers field
	@return m_possibleAnswers field
	*/
	std::vector<std::string> getPossibleAnswers() const;

	/*
	That's a useless method in the UML for the meantime
	*/
	int getCorrectAnswerId() const;

private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
};

