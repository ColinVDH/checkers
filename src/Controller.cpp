#include <iostream>
#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono;
#include "Controller.h"

//constructor
Controller::Controller(){
    ui=GameUI(); //initialize the UI.
}

void Controller::start(){
    do {
        srand(time(NULL)); //seed for random number generator (for picking the dark player if Player vs. Computer mode selected).
        ui.mainMenu(); //display main menu

        GameMode gm = getGameMode(); //returns the user inputted game mode.
        if (gm==TWOPLAYER) { //two player game
            board = new GameBoard();
            dark = new HumanPlayer(DARK);
            light = new HumanPlayer(LIGHT);
        }

        if (gm==PLAYERCOMPUTER){ //player vs. computer game
            if (rand()%2==0){ //randomly decide who will play as dark (go first).
                board=new GameBoard();
                dark=new ComputerPlayer(board, DARK);
                light=new HumanPlayer(LIGHT);
            }
            else{
                board=new GameBoard();
                dark=new HumanPlayer(DARK);
                light=new ComputerPlayer(board, LIGHT);
           }
         }

        if (gm==TWOCOMPUTER){
            if (rand()%2==0){ //randomly decide who will play as dark (go first).
                board=new GameBoard();
                dark=new ComputerPlayer(board, DARK);
                light=new ComputerPlayer(board, LIGHT);
            }
            else{
                board=new GameBoard();
                dark=new ComputerPlayer(board, DARK);
                light=new ComputerPlayer(board, LIGHT);
            }
        }
        current=dark; //dark always starts
        ui.initUI(board, current); //provides UI with the board and the current player.


        while (!checkLose()){ //game Loop runs until somebody loses.
            bool legalmove =false;
            while (!legalmove){ //loops until a legal move is provided
                if (gm==TWOPLAYER || (gm==PLAYERCOMPUTER && current->isHuman())) {
                    if (current == light) {
                        ui.updateBoard(true, true); //updates the board in a flipped position so that light is on bottom, show footer.
                        getValidInput(true); //get a valid move from the user.
                    } else {
                        ui.updateBoard(true);  //updates the board in a normal position (dark on bottom), show footer
                        getValidInput(false); //get a valid move from the user
                    }
                }
                else if (gm==PLAYERCOMPUTER && !current->isHuman()){ //computer player --- always update the board such that the computer is on top.
                    if (current== dark) ui.updateBoard(true, true);  //update the board in flipped position
                    else ui.updateBoard(true); //update board in normal position
                    pause(1000);
                }
                else if (gm==TWOCOMPUTER) {
                    ui.updateBoard(true);
                    pause(1000);
                }

                Move move = current->getMove(); //get move from current player (computer or human).
                if (!isLegalMove(move)){ //check if legal
                    showError(ILLEGAL, 1000); //show illegal message for 1 second
                }
                else {
                    legalmove=true;
                    executeMove(move); //execute the move
                }
            }
            current==dark ? current=light:current=dark; //switch the current player
            ui.updatePlayer(current); //update the board to fit perspective of current player.
        } //end of game loop
        current==dark ? ui.endGame(gm, light) : ui.endGame(gm, dark);  //display game over screen

        delete this->board;
        delete this->dark;
        delete this->light; //delete the board and both player objects.

    } while (playAgain()); //check if the user wants to play again. If so, repeat.
}

//gets the user input and returns the game mode.
GameMode Controller::getGameMode() {
    string i = getInput();
    if (i=="q") exit(0);
    else if (i=="1") return TWOPLAYER;
    else if (i=="2") return PLAYERCOMPUTER;
    else if (i=="3") return TWOCOMPUTER;
    else{
        showError(INVALID,1000); //show invalid error message for 1 second
        ui.mainMenu();//redisplay main menu
        return getGameMode(); //recursively call function if there is illegal input
    }
}

//gets the input from the user and returns in a string.
string Controller::getInput() {
    string i;
    getline(cin, i, '\n');
    return i;
}

//display a error (illegal or invalid) in the UI.
void Controller::showError(Error e, int time){
    if (e==INVALID){
        ui.InvalidInputMessage();
    }
    else if (e==ILLEGAL){
        ui.IllegalMoveMessage();
    }
    pause(time); //pause for a specified length of time after displaying the error.
}

//pause for a specified length of time in milliseconds. If 0 is given, the function with wait for a key press.
void Controller::pause(int time) {
    if (time==0) cin.get();
    else sleep_for(milliseconds(time));
}

//checks if the input move is legal
bool Controller::isLegalMove(Move chosen) {
    vector<Move> allmoves=board->getMoves(current->getColor());
    for (Move m: allmoves){
        if (chosen == m) return true;
    }
    return false;
}

//checks if user wants to play again
bool Controller::playAgain() {
    string i;
    while (true) {
        i = getInput();
        if (i == "q") exit(0);
        else if (i == "y") {
            return true;
        } else if (i == "n") { //functionally the same as "q"
            return false;
        } else showError(INVALID, 1000); //invalid input error
        //ui.gameOver();
    }
}

//checks if loss has occurred by checking if the current player has moves or pieces remaining.
bool Controller::checkLose() {
    Color current_color=current->getColor();
    return (!board->movesRemaining(current_color) || !board->piecesRemaining(current_color));
}

//perform the input move action
void Controller::executeMove(Move m) {
    Piece * piece= board->getPiece(m.getFirst());
    array<int,2> start=m.getFirst(), finish=m.getNext(); //get the first move sequence
    if (m.getLength()==2){ //checks if move is length 2
        if (board->isLegalSlide(piece, start,finish)) board->movePiece(start,finish);
        else if (board->isLegalJump(piece, start,finish)) { //checks if it is a jump, so that the jumped piece will be removed
            board->removePiece({(finish[0]+start[0])/2,(finish[1]+start[1])/2});
            board->movePiece(start,finish);
        }
    }
    else{//multijump
        board->removePiece({(finish[0]+start[0])/2,(finish[1]+start[1])/2}); //remove piece in between the current start and finish.
        board->movePiece(start,finish); //move piece
        while (m.hasNext()){ //while there are still remaining jumps
            start=finish; //update start and finish
            finish=m.getNext();
            board->removePiece({(finish[0]+start[0])/2,(finish[1]+start[1])/2}); //remove the jumped piece
            board->movePiece(start,finish);
     /*       if ((current == light && current->isHuman()) || (current==dark && !current->isHuman())) ui.updateBoard(false, true); //update board (no footer and flipped).
            else ui.updateBoard(false); //update board (no footer).
            pause(1000); //wait 1 second before going to next jump (animates move sequence).*/
        }
    }
}
//get a valid input
void Controller::getValidInput(bool flipped) {
    if (current->isHuman()){ //checks if current is human
        static_cast<HumanPlayer*>(current)->setInput(); //set the input (user input)
        while (!static_cast<HumanPlayer*>(current)->hasValidInput()){ //checks if the input is not valid
            showError(INVALID, 1000); //show error
            if (flipped) ui.updateBoard(true, true); //update board (flipped)
            else ui.updateBoard(true); //update board
            static_cast<HumanPlayer*>(current)->setInput(); // set input again (user input).
        }
        if (static_cast<HumanPlayer*>(current)->getInput()=="q") exit(0); //user quit request
    }
}

















