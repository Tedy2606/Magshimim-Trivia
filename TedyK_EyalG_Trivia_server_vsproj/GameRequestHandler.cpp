#include "GameRequestHandler.h"

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
	return RequestResult();
}

RequestResult GameRequestHandler::submitAnswer(const RequestInfo& info)
{
	return RequestResult();
}

RequestResult GameRequestHandler::getGameResults(const RequestInfo& info)
{
	return RequestResult();
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
