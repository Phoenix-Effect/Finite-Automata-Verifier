//
// Created by Suhail Ghafoor on 3/8/18.
//

#ifndef CODE_PARSER_H
#define CODE_PARSER_H

#include <iostream>
#include <vector>

using namespace std;

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
