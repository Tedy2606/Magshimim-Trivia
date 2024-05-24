#pragma once

// ********* responses *********
// status
#define ERROR_RESPONSE 0
#define OK_RESPONSE 1
#define BAD_RESPONSE 2


// ********* requests *********
// login handler
#define LOGIN_REQ 101
#define SIGNUP_REQ 102

// menu hanlder
#define LOGOUT_MSG_REQ 111
#define JOIN_ROOM_MSG_REQ 112
#define CREATE_ROOM_MSG_REQ 113
#define GET_STATS_MSG_REQ 114
#define GET_HIGH_SCORE_MSG_REQ 115
#define GET_PLAYERS_IN_ROOM_MSG_REQ 116
#define GET_ROOMS_MSG_REQ 117

// room member handler
#define GET_ROOM_STATS_REQ 120
#define LEAVE_ROOM_REQ 121

// room admin handler
#define CLOSE_ROOM_REQ 131
#define START_GAME_REQ 132
