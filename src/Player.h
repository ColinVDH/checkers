//
// Created by colin on 11/10/16.
//

#ifndef CHECKERS_PLAYER_H
#define CHECKERS_PLAYER_H


#include "Move.h"
#include "GameBoard.h"

class Player {
private:
    Color p;
public:
    Player(Color color);
    virtual Move getMove()=0;
    virtual bool isHuman()=0;
    Color getColor();
};




#endif //CHECKERS_PLAYER_H
