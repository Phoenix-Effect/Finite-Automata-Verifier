/**
    CSE355 optional project, Intersected.h Intersected.cpp
    Purpose: To generate an intersection of two tuples.

    @author Suhail Ghafoor
    @version 0.1 04/04/18
*/

#ifndef CODE_INTERSECTOR_H
#define CODE_INTERSECTOR_H

#include "Structs.h"
#include <algorithm>

class Intersector {
private:
    DFA_flat_tuple * spec;
    DFA_flat_tuple * system;
    DFA_flat_tuple * intersected;
    vector<string> niceNames;
    string findTransition(string state, string alpha, vector<Flat_transition*> ft);
    void makeCompliment();
    void makeIntersection();
    void encodeStateNames();
    void nicefyNames();
    int giveStateNum(string name);

public:
    DFA_flat_tuple * giveIntersected();
    Intersector(DFA_flat_tuple * spec, DFA_flat_tuple * system, bool nicefy);
};


#endif //CODE_INTERSECTOR_H