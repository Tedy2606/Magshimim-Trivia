#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponseWithJson(const json& data, int code)
{
    //make the buffer
    std::vector<unsigned char> buf;

    std::string data_as_str = data.dump();

    buf.push_back(code); // enter the msg code 
    int len = data_as_str.length();

    //messege len is 4 byte 
    unsigned char msg_len_as_bytes[LENGHT_IN_BYTES];
    memcpy(msg_len_as_bytes, (char*)&len, LENGHT_IN_BYTES);


    
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

Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& response)
{
    json data = {
        {"message", response.err}
    };

    return serializeResponseWithJson(data, ERROR_RESPONSE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LoginResponse& response)
{
    json data = {
        {"status", response.status}
    };

    return serializeResponseWithJson(data, LOGIN_REQ);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const SignupResponse& response)
{
    json data = {
        {"status", response.status}
    };

    return serializeResponseWithJson(data, SIGNUP_REQ);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LogoutResponse& response)
{
    json data = {
        {"status", response.status}
    };
    return serializeResponseWithJson(data, LOGOUT_MSG_REQ);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const JoinRoomResponse& response)
{
    json data = {
        {"status", response.status}
    };
    return serializeResponseWithJson(data, JOIN_ROOM_MSG_REQ);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const CreateRoomResponse& response)
{
    json data = {
        {"status", response.status}
    };
    return serializeResponseWithJson(data, CREATE_ROOM_MSG_REQ);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetPersonalStatsResponse& response)
{
    json data = {
        {"status", response.status}, {"statistics", response.statistics}
    };
    return serializeResponseWithJson(data, GET_STATS_MSG_REQ);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetHighScoreResponse& response)
{
    json data = {
        {"status", response.status},  {"statistics", response.statistics}
    };
    return serializeResponseWithJson(data, GET_HIGH_SCORE_MSG_REQ);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse& response)
{
    json data = {
        {"players", response.players}
    };
    return serializeResponseWithJson(data, GET_PLAYERS_IN_ROOM_MSG_REQ);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetRoomsResponse& response)
{
    string rooms = "";
    for (int i = 0; i < response.rooms.size(); i++)
    {
        rooms += response.rooms[i].name + ":" + std::to_string(response.rooms[i].id) + ":" + std::to_string(response.rooms[i].isActive);
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

Buffer JsonResponsePacketSerializer::serializeResponse(const CloseRoomResponse& response)
{
    json data = {
        {"status", response.status}
    };
    return serializeResponseWithJson(data, CLOSE_ROOM_REQ);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const StartGameResponse& response)
{
    json data = {
        {"status", response.status}
    };
    return serializeResponseWithJson(data, START_GAME_REQ);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetRoomStateResponse& response)
{
    string players = "";
    for (int i = 0; i < response.players.size(); i++)
    {
        players += response.players[i];
        if (i != response.players.size() - 1)
        {
            players += ",";
        }
    }

    json data = {
        {"status", response.status},  {"answerTimeout", response.answerTimeout},
        {"hasGameBegun", response.hasGameBegun}, {"players", players},
        {"questionCount", response.questionCount}
    };
    return serializeResponseWithJson(data, GET_ROOM_STATS_REQ);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LeaveRoomResponse& response)
{
    json data = {
        {"status", response.status}
    };
    return serializeResponseWithJson(data, LEAVE_ROOM_REQ);
}
