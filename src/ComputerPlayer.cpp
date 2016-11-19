#include "ComputerPlayer.h"



//constructor
ComputerPlayer::ComputerPlayer(GameBoard *b, Color color): Player(color){
    board=b;
}


//returns a random move, out of all possible (legal) moves
Move ComputerPlayer::getMove() {
    vector<Move> all_moves=getMoves();
    int index=randomInt(0, all_moves.size()-1); //random int from 0 to the size of the vector - 1.
    return all_moves[index];
}


//gets all possible (legal) moves
vector<Move> ComputerPlayer::getMoves(){
    vector<Move> all_moves;
    Move currentmove;
    for (int y = 0; y<8; y++) { //iterate through board coordinates
        for (int x = 0; x < 8; x++) {
            Piece * piece =board->getPiece(x,y);
            if (piece!=nullptr){ //if there is a piece at this position
                if ((piece->getType()==KING || piece->getColor()==LIGHT) && piece->getColor()==getColor()){ //checks if its the computer's color and the proper type to move down (light or king).
                    vector<array<int,2>> sequence = {{x,y},{x-2,y-2}};
                    if (board->isLegalJump(piece, sequence[0], sequence[1])) {
                        getMultiJumps(piece, sequence, all_moves);
                    }
                    sequence = {{x,y},{x+2,y-2}};
                    if (board->isLegalJump(piece, sequence[0], sequence[1])) {
                        getMultiJumps(piece, sequence, all_moves);
                    }
                }
                if ((piece->getType()==KING || piece->getColor()==DARK) && piece->getColor()==getColor()){ //checks if its the computer's color and the proper type to move down (dark or king).
                    vector<array<int,2>> sequence = {{x,y},{x-2,y+2}};
                    if (board->isLegalJump(piece, sequence[0], sequence[1])) {
                        getMultiJumps(piece, sequence, all_moves);
                    }
                    sequence = {{x,y},{x+2,y+2}};
                    if (board->isLegalJump(piece, sequence[0], sequence[1])) {
                        getMultiJumps(piece, sequence, all_moves);
                    }
                }
            }
        }
    }

    if (all_moves.empty()){  //no jump moves available
        for (int y = 0; y<8; y++) {
            for (int x = 0; x < 8; x++) {
                Piece * piece =board->getPiece(x,y);
                if (piece!=nullptr){
                    if ((piece->getType()==KING || piece->getColor()==LIGHT)&& piece->getColor()==getColor()){
                        vector<array<int,2>> sequence = {{x,y},{x-1,y-1}};
                        if (board->isLegalSlide(piece, sequence[0], sequence[1])) {
                            currentmove= Move(sequence);
                            all_moves.push_back(currentmove);
                        }
                        sequence = {{x,y},{x+1,y-1}};
                        if (board->isLegalSlide(piece, sequence[0], sequence[1])) {
                            currentmove= Move(sequence);
                            all_moves.push_back(currentmove);
                        }
                    }
                    if ((piece->getType()==KING || piece->getColor()==DARK)&& piece->getColor()==getColor()){
                        vector<array<int,2>> sequence = {{x,y},{x-1,y+1}};
                        if (board->isLegalSlide(piece, sequence[0], sequence[1])) {
                            currentmove= Move(sequence);
                            all_moves.push_back(currentmove);
                        }
                        sequence = {{x,y},{x+1,y+1}};
                        if (board->isLegalSlide(piece, sequence[0], sequence[1])) {
                            currentmove= Move(sequence);
                            all_moves.push_back(currentmove);
                        }
                    }
                }
            }
        }
    }
    return all_moves;
}


void ComputerPlayer::getMultiJumps(Piece * p, vector<array<int,2>> seed, vector<Move> &all_moves){

    Color c=p->getColor();
    Type t=p->getType();

    array<int,2> start=seed.back();
    array<int,2> finish;
    Move currentmove;

    if (t==KING || c==LIGHT){
        finish={start[0]-2, start[1]-2};
        if (board->isLegalJump(p,start,finish)){
            vector<array<int,2>> newseed = seed;
            newseed.push_back(finish);
            getMultiJumps(p,newseed, all_moves);
        }
        finish={start[0]+2, start[1]-2};
        if (board->isLegalJump(p,start,finish)){
            vector<array<int,2>> newseed = seed;
            newseed.push_back(finish);
            getMultiJumps(p, newseed, all_moves);
        }
        else{
            currentmove=Move(seed);
            all_moves.push_back(currentmove);
        }
    }

    if (t==KING || c==DARK){
        finish={start[0]-2, start[1]+2};
        if (board->isLegalJump(p,start,finish)){
            vector<array<int,2>> newseed = seed;
            newseed.push_back(finish);
            getMultiJumps(p, newseed, all_moves);
        }
        finish={start[0]+2, start[1]+2};
        if (board->isLegalJump(p,start,finish)){
            vector<array<int,2>> newseed = seed;
            newseed.push_back(finish);
            getMultiJumps(p, newseed, all_moves);
        }
        else{
            currentmove=Move(seed);
            all_moves.push_back(currentmove);
        }
    }
}


bool ComputerPlayer::isHuman() {
    return false;
}

int ComputerPlayer::randomInt(int first, int last) {
    unsigned int N = (last - first <= RAND_MAX) ? (last - first + 1U) : (RAND_MAX + 1U);
    unsigned int x = (RAND_MAX + 1U) / N;
    unsigned int y = x * N;
    unsigned int r;
    do {
        r = rand();
    } while (r >= y);
    return r / x + first;
}






