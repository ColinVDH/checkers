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
    vector<array<int,2>> sequence;
    int cursor=0;
};


#endif //CHECKERS_MOVE_H
