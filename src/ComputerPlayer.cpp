//
// Created by colin on 11/16/16.
//

#include "ComputerPlayer.h"


int MCTS_ITERATIONS=1;

ComputerPlayer::ComputerPlayer(GameBoard *b, Color color): Player(color){
    board=b;
}

bool ComputerPlayer::compareVisits(TreeNode *i, TreeNode *j) {
    return (i->getVisits()<j->getVisits());
}

Move ComputerPlayer::getMove() {

    State state = State(board, this->getColor());
    static TreeNode * rootNode=new TreeNode(state); //make the root node
    for (int i=0; i<MCTS_ITERATIONS; i++){ //repeat algorithm for the desired number of iterations
        TreeNode *node=rootNode; //copy the root
        State state=node->getState(); //clone the state of the root


//SELECT
        while (node->getUntriedMoves().empty() && !node->getChildNodes().empty()){ //node is fully expanded and non-terminal
                node = node->UCTselectChild();
                state.doMove(node->getMove());
        }


//EXPAND
        if (!node->getUntriedMoves().empty()){ // if we can expand (i.e. state/node is non-terminal)
            int rnd=randomInt(0, (int) node->getUntriedMoves().size()-1);
            Move randselection= node->getUntriedMoves().at(rnd);
            state.doMove(randselection);
            node=node->addChild(randselection, state); //add child and descend tree
        }

//ROLLOUT
        while (!state.getMoves().empty()){ //while state is non-terminal
            vector<Move> allmoves=state.getMoves();
            int rnd=randomInt(0, (int) allmoves.size()-1);
            Move randselection= allmoves.at(rnd);
            state.doMove(randselection);
        }

//BACKPROPAGATE
        while (node!=nullptr){ //backpropagate from the expanded node and work back to the root node
            node->Update(state.getResult(node->getPlayerMoved())); // state is terminal. Update node with result from POV of node.playerJustMoved
            node=node->getParentNode();
        }
    }
    sort(rootNode->getChildNodes().begin(),rootNode->getChildNodes().end(), compareVisits);
    Move move=rootNode->getChildNodes().back()->getMove(); //construct move array from node with the most number of visits


    delete rootNode;
    return move;
}

bool ComputerPlayer::isHuman() {
    return false;
}

int ComputerPlayer::randomInt(int first, int last) {
    unsigned int N = (last - first <= RAND_MAX) ? (last - first + 1U) : (RAND_MAX + 1U);
    unsigned int x = (RAND_MAX + 1U) / N;
    unsigned int y = x * N;
    unsigned int r;
    do {
        r = rand();
    } while (r >= y);
    return r / x + first;
}






