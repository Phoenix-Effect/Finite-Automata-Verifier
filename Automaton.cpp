/**
    CSE355 optional project, Automaton.h Automaton.cpp
    Purpose: This class makes a tuple from the parser which is the parsed
    input. It also takes care of converting NFA to DFA if required and
    has all the print functions. It is the core of the program

    @author Suhail Ghafoor
    @version 0.1 03/09/18
*/

#include "Automaton.h"

/**
 * This constructor calls all the other methods after construction which
 * generate the tuple.
 * @param p - The parser object containing the input
 * @param s - Name of the dead state if it needs to be added
 * @param b - Boolean value that enables or disables printing of epsilon
 * in place of an empty string which is hard to read
 */
Automaton::Automaton(Parser *p, string s, bool b) {
    this->deadStateName = s;
    this->printEpsilon = b;
    this->parser = p;
    auto * dfa = new DFA_Tuple();
    this->dfa = dfa;
    this->fillStateNames();
    this->dfa->alphabet = parser->alphabet;
    this->dfa->initialState = this->parser->initialState;
    this->dfa->finStates = this->parser->finalStates;
    this->makeDFATuple();
}

/**
 * This function fills the stateName vector with all statenames from
 * the transitions.
 */
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

/**
 * Uses the information from the parser to make a tuple of the DFA
 */
void Automaton::makeDFATuple() {

    //Implementing Gallier's NFA to DFA pseudo code
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

            //This is an extra addition for c++, if there are no outgoing transitions
            //from current state with given alphabet then generate a dead state. This
            //also takes care of self loop on the dead state
            if(U.empty()){
                U.insert(this->deadStateName);
            }

            if (!(isItAnElement(U))) {
                total++;
                this->dfa->states.push_back(U);
            }
            addTransitionsToDfa(S, this->dfa->alphabet[z], U);

        } //end for
    } //end while
}

/**
 * This function takes in a set and returns a string representation of that set.
 * @param s - Set of strings to be printed
 * @return String representing the set
 */
string Automaton::printSet(set<string> s) {
    set <string> ::iterator itr;
    string ret = "{";
    for(itr = s.begin(); itr != s.end(); itr++){
        ret += *itr;
        ret += ",";
    }
    ret.pop_back();
    ret += "}";
    return ret;
}

/**
 * This function takes in a name of a state and an alphabet and returns a set of all
 * the states that can be reached using the given alphabet.
 * @param state - Name of the state
 * @param alphabet - The transition alphabet
 * @return - Set of all states that can be reached from given state and alphabet
 */
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

/**
 * Function which checks if the given set of states is already a state in the
 * DFA tuple or not
 * @param U - Set of states
 * @return
 */
bool Automaton::isItAnElement(set<string> U) {
    for(vector<set<string>>::size_type z = 0; z != this->dfa->states.size(); z++) {
        if(this->dfa->states[z] == U)
            return true;
    }
    return false;
}

/**
 * Adds transitions to the new DFA tuple. Everything is kept as sets so doing future
 * computations is easier
 * @param intSet - Set of initial states.
 * @param alphabet - Transition alphabet
 * @param newStates - New state that can be reached using the alphabet
 */
void Automaton::addTransitionsToDfa(set<string> intSet, string alphabet, set<string> newStates) {
    auto * nt = new NFA_Transition();
    nt->initialStates = intSet;
    nt->alphabet = alphabet;
    nt->newStates = newStates;
    this->dfa->transitions.push_back(nt);
}

/**
 * Simple function that prints out the DFA. A boolean value can be used to change
 * whether it should print set of states as output or if it should just print the name
 * of the state. This is useful for NFA to DFA converted states.
 * @param s - Name of the DFA (e.g. specification DFA)
 * @param b - Boolean value that determines print type
 */
void Automaton::PrintDFA(string s, bool b) {
    cout << "% Input alphabet" << endl;
    for(vector<string>::size_type h = 0; h != this->dfa->alphabet.size(); h++){
        cout << this->dfa->alphabet[h] << endl;
    }

    cout << s << endl;
    cout << "% Transition function" << endl;
    for(vector<NFA_Transition*>::size_type z = 0; z != this->dfa->transitions.size(); z++){
        cout << nicePrint(this->dfa->transitions[z]->initialStates, b);
        cout << " " << this->dfa->transitions[z]->alphabet << " ";
        cout << nicePrint(this->dfa->transitions[z]->newStates, b);
        cout << endl;
    }

    cout << "% Initial state" << endl << this->dfa->initialState << endl;
    cout << "% Final states" << endl;
    printFinalStates(b);
}

/**
 * Prints compliment of final states
 * @param b - Boolean value that determines printing of states vs set of states
 */
void Automaton::printFinalStates(bool b) {
    bool toPrint;
    for(vector<set<string>>::size_type z = 0; z != this->dfa->states.size(); z++){
        toPrint = true;
        set <string> ::iterator itr;
        for(itr = this->dfa->states[z].begin(); itr != this->dfa->states[z].end(); itr++){
            for(vector<string>::size_type x = 0; x != this->dfa->finStates.size(); x++){
                if(*itr == this->dfa->finStates[x]){
                    toPrint = false;
                }
            }
        }

        if(toPrint){
            cout << nicePrint(this->dfa->states[z], b) << endl;
        }
    }
}

/**
 * Prints the shortest string in the given DFA. The computation is done in the DFA class
 * but this function prints it and decides what the epsilon should print
 */
void Automaton::shortestString() {
    auto graph = new DFA(dfa);
    string shortString = graph->giveShortestString();
    if(shortString.length() == 0 && this->printEpsilon)
        shortString = "epsilon";
    cout << shortString << endl;
}

/**
 * This function assigns a nicer looking name to each set of state and thus complies
 * with the input file since the input file assumes that each state can be stored in
 * type char.
 * @param s - Set of states that require a nicer name
 * @param b - Boolean to determine if they require a nice name or set name
 * @return A string that represents name of state.
 */
string Automaton::nicePrint(set<string> s, bool b) {
    long index;
    if(b){
        return printSet(s);
    } else {
        string toString = printSet(s);
        auto it = std::find(niceSetNames.begin(), niceSetNames.end(), toString);
        if (it == niceSetNames.end()){
            niceSetNames.push_back(toString);
            auto foundIt = std::find(niceSetNames.begin(), niceSetNames.end(), toString);
            index = std::distance(niceSetNames.begin(), foundIt);
        } else{
            index = std::distance(niceSetNames.begin(), it);
        }

        stringstream mystream;
        mystream << index;
        string retValue = mystream.str();
        return retValue;
    }
}