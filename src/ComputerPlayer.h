#ifndef CHECKERS_COMPUTERPLAYER_H
#define CHECKERS_COMPUTERPLAYER_H


#include "Player.h"
#include <string>
#include "GameBoard.h"

class ComputerPlayer: public Player{
public:
    ComputerPlayer(GameBoard *board, Color color);
    Move getMove();
    bool isHuman();

private:
    GameBoard * board;

    int randomInt(int start, int finish);
};

#endif //CHECKERS_COMPUTERPLAYER_H
