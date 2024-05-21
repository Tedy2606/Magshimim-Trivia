#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonResponsePacketDeserializer.h"

#define GET_ROOM_STATS_REQ 115
#define LEAVE_ROOM_REQ 116

#define OK_RESPONSE 1

class RequestHandlerFactory;

class RoomMemberRequestHandler : public IRequestHandler
{
public:
    RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser user);

    /***
    * function checks if a request is relevant
    * @param const RequestInfo& info - the info (mainly the id) of the request
    * @return if the request matches or not
    **/
    virtual bool isRequestRelevant(const RequestInfo& info) const override;

    /***
    * handles a room member request from the user - desirialise, procces, return response
    * @param const RequestInfo& info - the info (mainly the data) of the request
    * @return the result (serialised response and new handler)
    **/
    virtual RequestResult handleRequest(const RequestInfo& info) override;

private:
    /*
    Leaves the room
    @param const RequestInfo& info - the info of the request
    @return the result of the request
    */
    RequestResult leaveRoom(const RequestInfo& info);

    /*
    Returns the state of the room
    @param const RequestInfo& info - the info of the request
    @return the result of the request
    */
    RequestResult getRoomState(const RequestInfo& info);

    Room m_room;
    LoggedUser m_user;
    RoomManager& m_roomManager;
    RequestHandlerFactory& m_handlerFactory;
};
