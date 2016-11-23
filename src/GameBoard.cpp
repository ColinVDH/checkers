#include "GameBoard.h"
//constructor for game board -- dark pieces at the start of the array (bottom), light pieces at the back of the array (top)
GameBoard::GameBoard() {
    darkPieces =12; //keep track of pieces for each player
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

//GameBoard constructor
GameBoard::GameBoard(array<array<Piece *, 8>, 8> b, int darkP, int lightP) {
    board=b;
    lightPieces=lightP;
    darkPieces=darkP;
}

Piece * GameBoard::getPiece(int x, int y) {
    return board[y][x];
}

void GameBoard::setPiece(int x, int y, Piece *p) {
    if (board[y][x]!=nullptr) delete board[y][x];
    board[y][x]=p;
}

void GameBoard::setPiece(array<int, 2> a, Piece* p) {
    if (board[a[1]][a[0]]!=nullptr) delete board[a[1]][a[0]];
    board[a[1]][a[0]]=p;
}


Piece * GameBoard::getPiece(array<int, 2> a) {
    return board[a[1]][a[0]];
}

//returns true if the current jump is legal (piece provided is the jumper).
bool GameBoard::isLegalJump(Piece *p, array<int, 2> start, array<int, 2> finish) {
    if (p==nullptr) return false;
    Type type=p->getType();
    Color color=p->getColor();

    if (getPiece(finish)!=nullptr){ //checks if the destination tile is non-empty
        return false;
    }
    else if (!withinBounds(finish) || !withinBounds(start)){ //checks if the destination tile is within bounds
        return false;
    }

    else{
        if (type==KING || (color == LIGHT)) { //note that legal jump direction changes based on type and color
            if (finish[1]-start[1]==-2 && abs(finish[0]-start[0])==2){
                array<int,2> mid= {(finish[0]+start[0])/2,(finish[1]+start[1])/2};
                Piece * jumped = getPiece(mid);
                if (jumped!=nullptr && jumped->getColor()!=color) { //checks if the jumped piece is the opponents color
                    return true;
                }
            }
        }
        if  (type==KING || (color == DARK)) {
            if (finish[1]-start[1]==2 && abs(finish[0]-start[0])==2){
                array<int,2> mid= {(finish[0]+start[0])/2,(finish[1]+start[1])/2};
                Piece * jumped = getPiece(mid);
                if (jumped!=nullptr && jumped->getColor()!=color) { //checks if the jumped piece is the opponents color
                    return true;
                }
            }
        }
        return false;
    }
}
//checks if a legal slide has occured (normal, non-jump, move).
bool GameBoard::isLegalSlide(Piece * p, array<int, 2> start, array<int, 2> finish) {
    if (p==nullptr) return false;
    Type type=p->getType();
    Color color=p->getColor();

    if (getPiece(finish)!=nullptr){ //non-empty destination tile
        return false;
    }
    else if (!withinBounds(finish) || !withinBounds(start)){ //destination tile is out of bounds
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

//checks if jumps are available
bool GameBoard::jumpsAvailable(Color c) {
    for (int y=0; y<8; y++) { //iterate through all board positions
        for (int x = 0; x < 8; x++) {
            Piece* piece=board[y][x];
            if (piece!=nullptr && piece->getColor()==c){ //checks if piece is the correct color
                if (piece->getType()==KING || (c == LIGHT)) {
                    if (isLegalJump(piece, {x, y}, {x + 2, y - 2}) //checks if there is a down-right jump
                        || isLegalJump(piece, {x, y}, {x - 2, y - 2})) //checks if there is a down-left jump
                        return true;
                }
                if (piece->getType()==KING || (c == DARK)) {
                    if (isLegalJump(piece, {x, y}, {x + 2, y + 2}) //checks if there is an up-right jump
                        || isLegalJump(piece, {x, y}, {x - 2, y + 2})) //checks if there is an up-left jump
                        return true;
                }
            }
        }
    }
    return false;
}

//return true if there are pieces of the input color remaining.
bool GameBoard::piecesRemaining(Color c) {
    if (c==DARK) return darkPieces>0;
    else return lightPieces>0;
}

//returns true if there are moves of the input color remaining
bool GameBoard::movesRemaining(Color c) {
    for (int y=0; y<8; y++){ //iterate through all positions on the board.
        for (int x=0; x<8; x++){
            Piece* piece=board[y][x];
            if (piece!=nullptr && piece->getColor()==c){ //checks if the piece is the correct color
                if (piece->getType()==KING || (c == LIGHT)) {
                    if (isLegalJump(piece, {x, y}, {x + 2, y - 2}) //checks if there is an down-right jump
                        || isLegalJump(piece, {x, y}, {x - 2, y - 2}) //checks if there is an down-left jump
                        || isLegalSlide(piece, {x, y}, {x + 1, y - 1}) //checks if there is an down-right slide
                        || isLegalSlide(piece, {x, y}, {x - 1, y - 1})) //checks if there is an down-left slide
                        return true;
                }
                if (piece->getType()==KING || (c == DARK)) {
                    if (isLegalJump(piece, {x, y}, {x + 2, y + 2}) //checks if there is an up-right jump
                        || isLegalJump(piece, {x, y}, {x - 2, y + 2}) //checks if there is an up-left jump
                        || isLegalSlide(piece, {x, y}, {x + 1, y + 1}) //checks if there is an up-right slide
                        || isLegalSlide(piece, {x, y}, {x - 1, y + 1})) //checks if there is an up-left slide
                        return true;
                }
            }
        }
    }
    return false;
}

//remove piece from the board at position a.
void GameBoard::removePiece(array<int, 2> a) {
    if (getPiece(a)->getColor()==LIGHT) lightPieces--; //decrement lightpieces
    if (getPiece(a)->getColor()==DARK) darkPieces--; //decrement darkpieces
    delete board[a[1]][a[0]]; //delete object at that position
    board[a[1]][a[0]]=nullptr; //set the pointer to a null pointer.
}

//GameBoard destructor will delete all objects from the board.
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
//moves Piece from position start to position finish
void GameBoard::movePiece(array<int, 2> start, array<int, 2> finish) {
    setPiece(finish,getPiece(start)); //assign pointer at finish to the object at start.
    board[start[1]][start[0]]=nullptr; //the pointer at start should now be null.
    if ((finish[1]==0 && getPiece(finish)->getColor()==LIGHT) //checks if the piece has reached the end of the board
        || (finish[1]==7 && getPiece(finish)->getColor()==DARK))
        getPiece(finish)->setType(KING); //if so, assign it to be a king.

}

//returns true if the current position is empty
bool GameBoard::isEmpty(array<int,2> a) {
    return board[a[1]][a[0]]==nullptr;
}

//returns true if the current position is within the bounds of the board
bool GameBoard::withinBounds(array<int, 2> a) {
    return (a[0]>=0 && a[0]<=7 && a[1]>=0 && a[1]<=7);
}

//GameBoard copy constructor
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
//GameBoard assignment operator
GameBoard& GameBoard::operator=(GameBoard tmp){
    swap(darkPieces, tmp.darkPieces);
    swap(lightPieces, tmp.lightPieces);
    swap(board, tmp.board);
    return *this;
}

//GameBoard constructor
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



