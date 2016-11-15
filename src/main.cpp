#include <iostream>
#include "HumanPlayer.h"
#include "GameUI.h"
#include "Controller.h"

int main() {
    Controller control = Controller();
    control.start();
    return 0;
}