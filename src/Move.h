//
// Created by colin on 11/10/16.
//

#ifndef CHECKERS_MOVE_H
#define CHECKERS_MOVE_H

#include <string>
#include <vector>
#include <array>
using namespace std;

class Move {



public:
    Move(vector<array<int,2>> sequence);
    Move();
    bool hasNext();
    array<int,2> getFirst();
    array<int,2> getNext();
    int getLength();
    vector<array<int, 2>> getSequence();

private:
    vector<array<int,2>> sequence; //stores the sequence of move positions
    int cursor; //stores the index of the current move position
};


#endif //CHECKERS_MOVE_H
