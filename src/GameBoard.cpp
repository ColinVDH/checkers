
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
    if (!withinBounds({x,y}))return nullptr;
    return board[y][x];
}

void GameBoard::setPiece(int x, int y, Piece *p) {
    if (!withinBounds({x,y})) return;
    if (board[y][x]!=nullptr) delete board[y][x];
    board[y][x]=p;
}

void GameBoard::setPiece(array<int, 2> a, Piece* p) {
    if (!withinBounds(a)) return;
    if (board[a[1]][a[0]]!=nullptr) delete board[a[1]][a[0]];
    board[a[1]][a[0]]=p;
}


Piece * GameBoard::getPiece(array<int, 2> a) {
    if (!withinBounds(a)) return nullptr;
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
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            delete board[i][j];
        }
    }
    board=array<array<Piece*,8>,8>();
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

//gets all possible (legal) moves
vector<Move> GameBoard::getMoves(Color color){
    vector<Move> all_moves;
    all_moves.clear();
    Move currentmove;
    vector<array<int,2>> sequence;
    for (int y = 0; y<8; y++) { //iterate through board coordinates
        for (int x = 0; x < 8; x++) {
            Piece * piece =getPiece(x,y);
            if (piece!=nullptr && piece->getColor()==color){ //if there is a piece at this position
                if (piece->getType()==KING || piece->getColor()==LIGHT){ //checks if its the computer's color and the proper type to move down (light or king).
                    sequence = {{x,y},{x-2,y-2}};
                    if (isLegalJump(piece, sequence[0], sequence[1])) { //checks if jump is legal
                        getMultiJumps(piece, sequence, all_moves); //call multijump to append further jumps if possible
                    }
                    sequence = {{x,y},{x+2,y-2}};
                    if (isLegalJump(piece, sequence[0], sequence[1])) { //checks if jump is legal
                        getMultiJumps(piece, sequence, all_moves); //call multijump to append further jumps if possible
                    }
                }
                if (piece->getType()==KING || piece->getColor()==DARK){ //checks if its the computer's color and the proper type to move up (dark or king).
                    sequence = {{x,y},{x-2,y+2}};
                    if (isLegalJump(piece, sequence[0], sequence[1])) {  //checks if jump is legal
                        getMultiJumps(piece, sequence, all_moves); //call multijump to append further jumps if possible
                    }
                    sequence = {{x,y},{x+2,y+2}};
                    if (isLegalJump(piece, sequence[0], sequence[1])) { //checks if jump is legal
                        getMultiJumps(piece, sequence, all_moves); //call multijump to append further jumps if possible
                    }
                }
            }
        }
    }

    if (all_moves.empty()){  //no jump moves available , then you can now look for a regular move
        for (int y = 0; y<8; y++) { //iterate through board coordinates
            for (int x = 0; x < 8; x++) {
                Piece * piece =getPiece(x,y);
                if (piece!=nullptr && piece->getColor()==color){
                    if (piece->getType()==KING || piece->getColor()==LIGHT){ //checks if its the computer's color and the proper type to move down (light or king).
                        sequence = {{x,y},{x-1,y-1}};
                        if (isLegalSlide(piece, sequence[0], sequence[1])) { //checks if legal move
                            currentmove=Move(sequence);
                            all_moves.push_back(currentmove); //add move
                        }
                        sequence = {{x,y},{x+1,y-1}};
                        if (isLegalSlide(piece, sequence[0], sequence[1])) { //checks if legal move
                            currentmove=Move(sequence);
                            all_moves.push_back(currentmove); //add move
                        }
                    }
                    if (piece->getType()==KING || piece->getColor()==DARK){ //checks if its the computer's color and the proper type to move up (dark or king).
                        sequence = {{x,y},{x-1,y+1}};
                        if (isLegalSlide(piece, sequence[0], sequence[1])) { //checks if legal move
                            currentmove=Move(sequence);
                            all_moves.push_back(currentmove); //add move
                        }
                        sequence = {{x,y},{x+1,y+1}};
                        if (isLegalSlide(piece, sequence[0], sequence[1])) { //checks if legal move
                            currentmove=Move(sequence);
                            all_moves.push_back(currentmove); //add move
                        }
                    }
                }
            }
        }
    }
    printMoves(all_moves);
    cout<<"SIZE"<<all_moves.size();
    return all_moves; //return all possible legal moves
}

