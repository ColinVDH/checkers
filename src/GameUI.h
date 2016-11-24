//
// Created by colin on 11/11/16.
//

#ifndef CHECKERS_GAMEUI_H
#define CHECKERS_GAMEUI_H

#include "GameBoard.h"
#include "GameUI.h"
#include "Player.h"

enum GameMode{TWOPLAYER, PLAYERCOMPUTER, TWOCOMPUTER}; //enum to signify the GameMode type.
enum Error{INVALID, ILLEGAL}; //enum to signify the Error type.

class GameUI {

public:
    GameUI();
    void initUI(GameBoard *b, Player * p);
    void mainMenu();
    void clearScreen();
    void InvalidInputMessage();
    void IllegalMoveMessage();
    void updateBoard(bool footer);
    void endGame(GameMode gm, Player * loser);

    void updatePlayer(Player *pPlayer);

    void updateBoard(bool footer, bool flipped);

private:
    GameBoard * board; //pointer to game board
    Player * current; //pointer to current player

    void showFooter();
    void showBoard(bool flipped);
    void showHeader();

};


#endif //CHECKERS_GAMEUI_H
