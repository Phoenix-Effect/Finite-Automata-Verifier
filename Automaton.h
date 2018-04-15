/**
    CSE355 optional project, Automaton.h Automaton.cpp
    Purpose: This class makes a tuple from the parser which is the parsed
    input. It also takes care of converting NFA to DFA if required and
    has all the print functions. It is the core of the program

    @author Suhail Ghafoor
    @version 0.1 03/09/18
*/

#ifndef CODE_AUTOMATON_H
#define CODE_AUTOMATON_H

#include "DFA.h"
#include "Parser.h"
#include "Structs.h"
#include <algorithm>
#include <set>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>

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
    void printFinalStates(bool b);
    string deadStateName;
    bool printEpsilon;
    string nicePrint(set<string> s, bool b);
    vector<string> niceSetNames;
    string setToString(set<string> s);

public:
    Automaton(Parser *p, string s, bool b);
    void PrintDFA(string s, bool b);
    DFA_flat_tuple * giveTuple();
};


#endif //CODE_AUTOMATON_H
