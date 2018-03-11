//
// Created by Suhail Ghafoor on 3/8/18.
//

#include "Parser.h"

Parser::Parser() = default;

void Parser::addAlphabet(string line) {
    line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
    alphabet.push_back(line);
}

void Parser::addTransitions(string line) {
    string initialState = line.substr(0,line.find_first_of(' '));
    string alphabet = line.substr(line.find_first_of(' '), line.find_last_of(' '));
    string nState = line.substr(line.find_last_of(' '), line.length()-1);
    Transition * trans = new Transition(initialState, alphabet, nState);
    cleanTransition(trans);
    transitions.push_back(trans);
}

void Parser::setInitial(string line) {
    line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
    initialState = line;
}

void Parser::addFinalStates(string line) {
    line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
    finalStates.push_back(line);
}

void Parser::cleanTransition(Transition *t) {
    t->initialState.erase(remove_if(t->initialState.begin(), t->initialState.end(), ::isspace), t->initialState.end());
    t->alphabet.erase(remove_if(t->alphabet.begin(), t->alphabet.end(), ::isspace), t->alphabet.end());
    t->nState.erase(remove_if(t->nState.begin(), t->nState.end(), ::isspace), t->nState.end());
}