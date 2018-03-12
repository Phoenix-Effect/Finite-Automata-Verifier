//
// Created by Suhail Ghafoor on 3/8/18.
//

#ifndef CODE_PARSER_H
#define CODE_PARSER_H

#include <iostream>
#include <vector>
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
