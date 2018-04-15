/**
    CSE355 optional project, Structs.h
    Purpose: This header file contains all of the structs which are
    used in one or more classes. Having structs in a separate header
    makes it easier to include it in all classes without worrying about
    inter linking and also gives a brief overview of all the structs.

    @author Suhail Ghafoor
    @version 0.1 03/11/18
*/

#ifndef CODE_STRUCTS_H
#define CODE_STRUCTS_H

#include <string>
#include <set>
#include <vector>

using namespace std;

struct DFA_node_tran;
struct DFA_node;

/**
 * Color is used when traversing the DFA to distinguish
 * between untouched, processing and processed node.
 */
enum color{ white, grey, black};

/**
 * Transition struct used by the parser to keep the transition
 * neatly organized
 */
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

/**
 * A vector of this struct is kept by each node in the DFA
 * which tells it which alphabet leads to what node.
 */
struct DFA_node_tran{
    string alphabet;
    DFA_node * point;
    DFA_node_tran(string t, DFA_node * p){
        this->alphabet = t;
        this->point = p;
    }
};

/**
 * This struct is used by the DFA class to build a graph for
 * the given tuple and contains all the elements required to
 * traverse it and generate shortesting string.
 */
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

/**
 * Duplicate of transition? I forgot what i was using this for.
 */
struct NFA_Transition{
    set<string> initialStates;
    string alphabet;
    set<string> newStates;
};

/**
 * This struct is generated by the automaton class
 * and is used as in input in the DFA class
 */
struct DFA_Tuple{
    vector<set<string> > states;
    vector<string> alphabet;
    vector<NFA_Transition*> transitions;
    string initialState;
    vector<string> finStates;
};

struct Flat_transition{
    string initState;
    string alphabet;
    string nState;
};

struct DFA_flat_tuple{
    vector<string> states;
    vector<string> alphabet;
    vector<Flat_transition*> transitions;
    string initialState;
    vector<string> finStates;
};

#endif //CODE_STRUCTS_H
