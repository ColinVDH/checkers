//
// Created by colin on 11/10/16.
//

#include "Move.h"


//default constructor
Move::Move(){
    cursor=-1;
    sequence={};
}

//constructor
Move::Move(vector<array<int, 2>> s) {
    cursor=-1;
    sequence=s;
};

//get Next position in the move sequence
array<int,2> Move::getNext() {
    cursor++;
    return sequence[cursor];
}
//checks if there is another position in the move sequence
bool Move::hasNext() {
    return sequence.size()>(cursor+1);
}
//gets the first position in the move sequence
array<int,2> Move::getFirst() {
    cursor=0;
    return sequence[cursor];
}
//gets the number of positions in the move sequence
int Move::getLength() {
    return sequence.size();
}
//get the move sequence (returned as a vector of arrays {x,y})
vector<array<int,2>> Move::getSequence(){
    return sequence;
}

bool Move::operator==(const Move &other) const {
    return (sequence==other.sequence);
}

bool Move::operator!=(const Move &other) const {
    return !(sequence==other.sequence);
}






