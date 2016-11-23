//
// Created by colin on 11/10/16.
//

#ifndef CHECKERS_PLAYER_H
#define CHECKERS_PLAYER_H


#include "Move.h"
#include "GameBoard.h"
//Player is an abstract class (cannot be instantiated) that is the parent for HumanPlayer and ComputerPlayer
class Player {
public:
    Player(Color color);
    virtual Move getMove()=0; //virtual function to get the move from the player.
    virtual bool isHuman()=0; //virtual function to check if a player is human or not.
    Color getColor();
private:
    Color p; //color of the player
};




#endif //CHECKERS_PLAYER_H
