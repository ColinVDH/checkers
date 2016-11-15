//
// Created by colin on 11/10/16.
//

#include "Player.h"

Player::Player(Color color) {
    p=color;
}

Color Player::getColor(){
    return p;
}


/*
int Player::getNumPieces() {
    return numPieces;
}

void Player::removePiece() {
    numPieces--;
}

bool Player::hasLost() {
    return numPieces==0;
}
*/

