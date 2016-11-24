#ifndef CHECKERS_CONTROLLER_H
#define CHECKERS_CONTROLLER_H

#include "Move.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "GameUI.h"
#include <cstdlib>
#include <time.h>
#include <algorithm>
using namespace std;

class Controller {
public:
    Controller();
    void start();

private:
    GameBoard * board; //points to the game board.
    GameUI ui; //instance of the UI.
    Player * dark; //points to the dark player
    Player * light; //points to the light player
    Player * current; //points to the current player (light or dark).

    GameMode getGameMode();
    bool isLegalMove(Move m);
    void executeMove(Move m);
    bool checkLose();
    void pause(int time);
    string getInput();
    void showError(Error e, int time);
    bool playAgain();
    void getValidInput(bool flipped);
};


#endif //CHECKERS_CONTROLLER_H
