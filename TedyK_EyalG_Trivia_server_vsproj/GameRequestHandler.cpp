#include "GameRequestHandler.h"

#define ANSWERS_NUM 4

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handlerFactory, Game& game, LoggedUser user)
	: m_handlerFactory(handlerFactory), m_gameManager(handlerFactory.getGameManager()), m_game(game), m_user(user)
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
	response.question = this->m_game.getQuestionForUser(this->m_user).getQuestion();

	for (int i = 0; i < ANSWERS_NUM; i++)
	{
		response.answers[i] = this->m_game.getQuestionForUser(this->m_user).getPossibleAnswers()[i];
	}

	// make a response and serialize it
	response.status = OK_RESPONSE;
	result.newHandler = this->m_handlerFactory.createGameRequestHandler(this->m_user, this->m_game);
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
	this->m_game.submitAnswer(this->m_user, request.answerID);

	// make a response and serialize it
	response.status = OK_RESPONSE;
	result.newHandler = this->m_handlerFactory.createGameRequestHandler(this->m_user, this->m_game);
	result.buffer = seri.serializeResponse(response);

	return result;
}

RequestResult GameRequestHandler::getGameResults(const RequestInfo& info)
{
	JsonResponsePacketSerializer seri;
	GetGameResultsResponse response;
	RequestResult result;
	
	// go over the users
	for (auto& it : this->m_game.getUsers())
	{
		// get the current user's data
		PlayerResults playerData;

		playerData.username = it.first.GetUserName();
		playerData.correctAnswerCount = it.second.correctAnswerCount;
		playerData.wrongAnswerCount = it.second.wrongAnswerCount;

		playerData.averageAnswerTime = (playerData.correctAnswerCount + playerData.wrongAnswerCount) / it.second.totalAnswerTime;

		// push it to the response
		response.results.push_back(playerData);
	}

	// make a response and serialize it
	response.status = OK_RESPONSE;
	result.newHandler = this->m_handlerFactory.createGameRequestHandler(this->m_user, this->m_game);
	result.buffer = seri.serializeResponse(response);

	return result;
}

RequestResult GameRequestHandler::leaveGame(const RequestInfo& info)
{
	JsonResponsePacketSerializer seri;
	LeaveGameResponse response;
	RequestResult result;

	// leave the game
	this->m_game.removePlayer(this->m_user);

	// leave the room
	this->m_handlerFactory.getRoomManager().getRoom(this->m_game.getGameID()).removeUser(this->m_user);

	// make a response and serialize it
	response.status = OK_RESPONSE;
	result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
	result.buffer = seri.serializeResponse(response);

	return result;
}
