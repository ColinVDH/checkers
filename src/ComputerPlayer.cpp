#include "ComputerPlayer.h"

//constructor
ComputerPlayer::ComputerPlayer(GameBoard *b, Color color): Player(color){
    board=b;
}


//returns a random move, out of all possible (legal) moves
Move ComputerPlayer::getMove() {
    vector<Move> all_moves=getMoves();
    int index=randomInt(0, (int) all_moves.size()-1); //random int from 0 to the size of the vector - 1.
    return all_moves[index];
}


//gets all possible (legal) moves
vector<Move> ComputerPlayer::getMoves(){
    vector<Move> all_moves;
    static Move currentmove;
    vector<array<int,2>> sequence;
    for (int y = 0; y<8; y++) { //iterate through board coordinates
        for (int x = 0; x < 8; x++) {
            Piece * piece =board->getPiece(x,y);
            if (piece!=nullptr && piece->getColor()==getColor()){ //if there is a piece at this position
                if (piece->getType()==KING || piece->getColor()==LIGHT){ //checks if its the computer's color and the proper type to move down (light or king).
                    sequence = {{x,y},{x-2,y-2}};
                    if (board->isLegalJump(piece, sequence[0], sequence[1])) { //checks if jump is legal
                        getMultiJumps(piece, sequence, all_moves); //call multijump to append further jumps if possible
                    }
                    sequence = {{x,y},{x+2,y-2}};
                    if (board->isLegalJump(piece, sequence[0], sequence[1])) { //checks if jump is legal
                        getMultiJumps(piece, sequence, all_moves); //call multijump to append further jumps if possible
                    }
                }
                if (piece->getType()==KING || piece->getColor()==DARK){ //checks if its the computer's color and the proper type to move up (dark or king).
                    sequence = {{x,y},{x-2,y+2}};
                    if (board->isLegalJump(piece, sequence[0], sequence[1])) {  //checks if jump is legal
                        getMultiJumps(piece, sequence, all_moves); //call multijump to append further jumps if possible
                    }
                    sequence = {{x,y},{x+2,y+2}};
                    if (board->isLegalJump(piece, sequence[0], sequence[1])) { //checks if jump is legal
                        getMultiJumps(piece, sequence, all_moves); //call multijump to append further jumps if possible
                    }
                }
            }
        }
    }

    if (all_moves.empty()){  //no jump moves available , then you can now look for a regular move
        for (int y = 0; y<8; y++) { //iterate through board coordinates
            for (int x = 0; x < 8; x++) {
                Piece * piece =board->getPiece(x,y);
                if (piece!=nullptr && piece->getColor()==getColor()){
                    cout<<piece->getType();
                    if (piece->getType()==KING || piece->getColor()==LIGHT){ //checks if its the computer's color and the proper type to move down (light or king).
                        sequence = {{x,y},{x-1,y-1}};
                        if (board->isLegalSlide(piece, sequence[0], sequence[1])) { //checks if legal move
                            currentmove=Move(sequence);
                            all_moves.push_back(currentmove); //add move
                        }
                        sequence = {{x,y},{x+1,y-1}};
                        if (board->isLegalSlide(piece, sequence[0], sequence[1])) { //checks if legal move
                            currentmove=Move(sequence);
                            all_moves.push_back(currentmove); //add move
                        }
                    }
                    if (piece->getType()==KING || piece->getColor()==DARK){ //checks if its the computer's color and the proper type to move up (dark or king).
                        sequence = {{x,y},{x-1,y+1}};
                        if (board->isLegalSlide(piece, sequence[0], sequence[1])) { //checks if legal move
                            currentmove=Move(sequence);
                            all_moves.push_back(currentmove); //add move
                        }
                        sequence = {{x,y},{x+1,y+1}};
                        if (board->isLegalSlide(piece, sequence[0], sequence[1])) { //checks if legal move
                            currentmove=Move(sequence);
                            all_moves.push_back(currentmove); //add move
                        }
                    }
                }
            }
        }
    }
    printMoves(all_moves);
    return all_moves; //return all possible legal moves
}

//recursive function that takes a current seed (part of a jump move) and looks if another jump can be added on. If not, it adds the complete jump sequence to "all_moves" vector.
void ComputerPlayer::getMultiJumps(Piece * p, vector<array<int,2>> seed, vector<Move> &all_moves){

    Color c=p->getColor();
    Type t=p->getType();

    array<int,2> start=seed.back(); //the start of the next jump is the last coordinate in the "seed"
    array<int,2> finish; //the finish is unassigned.
    static Move currentmove;
    vector<array<int,2>> newseed;


    if (t==KING || c==LIGHT){ //checks the type and the color of the piece (computer piece) performing the jump
        finish={start[0]-2, start[1]-2};
        if (board->isLegalJump(p,start,finish)){
            newseed=seed;
            newseed.push_back(finish);
            getMultiJumps(p,newseed, all_moves); //recursively call function with updated seed.
        }
        finish={start[0]+2, start[1]-2};
        if (board->isLegalJump(p,start,finish)){
            newseed=seed;
            newseed.push_back(finish);
            getMultiJumps(p, newseed, all_moves); //recursively call function with updated seed.
        }
        else{
            currentmove=Move(seed);
            all_moves.push_back(currentmove); //add move
        }
    }

    if (t==KING || c==DARK){ //checks the type and the color of the piece (computer piece) performing the jump. Same as above but for a dark piece.
        finish={start[0]-2, start[1]+2};
        if (board->isLegalJump(p,start,finish)){
            newseed = seed;
            newseed.push_back(finish);
            getMultiJumps(p, newseed, all_moves); //recursively call function with updated seed.
        }
        finish={start[0]+2, start[1]+2};
        if (board->isLegalJump(p,start,finish)){
            newseed = seed;
            newseed.push_back(finish);
            getMultiJumps(p, newseed, all_moves); //recursively call function with updated seed.
        }
        else{
            currentmove=Move(seed);
            all_moves.push_back(currentmove); //add move
        }
    }
}

//returns true if human and false if computer.
bool ComputerPlayer::isHuman() {
    return false;
}

//helper function to generate a random integer in the interval (first, last).
int ComputerPlayer::randomInt(int first, int last) {
    unsigned int N = (last - first <= RAND_MAX) ? (last - first + 1U) : (RAND_MAX + 1U);
    unsigned int x = (RAND_MAX + 1U) / N;
    unsigned int y = x * N;
    unsigned int r;
    do {
        r = (unsigned int) rand();
    } while (r >= y);
    return r / x + first;
}

void ComputerPlayer::printMoves(vector<Move> moves) {
    for (Move m: moves){
        while (m.hasNext()){
            array<int,2> coord=m.getNext();
            cout<<coord[0]<<","<<coord[1]<<" ";
        }
        cout<<endl;

    }

}







