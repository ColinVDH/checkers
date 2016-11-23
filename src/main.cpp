#include <iostream>
#include "HumanPlayer.h"
#include "GameUI.h"
#include "Controller.h"

//called on program start
int main() {
    Controller control = Controller(); //initialize the controller
    control.start(); //start the game
    return 0;
}