//
// Created by colin on 11/12/16.
//

#ifndef CHECKERS_PIECE_H
#define CHECKERS_PIECE_H

#include <iostream>
using namespace std;

enum Type: bool {NORMAL, KING};
enum Color: bool {DARK, LIGHT};
inline ostream& operator<<(ostream &strm, const Color &c) {
    switch(c){
        case DARK: return strm<<"Red";
        case LIGHT: return strm<<"Blue";
    }
}

class Piece {
private:
    Type type;
    Color color;
public:
    Piece(Color c);
    Piece(Type t, Color c);
    Color getColor();
    Type getType();

    void setType(Type type);
};


#endif //CHECKERS_PIECE_H
