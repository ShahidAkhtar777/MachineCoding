#pragma once

#include <unordered_map>
#include "../models/Board.h"
using namespace std;

class BoardRepository
{
public:
    void addBoard(Board &board)
    {
        boardsById[board.getId()] = board;
    }

    Board *getBoardById(int boardId)
    {
        auto it = boardsById.find(boardId);
        return (it != boardsById.end()) ? &it->second : nullptr;
    }

private:
    unordered_map<int, Board> boardsById;
};
