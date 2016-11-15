//
// Created by colin on 11/10/16.
//

#ifndef CHECKERS_CONTROLLER_H
#define CHECKERS_CONTROLLER_H

#include "Move.h"
#include "HumanPlayer.h"
#include "GameUI.h"
#include <cstdlib>
using namespace std;

enum GameMode{TWOPLAYER, PLAYERCOMPUTER};
enum Error{INVALID, ILLEGAL};

class Controller {
private:
    GameBoard * board;
    GameUI ui;
    Player * dark;
    Player * light;
    Player * current;


    GameMode getGameMode();
    bool isLegalMove(Move m);
    void executeMove(Move m);
    bool checkLose();
    void pause(int time);
    string getInput();
    void showError(Error e, int time);
    bool playAgain();

public:
    Controller();
    void start();

    bool jumpsAvailable();

    void getValidInput(bool flipped);
};


#endif //CHECKERS_CONTROLLER_H
