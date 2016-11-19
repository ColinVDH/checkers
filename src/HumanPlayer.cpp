//
// Created by colin on 11/10/16.
//

#include "HumanPlayer.h"
#include <iostream>
#include <sstream>
using namespace std;

HumanPlayer::HumanPlayer(Color color): input(""), Player(color){}

string HumanPlayer::getInput() {
    return input;
}

void HumanPlayer::setInput(){
    string i;
    getline(cin, i);
    input=i;
}

bool HumanPlayer::hasValidInput(){
    if (input.length()==0) return false;
    if (input=="q") return true;
    vector<string> split_input = split(input,' ');
    if (split_input.size()<2) return false;
    for (auto const& item : split_input) {
        if (!((item.length()==2)
              && 0<=(item[0]-'a') && (item[0]-'a')<=7
              && 0<=(item[1]-'1') && (item[1]-'1')<=7)){
            return false;
        }
    }
    return true;
}

Move HumanPlayer::getMove() {
    vector<array<int,2>> sequence;
    if (!hasValidInput()) return Move();
    else{
        vector<string> split_input = split(input,' ');
        for (auto const& item : split_input){
            int x=item[0]-'a';
            int y=item[1]-'1';
            sequence.push_back({x,y});
        }
    }
    return Move(sequence);
}

vector<string> HumanPlayer::split(string s, char delim) {
    stringstream ss;
    vector<string> elements={};
    ss.str(s);
    string item;
    while (getline(ss, item, delim)){
        elements.push_back(item);
    }
    return elements;
}

bool HumanPlayer::isHuman(){
    return true;
}








