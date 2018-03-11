//
// Created by Suhail Ghafoor on 3/9/18.
//

#include "Automaton.h"

//the constructor makes a DFA from the given parsed input
Automaton::Automaton(Parser *p) {
    this->parser = p;
    auto * dfa = new DFA_Tuple();
    this->dfa = dfa;
    this->fillStateNames();
    this->dfa->alphabet = parser->alphabet;
    this->dfa->initialState = this->parser->initialState;
    this->makeDFATuple();
}

//Makes a vector of state names
void Automaton::fillStateNames() {
    for(vector<int>::size_type i = 0; i != parser->transitions.size(); i++) {
        if(!(find(stateNames.begin(), stateNames.end(), parser->transitions[i]->initialState) != stateNames.end())){
            stateNames.push_back(parser->transitions[i]->initialState);
        }

        if(!(find(stateNames.begin(), stateNames.end(), parser->transitions[i]->nState) != stateNames.end())){
            stateNames.push_back(parser->transitions[i]->nState);
        }
    }
}

//Uses the information from the parser to make a dfa tuple
void Automaton::makeDFATuple() {

    //implementing Gallier's NFA to DFA pseudo code
    set<string> initialStateSet;
    initialStateSet.insert(parser->initialState);
    dfa->states.push_back(initialStateSet);

    int total = 1, marked = 0;

    while(marked < total){
        marked++;
        set<string> S = dfa->states.at(marked-1);
        for(vector<string>::size_type z = 0; z != this->dfa->alphabet.size(); z++) {
            set<string> U;
            set<string>::iterator s;

            for(s = S.begin(); s != S.end(); ++s) {
                string state = *s;
                set<string> nStates = stateAndAlphaToNewStates(state, this->dfa->alphabet[z]);
                U.insert(nStates.begin(), nStates.end());
            }
            if (!(isItAnElement(U))) {
                total++;
                this->dfa->states.push_back(U);
            }
            addTransitionsToDfa(S, this->dfa->alphabet[z], U);

        } //end for
    } //end while
}

string Automaton::printSet(set<string> s) {
    set <string> ::iterator itr;
    string ret = "";
    for(itr = s.begin(); itr != s.end(); itr++){
        ret += *itr;
    }

    return ret;
}

// this function returns a set of all states that can be reached
// from given state and alphabet
set<string> Automaton::stateAndAlphaToNewStates(string state, string alphabet) {
    set<string> trans;
    vector<Transition*> moretrans = this->parser->transitions;

    for(vector<Transition*>::size_type x = 0; x != moretrans.size(); x++){
        if(moretrans[x]->initialState == state && moretrans[x]->alphabet == alphabet){
            trans.insert(moretrans[x]->nState);
        }
    }
    return trans;
}

//Given a set a states, checks if its in the dfa's vector of states
bool Automaton::isItAnElement(set<string> U) {
    for(vector<set<string>>::size_type z = 0; z != this->dfa->states.size(); z++) {
        if(this->dfa->states[z] == U)
            return true;
    }
    return false;
}

//Adds new transitions to DFA
void Automaton::addTransitionsToDfa(set<string> intSet, string alphabet, set<string> newStates) {
    auto * nt = new NFA_Transition();
    nt->initialStates = intSet;
    nt->alphabet = alphabet;
    nt->newStates = newStates;
    this->dfa->transitions.push_back(nt);
}

//Prints the DFA
void Automaton::PrintDFA() {
    for(vector<NFA_Transition*>::size_type z = 0; z != this->dfa->transitions.size(); z++){
        cout << printSet(this->dfa->transitions[z]->initialStates);
        cout << " - " << this->dfa->transitions[z]->alphabet << " - ";
        cout << printSet(this->dfa->transitions[z]->newStates);
        cout << endl;
    }
}

//Updates the accepting states in the new dfa
void Automaton::updateAcceptingStates() {
    //TODO makes the
}