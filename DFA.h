//
// Created by Suhail Ghafoor on 3/11/18.
//

#ifndef CODE_DFA_H
#define CODE_DFA_H

#include "Automaton.h"
#include "Structs.h"
#include <queue>

class DFA {
private:
    DFA_Tuple * tuple;
    void makeGraph();
    string setToString(set<string> S);
    vector<DFA_node*> states;
    void addTranisitions();
    void addStates();
    void setInitialStates();
    void setFinalStates();
    void makeShortestString();

public:
    DFA(DFA_Tuple * t);
    string giveShortestString();

};


#endif //CODE_DFA_H
