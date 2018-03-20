/**
    CSE355 optional project, DFA.h DFA.cpp
    Purpose: This class makes the actual DFA graph from the tuple. The graph
    is used to then generate the shortest string in the language.

    @author Suhail Ghafoor
    @version 0.1 03/11/18
*/

#include "DFA.h"

/**
 * Constructor that makes a graph from the tuple object
 * @param t - The tuple object
 */
DFA::DFA(DFA_Tuple *t) {
    this->tuple = t;
    makeGraph();
}

/**
 * Calls 5 functions each of which generate portion of the graph
 */
void DFA::makeGraph() {
    addStates();
    addTranisitions();
    setInitialStates();
    setFinalStates();
    makeShortestString();
}

/**
 * Takes in a set and returns a string representation of it. A little different
 * from printset since this allows the program to add extra hashing to the string
 * to make sure there is no conflict between 2 different DFAs.
 * @param S - Set of states
 * @return String representing the set
 */
string DFA::setToString(set<string> S) {
    string ret = "";
    set<string>::iterator s;

    for(s = S.begin(); s != S.end(); ++s) {
        ret += *s;
        ret += "#";
    }
    return ret;
}

/**
 * Traverses the graph using BFS and assigns a shortest string value
 * to each node which is the shortest string required to reach that node
 * from the initial state.
 */
void DFA::makeShortestString() {

    queue <DFA_node*> queue;
    DFA_node * initialNode;
    DFA_node * processNode;

    //Finds the initial node and sets it to grey and pushes it in the queue
    for(vector<DFA_node*>::size_type x = 0; x != this->states.size(); x++){
        if(this->states[x]->initial){
            initialNode = this->states[x];
        }
    }
    initialNode->col = grey;
    initialNode->shortestString = "";
    queue.push(initialNode);

    //Adds unprocessed nodes to the queue and keeps on processing until queue runs out
    while(!(queue.empty())){
        processNode = queue.front();
        queue.pop();
        processNode->col = black;

        //Pushes the shortest string of current node plus the transition alphabet to the
        //shortest string of the next node.
        for(vector<DFA_node_tran*>::size_type z = 0; z != processNode->transition.size(); z++){
            if(processNode->transition[z]->point->col == white){
                string nShortestString = processNode->shortestString;
                nShortestString += processNode->transition[z]->alphabet;
                queue.push(processNode->transition[z]->point);
                processNode->transition[z]->point->col = grey;
                processNode->transition[z]->point->shortestString = nShortestString;
            }
        }
    }
}

/**
 * This function makes sure all of the states have all of the transition functions
 */
void DFA::addTranisitions() {

    //Next add the transition function to all states
    for(vector<NFA_Transition*>::size_type x = 0; x != this->tuple->transitions.size(); x++){
        string inState = setToString(this->tuple->transitions[x]->initialStates);
        string nState = setToString(this->tuple->transitions[x]->newStates);
        DFA_node * point = nullptr;
        DFA_node * addingPoint = nullptr;

        for(vector<DFA_node*>::size_type y = 0; y != this->states.size(); y++){
            if(this->states[y]->name == nState){
                point = this->states[y];
            }

            if(this->states[y]->name == inState){
                addingPoint = this->states[y];
            }
        }

        DFA_node_tran * trans = new DFA_node_tran(this->tuple->transitions[x]->alphabet, point);
        addingPoint->transition.push_back(trans);
    }
}

/**
 * Adds all of the states to the vector that contains all nodes
 */
void DFA::addStates() {
    //First make all states and put them in a vector so they're accessible
    for(vector<set<string>>::size_type z = 0; z != this->tuple->states.size(); z++){
        string name = setToString(this->tuple->states[z]);
        DFA_node * node = new DFA_node(name);
        states.push_back(node);
    }
}

/**
 * Sets one of the nodes to initial in the vector
 */
void DFA::setInitialStates() {
    //assign initial states and accepting states
    set<string> initialStateSet;
    initialStateSet.insert(this->tuple->initialState);
    string initialStateString = setToString(initialStateSet);

    for(vector<DFA_node*>::size_type h = 0; h != this->states.size(); h++){
        if(this->states[h]->name == initialStateString){
            this->states[h]->initial = true;
        }
    }
}

/**
 * If a state was not final in the input then sets it to final and vice versa
 * since the program generates the compliment of given machine
 */
void DFA::setFinalStates() {
    for(vector<set<string>>::size_type y = 0; y != this->tuple->states.size(); y++){
        set<string>::iterator s;
        set<string> S = this->tuple->states[y];
        bool isThisSetFinal = true;

        for(s = S.begin(); s != S.end(); ++s){
            for(vector<string>::size_type x = 0; x != this->tuple->finStates.size(); x++){
                if(*s == this->tuple->finStates[x]){
                    isThisSetFinal = false;
                }
            }
        }

        if(isThisSetFinal){
            string makeItFinal = setToString(S);
            for(vector<DFA_node*>::size_type y = 0; y != this->states.size(); y++){
                if(this->states[y]->name == makeItFinal){
                    this->states[y]->accepting = true;
                }
            }
        }
    }
}

/**
 * Finds the shortest string in the given DFA graph.
 * @return The shortest string
 */
string DFA::giveShortestString() {
    vector<string> shortestStrings;

    for(vector<DFA_node*>::size_type x = 0; x != this->states.size(); x++){
        if(this->states[x]->accepting){
            shortestStrings.push_back(this->states[x]->shortestString);
        }
    }

    if(shortestStrings.empty()){
        return "No acceptable string in language";
    }
    string shortestString = shortestStrings.at(0);
    for(vector<string>::size_type z = 0; z != shortestStrings.size(); z++){
        if(shortestStrings[z].length() < shortestString.length()){
            shortestString = shortestStrings[z];
        }
    }

    return shortestString;
}