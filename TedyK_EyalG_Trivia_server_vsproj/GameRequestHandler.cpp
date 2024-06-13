#include "GameRequestHandler.h"

#define ANSWERS_NUM 4

bool isAllFinished = false;
std::mutex mtx;
std::condition_variable cv;

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handlerFactory, int gameID, LoggedUser user)
	: m_handlerFactory(handlerFactory), m_gameManager(handlerFactory.getGameManager()), m_gameID(gameID), m_user(user)
{
}

bool GameRequestHandler::isRequestRelevant(const RequestInfo& info) const
{
	return info.id == GET_QUESTION_REQ ||
		info.id == SUBMIT_ANSWER_REQ ||
		info.id == GET_GAME_RESULT_REQ ||
		info.id == LEAVE_GAME_REQ;
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& info)
{
	RequestResult result;

	switch (info.id)
	{
	case GET_QUESTION_REQ:
		result = getQuestion(info);
		break;
	case SUBMIT_ANSWER_REQ:
		result = submitAnswer(info);
		break;
	case GET_GAME_RESULT_REQ:
		result = getGameResults(info);
		break;
	case LEAVE_GAME_REQ:
		result = leaveGame(info);
		break;
	}

	return result;
}

RequestResult GameRequestHandler::getQuestion(const RequestInfo& info)
{
	JsonResponsePacketSerializer seri;
	GetQuestionResponse response;
	RequestResult result;
	
	// get the question and the answers
	response.question = this->m_gameManager.getRoom(this->m_gameID).getQuestionForUser(this->m_user).getQuestion();
	
	for (int i = 0; i < ANSWERS_NUM; i++)
	{
		response.answers[i] = this->m_gameManager.getRoom(this->m_gameID).getQuestionForUser(this->m_user).getPossibleAnswers()[i];
	}

	// make a response and serialize it
	response.status = OK_RESPONSE;
	result.newHandler = this->m_handlerFactory.createGameRequestHandler(this->m_user, this->m_gameID);
	result.buffer = seri.serializeResponse(response);

	return result;
}

RequestResult GameRequestHandler::submitAnswer(const RequestInfo& info)
{
	JsonResponsePacketSerializer seri;
	JsonResponsePacketDeserializer desi;
	SubmitAnswerResponse response;
	RequestResult result;

	// desrielize the request
	SubmitAnswerRequest request = desi.desirializeSubmitAnswerRequest(info.buffer);

	// submit the answer in the request
	response.isCorrect = this->m_gameManager.getRoom(this->m_gameID).submitAnswer(this->m_user, request.answerID);

	// make a response and serialize it
	response.status = OK_RESPONSE;
	result.newHandler = this->m_handlerFactory.createGameRequestHandler(this->m_user, this->m_gameID);
	result.buffer = seri.serializeResponse(response);

	return result;
}

RequestResult GameRequestHandler::getGameResults(const RequestInfo& info)
{
	std::map<LoggedUser, GameData>& users = this->m_gameManager.getRoom(this->m_gameID).getUsers();
	{
		isAllFinished = true;
		// check if there is a user who hasn't answered all of the questions
		std::unique_lock<std::mutex> lock(mtx);
		for (auto& it : users)
		{
			// check if total answers of current user is equal to the number of questions in the game
			if (it.second.correctAnswerCount + it.second.wrongAnswerCount < this->m_gameManager.getRoom(this->m_gameID).getQuestions().size())
			{
				isAllFinished = false;
				break;
			}
		}



		if (isAllFinished)
		{
			cv.notify_all();
		}
		else
		{

			cv.wait(lock, [] {return isAllFinished; });
			int done = 1;
		}





	}
	
	JsonResponsePacketSerializer seri;
	GetGameResultsResponse response;
	RequestResult result;
	
	// go over the users
	for (auto& it : users)
	{
		// get the current user's data
		PlayerResults playerData;

		playerData.username = it.first.GetUserName();
		playerData.correctAnswerCount = it.second.correctAnswerCount;
		playerData.wrongAnswerCount = it.second.wrongAnswerCount;
		playerData.totalAnswerTime = it.second.totalAnswerTime;

		// push it to the response
		response.results.push_back(playerData);
	}

	// make a response and serialize it
	response.status = OK_RESPONSE;
	result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
	result.buffer = seri.serializeResponse(response);

	return result;
}

RequestResult GameRequestHandler::leaveGame(const RequestInfo& info)
{
	JsonResponsePacketSerializer seri;
	LeaveGameResponse response;
	RequestResult result;

	// leave the game
	this->m_gameManager.getRoom(this->m_gameID).removePlayer(this->m_user);

	// leave the room
	this->m_handlerFactory.getRoomManager().getRoom(this->m_gameID).removeUser(this->m_user);

	// make a response and serialize it
	response.status = OK_RESPONSE;
	result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
	result.buffer = seri.serializeResponse(response);

	return result;
}
