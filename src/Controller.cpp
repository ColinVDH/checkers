//
// Created by colin on 11/10/16.
//

#include <iostream>
#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono;
#include "Controller.h"
/*#include <vector>
using namespace std;*/

Controller::Controller(){
    ui=GameUI();
}

void Controller::start(){
    do {
     ui.mainMenu();

    GameMode gm = getGameMode();
    if (gm==TWOPLAYER) {
        board = new GameBoard();
        dark = new HumanPlayer(DARK);
        light = new HumanPlayer(LIGHT);
    }

/*    if (gm==PLAYERCOMPUTER){
        if (rand()%2==0){
            board=new GameBoard();
            dark=new ComputerPlayer(DARK);
            light=new HumanPlayer(LIGHT);
            computerDark=true;
        }
        else{
            board=new GameBoard();
            dark=new HumanPlayer(DARK);
            light=new ComputerPlayer(LIGHT);
       }
     }*/
        current=dark;
        ui.initUI(board, current);


     while (!checkLose()){
         bool legalmove =false;
         while (!legalmove){
             if ((gm==TWOPLAYER && current==light)
                 || (gm==PLAYERCOMPUTER && !dark->isHuman())){
                 ui.updateBoard(true, true);
                 getValidInput(true);
             }
             else{
                 ui.updateBoard(true);
                 getValidInput(false);
             }
             Move move = current->getMove();
             if (!isLegalMove(move)){
                 showError(ILLEGAL, 500);
             }
             else {
                 legalmove=true;
                 executeMove(move);
             }
         }
         current==dark ? current=light:current=dark;
         ui.updatePlayer(current);
     }
     ui.endGame();

     delete board; delete dark; delete light;

     } while (playAgain());
}

GameMode Controller::getGameMode() {
    string i = getInput();
    if (i=="q") exit(0);
    else if (i=="1") return TWOPLAYER;
    else if (i=="2") return PLAYERCOMPUTER;
    else{
        showError(INVALID,500);
        ui.mainMenu();
        return getGameMode();
    }
}

string Controller::getInput() {
    string i;
    getline(cin, i, '\n');
    return i;
}

void Controller::showError(Error e, int time){
    if (e==INVALID){
        ui.InvalidInputMessage();
    }
    else if (e==ILLEGAL){
        ui.IllegalMoveMessage();
    }
    pause(time);
}


void Controller::pause(int time) {
    if (time==0) cin.get();
    else sleep_for(milliseconds(time));
}

bool Controller::isLegalMove(Move m) {
    array<int, 2> start = m.getFirst(), finish = m.getNext();
    if (board->getPiece(start)==nullptr){
        return false;
    }
    Piece * piece =  board->getPiece(start);
    Color color = piece->getColor();
    if (color == current->getColor()) {
        if (m.getLength()==2) {
            if (board->isLegalSlide(start, finish) && !board->jumpsAvailable(current->getColor())){
                return true;
            }
            if (board->isLegalJump(start,finish)){
                return true;
            }
            return false;
        }
        else{
            while (m.hasNext()){
                start=finish;
                finish=m.getNext();
                if (!board->isLegalJump(start,finish)){
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

bool Controller::playAgain() {
    string i;
    while (true) {
        i = getInput();
        if (i == "q") exit(0);
        else if (i == "y") {
            return true;
        } else if (i == "n") {
            return false;
        } else showError(INVALID, 1);
        //ui.gameOver();
    }
}

bool Controller::checkLose() {
    Color current_color=current->getColor();
    return (!board->movesRemaining(current_color) || !board->piecesRemaining(current_color));
}

void Controller::executeMove(Move m) {
    array<int,2> start=m.getFirst(), finish=m.getNext();
    if (m.getLength()==2){
        if (board->isLegalSlide(start,finish)) board->movePiece(start,finish);
        else if (board->isLegalJump(start,finish)) {
            board->removePiece({(finish[0]+start[0])/2,(finish[1]+start[1])/2});
            board->movePiece(start,finish);
        }
    }

    while (m.hasNext()){
        start=finish;
        finish=m.getNext();
        board->removePiece({(finish[0]+start[0])/2,(finish[1]+start[1])/2});
        board->movePiece(start,finish);
        //ui.updateBoard(false);
    }

}

void Controller::getValidInput(bool flipped) {
    if (current->isHuman()){
        static_cast<HumanPlayer*>(current)->setInput();
        while (!static_cast<HumanPlayer*>(current)->hasValidInput()){
            showError(INVALID, 500);
            if (flipped) ui.updateBoard(true, true);
            else ui.updateBoard(true);
            static_cast<HumanPlayer*>(current)->setInput();
        }
        if (static_cast<HumanPlayer*>(current)->getInput()=="q") exit(0);
    }
}










