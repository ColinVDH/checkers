#ifndef CHECKERS_BOARD_H
#define CHECKERS_BOARD_H

#include "Piece.h"
#include <string>
#include <array>

using namespace std;


class GameBoard {
public:
    GameBoard();
    GameBoard(array<array<Piece*,8>, 8> b, int darkP, int lightP);
    ~GameBoard();
    GameBoard(const GameBoard &obj);
    GameBoard(GameBoard *obj);
    GameBoard& operator=(GameBoard tmp);


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

private:
    array<array<Piece*,8>, 8> board; //represents the board and stores the pointers to Pieces
    int darkPieces, lightPieces; //stores the current number of light and dark pieces on the board.

};


#endif //CHECKERS_BOARD_H
