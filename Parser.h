/**
    CSE355 optional project, Parser.h Parser.cpp
    Purpose: To store all the input in memory so when the program is
    making an NFA/DFA it knows all of the transitions, alphabets and states
    before hand which makes it easier to generate the new machine.

    @author Suhail Ghafoor
    @version 0.1 03/08/18
*/

#ifndef CODE_PARSER_H
#define CODE_PARSER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Structs.h"

using namespace std;

class Parser {
private:
    void cleanTransition(Transition * t);

public:
    Parser();
    vector<string> alphabet;
    vector<Transition*> transitions;
    string initialState;
    vector<string> finalStates;
    void addAlphabet(string line);
    void addTransitions(string line);
    void setInitial(string line);
    void addFinalStates(string line);
};

#endif //CODE_PARSER_H