//recursive function that takes a current seed (part of a jump move) and looks if another jump can be added on. If not, it adds the complete jump sequence to "all_moves" vector.
void GameBoard::getMultiJumps(Piece * p, vector<array<int,2>> seed, vector<Move> &all_moves){
    cout<<"CALLED";
    Color c=p->getColor();
    Type t=p->getType();

    array<int,2> start=seed.back(); //the start of the next jump is the last coordinate in the "seed"
    array<int,2> finish1; //the finish is unassigned.
    array<int,2> finish2; //the finish is unassigned.
    Move currentmove;
    vector<array<int,2>> newseed;

    bool f1=false, f2=false, f3=false, f4=false;
    if (t==KING || c==LIGHT){ //checks the type and the color of the piece (computer piece) performing the jump
        finish1={start[0]-2, start[1]-2};
        finish2={start[0]+2, start[1]-2};

        if (isLegalJump(p,start,finish1) && notBackTrack(seed, finish1) && notRepeat(seed, finish1)){
            cout<<"oneok"<<endl;
            newseed=seed;
            newseed.push_back(finish1);
            getMultiJumps(p,newseed, all_moves); //recursively call function with updated seed.
            f1=true;
        }
        if (isLegalJump(p,start,finish2) && notBackTrack(seed, finish2) && notRepeat(seed, finish2)){
            cout<<"twook"<<endl;
            newseed=seed;
            newseed.push_back(finish2);
            getMultiJumps(p, newseed, all_moves); //recursively call function with updated seed.
            f2=true;
        }
        if (t!=KING && !f1 && !f2 ){
            currentmove=Move(seed);
            all_moves.push_back(currentmove); //add move
        }
    }

    if (t==KING || c==DARK){ //checks the type and the color of the piece (computer piece) performing the jump. Same as above but for a dark piece.
        finish1={start[0]-2, start[1]+2};
        finish2={start[0]+2, start[1]+2};
        if (isLegalJump(p,start,finish1) && notBackTrack(seed, finish1) && notRepeat(seed, finish1)){
            cout<<"threeok"<<endl;
            newseed = seed;
            newseed.push_back(finish1);
            getMultiJumps(p, newseed, all_moves); //recursively call function with updated seed.
            f3=true;
        }
        if (isLegalJump(p,start,finish2) && notBackTrack(seed, finish2) && notRepeat(seed, finish2)){
            cout<<"fourok"<<endl;
            newseed = seed;
            newseed.push_back(finish2);
            getMultiJumps(p, newseed, all_moves); //recursively call function with updated seed.
            f4=true;
        }
        if (t!=KING && !f3 && !f4){
            currentmove=Move(seed);
            all_moves.push_back(currentmove); //add move
        }
    }
    if (t==KING && !f1 && !f2 && !f3 && !f4){
        currentmove=Move(seed);
        all_moves.push_back(currentmove); //add move
    }
}

void GameBoard::printMoves(vector<Move> all_moves) {
    for (Move m: all_moves){
        for (array<int,2> coord: m.getSequence()){
            cout<<coord[0]<<","<<coord[1]<<"\t";
        }
        cout<<"\n";
    }
}

bool GameBoard::notRepeat(vector<array<int, 2>> &sequence, array<int, 2> &finish) {
    array<int,2> start=sequence.back();
    for (int i=1; i<sequence.size()-1; i++){
        if (sequence[i]==start && (sequence[i-1]==finish || sequence[i+1]==finish)) return false;
    }
    return true;
}

bool GameBoard::notBackTrack(vector<array<int, 2>> &sequence, array<int, 2> &finish) {
    return finish!=sequence.end()[-2];
}







