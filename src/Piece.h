//
// Created by colin on 11/12/16.
//

#ifndef CHECKERS_PIECE_H
#define CHECKERS_PIECE_H

#include <iostream>
using namespace std;

enum Type: bool {NORMAL, KING}; // boolean enum for the type of a piece (normal or king).
enum Color: bool {DARK, LIGHT}; //boolean enum for the color of piece (dark or light).

//overridding << operator for enum Color
inline ostream& operator<<(ostream &strm, const Color &c) {
    switch(c){
        case DARK: return strm<<"Red";
        case LIGHT: return strm<<"Blue";
    }
}

class Piece {
public:
    Piece(Color c);
    Piece(Type t, Color c);
    Color getColor();
    Type getType();
    void setType(Type type);

private:
    Type type; //type of the piece
    Color color; //color of the piece
};


#endif //CHECKERS_PIECE_H
