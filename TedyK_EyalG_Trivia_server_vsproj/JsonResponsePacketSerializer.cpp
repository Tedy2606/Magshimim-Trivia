#include "JsonResponsePacketSerializer.h"
#define ERROR_MSG_CODE 103
#define SIGNUP_MSG_CODE 102
#define LOGIN_MSG_CODE 101



#define LOGOUT_MSG_REQ 104

#define JOIN_ROOM_MSG_REQ 105
#define CREATE_ROOM_MSG_REQ 106
#define GET_STATS_MSG_REQ 107
#define GET_HIGH_SCORE_MSG_REQ 110


#define GET_PLAYERS_IN_ROOM_MSG_REQ 111
#define GET_ROOMS_MSG_REQ 112

#define CLOSE_ROOM_REQ 113
#define START_GAME_REQ 114
#define GET_ROOM_STATS_REQ 115
#define LEAVE_ROOM_REQ 116

#define LENGHT_IN_BYTES 4
buffer JsonResponsePacketSerializer::serializeResponseWithJson(json data, int code)
{
    //make the buffer
    std::vector<unsigned char> buf;

    std::string data_as_str = data.dump();

    buf.push_back(code); // enter the msg code 
    int len = data_as_str.length();

    //messege len is 4 byte 
    unsigned char msg_len_as_bytes[LENGHT_IN_BYTES];
    memcpy(msg_len_as_bytes, (char*)&len, LENGHT_IN_BYTES);


    //probably not the best way to do this but it can be improved after we know it works
    for (unsigned char c : msg_len_as_bytes)
    {
        buf.push_back(c);
    }

    //insert bytes into the vector
    for (char c : data_as_str) {
        buf.push_back(static_cast<unsigned char>(c));
    }

    return buf;
}

buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse response)
{
    //make the data json 
    json data = {
  {"message", response.err},
    };
    
    return serializeResponseWithJson(data, ERROR_MSG_CODE);
}

buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse response)
{
    //make the data json 
    json data = {
  {"status", response.status},
    };
    
    return serializeResponseWithJson(data, LOGIN_MSG_CODE);
}

buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse response)
{
    json data = {
  {"status", response.status},
    };

    return serializeResponseWithJson(data, SIGNUP_MSG_CODE);
}

buffer JsonResponsePacketSerializer::serializeResponse(LogoutResponse response)
{

    json data = {
  {"status", response.status},
    };
    return serializeResponseWithJson(data, LOGOUT_MSG_REQ);
}

buffer JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse response)
{

    json data = {
  {"status", response.status},
    };
    return serializeResponseWithJson(data, JOIN_ROOM_MSG_REQ);
}

buffer JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse response)
{

    json data = {
  {"status", response.status},
    };
    return serializeResponseWithJson(data, CREATE_ROOM_MSG_REQ);
}

buffer JsonResponsePacketSerializer::serializeResponse(GetPersonalStatsResponse response)
{

    json data = {
  {"status", response.status}, {"statistics", response.statistics}
    };
    return serializeResponseWithJson(data, GET_STATS_MSG_REQ);
}

buffer JsonResponsePacketSerializer::serializeResponse(GetHighScoreResponse response)
{

    json data = {
  {"status", response.status},  {"statistics", response.statistics}
    };
    return serializeResponseWithJson(data, GET_HIGH_SCORE_MSG_REQ);
}

buffer JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse response)
{

    json data = {
  {"players", response.players},
    };
    return serializeResponseWithJson(data, GET_PLAYERS_IN_ROOM_MSG_REQ);
}

buffer JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse response)
{
    //turn the struct into a string 
    string rooms = "";
    for (int i = 0; i < response.rooms.size(); i++)
    {
        rooms += response.rooms[i].name + ":" + std::to_string(response.rooms[i].id);
        if (i != response.rooms.size() - 1)
        {
            rooms += ",";
        }
    }
    json data = {
  {"status", response.status},  {"rooms", rooms}
    };
    return serializeResponseWithJson(data, GET_ROOMS_MSG_REQ);
}

buffer JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse response)
{
    json data = {
  {"status", response.status}
    };
    return serializeResponseWithJson(data, CLOSE_ROOM_REQ);
}

buffer JsonResponsePacketSerializer::serializeResponse(StartGameResponse response)
{
    json data = {
 {"status", response.status}
    };
    return serializeResponseWithJson(data, START_GAME_REQ);
}

buffer JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse response)
{
    return buffer();
}

buffer JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse response)
{
    json data = {
 {"status", response.status}
    };
    return serializeResponseWithJson(data, LEAVE_ROOM_REQ);
}
