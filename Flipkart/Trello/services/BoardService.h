#pragma once

#include <vector>
#include "../models/Board.h"
#include "../models/User.h"
#include "../repos/BoardRepo.h"

class BoardService {
public:
    void createBoard(const std::string& name, const User& creator) {
        Board board = newBoard(name, creator);
        boardRepository.addBoard(board);
    }

    void deleteBoard(int boardId);
    void addMemberToBoard(int boardId, const User& member);
    void removeMemberFromBoard(int boardId, const User& member);
    void modifyBoardAttributes(int boardId, const std::string& newName);

private:
    BoardRepository boardRepository;
};

inline void BoardService::

inline void BoardService::deleteBoard(int boardId) {
    Board* board = boardRepository.getBoardById(boardId);
    if (board) {
        boardRepository.deleteBoard(boardId);
    }
}

inline void BoardService::addMemberToBoard(int boardId, const User& member) {
    Board* board = boardRepository.getBoardById(boardId);
    if (board) {
        board->addMember(member);
    }
}

inline void BoardService::removeMemberFromBoard(int boardId, const User& member) {
    Board* board = boardRepository.getBoardById(boardId);
    if (board) {
        board->removeMember(member);
    }
}

inline void BoardService::modifyBoardAttributes(int boardId, const std::string& newName) {
    Board* board = boardRepository.getBoardById(boardId);
    if (board) {
        board->setName(newName);
    }
}
