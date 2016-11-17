//
// Created by colin on 11/10/16.
//

#include "Move.h"



Move::Move(){
    sequence={};
}

array<int,2> Move::getNext() {
    cursor++;
    return sequence[cursor];
}

bool Move::hasNext() {
    return sequence.size()>(cursor+1);
}

array<int,2> Move::getFirst() {
    cursor=0;
    return sequence[cursor];
}

int Move::getLength() {
    return sequence.size();
}

vector<array<int,2>> Move::getSequence(){
    return sequence;
}

Move::Move(vector<array<int, 2>> s) {
    sequence=s;
};





