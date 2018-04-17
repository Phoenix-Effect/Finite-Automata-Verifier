/**
    CSE355 optional project, Intersected.h Intersected.cpp
    Purpose: To generate an intersection of two tuples.

    @author Suhail Ghafoor
    @version 0.1 04/04/18
*/

#include "Intersector.h"


Intersector::Intersector(DFA_flat_tuple *spec, DFA_flat_tuple *system, bool nicefy) {
    this->spec = spec;
    this->system = system;
    intersected = new DFA_flat_tuple();
    makeCompliment();
    encodeStateNames();
    makeIntersection();
    if(nicefy){
        nicefyNames();
    }
}

void Intersector::makeCompliment() {
    vector<string> nFinStates;
    for(vector<string>::size_type z = 0; z != this->spec->states.size(); z++){
        if(find(this->spec->finStates.begin(), this->spec->finStates.end(), this->spec->states[z]) != this->spec->finStates.end()) {
            /* v contains x */
        } else {
            nFinStates.push_back(this->spec->states[z]);
        }
    }
    this->spec->finStates = nFinStates;
}

void Intersector::makeIntersection() {

    //intersect states
    for(vector<string>::size_type z = 0; z != this->spec->states.size(); z++){
        for(vector<string>::size_type x = 0; x != this->system->states.size(); x++){
            string intersectedStateName = this->spec->states[z] + this->system->states[x];
            intersected->states.push_back(intersectedStateName);
        }
    }

    //add alphabets
    intersected->alphabet = this->spec->alphabet;

    //initial state
    string intersectedInitialState = this->spec->initialState + this->system->initialState;
    intersected->initialState = intersectedInitialState;

    //final states
    for(vector<string>::size_type z = 0; z != this->spec->finStates.size(); z++){
        for(vector<string>::size_type x = 0; x != this->system->finStates.size(); x++){
            string intersectedFinState = this->spec->finStates[z] + this->system->finStates[x];
            intersected->finStates.push_back(intersectedFinState);
        }
    }

    //intersectioned transitions
    for(vector<string>::size_type z = 0; z != this->spec->states.size(); z++){
        for(vector<string>::size_type x = 0; x != this->system->states.size(); x++){
            for(vector<string>::size_type y = 0; y != this->spec->alphabet.size(); y ++){
                string nStateSpec = findTransition(this->spec->states[z], this->spec->alphabet[y], this->spec->transitions);
                string nStateSys = findTransition(this->system->states[x], this->spec->alphabet[y], this->system->transitions);

                auto * trans = new Flat_transition();
                trans->initState = this->spec->states[z] + this->system->states[x];
                trans->alphabet = this->spec->alphabet[y];
                trans->nState = nStateSpec + nStateSys;
                intersected->transitions.push_back(trans);
            }
        }
    }

    //all done

}

void Intersector::encodeStateNames() {
    string specMachine = "SP#";
    string sysMachine = "#SYS";

    for(vector<string>::size_type z = 0; z != this->spec->states.size(); z++){
        this->spec->states[z] += specMachine;
    }

    for(vector<string>::size_type z = 0; z != this->spec->finStates.size(); z++){
        this->spec->finStates[z] += specMachine;
    }

    for(vector<Flat_transition*>::size_type z = 0; z != this->spec->transitions.size(); z++){
        this->spec->transitions[z]->initState += specMachine;
        this->spec->transitions[z]->nState += specMachine;
    }
    this->spec->initialState += specMachine;



    for(vector<string>::size_type z = 0; z != this->system->states.size(); z++){
        this->system->states[z].insert(0, sysMachine);
    }

    for(vector<string>::size_type z = 0; z != this->system->finStates.size(); z++){
        this->system->finStates[z].insert(0, sysMachine);
    }

    for(vector<Flat_transition*>::size_type z = 0; z != this->system->transitions.size(); z++){
        this->system->transitions[z]->initState.insert(0, sysMachine);
        this->system->transitions[z]->nState.insert(0, sysMachine);
    }

    this->system->initialState.insert(0, sysMachine);

}

string Intersector::findTransition(string state, string alpha, vector<Flat_transition*> ft){
    for(vector<Flat_transition*>::size_type z = 0; z != ft.size(); z++){
        if(ft[z]->initState == state && ft[z]->alphabet == alpha){
            return ft[z]->nState;
        }
    }

    return "ERRORDUDE";
}

DFA_flat_tuple * Intersector::giveIntersected() {
    return intersected;
}

void Intersector::nicefyNames() {
     for(vector<string>::size_type z = 0; z != intersected->states.size(); z++){
         intersected->states[z] = to_string(giveStateNum(intersected->states[z]));
     }

     for(vector<Flat_transition*>::size_type z = 0; z != intersected->transitions.size(); z++){
         intersected->transitions[z]->initState = to_string(giveStateNum(intersected->transitions[z]->initState));
         intersected->transitions[z]->nState = to_string(giveStateNum(intersected->transitions[z]->nState));
     }

     for(vector<string>::size_type z = 0; z != intersected->finStates.size(); z++){
         intersected->finStates[z] = to_string(giveStateNum(intersected->finStates[z]));
     }

     intersected->initialState = to_string(giveStateNum(intersected->initialState));
}

int Intersector::giveStateNum(string name) {
    if(find(niceNames.begin(), niceNames.end(), name) != niceNames.end()) {
    } else {
        niceNames.push_back(name);
    }
    auto pos = std::distance(niceNames.begin(), find(niceNames.begin(), niceNames.end(), name));
    return (int)pos;
}