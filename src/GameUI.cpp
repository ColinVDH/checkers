#include "GameUI.h"
#include <iostream>

//constructor
GameUI::GameUI() {
    board=nullptr; //board and current player currently null
    current=nullptr;
}

//shows the footer on the game screen
void GameUI::showFooter() {
    if (current->isHuman()) cout<<"Enter move:";
}

//shows the board. If flipped, the board will be rotated 180 degrees and displayed.
void GameUI::showBoard(bool flipped) {
    string DE = "\033[40m   \033[49m"; // Empty dark tile
    string LE = "\033[47m   \033[49m"; // Empty light tile
    string WP = "\033[1;34;40m \u25CF \033[0;49m"; // White Piece
    string RP = "\033[1;31;40m \u25CF \033[0;39;49m"; // Red Piece
    string WK = "\033[1;34;40m \u265A \033[0;49m"; // White King
    string RK = "\033[1;31;40m \u265A \033[0;39;49m"; // Red King


    if (flipped){
        string result = "";


        for (int i=0; i<8; i++){ //iterate through board positions
            result+=to_string(i+1);
            for (int j=7; j>=0; j--){
                if (board->getPiece(j,i)==nullptr)
                    result+= ((i+j)%2==0) ? DE: LE; //display either dark empty or light empty (tile).
                else if (board->getPiece(j,i)->getColor()==DARK)
                    result+= (board->getPiece(j,i)->getType()==NORMAL) ? RP: RK; //display either red piece or red king
                else result+= (board->getPiece(j,i)->getType()==NORMAL) ? WP: WK; //display either white piece or white king
            }
            result+=to_string(i+1)+"\n"; //add the row number and a newline.
        }
        cout<<endl;
        cout<<" h  g  f  e  d  c  b  a "<<endl; //print column labels above
        cout<<result; //board string
        cout<<" h  g  f  e  d  c  b  a "<<endl; //print column labels below
        cout<<endl;
    }
    else{
        string result = "";


        for (int i=7; i>=0; i--){ //iterate through board positions
            result+=to_string(i+1);
            for (int j=0; j<8; j++){
                if (board->getPiece(j,i)==nullptr)
                    result+= ((i+j)%2==0) ? DE: LE; //display either dark empty or light empty (tile)
                else if (board->getPiece(j,i)->getColor()==DARK)
                    result+= (board->getPiece(j,i)->getType()==NORMAL) ? RP: RK; //display either red piece or red king
                else result+= (board->getPiece(j,i)->getType()==NORMAL) ? WP: WK; //display either white piece or white king
            }
            result+=to_string(i+1)+"\n"; //add the row number and a newline
        }
        cout<<endl;
        cout<<" a  b  c  d  e  f  g  h "<<endl;//print column labels above
        cout<<result; //board string
        cout<<" a  b  c  d  e  f  g  h "<<endl; //print column labels below
        cout<<endl;
    }
}

//display header
void GameUI::showHeader() {
    if (current->isHuman()) cout<< current->getColor() << " player";
    else cout<< "Computer "<<"("<<current->getColor()<<")";
    cout<<" turn."<<endl;
}

//update board, with options to show the footer and to show the board flipped.
void GameUI::updateBoard(bool footer, bool flipped) {
    clearScreen();
    showHeader();
    showBoard(flipped);
    if (footer) showFooter();
}

//update the board, option to show footer, with board in regular position.
void GameUI::updateBoard(bool footer){
    updateBoard(footer,false);
}


//display main menu screen
void GameUI::mainMenu() {
    clearScreen();
    cout<<"\n"
            "\n"
            " ██████╗██╗  ██╗███████╗ ██████╗██╗  ██╗███████╗██████╗ ███████╗\n"
            "██╔════╝██║  ██║██╔════╝██╔════╝██║ ██╔╝██╔════╝██╔══██╗██╔════╝\n"
            "██║     ███████║█████╗  ██║     █████╔╝ █████╗  ██████╔╝███████╗\n"
            "██║     ██╔══██║██╔══╝  ██║     ██╔═██╗ ██╔══╝  ██╔══██╗╚════██║\n"
            "╚██████╗██║  ██║███████╗╚██████╗██║  ██╗███████╗██║  ██║███████║\n"
            " ╚═════╝╚═╝  ╚═╝╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝\n"
            "                                                                \n"
            ""<<endl;
    cout<<"1. Player vs. Player"<<endl;
    cout<<"2. Player vs. Computer"<<endl;
    cout<<"3. Computer vs. Computer"<<endl<<endl;
    cout<<"Select:";
}

//print invalid input message
void GameUI::InvalidInputMessage() {
    cout<<"ERROR: Invalid Input!"<<endl;
}
//print illegal move message
void GameUI::IllegalMoveMessage() {
    cout<<"ERROR: Illegal Move!"<<endl;
}
//print game over screen
void GameUI::endGame(GameMode gm, Player * winner) {
    clearScreen();
    cout<<"\n"
            "\n"
            " ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ ██╗\n"
            "██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗██║\n"
            "██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝██║\n"
            "██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗╚═╝\n"
            "╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║██╗\n"
            " ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝╚═╝\n"
            "                                                                             \n"
            ""<<endl;
    if (gm==PLAYERCOMPUTER && !winner->isHuman()) cout<<"Computer wins!"<<endl;
    else if (gm==PLAYERCOMPUTER && winner->isHuman()) cout<<"You win!"<<endl;
    else cout<<winner->getColor()<<" wins!"<<endl;
    cout<<"Play again? (y/n) ";
}

//updates UI with the board and current player pointers.
void GameUI::initUI(GameBoard *b, Player *p) {
    board=b;
    current=p;
}

//clears the screen
void GameUI::clearScreen(){
    cout << string( 100, '\n' );
}

//updates the current player pointer
void GameUI::updatePlayer(Player *p) {
    current=p;
}




