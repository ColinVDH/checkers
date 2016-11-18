//
// Created by colin on 11/16/16.
//

#ifndef CHECKERS_TREENODE_H
#define CHECKERS_TREENODE_H

#include <vector>
#include <array>
#include <cmath>
#include <algorithm>
#include <bitset>
#include "GameBoard.h"
#include "Move.h"


using namespace std;

class State{

public:
    Color playerMoved;
    Color currentPlayer;
    GameBoard board;


    State(GameBoard * b, Color color) : board(*b){
        playerMoved = (Color)(bool)!color;
        currentPlayer=color;
    }

    State(const State &obj){
        playerMoved=obj.playerMoved;
        currentPlayer=obj.currentPlayer;
        board=obj.board;
    }

    State& operator=(State tmp){
        swap(playerMoved, tmp.playerMoved);
        swap(currentPlayer, tmp.currentPlayer);
        swap(board, tmp.board);
        return *this;
    }

/*    State Clone(){
        State newstate=State(board, currentPlayer);
        return newstate;
    }*/

    vector<Move> getMoves(){
        vector<Move> all_moves;
        Move currentmove;
        for (int y = 0; y<8; y++) {
            for (int x = 0; x < 8; x++) {
                Piece * piece =board.getPiece(x,y);
                if (piece!=nullptr){
                    if ((piece->getType()==KING || piece->getColor()==LIGHT) && piece->getColor()==currentPlayer){
                        vector<array<int,2>> sequence = {{x,y},{x-2,y-2}};
                        if (board.isLegalJump(piece, sequence[0], sequence[1])) {
                            getMultiJumps(piece, sequence, all_moves);
                        }
                        sequence = {{x,y},{x+2,y-2}};
                        if (board.isLegalJump(piece, sequence[0], sequence[1])) {
                            getMultiJumps(piece, sequence, all_moves);
                        }
                    }
                    if ((piece->getType()==KING || piece->getColor()==DARK) && piece->getColor()==currentPlayer){
                        vector<array<int,2>> sequence = {{x,y},{x-2,y+2}};
                        if (board.isLegalJump(piece, sequence[0], sequence[1])) {
                            getMultiJumps(piece, sequence, all_moves);
                        }
                        sequence = {{x,y},{x+2,y+2}};
                        if (board.isLegalJump(piece, sequence[0], sequence[1])) {
                            getMultiJumps(piece, sequence, all_moves);
                        }
                    }
                }
            }
        }

        if (all_moves.empty()){  //no jump moves available
            for (int y = 0; y<8; y++) {
                for (int x = 0; x < 8; x++) {
                    Piece * piece =board.getPiece(x,y);
                    if (piece!=nullptr){
                        if ((piece->getType()==KING || piece->getColor()==LIGHT)&& piece->getColor()==currentPlayer){
                            vector<array<int,2>> sequence = {{x,y},{x-1,y-1}};
                            if (board.isLegalSlide(piece, sequence[0], sequence[1])) {
                                currentmove= Move(sequence);
                                all_moves.push_back(currentmove);
                            }
                            sequence = {{x,y},{x+1,y-1}};
                            if (board.isLegalSlide(piece, sequence[0], sequence[1])) {
                                currentmove= Move(sequence);
                                all_moves.push_back(currentmove);
                            }
                        }
                        if ((piece->getType()==KING || piece->getColor()==DARK)&& piece->getColor()==currentPlayer){
                            vector<array<int,2>> sequence = {{x,y},{x-1,y+1}};
                            if (board.isLegalSlide(piece, sequence[0], sequence[1])) {
                                currentmove= Move(sequence);
                                all_moves.push_back(currentmove);
                            }
                            sequence = {{x,y},{x+1,y+1}};
                            if (board.isLegalSlide(piece, sequence[0], sequence[1])) {
                                currentmove= Move(sequence);
                                all_moves.push_back(currentmove);
                            }
                        }
                    }
                }
            }
        }
        return all_moves;
    }

    void getMultiJumps(Piece * p, vector<array<int,2>> seed, vector<Move> &all_moves){

        Color c=p->getColor();
        Type t=p->getType();

        array<int,2> start=seed.back();
        array<int,2> finish;
        Move currentmove;

        if (t==KING || c==LIGHT){
            finish={start[0]-2, start[1]-2};
            if (board.isLegalJump(p,start,finish)){
                vector<array<int,2>> newseed = seed;
                newseed.push_back(finish);
                getMultiJumps(p,newseed, all_moves);
            }
            finish={start[0]+2, start[1]-2};
            if (board.isLegalJump(p,start,finish)){
                vector<array<int,2>> newseed = seed;
                newseed.push_back(finish);
                getMultiJumps(p, newseed, all_moves);
            }
            else{
                currentmove=Move(seed);
                all_moves.push_back(currentmove);
            }
        }

        if (t==KING || c==DARK){
            finish={start[0]-2, start[1]+2};
            if (board.isLegalJump(p,start,finish)){
                vector<array<int,2>> newseed = seed;
                newseed.push_back(finish);
                getMultiJumps(p, newseed, all_moves);
            }
            finish={start[0]+2, start[1]+2};
            if (board.isLegalJump(p,start,finish)){
                vector<array<int,2>> newseed = seed;
                newseed.push_back(finish);
                getMultiJumps(p, newseed, all_moves);
            }
            else{
                currentmove=Move(seed);
                all_moves.push_back(currentmove);
            }
        }
    }



    void doMove(Move m){
        playerMoved=(Color)(bool)!playerMoved;
        Piece * piece= board.getPiece(m.getFirst());
        array<int,2> start=m.getFirst(), finish=m.getNext();
        if (m.getLength()==2){
            if (board.isLegalSlide(piece, start,finish))
                board.movePiece(start,finish);
            else if (board.isLegalJump(piece, start,finish)) {
                board.removePiece({(finish[0]+start[0])/2,(finish[1]+start[1])/2});
                board.movePiece(start,finish);
            }
        }

        while (m.hasNext()){
            start=finish;
            finish=m.getNext();
            board.removePiece({(finish[0]+start[0])/2,(finish[1]+start[1])/2});
            board.movePiece(start,finish);
        }
    }

    int getResult(Color player){
        if (board.piecesRemaining((Color)(bool)player)==0) return 0;
        if (board.piecesRemaining((Color)(bool) !player)==0) return 1;
        else if (board.movesRemaining((Color)(bool) player)==0) return 0;
        else if (board.movesRemaining((Color)(bool)!player)==0) return 1;
        return 0;
    }
};

class TreeNode{

private:
    Move move; //move to get to this node
    TreeNode * parentNode; //parent to this node
    vector<TreeNode*> childNodes; //all children of this node
    State state; //the game state associated with this ndoe
    double wins; //wins at this node
    int visits; //visits to this node
    vector<Move> untriedMoves; //all moves that haven't been explored / future child nodes
    Color playerMoved; //the player that just moved.

public:
  /*  TreeNode();*/
    TreeNode(State state);
    TreeNode(Move move, TreeNode * parent, State state);
    ~TreeNode();

    State getState();
    vector<Move> getUntriedMoves();
    vector<TreeNode*> getChildNodes();
    Move getMove();
    TreeNode* getParentNode();
    Color getPlayerMoved();
    int getVisits();
    double getWins();

    static bool compareUCT (TreeNode * i,TreeNode * j);
    static double getUCTvalue(TreeNode * tn);
    TreeNode* UCTselectChild();
    TreeNode* addChild(Move move, State state);
    void Update(double result);
};

#endif //CHECKERS_TREENODE_H
