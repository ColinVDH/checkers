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

private:
    vector<array<int,2>> sequence;
    int cursor=0;

public:
    Move(vector<array<int,2>> sequence);
    bool hasNext();
    array<int,2> getFirst();
    array<int,2> getNext();
    int getLength();
};


#endif //CHECKERS_MOVE_H
