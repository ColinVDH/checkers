//
// Created by colin on 11/10/16.
//

#ifndef CHECKERS_BOARD_H
#define CHECKERS_BOARD_H

#include "Piece.h"
#include <string>
#include <array>

using namespace std;




class GameBoard {
private:
    array<array<Piece*,8>, 8> board;
    int darkPieces, lightPieces;

public:
    GameBoard();
    GameBoard(array<array<Piece*,8>, 8> b, int darkP, int lightP);
    ~GameBoard();
    GameBoard* Clone();
    void setPiece(int x, int y, Piece *p);
    void setPiece(array<int,2> a, Piece *p);
    Piece * getPiece(int x, int y);
    Piece * getPiece(array<int,2> a);
    bool isEmpty(array<int,2> a);

    bool isLegalJump(Piece * p, array<int,2> start, array<int,2> finish);
    bool isLegalSlide(Piece * p, array<int,2> start, array<int,2> finish);
    bool jumpsAvailable(Color c);

    bool piecesRemaining(Color c);
    bool movesRemaining(Color c);

    void removePiece(array<int, 2> a);
    void movePiece(array<int,2> start, array<int,2> finish);

    bool withinBounds(array<int, 2> array);


};

#endif //CHECKERS_BOARD_H
