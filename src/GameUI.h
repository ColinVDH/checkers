//
// Created by colin on 11/11/16.
//

#ifndef CHECKERS_GAMEUI_H
#define CHECKERS_GAMEUI_H

#include "GameBoard.h"
#include "GameUI.h"
#include "Player.h"

class GameUI {
private:
    GameBoard * board;
    Player * current;

    void showFooter();
    void showBoard(bool flipped);
    void showHeader();

public:
    GameUI();
    void initUI(GameBoard *b, Player * p);
    void mainMenu();
    void clearScreen();
    void InvalidInputMessage();
    void IllegalMoveMessage();
    void updateBoard(bool footer);
    void endGame();

    void updatePlayer(Player *pPlayer);

    void updateBoard(bool footer, bool flipped);
};


#endif //CHECKERS_GAMEUI_H
