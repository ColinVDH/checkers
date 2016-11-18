//
// Created by colin on 11/10/16.
//


#include "GameBoard.h"

GameBoard::GameBoard() {
    darkPieces =12;
    lightPieces = 12;
    for (int y = 0; y<8; y++) {
        for (int x = 0; x<8; x++) {
            if (y < 3) {
                if ((y + x) % 2 == 0) board[y][x] = new Piece(DARK);
                else board[y][x]=nullptr;
            } else if (y > 4) {
                if ((y + x) % 2 == 0) board[y][x] = new Piece(LIGHT);
                else board[y][x]=nullptr;
            }
        }
    }
}

Piece * GameBoard::getPiece(int x, int y) {
    return board[y][x];
}

void GameBoard::setPiece(int x, int y, Piece *p) {
    if (board[y][x]!=nullptr) delete board[y][x];
    board[y][x]=p;
}

void GameBoard::setPiece(array<int, 2> a, Piece *p) {
    if (board[a[0]][a[1]]!=nullptr) delete board[a[0]][a[1]];
    board[a[0]][a[1]]=p;
}


Piece * GameBoard::getPiece(array<int, 2> a) {
    return board[a[1]][a[0]];
}



bool GameBoard::isLegalJump(Piece *p, array<int, 2> start, array<int, 2> finish) {
    Type type=p->getType();
    Color color=p->getColor();

    if (getPiece(finish)!=nullptr){
        return false;
    }
    else if (!withinBounds(finish)){
        return false;
    }

    else{
        if (type==KING || (color == LIGHT)) {
            if (finish[1]-start[1]==-2 && abs(finish[0]-start[0])==2){
                array<int,2> mid= {(finish[0]+start[0])/2,(finish[1]+start[1])/2};
                Piece * jumped = getPiece(mid);
                if (jumped!=nullptr && jumped->getColor()!=color) {
                    return true;
                }
            }
        }
        if  (type==KING || (color == DARK)) {
            if (finish[1]-start[1]==2 && abs(finish[0]-start[0])==2){
                array<int,2> mid= {(finish[0]+start[0])/2,(finish[1]+start[1])/2};
                Piece * jumped = getPiece(mid);
                if (jumped!=nullptr && jumped->getColor()!=color) {
                    return true;
                }
            }
        }
        return false;
    }
}

bool GameBoard::isLegalSlide(Piece * p, array<int, 2> start, array<int, 2> finish) {
    Type type=p->getType();
    Color color=p->getColor();

    if (getPiece(finish)!=nullptr){
        return false;
    }
    else if (!withinBounds(finish)){
        return false;
    }

    else{
        if (type==KING || (color == LIGHT)) {
            if (finish[1]-start[1]==-1 && abs(finish[0]-start[0])==1){
                return true;
            }
        }
        if  (type==KING || (color == DARK)) {
            if (finish[1]-start[1]==1 && abs(finish[0]-start[0])==1){
                return true;
            }
        }
        return false;
    }
}

bool GameBoard::jumpsAvailable(Color c) {
    for (int y=0; y<8; y++) {
        for (int x = 0; x < 8; x++) {
            Piece* piece=board[y][x];
            if (piece!=nullptr && piece->getColor()==c){
                if (piece->getType()==KING || (c == LIGHT)) {
                    if (isLegalJump(piece, {x, y}, {x + 2, y - 2})
                        || isLegalJump(piece, {x, y}, {x - 2, y - 2}))
                        return true;
                }
                if (piece->getType()==KING || (c == DARK)) {
                    if (isLegalJump(piece, {x, y}, {x + 2, y + 2})
                        || isLegalJump(piece, {x, y}, {x - 2, y + 2}))
                        return true;
                }
            }
        }
    }
    return false;
}

bool GameBoard::piecesRemaining(Color c) {
    if (c==DARK) return darkPieces>0;
    else return lightPieces>0;
}

bool GameBoard::movesRemaining(Color c) {
    for (int y=0; y<8; y++){
        for (int x=0; x<8; x++){
            Piece* piece=board[y][x];
            if (piece!=nullptr && piece->getColor()==c){
                if (piece->getType()==KING || (c == LIGHT)) {
                    if (isLegalJump(piece, {x, y}, {x + 2, y - 2})
                        || isLegalJump(piece, {x, y}, {x - 2, y - 2})
                        || isLegalSlide(piece, {x, y}, {x + 1, y - 1})
                        || isLegalSlide(piece, {x, y}, {x - 1, y - 1}))
                        return true;
                }
                if (piece->getType()==KING || (c == DARK)) {
                    if (isLegalJump(piece, {x, y}, {x + 2, y + 2})
                        || isLegalJump(piece, {x, y}, {x - 2, y + 2})
                        || isLegalSlide(piece, {x, y}, {x + 1, y + 1})
                        || isLegalSlide(piece, {x, y}, {x - 1, y + 1}))
                        return true;
                }
            }
        }
    }
    return false;
}

void GameBoard::removePiece(array<int, 2> a) {
    if (getPiece(a)->getColor()==LIGHT) lightPieces--;
    if (getPiece(a)->getColor()==DARK) darkPieces--;
    delete board[a[1]][a[0]];
    board[a[1]][a[0]]=nullptr;
}

GameBoard::~GameBoard() {
    array<array<Piece*,8>,8>::const_iterator row;
    array<Piece*,8>::const_iterator col;

    for (row = board.begin(); row != board.end(); ++row)
    {
        for (col = row->begin(); col != row->end(); ++col)
        {
            delete (*col);
        }
    }

}

void GameBoard::movePiece(array<int, 2> start, array<int, 2> finish) {
    board[finish[1]][finish[0]]=board[start[1]][start[0]];
    if ((finish[0]==0 && getPiece(start)->getColor()==LIGHT)
        || (finish[0]==7 && getPiece(start)->getColor()==DARK))
        getPiece(start)->setType(KING);
    board[start[1]][start[0]]=nullptr;
}

bool GameBoard::isEmpty(array<int,2> a) {
    return board[a[1]][a[0]]==nullptr;
}

bool GameBoard::withinBounds(array<int, 2> a) {
    return (a[0]>=0 && a[0]<=7 && a[1]>=0 && a[1]<=7);
}



GameBoard::GameBoard(array<array<Piece *, 8>, 8> b, int darkP, int lightP) {
    board=b;
    lightPieces=lightP;
    darkPieces=darkP;
}

GameBoard::GameBoard(const GameBoard &obj) {
    board=array<array<Piece*,8>,8>();
    darkPieces = obj.darkPieces;
    lightPieces = obj.lightPieces;
    for (int y = 0; y<8; y++) {
        for (int x = 0; x<8; x++) {
            if (obj.board[y][x]==nullptr)
                board[y][x]=nullptr;
            else
                board[y][x]=new Piece(*obj.board[y][x]);

        }
    }
}

GameBoard& GameBoard::operator=(GameBoard tmp){
    swap(darkPieces, tmp.darkPieces);
    swap(lightPieces, tmp.lightPieces);
    swap(board, tmp.board);
    return *this;
}

GameBoard::GameBoard(GameBoard *obj) {
    board=array<array<Piece*,8>,8>();
    darkPieces = obj->darkPieces;
    lightPieces = obj->lightPieces;
    for (int y = 0; y<8; y++) {
        for (int x = 0; x<8; x++) {
            if (obj->board[y][x]==nullptr)
                board[y][x]=nullptr;
            else
                board[y][x]=new Piece(*obj->board[y][x]);

        }
    }
}



