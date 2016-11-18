//
// Created by colin on 11/12/16.
//

#include "Piece.h"

Piece::Piece(Type t, Color c) {
    color=c;
    type=t;
}

Color Piece::getColor() {
    return color;
}

Type Piece::getType() {
    return type;
}

Piece::Piece(Color c) {
    color=c;
    type=NORMAL;
}

void Piece::setType(Type t) {
    type=t;
}


