#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handlerFactory, Game& game, LoggedUser user)
{
}

bool GameRequestHandler::isRequestRelevant(const RequestInfo& info) const
{
	return false;
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& info)
{
	return RequestResult();
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
	return RequestResult();
}
