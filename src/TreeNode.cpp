//
// Created by colin on 11/16/16.
//

/**
 * A node in the game tree. Note wins is always from the viewpoint of playerJustMoved.
**/



#include "TreeNode.h"



/*TreeNode::TreeNode() {
    this->move=Move();
    this->parentNode=nullptr;
    this->state=State();
    this->wins=0.0;
    this->visits=0;
    this->playerMoved=this->state.playerMoved;
    this->untriedMoves=this->state.getMoves();
    this->childNodes= vector<TreeNode*>();
}*/


//this is called for the root node
TreeNode::TreeNode(State s): state(s), move(Move()), parentNode(nullptr), wins(0.0), visits(0){
    playerMoved=s.playerMoved;
    untriedMoves=s.getMoves();
    childNodes={};


}

//this is called for a regular child node
TreeNode::TreeNode(Move move, TreeNode *parent, State s): move(move), parentNode(parent), state(s), wins(0.0), visits(0) {
    playerMoved=state.playerMoved;
    untriedMoves=state.getMoves();
    childNodes={};
}

TreeNode::~TreeNode() {
    for (TreeNode* tn: childNodes){
        delete tn;
    }
    delete parentNode;
}

//get the "value" of a particular node using the UCT formula
double TreeNode::getUCTvalue(TreeNode *tn) {
    return tn->wins/tn->visits + sqrt((2*log((tn->getParentNode()->getVisits())/tn->visits)));
}

bool TreeNode::compareUCT(TreeNode *i, TreeNode *j) {
    return (getUCTvalue(i)<getUCTvalue(j));
}

//select the optimal child node by their value using UCT.
TreeNode* TreeNode::UCTselectChild() {
    sort(childNodes.begin(),childNodes.end(), compareUCT);
    return childNodes.back();
}

/**
  * Add a child node to this node
 **/

TreeNode *TreeNode::addChild(Move move, State state) {
    TreeNode * node= new TreeNode(move, this, state);
    for( std::vector<Move>::iterator iter = untriedMoves.begin(); iter != untriedMoves.end(); ++iter ) {
        if( (*iter).getSequence() == move.getSequence()) {
            untriedMoves.erase(iter);
            break;
        }
    }
    this->childNodes.push_back(node);
    return node;
}


/**
 * during backpropagation, you update the node by adding another visit, and then adding the propagated result to the win total.
**/

void TreeNode::Update(double result) {
    this->visits+=1;
    this->wins+=result;
}

State TreeNode::getState() {
    return state;
}

vector<Move> TreeNode::getUntriedMoves() {
    return untriedMoves;
}

vector<TreeNode *> TreeNode::getChildNodes() {
    return childNodes;
}

Move TreeNode::getMove() {
    return move;
}

TreeNode *TreeNode::getParentNode() {
    return parentNode;
}

Color TreeNode::getPlayerMoved() {
    return playerMoved;
}

int TreeNode::getVisits() {
    return visits;
}

double TreeNode::getWins() {
    return wins;
}

