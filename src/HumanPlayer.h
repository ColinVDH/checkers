//
// Created by colin on 11/10/16.
//

#ifndef CHECKERS_HUMANPLAYER_H
#define CHECKERS_HUMANPLAYER_H

#include "Player.h"
#include <string>

class HumanPlayer: public Player{
public:
    HumanPlayer(Color color);
    Move getMove();
    bool hasValidInput();
    void setInput();
    string getInput();
    bool isHuman();
private:
    string input; //stores the current input given by the user
    vector<string> split(string s, char delim);

};




#endif //CHECKERS_HUMANPLAYER_H
