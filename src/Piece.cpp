//
// Created by colin on 11/12/16.
//

#include "Piece.h"

//constructor
Piece::Piece(Type t, Color c) {
    color=c;
    type=t;
}

//constructor
Piece::Piece(Color c) {
    color=c;
    type=NORMAL;
}

//return color of piece
Color Piece::getColor() {
    return color;
}
//returns type of piece (king or normal)
Type Piece::getType() {
    return type;
}

//set the type (king or normal)
void Piece::setType(Type t) {
    type=t;
}
