#include "GameUI.h"
#include <iostream>

//constructor
GameUI::GameUI() {
    board=nullptr; //board and current player currently null
    current=nullptr;
}

//shows the footer on the game screen
void GameUI::showFooter() {
    if (current->isHuman()){
        cout<<"Enter a sequence of coordinates to move a piece\n"
            "  e.g., 'F1 D4 B1' would be a double jump\n";
        cout<< current->getColor() << " Player Move:";
    }
    else cout<< "Computer "<<"("<<current->getColor()<<") Turn...";
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
        cout<<"  H  G  F  E  D  C  B  A "<<endl; //print column labels above
        cout<<result; //board string
        cout<<"  H  G  F  E  D  C  B  A "<<endl; //print column labels below
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
        cout<<"  A  B  C  D  E  F  G  H "<<endl;//print column labels above
        cout<<result; //board string
        cout<<"  A  B  C  D  E  F  G  H "<<endl; //print column labels below
        cout<<endl;
    }
}

//display header
void GameUI::showHeader() {
    if (gm==TWOPLAYER) cout<<"CHECKERS: Two-Player Mode        Turn: ";
    else if (gm==PLAYERCOMPUTER) cout<<"CHECKERS: One-Player Mode        Turn: ";
    else if (gm==TWOCOMPUTER) cout<<"CHECKERS: Demo Mode        Turn: ";
    cout<<turn_number<<endl;
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

    cout<<"Main Menu Options:\n"
            "  1. Play Checkers with a computer opponent\n"
            "  2. Play Checkers with another person\n"
            "  3. Game Demo \n"
            "  4. Quit\n";
    cout<<"Enter a number to choose:";
}

//print invalid input message
void GameUI::InvalidInputMessage() {
    cerr<<"ERROR: Invalid input provided"<<endl;
}
//print illegal move message
void GameUI::IllegalMoveMessage() {
    cerr<<"ERROR: Illegal move attempted"<<endl;
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
    cout<<"Would you like to play again? (y or n) ";
}

//updates UI with the board and current player pointers.
void GameUI::initUI(GameBoard *b, Player *p, GameMode g) {
    board=b;
    current=p;
    gm=g;
    turn_number=1;
}

//clears the screen
void GameUI::clearScreen(){
    cout << string( 100, '\n' );
}

//updates the current player pointer
void GameUI::updatePlayer(Player *p) {
    current=p;
}

void GameUI::incrementTurn() {
    turn_number++;
}




