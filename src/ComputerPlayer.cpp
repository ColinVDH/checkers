#include "ComputerPlayer.h"

//constructor
ComputerPlayer::ComputerPlayer(GameBoard *b, Color color): Player(color){
    board=b;
}


//returns a random move, out of all possible (legal) moves
Move ComputerPlayer::getMove() {
    vector<Move> all_moves=board->getMoves(getColor());
    int index=randomInt(0, (int) all_moves.size()-1); //random int from 0 to the size of the vector - 1.
    return all_moves[index];
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








