//
// Created by colin on 11/10/16.
//

#include "HumanPlayer.h"
#include <sstream>
using namespace std;

//constructor
HumanPlayer::HumanPlayer(Color color): input(""), Player(color){}

//return the current input
string HumanPlayer::getInput() {
    return input;
}
//set the current input by getting it from the user
void HumanPlayer::setInput(){
    string i;
    getline(cin, i);
    input=i;
}
//checks if the user has valid input (of the form "a1 b2" etc...)
bool HumanPlayer::hasValidInput(){
    if (input.length()==0) return false; //no input
    if (input=="q") return true; //quit character
    vector<string> split_input = split(input,' '); //split input by whitespace into a vector of strings.
    if (split_input.size()<2) return false;
    for (auto const& item : split_input) {
        if (!((item.length()==2)
              && 0<=(item[0]-'a') && (item[0]-'a')<=7
              && 0<=(item[1]-'1') && (item[1]-'1')<=7)){ //checks if the first part of each word is a letter from a to h and the second part is a number from 1 to 8
            return false;
        }
    }
    return true;
}
//returns the human players move
Move HumanPlayer::getMove() {
    vector<array<int,2>> sequence;
    if (!hasValidInput()) return Move(); //returns an empty move if there is no valid input
    else{
        vector<string> split_input = split(input,' '); //split input by whitespace into a vector of strings.
        for (auto const& item : split_input){
            int x=item[0]-'a'; //convert the labels to actual x coordinates
            int y=item[1]-'1'; //convert the label to actual y coordinate
            sequence.push_back({x,y}); //add to the move sequence
        }
    }
    return Move(sequence); //return the move
}

//helper method to split a string into a vector of strings, given a delimiter
vector<string> HumanPlayer::split(string s, char delim) {
    stringstream ss; //string stream
    vector<string> elements={};
    ss.str(s);
    string item;
    while (getline(ss, item, delim)){
        elements.push_back(item);
    }
    return elements;
}
//checks if human
bool HumanPlayer::isHuman(){
    return true;
}








