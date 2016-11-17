//
// Created by colin on 11/11/16.
//

#include "GameUI.h"
#include <iostream>

GameUI::GameUI() {
    board=nullptr;
    current=nullptr;
}

void GameUI::showFooter() {
    if (current->isHuman()) cout<<"Enter move:";
}

void GameUI::showBoardFlipped(){
    // "\033" is ESC while the "[##m" part are ANSI codes and "\u25CF" is a circle
    string DE = "\033[40m   \033[49m"; // Empty dark tile
    string LE = "\033[47m   \033[49m"; // Empty light tile
    string WP = "\033[1;34;40m \u25CF \033[0;49m"; // White Piece
    string RP = "\033[1;31;40m \u25CF \033[0;39;49m"; // Red Piece

    string result = "";


    for (int i=0; i<8; i++){
        result+=to_string(i+1);
        for (int j=7; j>=0; j--){
            if (board->getPiece(j,i)==nullptr){
                result+= ((i+j)%2==0) ? DE: LE;
            }
            else result+= (board->getPiece(j,i)->getColor()==DARK) ? RP : WP;
        }
        result+=to_string(i+1)+"\n";
    }
    cout<<" h  g  f  e  d  c  b  a "<<endl;
    cout<<result;
    cout<<" h  g  f  e  d  c  b  a "<<endl;

}

void GameUI::showBoard() {

    // "\033" is ESC while the "[##m" part are ANSI codes and "\u25CF" is a circle
    string DE = "\033[40m   \033[49m"; // Empty dark tile
    string LE = "\033[47m   \033[49m"; // Empty light tile
    string WP = "\033[1;34;40m \u25CF \033[0;49m"; // White Piece
    string RP = "\033[1;31;40m \u25CF \033[0;39;49m"; // Red Piece

    string result = "";


    for (int i=7; i>=0; i--){
        result+=to_string(i+1);
        for (int j=0; j<8; j++){
            if (board->getPiece(j,i)==nullptr){
                result+= ((i+j)%2==0) ? DE: LE;
            }
            else result+= (board->getPiece(j,i)->getColor()==DARK) ? RP : WP;
        }
        result+=to_string(i+1)+"\n";
    }
    cout<<" a  b  c  d  e  f  g  h "<<endl;
    cout<<result;
    cout<<" a  b  c  d  e  f  g  h "<<endl;
}

void GameUI::showHeader() {
    if (current->isHuman()) cout<< current->getColor() << " player";
    else cout<< "Computer "<<"("<<current->getColor()<<")";
    cout<<" turn."<<endl;
}


void GameUI::updateBoard(bool footer, bool flipped) {
    clearScreen();
    showHeader();
    flipped ? showBoardFlipped() : showBoard();
    if (footer) showFooter();
}

void GameUI::updateBoard(bool footer){
    updateBoard(footer,false);
}



void GameUI::mainMenu() {
    clearScreen();
    cout<<"Welcome to Checkers"<<endl<<endl;
    cout<<"1. Player vs. Player"<<endl;
    cout<<"2. Player vs. Computer"<<endl<<endl;
    cout<<"Select:";
}


void GameUI::InvalidInputMessage() {
    cout<<"ERROR: Invalid Input!"<<endl;
}

void GameUI::IllegalMoveMessage() {
    cout<<"ERROR: Illegal Move!"<<endl;
}

void GameUI::endGame() {
    clearScreen();
    cout<<"Game Over!"<<endl<<endl;
    cout<<"Play again? (y/n) ";
}

void GameUI::initUI(GameBoard *b, Player *p) {
    board=b;
    current=p;
}

void GameUI::clearScreen(){
    cout << string( 100, '\n' );
}

void GameUI::updatePlayer(Player *p) {
    current=p;
}




