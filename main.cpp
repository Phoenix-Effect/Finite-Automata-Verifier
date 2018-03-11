#include <iostream>
#include <fstream>
#include "Parser.h"
#include "Automaton.h"

using namespace std;

void readLines(Parser * p);

int main() {

    //TODO: Change input buffer before submitting
    ifstream in("/Users/Suhail/Documents/University/CSE355/Optional Project/project files/exmp01_M1.txt");
    cin.rdbuf(in.rdbuf());

    auto * parser = new Parser();
    readLines(parser);

    auto * fa = new Automaton(parser);
    fa->PrintDFA();

    cout << "Done" << endl;
    return 0;
}

void readLines(Parser * p){
    string line;
    int type = -1;

    //read line by line until empty line
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