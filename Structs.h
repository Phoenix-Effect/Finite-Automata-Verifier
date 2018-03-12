//
// Created by Suhail Ghafoor on 3/11/18.
//

#ifndef CODE_STRUCTS_H
#define CODE_STRUCTS_H

#include <string>
#include <set>
#include <vector>

using namespace std;

struct DFA_node_tran;
struct DFA_node;

enum color{ white, grey, black};

struct Transition{
    string initialState;
    string alphabet;
    string nState;
    Transition(string inS, string alph, string nS ){
        initialState = inS;
        alphabet = alph;
        nState = nS;
    }
};

struct DFA_node_tran{
    string alphabet;
    DFA_node * point;
    DFA_node_tran(string t, DFA_node * p){
        this->alphabet = t;
        this->point = p;
    }
};

struct DFA_node{
    string name;
    vector<DFA_node_tran*> transition;
    bool initial;
    bool accepting;
    string shortestString;
    color col;
    DFA_node(string s){
        this->name = s;
        col = white;
        initial = false;
        accepting = false;
        shortestString = "Not yet traversed";
    }
};

struct NFA_Transition{
    set<string> initialStates;
    string alphabet;
    set<string> newStates;
};

struct DFA_Tuple{
    vector<set<string> > states;
    vector<string> alphabet;
    vector<NFA_Transition*> transitions;
    string initialState;
    vector<string> finStates;
};

#endif //CODE_STRUCTS_H
