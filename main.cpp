/**
    CSE355 optional project, main.cpp
    Purpose: Takes an automaton from an input file and converts it to a DFA
    if its an NFA then generates a compliment of that new DFA and finds the
    shortest string in the new DFA.

    @author Suhail Ghafoor
    @version 0.2 04/04/18
*/
#include <iostream>
#include <fstream>
#include "Parser.h"
#include "Automaton.h"
#include "Intersector.h"
#include "helper.h"

using namespace std;

/*
 *  Config box begin, change settings here.
 */

// I/O
bool takeInputFromFile = true;
string inputFilePath = "/Users/Suhail/Documents/University/CSE355/Optional Project/project files/m3test.txt";

// Other settings
bool printEpsilonInsteadOfEmptyString = true;
bool nicefyNames = true;
string deadStateName = "Dead-State";

/*
 *  Config box end
 */

int main() {

    ifstream in(inputFilePath);

    if(takeInputFromFile) {
        cin.rdbuf(in.rdbuf());
    }

    //make parser for both specifications so we can read it from input
    auto * specificationAutomaton = new Parser();
    auto * systemAutomaton = new Parser();

    //fills up parser from given input file
    readLines(specificationAutomaton, systemAutomaton);

    //this class turns NFA to DFA if required and also a tuple which
    // is used by the graph
    auto * specification = new Automaton(specificationAutomaton, deadStateName, printEpsilonInsteadOfEmptyString);
    auto * system = new Automaton(systemAutomaton, deadStateName, printEpsilonInsteadOfEmptyString);

    //get tuple from specifications
    auto * specTuple = specification->giveTuple();
    auto * systemTuple = system->giveTuple();

    //print the specs and system to a js file before it is altered by the intersector
    jsonPrint(specTuple, "specNormal.js");
    jsonPrint(systemTuple, "system.js");

    //make the new intersected dfa and find the shortest string
    auto * intersected = new Intersector(specTuple, systemTuple, nicefyNames);
    auto * dfa = new DFA(intersected->giveIntersected());
    string shortest = dfa->giveShortestString();

    //print the new specs and the intersected tuple to a file
    jsonPrint(specTuple, "specs.js");
    jsonPrint(intersected->giveIntersected(), "intersected.js");

    //output to console
    if(shortest.empty() || shortest == "Not yet traversed"){
        cout << "The system satisfies the specification!";
    } else{
        cout << "The system does not satisfy the specification!" << endl;
        cout << "The counterexample that demonstrates that the specification does not hold is: " << shortest;
    }

    freopen("1210107207_Milestone2_str.txt","w",stdout);
    cout << "Shortest string: ";
    cout << shortest;

    freopen("1210107207_Milestone2_M.txt","w",stdout);
    printMachine(intersected->giveIntersected());

    return 0;
}



