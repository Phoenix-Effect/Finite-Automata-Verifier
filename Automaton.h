//
// Created by Suhail Ghafoor on 3/9/18.
//

#ifndef CODE_AUTOMATON_H
#define CODE_AUTOMATON_H

#include "DFA.h"
#include "Parser.h"
#include "Structs.h"
#include <algorithm>
#include <set>
#include <iostream>
#include <iterator>

using namespace std;

class Automaton {
private:
    vector<string> stateNames;
    Parser * parser;
    void fillStateNames();
    DFA_Tuple * dfa;
    void makeDFATuple();
    string printSet(set<string> s);
    set<string> stateAndAlphaToNewStates(string state, string alphabet);
    bool isItAnElement(set<string> U);
    void addTransitionsToDfa(set<string> intSet, string alphabet, set<string> newStates);
    void printFinalStates();

public:
    Automaton(Parser * p);
    void PrintDFA(string s);
    void shortestString();
};


#endif //CODE_AUTOMATON_H
