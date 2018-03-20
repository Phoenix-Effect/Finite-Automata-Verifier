/**
    CSE355 optional project, Parser.h Parser.cpp
    Purpose: To store all the input in memory so when the program is
    making an NFA/DFA it knows all of the transitions, alphabets and states
    before hand which makes it easier to generate the new machine.

    @author Suhail Ghafoor
    @version 0.1 03/08/18
*/

#include "Parser.h"

/**
 *  Default constructor since parser doesn't have any variables
 */
Parser::Parser() = default;

/**
 * Adds alphabet to parser
 * @param line - The input line that contains alphabet
 */
void Parser::addAlphabet(string line) {
    line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
    alphabet.push_back(line);
}

/**
 * Store transition from input file
 * @param line - The input line that contains a transition. This line
 * is turned into a struct of type transition.
 */
void Parser::addTransitions(string line) {
    string initialState = line.substr(0,line.find_first_of(' '));
    string alphabet = line.substr(line.find_first_of(' '), line.find_last_of(' '));
    string nState = line.substr(line.find_last_of(' '), line.length()-1);
    Transition * trans = new Transition(initialState, alphabet, nState);
    cleanTransition(trans);
    transitions.push_back(trans);
}

/**
 * Sets the initial state
 * @param line - Line containing the name of the initial state
 */
void Parser::setInitial(string line) {
    line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
    initialState = line;
}

/**
 * Add all the final states to the parser object
 * @param line - Line that contains the name of final states
 */
void Parser::addFinalStates(string line) {
    line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
    finalStates.push_back(line);
}

/**
 * Makes sure the transition object values do not contain any spaces
 * @param t - The transition object to clean
 */
void Parser::cleanTransition(Transition *t) {
    t->initialState.erase(remove_if(t->initialState.begin(), t->initialState.end(), ::isspace), t->initialState.end());
    t->alphabet.erase(remove_if(t->alphabet.begin(), t->alphabet.end(), ::isspace), t->alphabet.end());
    t->nState.erase(remove_if(t->nState.begin(), t->nState.end(), ::isspace), t->nState.end());
}