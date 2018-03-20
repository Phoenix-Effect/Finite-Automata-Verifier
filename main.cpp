/**
    CSE355 optional project, main.cpp
    Purpose: Takes an automaton from an input file and converts it to a DFA
    if its an NFA then generates a compliment of that new DFA and finds the
    shortest string in the new DFA.

    @author Suhail Ghafoor
    @version 0.1 03/06/18
*/
#include <iostream>
#include <fstream>
#include "Parser.h"
#include "Automaton.h"

using namespace std;
void readLines(Parser * p);

/*
 *  Config box begin, change settings here.
 */

// I/O
bool outputDFAToFile = true;
bool outputShortestStringToFile = true;
bool takeInputFromFile = false;
string inputFilePath = "/Users/Suhail/Documents/University/CSE355/Optional Project/Code/document.txt";

// Other settings
bool printEpsilonInsteadOfEmptyString = true;
bool printStateSets = true;
string deadStateName = "Dead-State";

/*
 *  Config box end
 */

int main() {

    ifstream in(inputFilePath);

    if(takeInputFromFile) {
        cin.rdbuf(in.rdbuf());
    }

    auto * parser = new Parser();
    readLines(parser);

    auto * fa = new Automaton(parser, deadStateName, printEpsilonInsteadOfEmptyString);

    //Print shortest string to screen and then to file
    cout << "Shortest string: ";
    fa->shortestString();

    //Change output buffer to file to print the new dfa
    if(outputDFAToFile){
        freopen("1210107207_Milestone1_Dp.txt","w",stdout);
    }
    fa->PrintDFA("% Specification automaton", printStateSets);


    if(outputShortestStringToFile){
        freopen("1210107207_Milestone1_str.txt","w",stdout);
        cout << "Shortest string: ";
        fa->shortestString();
    }

    return 0;
}

//This function reads the input line by line and hands each line to
// gives them to the parser object
void readLines(Parser * p){
    string line;
    int type = -1;

    while (getline(cin, line)) {
        if(line.empty()) break;
        if(line.find("Input alphabet") != string::npos){
            type = 0;
        } else if(line.find("Specification automaton") != string::npos){
            type = -1;
        } else if(line.find("Transition function") != string::npos){
            type = 1;
        } else if(line.find("Initial state") != string::npos){
            type = 2;
        } else if(line.find("Final states") != string::npos){
            type = 3;
        } else{
            switch(type){
                case 0:
                    p->addAlphabet(line);
                    break;
                case 1:
                    p->addTransitions(line);
                    break;
                case 2:
                    p->setInitial(line);
                    break;
                case 3:
                    p->addFinalStates(line);
                    break;
                default:
                    ;
            }
        }
    }
}